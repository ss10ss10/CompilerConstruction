#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_length(char *, int *, char *);

int main(int argc, char *argv[])
{
    //check number of args
    if(argc != 3)
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
    memset(buffer, '\0', sizeof(char)*1000);
    int lineLens[1000];
    memset(lineLens, '\0', 1000);

    char longestString[200];
    int max;
    max = 0;
    
    
    int i = 0;
    int occure = 0;
    while (fgets(buffer, 1000, fp) != NULL)
    {
        if(get_length(buffer, &occure, argv[2]) == 0)
        {
            continue;
        }
        printf("%d. ", i+1);
        fputs(buffer, stdout);
        lineLens[i] = get_length(buffer, &occure, argv[2]);
        i++;
    }

    printf("\n Number of lines: %d",i);
    for(int j = 0; j<i; j++)
    {
        printf("\n Number of characters in line %d: %d",j+1,lineLens[j]);  
    }
    
    printf("\n Character '%s' has %d occurrences.\n",argv[2], occure/2); // doubles the occurances of the character to be found. Why?
    fclose(fp);
    return 0;
}

int get_length(char *s, int *te, char *occ)
{
    int len = 0;
    int occur = 0;
    for(int i = 0; s[i]!='\n'; i++)
    {
        if (s[i] == ' ')
            continue;
        if (s[i] == '\0')
            break;
        if (s[i] == *occ)
            occur++;
        len++;
    }
    *te = *te + occur;
    return len;
}
