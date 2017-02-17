#include <stdio.h>
#include <stdlib.h>
#include "stream.h"
#include <time.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	char * list = malloc(sizeof(char)*INPUT);
	char * author = malloc(sizeof(char)*INPUT);
	if (argv[1]==NULL)
	{
		printf("no author\n");
		return 0;
	}

	if(strcmp(argv[1],"-r")==0)
	{
		strcpy(author,argv[2]);
		
	}else
	{
		strcpy(author,argv[1]);
	}

	printf("list streams: ");
	fgets(list,INPUT,stdin);
	list[strlen(list)-1]='\0';


	if(strcmp(argv[1],"-r")==0)
	{
		removeUser(author,list);
		
	}else
	{
		addUser(author,list);
	}
	
	free(list);
	free(author);

	return 0;
}