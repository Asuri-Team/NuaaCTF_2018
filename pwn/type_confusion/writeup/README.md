# type_confusion

类型混淆，可以先释放一个 c1类的 obj, 然后分配一个 c2 类的 obj, 然后利用 see c1 obj 的功能调用虚函数，会调用 c2 的虚函数，c2 的相应虚函数的作用就是 system("sh)

```
int c2::dump()
{
    system("sh");
}
```

具体看 `exp` 和源码