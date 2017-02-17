#include <stdio.h>
#include <stdlib.h>
#include "stream.h"
#include <time.h>
#include <string.h>

int main(int argc, char const *argv[])
{

	char * buffer = malloc(sizeof(char)*INPUT); 
	char * text = malloc(sizeof(char)*INPUT);
	char * streamname = malloc(sizeof(char)*INPUT); 
	char * author = malloc(sizeof(char)*INPUT); 
	char * datetime = malloc(sizeof(char)*INPUT);
	strcpy(author,argv[1]);


	
	if(argv[1]== NULL)
	{
		printf("no author\n");
		return 0;
	}
	
		
	
	
	readInput(&streamname,&text);
	getTimeDate(&datetime);
	
	struct userPost * post = formatEntry(author, streamname,datetime,text);

	int ret = submitPost(post);

	if(ret == 0)
		printf("no stream \n");
	if(ret==-1)
		printf("not authorized\n");

	freeUserPost(post);
	free(buffer);
	free(text);
	free(streamname);
	free(author);
	free(datetime);

	return 0;
}
