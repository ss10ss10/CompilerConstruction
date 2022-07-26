/*
Muhammad Sulaiman Sultan: 231453415
Compiler Construction Section A
Assignment 2
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char add[] = "100000";
char and[] = "100100";
char or[] = "100101";
char andi[] = "001100";
char ori[] = "001101";
char addi[] = "001000";
char sw[] = "101011";
char lw[] = "100011";
char slt[] = "101010";


char * toBin(int);
char * operation(char*);


int regidx = 0;
char mips[36] = {};

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("Invalid inputs!");
		exit(0);
	}
	FILE *fp;
	fp = fopen(argv[1], "r");
	if (fp == NULL)
	{
		printf("File not opened!");
		exit(0);
	}

	char* buff = (char*) malloc(sizeof(char)*100000);

    char c = fgetc(fp);
	while (1)
	{
		memset(mips, 0, 36);
		int regCnt = 0;
		char op[5]={};
		int i = 0;
    	while(1)
		{
    	    if (c == ' ' || c == '\n' || c == '\0' || c == EOF)
			{
    	        break;
			}

    	    op[i] = c;
    	    c = fgetc(fp);
    	    i++;
    	}



		regidx = 0;
		while(regidx < 6)
		{
			mips[regidx] = '0';
			regidx++;
		}
	
		regidx = 0;
		mips[24] = ' ';
		while(regidx < 6)
		{
			mips[25 + regidx] = '0';
			regidx++;
		}





		char * opcode = {operation(op)};

		int opidx = 0;
		mips[29] = ' ';
		while (opidx < 6)
		{
			mips[30 + opidx] = opcode[opidx];
			opidx++;
		}
		
		c = fgetc(fp);
		char num[2] = {};
		if (c == '$')
		{
			c = fgetc(fp);
			int j = 0;
			while (1)
			{
				if (c == '$')
					c = fgetc(fp);
				if (c == ',' || c == EOF || c == '\0' || c == '\n')
				{
					int x = atoi(num);
					char * d = toBin(x);
					// printf("%s",d);

					// int k = 1;
					// while(k <= 5)
					// {
					// 	printf("%d",d[k]);
					// 	k++;
					// }
					// printf("\n");
					j = 0;
					memset(num, 0, 2);
					if (regCnt == 0)
					{
						mips[18] = ' ';
						regidx = 0;
						while (regidx < 5)
						{
							mips[19 + regidx] = d[regidx];
							// printf("%d",mips[19 + regidx]);
							// snprintf(mips[19+regidx], 1, d[regidx]);
							regidx++;
						}
						// memset(d, '\0', 6);
						regCnt++; 
					}
					else if (regCnt == 1)
					{
						mips[6] = ' ';
						regidx = 0;
						while (regidx < 5)
						{
							mips[7 + regidx] = d[regidx];
							// printf("%d",mips[7 + regidx]);
							// snprintf(mips[7+regidx], 1, d[regidx]);

							regidx++;
						}
						// memset(d, '\0', 6);
						regCnt++; 
					}
					else if (regCnt == 2)
					{
						mips[12] = ' ';
						regidx = 0;
						while (regidx < 5)
						{
							mips[13 + regidx] = d[regidx];
							// printf("%d",mips[13 + regidx]);
							

							// snprintf(mips[13+regidx], 1, d[regidx]);
							regidx++;
						}
						// memset(d, '\0', 6);
						regCnt++; 
					}
					char num[2] = {};

					if (c == '\n' || c == '\0' || c == EOF)
					{
						break;	 
					}
				}
				else if (atoi(&c) >= 0 && atoi(&c) <= 9)
				{
					num[j] = c;
					j++;
				}
				c = fgetc(fp);
			}
			// if (c == '\n')
			// 	continue;

			// c = fgetc(fp);
		}
		printf("%s\n",mips);

		c = fgetc(fp);
	
		if (c == EOF)
			break;
	}
	return 0;
}

char * toBin(int dec)
{
	int j = 5;
	int i = 0;
	static int decimal[5];
	static char dec1[5];
	while (i<5)
	{
		decimal[j] = dec % 2;
		dec = dec / 2;
		dec1[i] = decimal[j] + '0';
		i++;
		j--;
	}
	
	return dec1;
}

char * operation(char * a)
{
	if (!strcmp(a, "and"))
		return and;
	else if (!strcmp(a, "add"))
		return add;
	else if (!strcmp(a, "or"))
		return or;
	else if (!strcmp(a, "andi"))
		return andi;
	else if (!strcmp(a, "ori"))
		return ori;
	else if (!strcmp(a, "addi"))
		return addi;
	else if (!strcmp(a, "sw"))
		return sw;
	else if (!strcmp(a, "lw"))
		return lw;
	else if (!strcmp(a, "slt"))
		return slt;
}
// 000000 01010(10) 01011(11) 01001(9) 00000 100000(add) = add $9,$10,$11

// 000000 01001(9) 01010(10) 01100(12) 00000 100000(add) = add $12,$9,$10

// 000000 01001(9) 01100(12) 01101(13) 00000 100100(and) = and $13,$10,$12