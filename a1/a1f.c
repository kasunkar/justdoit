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
		sprintf(array[i],"%d",i);
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
	char * list[6] = {"int ","float ","char ","double ","short ","void "};
	
	for(i=0;i<4;i++)
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


/*int isRealClass(char **  array, int i)
{

	if(array[])

}*/

char ** reduceWhiteSpace(char *** array, int size, int *newSize)
{
	char ** reducedArray = malloc(sizeof(*(*array)));
	int i = 0;

	for(i=0;i<size;i++)
	{
		reducedArray[i]=malloc(sizeof(char)*MAX);

	} 

	i=0;
	int j=0;
	char blanks[MAX];
	while(i<size)
	{

		strcpy((*array)[i],reducedArray[j]);
		j++;
		i++;
		/*if(!isBlank((*array)[i]))
		{
			strcpy((*array)[i],reducedArray[j]);
			j++;
		}else
		{
			while(isBlank((*array)[i]))
			{
				strcat(blanks,(*array)[i]);
				i++;
			}

			strcpy(reducedArray[j],blanks);
			j++;
		}*/
	}

	*newSize = j;
	return reducedArray;
}

int countBlanks(char ** array, int size)
{
	int i =0;
	int count=0;
	for (i = 0; i < size; i++)
	{
		if(isBlank(array[i]))
			count++;
	}

	return count;
}

