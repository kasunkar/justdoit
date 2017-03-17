#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "a3.h"


int main(int argc, char const *argv[])
{
	char header [] = "<!DOCTYPE html>\n<html>\n<body>\n";
	FILE * html = fopen("a3.html","w");
	fputs(header,html);
	char * test = malloc(sizeof(char)*S_BUF);
	strcpy(test,".b(name=\"btn12\",link=\"facebook.com\"");
	/*char * action = getParaVal(test,"name=");
	
	printVal(action);*/
	free(test);
	/*free(action);
	.b  .d  .e  .h  .i  .l  .p  .r  .t*/

	char * line = malloc(sizeof(char)*L_BUF);
	int i=0;
	FILE * fp = fopen("config.wpml","r");
	char c = fgetc(fp);
	int end=0;
	while(end==0)
	{

		if(c=='\n' || c==EOF)
		{
			if(c==EOF){
				end=1;
			}else{
				c=fgetc(fp);
			}
			line[i]='\0';
			char * tag;
			if(line[0]=='.'){
				int start = 0;
				int numTags = countDots(line);
				char * tagStack= malloc(sizeof(char)*numTags+1);
				memset(tagStack,'\0',numTags+1);
				int k=0;
				for(k=0;k<numTags;k++){
					tag = getNextTag(line,&start);
					tagStack[k]=tag[0];
					tagStack[k+1]='\0';
					writeToPage(html,tag);
					fputs("\n<br>\n",html);
					/*tag is some tag that starts with a .
*/					
					free(tag);
				}
				closeTags(html,tagStack,k);
				
				free(tagStack);
			}else{
				if(line[0]!=EOF)
				{
					fputs(line,html);
					fputs("\n",html);
				}
			}
			memset(line,'\0',L_BUF);
			i=0;
		}

		line[i]=c;
		i++;
		c = fgetc(fp);

	}
	strcpy(line,"\n</body>\n</html>\n");
	fputs(line,html);
	free(line);
	fclose(html);
	fclose(fp);
	return 0;
}
