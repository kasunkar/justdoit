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
		array[i] = malloc(sizeof(char)*TOKEN);
		sprintf(array[i],"%d",i);
	}

	return array;
}

void extendArray(char *** array, int oldSize, int newSize)
{
	*array = realloc(*array,(sizeof(char *)*newSize));
	int i =0;
	for(i=oldSize;i<newSize;i++)
	{
		(*array)[i]=malloc(sizeof(char)*TOKEN);
		sprintf((*array)[i],"%d",i);
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
	if(str[strlen(str)-1]==";" || str[strlen(str)-1]==",")
		return 1;
	return 0;
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
int isBlank(char * str)
{

	if(strcmp(str," ")==0)
		return 1;


	return 0;
}
int isClass(char * str)
{

	if(strcmp(str,"class ")==0)
		return 1;


	return 0;
}

int printStruct(FILE * outfile, char * content)
{
	fprintf(outfile, "struct{\n%s\n};",content );
}
