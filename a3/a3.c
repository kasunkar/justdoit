#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "a3.h"


int main(int argc, char const *argv[])
{
	char header [] = "!DOCTYPE html\n<html>\n<body>\n";
	FILE * html = fopen("a3.html","w");
	fputs(header,html);
	char * test = malloc(sizeof(char)*S_BUF);
	strcpy(test,"action=\"action.php\"");
	char * action = getParaVal(test,"action=");
	
	printVal(action);
	free(test);
	free(action);
	/*.b  .d  .e  .h  .i  .l  .p  .r  .t*/

	/*char * line = malloc(sizeof(char)*L_BUF);
	int i=0;
	FILE * fp = fopen("config.wpml","r");
	char c = fgetc(fp);
	
	while(c!=EOF)
	{
		if(c=='\n')
		{
			line[i]='\0';
			printf("%d\n", countDots(line));
			memset(line,'\0',L_BUF);
			i=0;
		}
		line[i]=c;
		i++;
		c = fgetc(fp);

	}
	printf("%d\n", countDots(line));
	
	char footer [] = "</body>\n</html>\n";
	fputs(footer,html);
	fclose(html);
	fclose(fp);*/
	return 0;
}
