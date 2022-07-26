/*
	Muhammad Sulaiman Sultan
	231453415
	Semester Project
	Compiler Construction
	LL(1) Parser
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare_tops(char, char);
// functions to manage stacks
int isfull(char []);
int isempty(char []);
char push(char *, char);
char pop(char []);
char peek(char []);
void init_Stacks(char a[], char b[]);
char *strrev(char *);
// stacks
char stack1[10];
char stack2[10];

char action[8][7] = {
	"A->BwA",
	"A->BwA",
	"A->e",
	"B->yC",
	"B->CxB",
	"C->z",
	"Error",
	""};

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("Invalid number of inputs!");
		exit(0);
	}
	if (argv[1][strlen(argv[1])-1] != '$')
	{
		printf("Input string invalid: $\n");
		exit(0);
	}
	char start[2] = {'A','$'};
	init_Stacks(start, argv[1]);
	
	int condition = 1;
	int counter = 1;
	while(condition)
	{
		int ret;
		char top_s1 = peek(stack1);
		char top_s2 = peek(stack2);
		if (top_s1 == top_s2)
			ret = 7;
		else
			ret = compare_tops(top_s1, top_s2);

		printf("\n%d: Top of s1            Top of s2                   Action\n",counter);
		printf("------------------------------------\n");
		printf("     %s                 %s                   %s\n\n", strrev(stack1), strrev(stack2), action[ret]);
		strrev(stack1); 
		strrev(stack2);

		if (top_s1 == '$' && top_s2 == '$')
		{	
			printf("\nString Accepted!\n");
			condition = 0;
		}
		if (top_s1 == top_s2)
		{
			pop(stack1);
			pop(stack2);
		}
		else if (ret < 6)
		{
			pop(stack1);
			char act[3];
			int i = 0;
			while(i+3 < strlen(action[ret]))
			{
				act[i] = action[ret][3+i];
				i++;
			}
			i = strlen(act)-1;
			while(i >= 0)
			{
				push(stack1,act[i]);
				i--;
			}
			memset(act, '\0', strlen(act)*sizeof(act[0]));
		}
		if (top_s1 == 'A' && top_s2 == '$')
		{	
			pop(stack1);
		}
		if (!strcmp(action[ret],"Error"))
		{
			printf("\nString Rejected!\n");
			condition = 0;
		}
		counter++;
	}
	return 0;
}

void init_Stacks(char argv1[], char argv2[])
{
	int i = 0;
	int j = strlen(argv1)-1;
	while(j >= 0)
	{
		stack1[i] = argv1[j];
		i++;
		j--;
	}

	i = 0;
	j = strlen(argv2)-1;
	while(j >= 0)
	{
		stack2[i] = argv2[j];
		i++;
		j--;
	}
}

int compare_tops(char a, char b)
{
	if (a == 'A' && b == 'y')
		return 0;
	else if (a == 'A' && b == 'z')
		return 1;
	else if (a == 'A' && b == '$')
		return 2;
	else if (a == 'B' && b == 'y')
		return 3;
	else if (a == 'B' && b == 'z')
		return 4;
	else if (a == 'C' && b == 'z')
		return 5;
	return 6;
}

int isempty(char a[])
{
	if (strlen(a) == 0)
		return 1;
	return 0;
}
int isfull(char a[])
{
	if (strlen(a) == 10)
		return 1;
	return 0;
}
char peek(char a[])
{
	return a[strlen(a)-1];
}
char pop(char a[])
{
	char temp;
	temp = a[strlen(a)-1];
	a[strlen(a)-1] = '\0';
	return temp;
}
char push(char *a, char data)
{
	if (!isfull(a))
		a[strlen(a)] = data;
	return a[strlen(a)];
}
char *strrev(char *str){
	char *str2 = str;
    char cnt, *start, *end;

    if(!str2 || !*str2)
        return str2;
    for(start=str2,end=str2+strlen(str2)-1;start < end;start++,end--){
        cnt=*start;*start=*end;*end=cnt;
    }
    return str2;
}
