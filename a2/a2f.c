#include <stdio.h>
#include <stdlib.h>
#include "stream.h"
#include <string.h>
#include <time.h>

void readInput(char ** streamname, char ** text)
{
	int bufferLen=0;
	int textLen = 0;
	int curLen=INPUT;
	char * buffer  = malloc(sizeof(char)*INPUT);
	
	printf("Stream: ");
	fgets(buffer,INPUT,stdin);
	buffer[strlen(buffer)-1]='\0';
	strcpy(*streamname,buffer);
	printf("enter text: ");
	memset(buffer,'\0',INPUT);

	while(fgets(buffer,INPUT,stdin))
	{
		printf("-");
		bufferLen = strlen(buffer);
		textLen = textLen + bufferLen;
		if(textLen >= curLen )
		{
			curLen=curLen+INPUT;
			*text =realloc(*text,sizeof(char)*curLen);
		}

		strcat(*text,buffer);			
	}

	free(buffer);
}

void  getTimeDate(char ** DT)
{
	struct tm *  tm;
	time_t rawtime;
	char * datetime = malloc(sizeof(char)*INPUT);
	rawtime = time(NULL);
	tm  = localtime(&rawtime);
	strftime(datetime,INPUT,"%b. %d, %G %I:%M %p",tm);
	strcpy(*DT,datetime);
	free(datetime);

}

struct userPost * formatEntry(char * username, char * streamname, char * date, char *  text)
{
	struct userPost * post = malloc(sizeof(struct userPost));
	post->username = malloc(sizeof(char)*strlen(username));
	post->streamname = malloc(sizeof(char)*strlen(streamname));
	post->date = malloc(sizeof(char)*strlen(date));
	post->text = malloc(sizeof(char)*strlen(text));

	strcpy(post->username,username);
	strcpy(post->streamname,streamname);
	strcpy(post->date,date);
	strcpy(post->text,text);

	return post;

}


void freeUserPost(struct userPost * post)
{
	free(post->username);
	free(post->streamname);
	free(post->date);
	free(post->text);
	free(post);

}

int addUser(char * username, char * list)
{
	char * file = malloc(sizeof(char)*INPUT);
	int i =0;
	int j=0;
	while(list[i]!='\0')
	{
		if(list[i]==',')
		{
			strcat(file,"StreamUsers");
			FILE * fp = fopen(file,"a");
			if(fp == NULL)
				fp = fopen(file,"w+");
				
			if(!userExists(file,username))
			{	
			
				fputs(username,fp);
				fputs(" 0\n",fp);
			}
			fclose(fp);
			memset(file,'\0',INPUT);
			j=0;
			i++;

		}
		file[j]=list[i];
		j++;
		i++;
	}

	strcat(file,"StreamUsers");
	FILE * fp = fopen(file,"a");
	if(fp == NULL)
		fp = fopen(file,"w+");

	if(!userExists(file,username))
	{			
		fputs(username,fp);
		fputs(" 0\n",fp);		
	}
	
	fclose(fp);
	free(file);
	return 1;
}

int isNum(char str)
{
	if(str=='0' || str=='1' || str=='2'||str=='3' || str=='4'||str=='5' || str=='6'||str=='7' || str=='8' || str=='9')
	{
		return 1;
	}
	return 0;
}

int indexOfSpace(char * str)
{
	int i =0;
	while(i<strlen(str))
	{
		if(str[i]==' ')
		{
			return i-1;
		}
		i++;
	}
	return 0;
}
int removeUser(char * username, char * list)
{

	int i=0;
	int j=0;
	char * file = malloc(sizeof(char)*INPUT);
	char * outStr = malloc(sizeof(char)*LARGE_BUFFER);
	
	while(i<strlen(list))
	{
		if(list[i]==',' || i==strlen(list)-1)
		{
			if(i==strlen(list)-1)
				file[j]=list[i];
			
			strcat(file,"StreamUsers");
			
			FILE * fp = fopen(file,"r");
			if(fp!=NULL)
			{
				char * currentName = malloc(sizeof(char)*INPUT);
					
				while(fgets(currentName,INPUT,fp))
				{
					printf("%s\n", currentName);
					if(strncmp(currentName,username,indexOfSpace(currentName))!=0)
					{
						strcat(outStr,currentName);
					}	
				}

				free(currentName);
				fclose(fp);
				
				fp = fopen(file,"w");
				strcat(outStr,"\n");
				fputs(outStr,fp);
				fclose(fp);
				memset(outStr,'\0',LARGE_BUFFER);
				
				
				memset(file,'\0',INPUT);
				j=0;
			}
		}else if (list[i]!=' ')
		{
			file[j]=list[i];
			j++;
		}
		i++;
	}
	free(outStr);
	free(file);
	return 1;
}

int userExists(char * file, char * username)
{
	char * currentName = malloc(sizeof(char)*INPUT);
	FILE * fp = fopen(file,"r");
	if(fp==NULL)
	{
		free(currentName);
		fclose(fp);	
		return -1;
	}

	char c = fgetc(fp);
	int i=0;
	while(c!=EOF)
	{
		if(c==' ' || c=='\n')
		{
			currentName[i]='\0';
			if(strcmp(currentName,username)==0)
			{
				free(currentName);
				fclose(fp);
				return 1;
			}
			i =0;
			memset(currentName,'\0',INPUT);
		}else
		{
			currentName[i]=c;
			i++;
		}
		c=fgetc(fp);
	}


	free(currentName);
	fclose(fp);
	return 0;
}

void printPost(struct userPost * post)
{
	printf("Author:%s\n",post->username);
	printf("Stream:%s\n",post->streamname);
	printf("Date:%s\n",post->date);
	printf("Text:%s\n",post->text);
}

int updateStream(struct userPost * post)
{
	
	char * file = malloc(sizeof(char)*INPUT);
	char * temp = malloc(sizeof(char)*LARGE_BUFFER);
	strcpy(file,post->streamname);
	strcat(file,"Stream");
	FILE * fp = fopen(file,"a");
	sprintf(temp, "Sender: %s\nDate: %s\n%s", post->username,post->date,post->text);
	fprintf(fp, "Sender: %s\nDate: %s\n%s", post->username,post->date,post->text);
	fclose(fp);
	
	strcat(file,"Data");
	FILE * fp2 = fopen(file,"a+");

	char * numbers = malloc(sizeof(char)*INPUT);

	while(fgets(numbers,INPUT,fp2));

	if(isNum(numbers[0]))
	{
		int lastNum=0;
		sscanf(numbers,"%d",&lastNum);
		//printf("not first entry lastNum: %d\n",lastNum );
		int newNum = lastNum + strlen(temp);
		fprintf(fp, "%d\n", newNum);

	}else
	{
		int newNum =  strlen(temp)-2;
		fprintf(fp, "%d\n", newNum);
	}
	free(temp);
	free(numbers);
	free(file);
	fclose(fp2);
}

int submitPost(struct userPost * post)
{
	char * file = malloc(sizeof(char)*INPUT);
	char * currentName = malloc(sizeof(char)*INPUT);
	strcpy(file,post->streamname);
	strcat(file,"StreamUsers");
	int match=0;
	FILE * fp = fopen(file,"r");
	if(fp==NULL)
	{
		free(currentName);
		free(file);
		return 0;
	}

	if(userExists(file,post->username))
	{
		updateStream(post);
	}else
	{
		free(currentName);
		free(file);
		fclose(fp);
		return -1;
	}
	
	free(currentName);
	free(file);
	fclose(fp);
	return 1;
}
