/* kvm api
* see https://www.kernel.org/doc/Documentation/virtual/kvm/api.txt
*/
#include <fcntl.h>
#include <linux/kvm.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <unistd.h>

#include "vm.h"
#include "bits.h"

/* set rip = entry point
 * set rsp = MAX_KERNEL_SIZE + KERNEL_STACK_SIZE (the max address can be used)
 *
 * set rdi = PS_LIMIT (start of free (unpaging) physical pages)
 * set rsi = MEM_SIZE - rdi (total length of free pages)
 * Kernel could use rdi and rsi to initalize its memory allocator.
 */
void setup_regs(vm *vm, size_t entry)
{
	struct kvm_regs regs;
	if (ioctl(vm->vcpufd, KVM_GET_REGS, &regs) < 0 )
		pexit("ioctl(KVM_GET_REGS)");
	
	regs.rip = entry;
	regs.rsp = MAX_KERNEL_SIZE + KERNEL_STACK_SIZE;	
	regs.rdi = PS_LIMIT; //(start of free (unpaging) physical pages)
	regs.rsi = MEM_SIZE - regs.rdi;
	regs.rflags = 0x2;

	if (ioctl(vm->vcpufd, KVM_SET_REGS, &regs) < 0)
		pexit("ioctl(KVM_SET_REGS)");
}

/* Maps:
 * 0 ~ 0x200000 -> 0 ~ 0x200000 with kernel privilege
 */
void setup_paging(vm *vm)
{
	struct kvm_sregs sregs;
	if( ioctl(vm->vcpufd, KVM_GET_SREGS, &sregs) < 0 )
		pexit("ioctl(KVM_GET_SREGS)");

	uint64_t pml4_addr = MAX_KERNEL_SIZE;
	uint64_t *pml4 = (void *)(vm->mem + pml4_addr);

	uint64_t pdp_addr = pml4_addr + 0x1000;
	uint64_t *pdp = (void *)(vm->mem + pdp_addr);

	uint64_t pd_addr = pdp_addr + 0x1000;
	uint64_t *pd = (void *)(vm->mem + pd_addr);

	pml4[0] = PDE64_PRESENT | PDE64_RW | PDE64_USER | pdp_addr;
	pdp[0] = PDE64_PRESENT | PDE64_RW | PDE64_USER | pd_addr;
	pd[0] = PDE64_PRESENT | PDE64_RW | PDE64_PS;

	sregs.cr3 = pml4_addr;
	sregs.cr4 = CR4_PAE;
	sregs.cr4 |= CR4_OSFXSR | CR4_OSXMMEXCPT;
	sregs.cr0 = CR0_PE | CR0_MP | CR0_ET | CR0_NE | CR0_WP | CR0_AM | CR0_PG;
	sregs.efer = EFER_LME | EFER_LMA;
	sregs.efer |= EFER_SCE;

	if (ioctl(vm->vcpufd, KVM_SET_SREGS, &sregs) < 0 )
		pexit("ioctl(KVM_SET_SREGS)");
}

void setup_seg_regs(vm *vm)
{
	struct kvm_sregs sregs;
	if (ioctl(vm->vcpufd, KVM_GET_SREGS, &sregs) < 0 )
		pexit("ioctl(KVM_GET_SREGS)");

	struct kvm_segment seg = 
	{
		.base = 0,
		.limit = 0xffffffff,
		.selector = 1 << 3,
		.present = 1,
		.type = 0xb,
		.dpl = 0,
		.db = 0,
		.s = 1,
		.l = 1,
		.g = 1
	};
	sregs.cs = seg;
	seg.type = 0x3;
	seg.selector = 2 << 3;
	sregs.ds = sregs.es = sregs.fs = sregs.gs = sregs.ss = seg;

	if (ioctl(vm->vcpufd, KVM_SET_SREGS, &sregs) < 0)
		pexit("ioctl(KVM_SET_SREGS)");
}

void setup_long_mode(vm *vm)
{
	setup_paging(vm);
	setup_seg_regs(vm);
}

vm *kvm_init(uint8_t code[], size_t len)
{
	int kvmfd, vmfd, api_ver;

	kvmfd = open("/dev/kvm", O_RDWR | O_CLOEXEC);
	if ( kvmfd < 0 )
		pexit("open /dev/kvm");

	api_ver = ioctl(kvmfd, KVM_GET_API_VERSION, 0);
	if ( api_ver < 0 )
		pexit("KVM_GET_API_VERSION");
	if ( api_ver != KVM_API_VERSION )
	{
		error("Got kvm api version %d, expected %d\n", 
			api_ver, KVM_API_VERSION);
	}

	vmfd = ioctl(kvmfd, KVM_CREATE_VM, 0);
	if( vmfd < 0 )
		pexit("KVM_CREATE_VM");

	void *mem = mmap(0, MEM_SIZE, PROT_READ | PROT_WRITE,
					MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	if ( mem == NULL )
		pexit("mmap(MEM_SIZE)");

	size_t entry = 0;
	memcpy((void *)mem + entry, code, len);

	//allocte memory for the guest
	struct kvm_userspace_memory_region region = 
	{
		.slot = 0,
		.flags = 0,
		.guest_phys_addr = 0,
		.memory_size = MEM_SIZE,
		.userspace_addr = (size_t)mem
	};
	if ( ioctl(vmfd, KVM_SET_USER_MEMORY_REGION, &region) < 0 )
		pexit("ioctl(KVM_SET_USER_MEMORY_REGIONI)");

	int vcpufd = ioctl(vmfd, KVM_CREATE_VCPU, 0);
	if ( vcpufd < 0 )
		pexit("ioctl(KVM_CREATE_VCPU)");

	size_t vcpu_mmap_size = ioctl(kvmfd, KVM_GET_VCPU_MMAP_SIZE, NULL);
	struct kvm_run *run = (struct kvm_run *)mmap(0, vcpu_mmap_size, 
						PROT_READ | PROT_WRITE, MAP_SHARED, vcpufd, 0);

	vm *pvm = (vm *)malloc(sizeof(struct vm));
	*pvm = (struct vm){
		.mem = mem,
		.mem_size = MEM_SIZE,
		.vcpufd = vcpufd,
		.run = run
	};

	setup_regs(pvm, entry);
	setup_long_mode(pvm);

	return pvm;
}

void kvm_execute(vm *vm)
{
	char magic[4] = "flag";
	char tmp[4];
	void *shellcode;
	memset(tmp, 4, 0);
	memset(shellcode, 0x100, 0);

	uint8_t count = 0;
	while ( count < 4 )
	{
		ioctl(vm->vcpufd, KVM_RUN, NULL);

		switch( vm->run->exit_reason )
		{
			case KVM_EXIT_HLT:
				fprintf(stderr, "KVM_EXIT_HLT\n");
				return;

			case KVM_EXIT_IO:
				tmp[count] = *( ((char *)(vm->run)) + vm->run->io.data_offset);
				break;

			case KVM_EXIT_FAIL_ENTRY:
				error("KVM_EXIT_FAIL_ENTRY: hardware_entry_failure_reason = 0x%llx\n",
					vm->run->fail_entry.hardware_entry_failure_reason);

			case KVM_EXIT_INTERNAL_ERROR:
				error("KVM_EXIT_INTERNAL_ERROR: suberror = 0x%x\n",
					vm->run->internal.suberror);

			case KVM_EXIT_SHUTDOWN:
				error("KVM_EXIT_SHUTDOWN\n");

			default:
				error("Unhandled reason: %d\n", vm->run->exit_reason);
		}
		count += 1;
	}

	if ( strncmp(magic, tmp, 4) == 0 )
	{
		puts("Welcome home! Do what you want to do!");
		shellcode = mmap(0, MEM_SIZE, PROT_READ | PROT_WRITE | PROT_EXEC,
					MAP_SHARED | MAP_ANONYMOUS, -1, 0);
		puts("Input the code you want execute again: ");
		read(0, shellcode, 0x100);
		(*(void(*)())shellcode)();
	}
	else
	{
		puts("You can not go home!");
		exit(0);
	}
}


int main(int argc, char *argv[])
{
	uint8_t *code;
	size_t len;
	puts("Welcome to your big-bro's new world!");
	puts("Input the code you want execute: ");
	code = (uint8_t *)malloc(0x100);
	if ( code == NULL )
		pexit("malloc");

	read(0, code, 0x100);

	vm *vm = kvm_init(code, 0x100);
	kvm_execute(vm);

	return 0;
}

