#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "a3.h"

char *  getParaVal(char * str, char * paraName){
	char * paraVal;
	char * buffer = malloc(sizeof(char)*S_BUF);
	int j=0;
	int i =0;
	while(i<strlen(str)){
		if(isDelimiter(str[i])){
			if(strncmp(paraName,buffer,indexOf(buffer,'=')-1)==0)
			{
				paraVal =  getQuotedVal(buffer);
				printf("INNER %s\n", paraVal);
			}else
			{
				memset(buffer,'\0',S_BUF);
				j=-1;
			}
		}
		j++;
		i++;
	}
	free(buffer);
	return paraVal;
}

char * getQuotedVal(char * str){
	char * val = malloc(sizeof(char)*S_BUF);
	int i = 0;
	int j=0;
	int flag =0;
	
	while(i<strlen(str)){
		printf("%c\n",str[i]);
		
		if(str[i]=='\"')
		{
			i++;
			flag++;
		}
		

		if(flag==1){
			printf("getting copied\n");
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
			return i+1;
		}
		i++;
	}
	return -1;
}
/*
char *  getLinkPara(char * str);
char *  getTextPara(char * str);
char *  getFilePara(char * str);
char *  getNamePara(char * str);
char *  getActionPara(char * str);
char *  getValuePara(char * str);

*/

int isDelimiter(char c)
{
	if(c==' ')
		return 1;

	return 0;
}