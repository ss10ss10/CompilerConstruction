#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[])
{
    //check number of args
    if(argc != 2)
    {
        printf("This program needs a text file as argument\n");
        exit(0);
    }
    //your logic goes here
    FILE *fp;
    fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        printf("Error! The file did not open!");
        exit(0);
    }
    char* buffer = (char*) malloc(sizeof(char)*1000);
    char longestString[200];
    int max;
    max = 0;
    while (fgets(buffer, 1000, fp) != NULL)
    {
        if (strlen(buffer) > max)
        {
            strcpy(longestString,buffer);
            max = strlen(buffer);
        }
    }
    printf("Longest line in the file: \n");
    fputs(longestString, stdout);
    fclose(fp);
    return 0;
}