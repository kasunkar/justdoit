#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "a1h.h"

char ** getArray(int size)
{
	char ** array = malloc(sizeof(char*)*size);
	int i=0;
	for ( i = 0; i < size; i++)
	{
		array[i] = malloc(sizeof(char)*TOKEN_SIZE);
		
	}

	return array;
}

char ** getList(int size)
{
	char ** array = malloc(sizeof(char*)*FN_PER_CLASS);
	int i=0;
	for ( i = 0; i < FN_PER_CLASS; i++)
	{
		array[i] = malloc(sizeof(char)*size);
		
	}

	return array;
}

void extendArray(char *** array, int oldSize, int newSize)
{
	*array = (char **)realloc(*array,(sizeof(char *)*newSize));
	
	int i =0;
	for(i=oldSize;i<newSize;i++)
	{
		((*array)[i])=malloc(sizeof(char)*TOKEN_SIZE);
		
	}
}
void printTokens(char ** array,int size)
{
	int i=0;

	for ( i = 0; i < size; i++)
	{
			printf("%s\n", array[i]);
		
	}
}
int isEnd(char * str)
{
	if(str[strlen(str)-1]==';')
		return 1;
	return 0;
}

void showWhiteSpace(char ** array, int index)
{
	int i=0;
	
		for(i=0;i<strlen(array[index]);i++)
		{
			if(array[index][i]==' '){
				printf("~BLANK_SPACE~");
			}
			else if (array[index][i]=='\n'){
				printf("~NEW_LINE~");
			}
			else if (array[index][i]=='\t'){
				printf("~TAB_ULAR~");
			}
			else
			{
				printf("%c", array[index][i]);
			}
		}
}

int isDataType(char * str)
{
	int i;
	char * list[6] = {"int","float","char","double","short","void"};
	
	for(i=0;i<6;i++)
	{
		if(strcmp(list[i],str)==0)
			return 1;
	}

	return 0;
}

int isWhiteChar(char c)
{
	if(c == ' ' || c=='\n' || c=='\t')
		return 1;

	return 0;
}

int delimiter(char  c)
{
	if(c==' ' || c=='\t'||  c=='\n' || c=='{' || c=='}'|| c=='(' || c==')'|| c==','|| c=='\"')
		return 1;
	
	return 0;
}

int openParan(char * str)
{
	if(strcmp(str,"(")==0)
		return 1;

	return 0;
}

int closeParan(char * str)
{
	if(strcmp(str,")")==0)
		return 1;

	return 0;
}

int openBrace(char * str)
{
	if(strcmp(str,"{")==0)
		return 1;

	return 0;
}

int closeBrace(char * str)
{
	if(strcmp(str,"}")==0)
		return 1;

	return 0;
}


int isQuotes(char c)
{
	if(c=='\"')
		return 1;

	return 0;
}

int isEscaped(char c)
{
	if(c=='\\')
		return 1;

	return 0;
}

int isBlank(char * str)
{
	int i=0;
	for(i=0;i<strlen(str);i++)
	{
		if(str[i]!=' ' || str[i]!='\n' ||str[i]!='\t')
			return 0;
	}
	return 1;
}
int isClass(char * str)
{

	if(strcmp(str,"class")==0)
		return 1;


	return 0;
}

int printStruct(FILE * outfile, char * content)
{
	fprintf(outfile, "struct{\n%s\n};",content );
}


int isRealClass(char **array, int index)
{
	if(isClass(array[index]))
	{
	    if(openBrace(array[index+4]) || openBrace(array[index+3]))
	    {
	    	
	    	return 1;
	    }
	}
	return 0;
}



char * getFunctionPtr(FILE * fp,char * fnList, char* class)
{
	char * fnPtr = malloc(sizeof(char) *MAX);
	int fnPtrIndex=0;
	char token[MAX];
	int tokenIndex=0;
	
	int i=0;
	fnPtrIndex = strlen(fnPtr);
	while(fnList[i]!=' ')
	{
		fnPtr[fnPtrIndex] = fnList[i];
		fnPtrIndex++;
		i++;
		fnPtr[fnPtrIndex]='\0';

	}
	i++;
	strcat(fnPtr," ");
	strcat(fnPtr,class);
	fnPtrIndex = strlen(fnPtr);
	while(fnList[i]!='(')
	{
		fnPtr[fnPtrIndex]=fnList[i];
		i++;
		fnPtrIndex++;
		fnPtr[fnPtrIndex]='\0';
		
	}
	i++;
	while(fnList[i]!=')')
	{
		

		//printf("in close char is:%c\n",fnList[i]);
		if(fnList[i]==' ' || fnList[i]==',')
		{
			//printf("in space data is: %s\n",token);
			if(isDataType(token))
			{
				//printf("is isDataType token is: %s\n",token);
				fnPtr[fnPtrIndex]=token[0];
				fnPtrIndex++;
			    fnPtr[fnPtrIndex]='\0';
				
			}
			memset(token,'\0',MAX);
			tokenIndex=0;

		}

		if(fnList[i]==',' || fnList[i]==' ')
		{
			memset(token,'\0',MAX);
			tokenIndex=0;
		}else
		{
			token[tokenIndex]=fnList[i];
		    tokenIndex++;
	        token[tokenIndex]='\0';
		}
		

		i++;	
	}

	return fnPtr;
}


void printFnPtrs(FILE * fp, char * fnList)
{
	char temp[MAX*FN_PER_CLASS];
	strcpy(temp,fnList);
	int i=0;
	int j=0;

	int * indexOfFns = fnLimits(fnList);
	int indexOfParan[indexOfFns[0]+1];
	int fnCount=indexOfFns[0];
	indexOfParan[0]=fnCount;

	while(fnList[i]!=')')
	{
		temp[j]=fnList[i];
		i++;
		j++;
		temp[j]='\0';
	}
	temp[j]=fnList[i];
	i++;
	j++;
	temp[j]='\0';
	/*first fn pointer is in temp made*/
	printf("fn%d: %s\n",0,temp);
	
	
	if(fnCount==1)
		return;


	

	for(i=1;i<fnCount;i++)
	{
		indexOfParan[i]=nextCloseParan(&fnList[indexOfFns[i]])+1;
		indexOfParan[i]=indexOfParan[i]+indexOfFns[i];
	}

	for(i=0;i<fnCount;i++)
	{
		char fnTemp[MAX];
		int tempIndex=0;
		int j=0;
		for(j=indexOfFns[i]+1;j<indexOfParan[i];j++)
		{
			fnTemp[tempIndex]=fnList[j];
			tempIndex++;
			fnTemp[tempIndex]='\0';
		}
		printf("fn%d: %s\n",i,fnTemp);

	}
	
	
}


int * fnLimits(char * fnList){

	int i =0;
	int j=0;
	int count = 0;

	for(i=0;i<strlen(fnList);i++)
	{
		if(fnList[i]=='~')
			count++;
	}

	int * indexes = malloc(sizeof(int)*count+1);
	indexes[0]=count;
	i=0;
	count=1;
	for(i=0;i<strlen(fnList);i++)
	{
		if(fnList[i]=='~')
		{
			indexes[count]=i;
			count++;
		}
	}
	return indexes;
}

int nextCloseParan(char * str)
{
	int i=0;
	while(str[i]!=')')
	{
		i++;
	}

	printf("\n");
	return i;
}
