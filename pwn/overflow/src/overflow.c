#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int protector = 0;

void get_flag()
{
	int fd = open("flag", O_RDONLY);
	if (fd < 0)
		perror("open");
	char flag[100];
	memset(flag, 0, 100);
	read(fd, flag, 100);
	write(1, flag, 100);
}


int main(int argc, char *argv[])
{	
	int random;
	char buf[0x20];
	memset(buf, 0, 0x20);
	
	srand(time(0));
	random = rand();
	protector = random;
	
	puts("You can't bypass it.");
	read(0, buf, 100);

	if( random != protector )
	{
		puts("You touched me!");
		exit(0);
	}
	return 0;
}