# password_checker

`snprintf` 误用， 它返回的是格式化解析后形成的字符串的长度（及期望写入目标缓冲区的长度），而不是实际写入 目标缓冲区的内存长度。

```

    int off = snprintf(buf, 0x100, "name:%s&", input);
    ...........................
    ...........................    
    ...........................
    // off 可能会比较大，出现越界写
    off = snprintf(buf + off, 0x100 - off, "pwd:%s", input);

```


所以利用 `snprintf` 让 off 移动到返回地址的位置， 然后写返回地址为 getshell 函数的地址。


具体看 `exp` 和源码