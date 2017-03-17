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
	int i =2;
/*
	printf("%s\t\t%s\n", str,paraName);
*/
	while(i<strlen(str)){
		
		if(str[i]==','|| i==strlen(str)-1)
		{
			if(i==strlen(str)-1){
				buffer[j]=str[i];
			}
			if(strncmp(paraName,buffer,indexOf(buffer,'=')+1)==0)
			{
				/*printf("matched tag: %s\n",buffer );
				*/
				if(strcmp(paraName,"size=")==0)
				{
					paraVal=getSizePara(buffer);
					free(buffer);
					return paraVal;
				}else{
					paraVal =  getQuotedVal(buffer);
					
					free(buffer);
				/*	printf("FINAL: %s\n",paraVal);
				*/	
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

void writeToPage(FILE * fp, char * tag)
{
	char * html = malloc(sizeof(char)*L_BUF);
	if(tag[0]=='b'){
		char * name = getParaVal(tag,"name=");
		char *link = getParaVal(tag,"link=");
		char * final = malloc(sizeof(char)*L_BUF);

		sprintf(final,"<form action=\"%s\">\n\t <input type=\"submit\" value=\"%s\"/>\n</form>\n",link,name);

		fputs(final,fp);
		free(name);
		free(link);
		free(final);
	}
	else if(tag[0]=='d'){
		fputs("<hr>\n",fp);
	}	
	else if(tag[0]=='e'){

	}
	else if(tag[0]=='h'){
		char * size = getParaVal(tag,"size=");
		if(size==NULL)
		{
			size = malloc(sizeof(char)*S_BUF);
			memset(size,'\0',S_BUF);
			strcpy(size,"3");
		}

		char * text = getParaVal(tag,"text=");
		if(text==NULL)
		{
			text = malloc(sizeof(char)*S_BUF);
			memset(text,'\0',S_BUF);
			strcpy(text,"HEADING");
		}

		char * final = malloc(sizeof(char)*L_BUF);


		sprintf(final,"<h%s>%s",size,text);
		fputs(final,fp);
		free(text);
		free(size);
		free(final);

	}
	else if(tag[0]=='i'){
		char * action=getParaVal(tag,"action=");
		if(action==NULL)
		{
			action = malloc(sizeof(char)*S_BUF);
			memset(action,'\0',S_BUF);
		}
		char * text=getParaVal(tag,"text=");
		char * name=getParaVal(tag,"name=");
		char * value=getParaVal(tag,"value=");

		<form action="/action_page.php">
	  	First name: <input type="text" name="fname"><br>
	  	Last name: <input type="text" name="lname"><br>
	  	<input type="submit" value="Submit">
		</form>

	}
	else if(tag[0]=='l'){

		char * final = malloc(sizeof(char)*L_BUF);
		char * link = getParaVal(tag,"link=");
		char * text = getParaVal(tag,"text=");


		sprintf(final,"<a href=\"%s\">%s</a>",link,text);
		fputs(final,fp);
		free(link);
		free(text);
		free(final);
	}
	else if(tag[0]=='p'){

	}
	else if(tag[0]=='r'){

	}
	else if(tag[0]=='t'){
		char * text = getParaVal(tag,"text=");
		if(text==NULL)
		{
			text = malloc(sizeof(char)*S_BUF);
			memset(text,'\0',S_BUF);
			strcpy(text,"Default text");
		}

		char * file = getParaVal(tag,"file=");
		
		char * final = malloc(sizeof(char)*L_BUF);

		if(file==NULL)
		{
			sprintf(final,"<textarea>%s</textarea>",text);
			fputs(final,fp);
		}else
		{
			sprintf(final,"<textarea>%s</textarea>",file);
			fputs(final,fp);
			
			
		}


		free(text);
		free(file);
		free(final);

	}

	free(html);
}
void closeTags(FILE * fp, char * tagStack, int count)
{
	int i=count;
	for (i = count; i > -1; i--)
	{

		else if(tagStack[i]=='h'){
			fputs("<\\h3>\n",fp);
		}
		else if(tagStack[i]=='p'){

		}
		else if(tagStack[i]=='r'){

		}
		else if(tagStack[i]=='t'){

		}
	}
		
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
		
		if(str[i]=='\\')
		{
			i++;
			val[j]=str[i];
			j++;
			val[j]='\0';
			i++;
		}

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