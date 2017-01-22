#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "a1h.h"

#define MAX 256 
int main(int argc, char* argv[])
{

	int initTokens = 100;
	FILE * infile = fopen(argv[1],"r");
	char outfileName[50];
	strcpy(outfileName,argv[1]);
	outfileName[strlen(outfileName)-1]='\0';
	FILE * outfile = fopen(outfileName,"w+");
	int tokenCount =0;
	int tokenIndex=0;
	int waste=0;
	int i=0;
	int innerBraces=0;
	int functionIndex [FXNPERCLASS];
	int functionCount=0;
	char c = fgetc(infile);
	char ** array = getArray(initTokens);
	
	while(c!=EOF)
	{
		array[tokenCount][tokenIndex]=c;
		tokenIndex++;
		if(c==' ' || c=='\t'||  c=='\n')
		{
			array[tokenCount][tokenIndex]='\0';
			tokenIndex=0;
			tokenCount++;
		}

		if(tokenCount>=initTokens)
			extendArray(&array,initTokens,tokenCount+initTokens);
	
		c=fgetc(infile);

	}

	printTokens(array,tokenCount);
	


	while(i<tokenCount)
	{
		if(isClass(array[i]))
		{
			fputs("struct ",outfile);
			i++;
		}
		/*if its a datatype check if its a variable or a function*/
		if(isDataType[array[i]])
		{
			if(!isEnd(array[i+1]))/*if not a variable store fxn location*/
			{
				functionIndex[functionCount]=i;
				functionCount++;

			}
		}
		fputs(array[i],outfile);
	}

	fclose(outfile);
	fclose(infile);
	return 0;
}