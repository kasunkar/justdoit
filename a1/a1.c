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
	int whiteSpaceFlag=0;
	int charFlag =0;
    int delimFlag=0;
	while(c!=EOF)
	{
		printf("c is: %c\n",c);
		if(delimiter(c))
		{
            delimFlag=1;
			//printf("its a delim\n");
			if(isWhiteChar(c))/*char before delim*/
			{

				if(charFlag==1)/*file starts with white space*/
				{
                    charFlag=0;
					tokenCount++;
                    if(tokenCount == initTokens)
                    {
                        extendArray(&array,initTokens,tokenCount+initTokens);
                        initTokens = tokenCount+initTokens;
                    }
					tokenIndex=0;
                    
                }

                array[tokenCount][tokenIndex]=c;
                tokenIndex++;
                array[tokenCount][tokenIndex]='\0';
            
            }
            else if (isQuotes(c))
            {
                tokenCount++;
                if(tokenCount == initTokens)
                {
                    extendArray(&array,initTokens,tokenCount+initTokens);
                    initTokens = tokenCount+initTokens;
                }
                tokenIndex=0;
                array[tokenCount][tokenIndex]=c;
                tokenIndex++;
                int endQuote=0;
                c=fgetc(infile);
                while(endQuote!=1)
                {
                    printf("in while %c\n",c);
                    array[tokenCount][tokenIndex]=c; 
                    tokenIndex++;
                    printf("at index %d\n",tokenIndex); 

                    if(isQuotes(c) && !isEscaped(array[tokenCount][tokenIndex-2]))
                    {    
                        endQuote=1;
                        printf("endQuote set %d\n",endQuote);
                    }
                    c=fgetc(infile); 
                }
                
                array[tokenCount][tokenIndex]='\0';

            }/*other delimiters*/
			else
			{
                tokenCount++;
                if(tokenCount == initTokens)
                {
                    extendArray(&array,initTokens,tokenCount+initTokens);
                    initTokens = tokenCount+initTokens;
                }
                tokenIndex=0;
				array[tokenCount][tokenIndex]=c;
				tokenIndex++;
				array[tokenCount][tokenIndex]='\0';

			}
            charFlag=0;

		}
        else /*not deliimter*/
		{
			if(delimFlag==1)
			{
				array[tokenCount][tokenIndex]='\0';
				tokenCount++;
                if(tokenCount == initTokens)
                {
                    extendArray(&array,initTokens,tokenCount+initTokens);
                    initTokens = tokenCount+initTokens;
                }
				tokenIndex=0;
			}

			array[tokenCount][tokenIndex]=c;
			tokenIndex++;
			array[tokenCount][tokenIndex]='\0';

            charFlag =1;
            delimFlag=0;
            whiteSpaceFlag=0;
		}

		
		

		c=fgetc(infile);


	}
    tokenCount++;
    printTokens(array,tokenCount);

    char ** reducedArray = getArray(tokenCount);
    int rCount=0;
    int aIndex=0;
	
    /*while(rCount!=tokenCount)
    {
        if(isQuotes(array[aIndex]))
        {
            printf("IS QUOTES\n");
            strcpy(reducedArray[rCount],array[aIndex]);
            aIndex++;
            while(!isQuotes(array[aIndex])&&!isEscaped(array[aIndex-1]))
            {
                strcat(reducedArray[rCount],array[aIndex]);
                aIndex++;
            }
            strcat(reducedArray[rCount],array[aIndex]);
        }
        else
        {
            strcpy(reducedArray[rCount],array[aIndex]);
        }
        
        rCount++;
        aIndex++;
    }*/

    printTokens(reducedArray,rCount);



	/*	array i populated with tokens*/
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