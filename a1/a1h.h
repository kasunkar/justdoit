/*cis*2750
Kasun Karunagoda
0830717
Assignment 1
*/

#define TOKEN 64
#define FXNPERCLASS 10

char ** getArray(int size);

void extendArray(char *** array, int oldSize, int newSize);

int isClass(char * str);

int isDataType(char * str);

void printTokens(char ** array,int size);

int classToStruct();

int openBrace(char * str);

int closeBrace(char * str);

int delimiter(char  c);

