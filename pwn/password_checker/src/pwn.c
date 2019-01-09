#include <stdio.h>
#include <string.h>


// gcc pwn.c -m32 -o ../dist/pwn -w


unsigned int init_stdio()
{
  setvbuf(stdin, 0LL, 2, 0LL);
  setvbuf(stdout, 0LL, 2, 0LL);
  setvbuf(stderr, 0LL, 2, 0LL);
  return 0;
}

int getshell(){
    system("sh");
}

char input[0x400]={0};


int generate(){
    char buf[0x100];
    read(0, input, 0x400);
    
    int off = snprintf(buf, 0x100, "name:%s&", input);

    memset(input, '\x00', 0x400);
    read(0, input, 0x400);

    off = snprintf(buf + off, 0x100 - off, "pwd:%s", input);

    if(!strcmp(buf, "name:admin&pwd:admin")){
        puts("please pwn it");
    }
    printf("Your login string: %s", buf);
}

int main(int argc, char const *argv[])
{
    init_stdio();
    puts("welcome.....");
    generate();
    return 0;
}
