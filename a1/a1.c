#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "a1h.h"

int main(int argc, char* argv[])
{

	char * classlist=malloc(sizeof(char)*MAX);
	char * functionlist=malloc(sizeof(char)*MAX*MAX);
	char * variablelist=malloc(sizeof(char)*MAX*10);


	int initTokens = 100;
	FILE * infile = fopen(argv[1],"r");
	/*char outfileName[50];
	strcpy(outfileName,argv[1]);
	outfileName[strlen(outfileName)-1]='\0';
	FILE * outfile = fopen(outfileName,"w+");*/
	int tokenCount =0;
	int tokenIndex=0;
	int i=0;
	int innerBraces=-1;
	int functionIndex [FXNPERCLASS];
	int functionCount=0;
	char c = fgetc(infile);
	
	char ** array = getArray(initTokens);
	int delimFlag=0;
	

	while(c!=EOF)
	{
		printf("c is: %c\n",c);
		if(delimiter(c))
		{
			printf("its a delim\n");
			if(delimFlag==0)/*char before delim*/
			{

				if(tokenCount!=0)/*file starts with white space*/
				{
					tokenCount++;
					tokenIndex=0;
				}

				if(tokenCount == initTokens)
				{
					extendArray(&array,initTokens,tokenCount+initTokens);
					initTokens = tokenCount+initTokens;
				}
				
				array[tokenCount][tokenIndex]=c;
				tokenIndex++;
				array[tokenCount][tokenIndex]='\0';
				printf("[%d]buidling token: %s\n", delimFlag,array[tokenCount]);

				
			}
			else
			{

				array[tokenCount][tokenIndex]=c;
				tokenIndex++;
				printf("[%d]buidling token: %s\n", delimFlag,array[tokenCount]);
				//array[tokenCount][tokenIndex]='\0';

			}
			delimFlag=1;


		}else /*not deliimter*/
		{
			if(delimFlag==1)
			{
				array[tokenCount][tokenIndex]='\0';
				tokenCount++;
				tokenIndex=0;
			}

			array[tokenCount][tokenIndex]=c;
			tokenIndex++;
			array[tokenCount][tokenIndex]='\0';
			printf("[%d]buidling token: %s\n", delimFlag,array[tokenCount]);
			delimFlag=0;
		}

		
		

		c=fgetc(infile);


	}

	printTokens(array,tokenCount);
	



	/*printTokens(array,tokenCount);


	array i populated with tokens*/
	/*int j=0;
	while(i<tokenCount)
	{

		printf("%s",array[i]);
		i++;

		int realClass=0;
		if(isClass(array[i]))
		{
			if(i>0)
			{
				if(strcmp(array[i-1],"\n")==0)
				{
					realClass=1;
					j++;
				}	
			}
		}


	}
	*/	
	//printf("%d many real classes\n", j);


	printf("\n");
	//fclose(outfile);
	fclose(infile);
	return 0;
}