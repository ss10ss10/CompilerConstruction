/*
Muhammad Sulaiman Sultan: 231453415
Muhammad Sameed Gilani: 231488347
Compiler Cnstruction Section A
Assignment 1
Submitted to: M. Rauf Butt
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MSG "Good Morning"
#define ABC "Morning"
#define DEF "Good"

void stripOffComments(char fileArg[100]);
void stripSlash(char fileArg[100]);
void stripStar();
void stripBlank();
void macroExpansion(char fileArg[100]);
void includeHeaders(char fileArg[100]);
void removeComments(char fileArg[100]);


char fileName[100]; // Will keep the file name, from argv[1]

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		printf("Need to have a file name in the arguments of this program\n");
		exit(0);
	}
    strcpy(fileName,argv[1]);
	macroExpansion(fileName); // Creates out1.c
    stripOffComments(fileName); // Creates out2.c
	includeHeaders(fileName); // Creates final.c

	return 0;
}

void stripOffComments(char fileArg[100]){
    /*
        All comments and blank lines from the source file are removed and written to out1.c
        The Source file is not changed
    */

    // stripSlash(fileArg);
    // stripStar();
	removeComments(fileArg);
    stripBlank();

    
}

void removeComments(char fileArg[100])
{
	FILE *SourceFile; 
    FILE *outFile;

	SourceFile = fopen(fileArg,"r");
    outFile = fopen("out2.c","w+");
	char* buff = (char*) malloc(sizeof(char)*1000);
	char* buff2 = (char*) malloc(sizeof(char)*1000);

	char c = ' ';
	int idx = 0;

	while (c != EOF)
	{
		c = fgetc(SourceFile);
		printf("%c",c);
		buff[idx] = c;
		idx++;
	}

	int i,j = 0;
	int flag = 0;
	while(buff[i] != EOF)
	{
		if(buff[i] == '/') 
		{
			if(buff[i+1] == '/')
				while(buff[i] != '\n')
					i++;
			if (buff[i+1] =='*')
			{
				i+=2;
				while(buff[i] != EOF)
				{
					if(buff[i-1] == '*' && buff[i] == '/')
					{
						i++;
						break;
					}
					i++;
				}
			}
		}
		fputc(buff[i],outFile);
		i++;
		j++;
	}
	fclose(SourceFile);
	fclose(outFile);
}
// void stripSlash(char fileArg[100]){
//     /*
//         Function will remove all single line comments from the source file and writes the new file as, out1.c
//     */

//     // Creating file handlers
//     FILE *SourceFile; 
//     FILE *outFile;

//     // Source file is opened to be read and out file to be written to 
//     SourceFile = fopen(fileArg,"r");
//     outFile = fopen("out2.c","w+");

//     if (SourceFile == NULL){ // Prints an error and exits if the source file doesnt open
// 		printf("Error opening file");
// 		exit(0);
// 	}

//     char* buffer = (char*) malloc(sizeof(char)*100000); // Memory allocated
//     int i = 0;

//     // File is read line by line and stored in the buffer
//     // If  it sees a //, everything following it is skipped from being written
//     while(fgets(buffer,100000,SourceFile) != NULL){
//         i = 0;
//         while(buffer[i] != '\0'){ // Will read the current line until it reaches end of line
//             if(buffer[i] == '/' && buffer[i+1] == '/'){
//                 while(buffer[i] != '\n'){
//                     i ++;
//                 }
//             }
//             fputc(buffer[i],outFile); // Line is written to out file
//             i ++;
//         }
//     }

//     fclose(SourceFile);
//     fclose(outFile);
// }

// void stripStar(){
//     /*
//         Function will remove any multiline comments and updates the out1.c file 
//     */

//     // Creating file handlers
//     FILE *SourceFile; 
//     FILE *outFile;

//     SourceFile = fopen("out2.c","r"); // Source file from prev function is opened to be read

//     char* buffer = (char*) malloc(sizeof(char)*100000); // Memory allocated
//     char currC = ' ';
//     int i = 0;
//     currC = fgetc(SourceFile);
//     // Source file is read character by character and written to the buffer
//     while(currC != EOF){
//         buffer[i] = currC;
//         i++;
//         currC = fgetc(SourceFile);
//     }
//     buffer[i] = '$'; // To indicate the end of a buffer

//     i = 0;
//     fclose(SourceFile);

//     outFile = fopen("out2.c","w+"); // out1.c is opened for writing

//      // buffer is read. If a /* is seen, it will skip all the text between that /*,
//     //  until it sees a */
//     while (buffer[i] != '$'){ 
        
//         if(buffer[i] == '/' && buffer[i+1] == '*'){
//             i = i+2; // +2, to skip the /*
//             while(buffer[i] != '*' && buffer[i+1] != '/'){
//                 i++;
//             }
//             i = i+2; // skip the */
//         }
//         fputc(buffer[i],outFile); // Everything else is written to the file
//         i++;
//     }
//     fclose(outFile);
// }

void stripBlank(){
    /*
        Function will remove any blank lines from the file and updates the out1.c file.
    */

    // Creating file handlers
    FILE *SourceFile;
    FILE *TempFile;
    FILE *OutFile;

    // Open the source file from previous function(For Reading) and create a temp file(For Writing)
    SourceFile = fopen("out2.c","r");
    TempFile = fopen("Temp","w+");

    char* buffer = (char*) malloc(sizeof(char)*100000); // Memory allocated 

    // Reads the file character by character and writes it to the temp file
    // char currC = ' ';
    // currC = fgetc(SourceFile);

    // while(currC != EOF){
    //     fputc(currC,TempFile);
    //     currC = fgetc(SourceFile);
    // }

    char* buffer2 = (char*) malloc(sizeof(char)*100000); // Memory allocated 
	while (fgets(buffer2, 100000, SourceFile) != NULL)
	{
		fputs(buffer2, TempFile);
	}

    fclose(SourceFile);
    fclose(TempFile);


    // Opens the temp file(For reading) and the Out1.c file(For writing)
    TempFile = fopen("Temp", "r");
    OutFile = fopen("out2.c","w+");
    
    // Reads the temp file and writes each line to the buffer
    while(fgets(buffer,100000,TempFile) != NULL){
        int i = 0;
        int check = 1; // Flag to see if there is text at any point in the line

        if(buffer[0] == '\n' ) continue;
           
        
        if(buffer[0] == ' ' || buffer[0] == '\t' ){         // Will see if the line starts with a space or tab
            while(buffer[i] == ' ' || buffer[i] == '\t' ){ //  It will then see if the line has any text in it
                i++;

                if(buffer[i] == '\n' || buffer[i] == '\0'){ // Line has no text in it so it is not written to out file
                    check = 0;
                    break;
                }
                 
            }
        
            if(check == 1) // The line has some text in it so it will be written to out file
			{
				// fprintf(OutFile,"%s",buffer); 
				fputs(buffer, OutFile);
			}
            
             
        }
        else  // If the line starts with any text it is written to the out file
		{	
			// fprintf(OutFile,"%s",buffer);
			fputs(buffer, OutFile);
		}	
	}
    fclose(TempFile);
    remove("Temp"); // Temp file is deleted
    fclose(OutFile);
	strcpy(fileName,"out2.c");
}

void macroExpansion(char fileArg[100])
{
	FILE *fp;
	fp = fopen(fileArg,"r");
	if(fp == NULL)
	{
		printf("Error opening file.");
		exit(0);
	}
	
	
	char* buff = (char*) malloc(sizeof(char)*1000); // Will store each line read
	char* mHead = (char*) malloc(sizeof(char)*1000); // Will store the head of the macro
	char* mBody = (char*) malloc(sizeof(char)*1000); // Will store the body of the macro
	int* mLine = (int*) malloc(sizeof(int) * 1000); // Will store all the line numbers of the macros
	
	int mHeadCounter = 0;
	int mBodyCounter = 0;
	int mLineCount = 0;

	int lCount = 0;
	int macroCount = 0;

	while(fgets(buff,1000,fp) != NULL)
	{
		lCount++;
		if((buff[0] == '#' && buff[1] == 'd' && buff[2] == 'e' && buff[3] == 'f' && buff[4] == 'i' && buff[5] == 'n' && buff[6] == 'e') || (buff[0] == '#' && buff[1] == 'D' && buff[2] == 'E' && buff[3] == 'F' && buff[4] == 'I' && buff[5] == 'N' && buff[6] == 'E')) {
			
			mLine[mLineCount] = lCount; //Stores the line at which the macro is
			mLineCount++;
			int check = 7; 

			while(buff[check] == ' ') // Gets us to the first character of the macro head
			{	
				check ++;
			}

			while(buff[check]!= ' ') // Gets the Head of the macro
			{
				mHead[mHeadCounter] = buff[check];
				check++;
				mHeadCounter++;
			}

			macroCount++;
			mHead[mHeadCounter] = '`';
			mHeadCounter++;
			
			while(buff[check] == ' ') // Gets us to the first character of the macro body			
				check ++;

			while(buff[check]!='\0') // Gets the body of the macro
			{	
				mBody[mBodyCounter] = buff[check];
				check++;
				mBodyCounter++;
			}

			mBody[mBodyCounter] = '`';
			mBodyCounter++;
		}
			// printf("%d %s",lCount,buff); //Prints each line preceeded by the line number
	}		
	// if(macroCount != 0) // Prints the macro line numbers and the macro heads and bodies
	// {
	// 	int prnt = 0;
	// 	int prntHead = 0;
	// 	int prntBody = 0;
	// 	mLineCount = 0;
	// 	while (prnt < macroCount)
	// 	{
	// 		printf("\nMacro is on line: %d\n",mLine[mLineCount]);
	// 		mLineCount++;
	// 		printf("Macro is: ");
	// 		while (mHead[prntHead] != '`')
	// 		{
	// 			printf("%c", mHead[prntHead]);
	// 			prntHead++;
	// 		}
	// 		prntHead++;
	// 		prnt++;
	// 		printf("\nMacro string: ");
	// 		while (mBody[prntBody] != '`')
	// 		{
	// 			printf("%c", mBody[prntBody]);
	// 			prntBody++;
	// 		}
	// 		prntBody++;
	// 	}
	// }
	rewind(fp); // Rewinds the file pointer
    FILE *outFile;
    outFile = fopen("out1.c","w+");
	char store_c[50];
	char store_d[50];
	char* buff2 = (char*) malloc(sizeof(char)*1000); // Will store each line read
	int flag = 0;
	while(fgets(buff, 1000, fp) != NULL)
	{
		int i = 0;
		int j = 0;
		int macroLoopCount = 0;
		while (macroLoopCount < macroCount) // Loops runs for the total number of macros
		{
			int k = 0;
			int l = 0;
			while(i < strlen(mHead)) // This loop stores the each macro head in store_c
			{
				if (mHead[i] == '`')
				{
					i++;
					break;
				}
				store_c[k] = mHead[i];
				k++;
				i++;
			}
			while(j < strlen(mBody)) // This loop stores the each macro body in store_d
			{
				if (mBody[j] == '`')
				{
					j++;
					break;
				}
				store_d[l] = mBody[j];
				l++;
				j++;
			}
			if (strstr(buff,store_c) != NULL && buff[0] != '#') // This code segment replaces all instances of macro head with its body. It only ignores the #define macro definitions
			{
				flag = 1;
				int itr = 0;
				int itr2 = 0;
				int itr3 = 0;
				int itr4 = 0;
				while (buff[itr] != '\n')
				{
					if (buff[itr] == store_c[itr2])
					{
						while(store_d[itr4] != '\n')
						{
							buff2[itr3] = store_d[itr4];
							itr4++;
							itr3++;
						}
						itr+=strlen(store_c);
					}
					buff2[itr3] = buff[itr];
					itr++;
					itr3++;
				}
				buff2[itr3] = '\n';
				itr3++;
			}
			else if (strstr(buff,store_c) != NULL && buff[0] == '#') // Stops the macro definition from being written to file
			{
				flag = -1;
			}	
			macroLoopCount++;
		}
		
		if (flag == 1)
		{
			fputs(buff2, outFile);
			flag = 0;
		}
		else if (flag == -1)
		{
			flag = 0;
			continue;
		}
		else
			fputs(buff, outFile);
	}
	fclose(outFile);
	strcpy(fileName, "out1.c");
}
void includeHeaders(char fileArg[100])
{
	char* buff = (char*) malloc(sizeof(char)*100000); // Will store each line read
	char* include = (char*) malloc(sizeof(char)*100000); // Will store the include files

	FILE *fp;
	FILE *final;
	fp = fopen(fileArg, "r");
	final = fopen("final.c", "w+");
	while(fgets(buff,100000,fp) != NULL)
	{
		int i = 0;
		if (strstr(buff,"stdio.h") != NULL)
		{
			FILE *stdio;
			stdio = fopen("pa1_stdio", "r");
			while(fgets(include, 100000, stdio) != NULL)
				fputs(include, final);
			fclose(stdio);
		}
		else if (strstr(buff,"stdlib.h") != NULL)
		{
			FILE *stdlib;
			stdlib = fopen("pa1_stdlib", "r");
			while(fgets(include, 100000, stdlib) != NULL)
				fputs(include, final);
			fclose(stdlib);
		}
		else if (strstr(buff,"string.h") != NULL)
		{
			FILE *string;
			string = fopen("pa1_string", "r");
			while(fgets(include, 100000, string) != NULL)
				fputs(include, final);
			fclose(string);
		}
		else
		{
			fputs(buff, final);
		}
	}
	fclose(final);
	final = fopen("final.c", "r");
	while(fgets(buff,100000,final) != NULL)
	{
		printf("%s",buff);
	}
	fclose(final);
}