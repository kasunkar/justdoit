#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "a3.h"

char *  getParaVal(char * str, char * paraName){
	char * paraVal=NULL;
	char * buffer = malloc(sizeof(char)*S_BUF);
	memset(buffer,'\0',S_BUF);
	int j=0;
	int i =0;


	while(i<strlen(str)){
		
		if(str[i]==','|| i==strlen(str)-1){
			
			if(i==strlen(str)-1)
				buffer[j]=str[i];
			if(strncmp(paraName,buffer,indexOf(buffer,'=')+1)==0)
			{
				if(strcmp(paraName,"size=")==0)
				{
					paraVal=getSizePara(buffer);
					free(buffer);
					return paraVal;
				}else{
					paraVal =  getQuotedVal(buffer);
					free(buffer);
					return paraVal;
				}
			}
			memset(buffer,'\0',S_BUF);
			j=0;
			i++;
			
		}

		buffer[j]=str[i];
		j++;
		i++;
	}
	free(buffer);
	return paraVal;
}

void printVal(char * str)
{
	if(str==NULL)
	{
		printf("NULL STRING\n");
	}else{
		printf("%s\n", str);
	}

}

char * getSizePara(char * str)
{
	char *  size = malloc(sizeof(char)*S_BUF);
	memset(size,'\0',S_BUF);
	if(indexOf(str,'x')==-1)
	{
		size[0] = str[indexOf(str,'=')+1];
	}else
	{

		int i=indexOf(str,'=')+1;
		int j=0;
		while(isdigit(str[i]) || str[i]=='x')
		{
			size[j]=str[i];
			j++;
			i++;
		}
	}
	return size;
}

char * getNextTag(char * line,int *start)
{
	char * tag = malloc(sizeof(char)*S_BUF);
	int i=*start+1;
	int j=0;
	int end=0;
	while(end==0){		
		
		if(line[i]==')'){
			tag[j]=line[i];
			j++;
			i++;
			if(line[i]=='.'||line[i]=='\0'){
				end =1;
			}else{
				i--;
			}
		}
		if(end!=1)
		{
			tag[j]=line[i];
			j++;
			i++;
		}
	}
	tag[j]='\0';

	*start = i;
	return tag;
}

char * getQuotedVal(char * str){
	char * val = malloc(sizeof(char)*S_BUF);
	int i = 0;
	int j=0;
	int flag =0;
	
	while(i<strlen(str)){
		
		if(str[i]=='\"')
		{
			i++;
			flag++;
		}
		

		if(flag==1){
			val[j]=str[i];
			j++;
			val[j]='\0';
		}

		i++;
	}

	return val;

}

int indexOf(char * str, char c)
{
	int i =0;
	while(i<strlen(str))
	{
		if(str[i]==c)
		{
			return i;
		}
		i++;
	}
	return -1;
}
int countDots(char * str)
{
	int i=0;
	int count=0;

	while(i<strlen(str))
	{
		if(str[i]=='\"')
		{
			i++;
			while(str[i]!='\"'){
				i++;
			}
			i++;
		}
		if(str[i]=='.')
		{
			count++;
		}
		i++;
	}

	return count;
}
int isDelimiter(char c)
{
	if(c==',')
		return 1;

	return 0;
}