#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

// g++ pwn.cpp -o ../dist/pwn -w

unsigned int init_stdio()
{
    setvbuf(stdin, 0LL, 2, 0LL);
    setvbuf(stdout, 0LL, 2, 0LL);
    setvbuf(stderr, 0LL, 2, 0LL);
    return 0;
}

class base
{
  public:
    int age;
    ~base()
    {
        ;
    }
    base()
    {
        this->age = 0;
    }
    virtual int dump() = 0;
};

class c1 : public base
{
  public:
    ~c1()
    {
        printf("c1 object deleted\n");
    }
    virtual int dump();
};

int c1::dump()
{
    puts("Your are look a c1 object");
}

class c2 : public base
{
  public:
    ~c2()
    {
        system("sh");
    }
    virtual int dump();
};

int c2::dump()
{
    system("sh");
}

void get_str(char *buf, int size, char term)
{
    char ch;
    int i = 0;

    for (i = 0; i < size; i++)
    {
        read(0, &ch, 1);
        if (ch == term)
        {
            buf[i] = '\0';
            return;
        }
        else
        {
            buf[i] = ch;
        }
    }

    if (i == size)
    {
        buf[size - 1] = '\0';
    }
    else
    {
        buf[i] = '\0';
    }
}

unsigned int get_num()
{
    char buf[20];
    get_str(buf, 20, '\n');
    return atoi(buf);
}

int menu()
{

    puts("1.see a c1 class object info");
    puts("2.free a c1 class object");
    puts("Your choice: ");
}

base *obj_tbl[20] = {0};

void add_o1()
{
    int i;
    for (i = 0; obj_tbl[i] && i < 20; i++)
    {
    }

    if (i >= 20)
    {
        puts("full");
        return;
    }
    obj_tbl[i] = new c1();

    puts("add o1!");
}

void add_o2()
{

    int i;
    for (i = 0; obj_tbl[i] && i < 20; i++)
    {
        ;
    }

    if (i >= 20)
    {
        return;
    }
    obj_tbl[i] = new c2();
    puts("add o2!");
}

void see_o1()
{

    printf("Index: ");
    unsigned int i;
    i = get_num();
    if (i >= 20 && obj_tbl[i])
    {
        return;
    }
    obj_tbl[i]->dump();
}

void free_o1()
{

    printf("Index: ");
    unsigned int i;
    i = get_num();
    if (i >= 20 && obj_tbl[i])
    {
        return;
    }
    free(obj_tbl[i]);
    obj_tbl[i] = 0;
}

int main(int argc, char const *argv[])
{
    init_stdio();
    int choice;

    for (int i = 0; i < 20; i++)
    {
        obj_tbl[i] = new c1();
    }

    while (1)
    {
        menu();
        choice = get_num();
        switch (choice)
        {
        case 100:
            add_o2();
            break;
        case 1:
            see_o1();
            break;
        case 2:
            free_o1();
            break;
        default:
            return 0;
        }
    }

    puts("welcome.....");
    return 0;
}
