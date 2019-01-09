#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<sys/ptrace.h>
#include<signal.h>

#define ANTI_REV_JMP            \
    __asm__ __volatile__(       \
     "jnz   rubbish\n"         \
     "jz    rubbish\n"         \
     ".byte 0xe8, 0xca,0xdd,0x08,0xae,0xe9\n"  \
     "rubbish:\n"               \
     "xor %%eax, %%eax\n"       \
     :::"eax"                   \
     );

#define ANTI_REV_PUSH           \
    __asm__ __volatile__(       \
     "push rublabel\n"          \
     "ret\n"                   \
     "rublabel:\n"              \
     "xor %%eax, %%eax\n"       \
     :::"eax"                   \
     );


#define ANTI_DEBUG_PTRACE  ptrace(PTRACE_TRACEME, 0, 1, 0) < 0
// #define BOOL int
// #define TRUE 1
// #define FALSE 0
#define get_bit(src, i) (0x1&(src >> i))
#define set_bit(dst, bit, i) dst = ((dst)|(bit << i))
#define LENGTH 24

char code_main[] = "int main(){\n" 
                 "    int result = MUL(1+3, 1+4);\n"
                 "    printf(\" answer is %d\", result);\n"
                 "    return 0;\n"
                 "}\n";
int be_overtime = 0;
int code_answer = 0;
int be_cheated = 0;
char bit_table[] = {3, 7, 2, 1, 6, 4, 5, 0};

#ifdef DEBUG
char flag[] = "nuaactf{Haa!You_G0t_1t!}";
#endif 

void anti_overtime(int sig){
    be_overtime = 1;
}

void __attribute__((constructor))setupSig(void){
    signal(SIGALRM, anti_overtime);
#ifndef DEBUG
    alarm(5);
#endif
}

void put_welcome(){
    puts("*************************************");
    puts("*         welcome to nuaa ctf        ");
    puts("*                                    ");
    puts("*  Let's start our C program class~  ");
    puts("*************************************");
}


unsigned char bit_translate(unsigned char u){
// #ifndef DEBUG
    ANTI_REV_JMP
// #endif
    int index;
    unsigned char dst_u = 0;
    for(index = 0; index < 8; index++){
        unsigned char tmp = get_bit(u, index);
        set_bit(dst_u, tmp, bit_table[index]);
    }
    return dst_u;
}

void get_input_and_trans(unsigned char dst[]){
    int i, length = LENGTH;
    puts("Hey you, what's your password?");
    puts("format:nuaactf{.+}, length:24");
    for(i = 0; i < length; i++){
        scanf("%c", &dst[i]);
    }
    puts("em?ok, you can get in...");

#ifndef DEBUG
    // ANTI_REV_JMP
#endif
    
    for(i = 0; i < length; i++){
        // dst[i] = (unsigned char)tmp[i];
        dst[i] = bit_translate(dst[i]);
    }
    return;
}

void read_code_and_answer(){

    puts("first, we try to read code");
    puts("could you tell me the output of code following?");
    puts("#define MUL(X,Y) X*Y");
    puts("#include<stdio.h>");
    puts(code_main);
    printf("your answer is:");
    scanf("%d", &code_answer);
    
#ifdef DEBUG
    printf("now input answer is %d\n", code_answer);
#endif

    puts("Ok? you must trust yourself :)");
    return;
}

void find_final_answer(unsigned char dst[]){
    
    int i = 0;
    unsigned char check[] = {190, 116, 48, 48, 176, 124, 188, 242, 42, 48, 48, 16, 98, 182, 116, 230, 164, 88, 124, 230, 80, 124, 16, 118};
    puts("Well,Well,You get here right?");
#ifndef DEBUG
    if(be_cheated&&(!be_overtime)){
#endif
        puts("!!! Hey !!!");
        puts("Do you remember your password?");
        for(i = 0; i < LENGTH; i++){
            dst[i] ^= code_answer;
            //TODO:Compare with hard code number
            if(check[i] != dst[i])
                break;
        }
        if(i == LENGTH){
            puts("YOU ARE RIGHT!THE KEY IS FLAG!");
        }
        else{
            puts("O?Nearly");
        }
#ifndef DEBUG
    }
    else{
        puts("En?No No No you are not clever~");
    }
#endif 
    return;
}

int main(){

    unsigned char chs[LENGTH + 1] = {0};
    put_welcome();
#ifndef DEBUG
    if(ANTI_DEBUG_PTRACE){
        printf("Hey guys, what are you doing?!not cheat me~\n");
        be_cheated += 1;
        exit(-1);
    }
#endif
    get_input_and_trans(chs);
/*
    chs = (unsigned char*)flag;
    int i = 0;
    puts("FIRST trans is");
    for(i = 0; i < LENGTH; i++){
        chs[i] = bit_translate(chs[i]);
        printf("%d ", chs[i]);
    }
*/  
    read_code_and_answer();
    find_final_answer(chs);
    return 0;
}
