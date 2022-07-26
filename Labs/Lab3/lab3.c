#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void removeBlankLines(char *);

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		printf("Need to have a file name in the arguments of this program\n");
		exit(0);
	}
	
	removeBlankLines(argv[1]);
	return 0;
}

void removeBlankLines(char *str)
{
	FILE *fp;
	fp = fopen(str,"r");
	if(fp == NULL)
	{
		printf("Error opening file.");
		exit(0);
	}
	
	char* buff = (char*) malloc(sizeof(char)*1000);
	char* buff2 = (char*) malloc(sizeof(char)*1000);
	
	char c = ' ';
	int len = 0;
	int idx = 0;
	while (c != EOF)
	{
		c = fgetc(fp);
		buff[idx] = c;
		printf("%c",buff[idx]);
		idx++;
	}

	printf("\nOutput:\n");
	
	int idx2 = 0;
	int flag = 0;
	idx = 0;
	while (buff[idx] != EOF)
	{
		if (idx == 0 && buff[idx] == '\n') idx++;
		if (buff[idx-1] == '\n')
			while (buff[idx] == '\n' || buff[idx] == ' ')
				idx++;
		buff2[idx2] = buff[idx];
		idx++;
		idx2++;
	}
	fputs(buff2, stdout);
}
