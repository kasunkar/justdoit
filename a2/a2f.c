#include <stdio.h>
#include <stdlib.h>
#include "a2h.h"
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

void printPost(struct userPost * post)
{
	printf("Author:%s\n",post->username);
	printf("Stream:%s\n",post->streamname);
	printf("Date:%s\n",post->date);
	printf("Text:%s\n",post->text);
}