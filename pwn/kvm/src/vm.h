#ifndef VM_H
#define VM_H

#include <stdint.h>

#define PS_LIMIT (0x200000)
#define KERNEL_STACK_SIZE (0x4000)
#define MAX_KERNEL_SIZE (PS_LIMIT - 0x5000 - KERNEL_STACK_SIZE)
#define MAX_CODE_SIZE 0x10000
#define MEM_SIZE (PS_LIMIT * 0x2)

typedef struct vm
{
	void *mem;
	uint64_t mem_size;
	int vcpufd; //just supporting one vCPU
	struct kvm_run *run;
} vm;


vm *kvm_init(uint8_t code[], size_t len);
void setup_regs(vm *vm, size_t entry);
void setup_long_mode(vm *vm);
void setup_paging(vm *vm);
void setup_seg_regs(vm *vm);
int check_iopl(vm *vm);
void kvm_execute(vm *vm);
void copy_argv(vm *vm, int argc, char *argv[]);
void read_file(char *filename, uint8_t** content_ptr, size_t* size_ptr);

/* Common macros */
#define error(fmt, ...) do { \
  fprintf(stderr, fmt, ##__VA_ARGS__); \
  exit(EXIT_FAILURE); \
} while(0)

#define pexit(x) do { \
  perror(x); \
  exit(EXIT_FAILURE); \
} while(0)

#endif 