#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "a1h.h"

#define MAX 256 
int main(int argc, char* argv[])
{

	char * classlist=malloc(sizeof(char)*MAX);
	char * functionlist=malloc(sizeof(char)*MAX);
	char * variablelist=malloc(sizeof(char)*MAX);


	int initTokens = 100;
	FILE * infile = fopen(argv[1],"r");
	char outfileName[50];
	strcpy(outfileName,argv[1]);
	outfileName[strlen(outfileName)-1]='\0';
	FILE * outfile = fopen(outfileName,"w+");
	int tokenCount =0;
	int tokenIndex=0;
	int i=0;
	int innerBraces=-1;
	int functionIndex [FXNPERCLASS];
	int functionCount=0;
	char c = fgetc(infile);
	char ** array = getArray(initTokens);
	
	while(c!=EOF)
	{
		
		if(delimiter(c))
		{
			if(tokenIndex==0)
			{
				array[tokenCount][tokenIndex]=c;
				array[tokenCount][tokenIndex+1]='\0';
				tokenIndex=0;
				tokenCount++;
			}else
			{
				array[tokenCount][tokenIndex]='\0';
				tokenIndex=0;
				tokenCount++;
				array[tokenCount][tokenIndex]=c;
				array[tokenCount][tokenIndex+1]='\0';
				tokenCount++;


			}
		}else
		{
			array[tokenCount][tokenIndex]=c;
			tokenIndex++;
		}
		if(tokenCount == initTokens){
			
			extendArray(&array,initTokens,tokenCount+initTokens);
			initTokens = tokenCount+initTokens;
		}
		c=fgetc(infile);

	}
	
	printf("%d\n",tokenCount);
	printTokens(array,tokenCount);
	
	/*array i populated with tokens*/

	while(i<tokenCount)
	{

		if(isClass(array[i])) /*when class comes up*/
		{

			while(isBlank(array[i]))/* get rid of spaces, get to the name*/
				i++;


			strcpy(classlist,array[i]); /*store the class name in class list*/

			while(!openBrace(array[i])) /*find opening brace for class*/
				i++;
			
			innerBraces=1; /*{=+1, }=-1 terminate when inner brace =0*/ 
			i++;

			while(innerBraces!=0) /*within scope of class find functions and variables*/
			{

				if(openBrace(array[i]))
					innerBraces++;

				if(closeBrace(array[i]))
					innerBraces--;

				/*find varibles and store in variable list*/

				if(isDataType(array[i])) /*found a data type*/
				{ 

					
					i++;
					int j=i;
					while(isBlank(array[i]))/*ignore all blanks*/
						i++;

					char unknown[MAX];
					strcpy(unknown,array[i]);/*copy potential*/

					while(isBlank(array[i]))
						i++;

				}

				/*find functions and store in fxnlist*/

				i++;
			}

		}

		i++;
	}

	

	fclose(outfile);
	fclose(infile);
	return 0;
}