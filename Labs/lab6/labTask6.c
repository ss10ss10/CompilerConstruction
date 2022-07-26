#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		printf("Need to have a file name in the arguments of this program\n");
		exit(0);
	}
	
	FILE *fp;
	fp = fopen(argv[1],"r");
	if(fp == NULL)
	{
		printf("Error opening file.");
		exit(0);
	}
	
	int accepted = 0; 
	
	int currState = 0;
	
	char currInp = fgetc(fp);	
	
	if (currInp == 'a' && currState == 0)
		goto Q1;
	if (currInp == 'b' && currState == 0)
		goto Q2;
	int nextState;
Q1:
	accepted = 0;
	if (currInp == 'a' || currInp == 'b')
		printf("Recieved %c on state q%d ---- Moving to state q1\n", currInp, currState);
	currInp = fgetc(fp);
	if (currInp == 'a' || currInp == 'b')
	{
		currState = 1;
		if (currInp == 'a')
			goto Q3;
		else if (currInp == 'b')
			goto Q2;
	}
	else if (currInp == '$')
		goto Final;
Q2:
	accepted = 0;
	if (currInp == 'a' || currInp == 'b')
		printf("Recieved %c on state q%d ---- Moving to state q2\n", currInp, currState);
	currInp = fgetc(fp);
	if (currInp == 'a' || currInp == 'b')
	{
		currState = 2;
		if (currInp == 'a')
			goto Q1;
		else if (currInp == 'b')
			goto Q4;
	}
	else if (currInp == '$')
		goto Final;
Q3:
	accepted = 1;
	if (currInp == 'a' || currInp == 'b')
		printf("Recieved %c on state q%d ---- Moving to state q3\n", currInp, currState);
	currInp = fgetc(fp);
	if (currInp == 'a' || currInp == 'b')
	{ 
		currState = 3;
		if (currInp == 'a')
			goto Q3;
		else if (currInp == 'b')
			goto Q2;		
	}
	else if (currInp == '$')
		goto Final;
Q4:
	accepted = 1;
	if (currInp == 'a' || currInp == 'b')
		printf("Recieved %c on state q%d ---- Moving to state q4\n", currInp, currState);
	currInp = fgetc(fp);
	if (currInp == 'a' || currInp == 'b')
	{
		currState = 4;
		if (currInp == 'a')
			goto Q1;
		else if (currInp == 'b')
			goto Q4;	
	}
	else if (currInp == '$')
		goto Final;
		
	
Final:
	printf("End of string.\n");
	if(accepted == 1)
		printf("String accepted\n");
	else
		printf("String rejected\n");
	
	
	return 0;
}


