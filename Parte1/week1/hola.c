#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "unistd.h"

struct mistruct
{
	char szVar[20+1];
};

typedef struct mist
{
	char szVar[10+1];
} miStr;

typedef int intPepe;

int main(int inc, char *argv[]) 
{
	int a = 1;

	intPepe inVar=0;
	printf("Hello world!");
	
	return 0;
}
