#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MSG "Good Morning"

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
	
	
	char* buff = (char*) malloc(sizeof(char)*1000); // Will store each line read
	char* mHead = (char*) malloc(sizeof(char)*1000); // Will store the head of the macro
	char* mBody = (char*) malloc(sizeof(char)*1000); // will store the body of the macro

	
	int mLine = 0;
	int mHeadCounter = 0;
	int lCount = 0;
	int mBodyCounter =0;

	while(fgets(buff,1000,fp) != NULL)
	{
		lCount ++;
		if((buff[0] == '#' && buff[1] == 'd' && buff[2] == 'e' && buff[3] == 'f' && buff[4] == 'i' && buff[5] == 'n' && buff[6] == 'e') || (buff[0] == '#' && buff[1] == 'D' && buff[2] == 'E' && buff[3] == 'F' && buff[4] == 'I' && buff[5] == 'N' && buff[6] == 'E')) {
			
			mLine = lCount; //Stores the line at which the macro is
			int check = 7; 

			while(buff[check] == ' '){ // Gets us to the first character of the macro head
				check ++;
			}

			while(buff[check]!= ' '){ // Gets the Head of the macro
				mHead[mHeadCounter] = buff[check];
				check++;
				mHeadCounter++;
			}
			while(buff[check] == ' '){ // Gets us to the first character of the macro body
				check ++;
			}
			while(buff[check]!='\0'){ // Gets the body of the macro
				mBody[mBodyCounter] = buff[check];
				check++;
				mBodyCounter++;
			}

			
			
		}
			printf("%d %s",lCount,buff); //Prints each line preceeded by the line number
	}

	if(mLine != 0){
	printf("Macro is on line number: %d",mLine);
	printf("\nMacro is: %s ",mHead);
	printf("\nMacro string: %s: ",mBody);
	}
		
	
	
	
	return 0;
}
