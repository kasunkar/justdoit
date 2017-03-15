#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "a3.h"


int main(int argc, char const *argv[])
{
	

	char * test = malloc(sizeof(char)*S_BUF);
	strcpy(test,"size=\"23\" action=\"action.php\"");
	printf("ssss\n");
	char * action = getParaVal(test,"action=");
	printf("%s\n", test);
	free(test);
	return 0;
}
