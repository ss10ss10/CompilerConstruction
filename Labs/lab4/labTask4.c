#include <stdio.h>
#include <stdlib.h>

void removeUnnecessarySpaces(char *);

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		printf("Need to have a file name in the arguments of this program\n");
		exit(0);
	}
	
	removeUnnecessarySpaces(argv[1]);
	return 0;
}

void removeUnnecessarySpaces(char *str)
{
	char* buff = (char*) malloc(sizeof(char)*1000);
	
	int i = 0;
	int j = 0;
	while(str[i]!='\0')
	{
		if (i==0 && str[i]==' ')
			i++;
		while (i > 0 && str[i-1]==' ' && str[i]==' ')
			i++;
		if (str[i+2]=='\0' && str[i+1] == ';' && str[i] == ' ')
			i++;
		buff[j] = str[i];
		i++;
		j++;
	}
	
	j = 0;
	while(buff[j] != '\0')
	{
		if (buff[j] == ' ' && buff[j+1] == ';')
			j++;
		printf("%c", buff[j]);
		j++;
	}
	printf("\n");
}
