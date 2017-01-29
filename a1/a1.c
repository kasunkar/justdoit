#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "a1h.h"

int main(int argc, char* argv[])
{



	int initTokens = 100;
	FILE * infile = fopen(argv[1],"r");
    if(infile==NULL)
        printf("no file\n");
	char outfileName[50];
	strcpy(outfileName,argv[1]);
	outfileName[strlen(outfileName)-1]='\0';
	FILE * outfile = fopen(outfileName,"w+");
	int tokenCount =0;
	int tokenIndex=0;
	int i=0;
	int innerBraces=-1;
    char endChar[]="~~";
	char c = fgetc(infile);
	
	char ** array = getArray(initTokens);
	int whiteSpaceFlag=0;
	int charFlag =0;
    int delimFlag=0;
	while(c!=EOF)
	{
		if(delimiter(c))
		{
            delimFlag=1;
			//printf("its a delim\n");
			if(isWhiteChar(c))/*char before delim*/
			{

				if(charFlag==1 || delimFlag==1)/*file starts with white space*/
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
                    array[tokenCount][tokenIndex]=c; 
                    tokenIndex++;

                    if(isQuotes(c) && !isEscaped(array[tokenCount][tokenIndex-2]))
                    {    
                        endQuote=1;
                    }else
                    {
                        c=fgetc(infile); 
                    }
                }
                
                array[tokenCount][tokenIndex+1]='\0';

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
                delimFlag=1;
                whiteSpaceFlag=0;

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
    //printTokens(array,tokenCount);

    
    /* tokens properly loaded*/



    char ** classlist= getList(tokenCount);
    char ** functionlist=getList(tokenCount);
    char ** variablelist=getList(tokenCount);
    i = 0;
    int classIndex=0;
    while(i<tokenCount)
    {
        if(isClass(array[i]))
        {
            //printf("R: %d\n",openBrace(array[i+4]));
            if(openBrace(array[i+4]) || openBrace(array[i+3]))
            {
                strcpy(classlist[classIndex],array[i + 2]);
                strcpy(classlist[classIndex+1],";");
                //printf("classlist: %s\n",classlist[classIndex]);
                innerBraces=1;
                i=i+5; 
            }

            while(innerBraces!=0)
            {
                if(openBrace(array[i]))
                    innerBraces++;

                if(closeBrace(array[i]))
                    innerBraces--;

                if(isDataType(array[i]))
                {
                    /*case for function*/
                    /*look for opening paran*/
                    if(openParan(array[i+4]) || openParan(array[i+3]))
                    {
                        //printf("%s%s%s%s%s is a function\n",array[i],array[i+1],array[i+2],array[i+3],array[i+4]);
                        /*copy till open paran*/
                        while(!closeParan(array[i]))
                        {
                            strcat(functionlist[classIndex],array[i]);
                            i++;
                        }
                        strcat(functionlist[classIndex],array[i]);
                        i++;
                        /*at token after  ) */

                        /*if prototype*/
                        if(isEnd(array[i]) || isEnd(array[i+2]))
                        {
                            strcat(functionlist[classIndex],array[i]);
                            strcat(functionlist[classIndex],endChar);
                        }else
                        {
                            while(!openBrace(array[i]))
                            {
                                strcat(functionlist[classIndex],array[i]);
                                i++;
                            }
                            strcat(functionlist[classIndex],array[i]);
                            i++;
                            int functionBrace=1;
                            while(functionBrace!=0)
                            {
                                if(openBrace(array[i]))
                                    functionBrace++;

                                if(closeBrace(array[i]))
                                    functionBrace--;


                                strcat(functionlist[classIndex],array[i]);
                                i++;

                            }
                            strcat(functionlist[classIndex],"\n");
                            

                        }



                    }else/*copy variables till ;*/
                    {
                        while(!isEnd(array[i]))
                        {
                            strcat(variablelist[classIndex],array[i]);
                            i++;
                        }
                        strcat(variablelist[classIndex],array[i]);
                        strcat(variablelist[classIndex],"\n\t");
                       
                    
                        //printf("%s%s%s is a variable\n",array[i],array[i+1],array[i+2]);
                    }

                }
                i++;

            }
            classIndex++;
        }
        i++;
    }
    i=0;
    while(!isEnd(classlist[i]))
    {
        printf("classlist: %s\n", classlist[i]);
        printf("functionlist: %s\n", functionlist[i]);
        printf("variablelist: %s\n\n\n\n\n", variablelist[i]);
        i++;
    
    }

    /*printing output*/

    i=0;
    classIndex=0;
    while(i<tokenCount)
    {
        if(isRealClass(array,i))
        {
            fprintf(outfile,"\nstruct %s {\n",classlist[classIndex]);
            fprintf(outfile, "\t%s",variablelist[classIndex]);
            fprintf(outfile, "%s","\n}");
            fprintf(outfile, "\n%s", functionlist[classIndex]);




            classIndex++;

        }
        else
        {
            /*fputs(array[i],outfile);*/
        }
        i++;


    }

    printf("%s\n",  getFunctionPtr(NULL,"int fn(  int a,int b)","A") );
    fclose(outfile);
    fclose(infile);
	return 0;
}