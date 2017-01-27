/*cis*2750
Kasun Karunagoda
0830717
Assignment 1
*/

#define TOKEN 64
#define FXNPERCLASS 10
#define MAX 256 


char ** getArray(int size);

void extendArray(char *** array, int oldSize, int newSize);

int isClass(char * str);

int isDataType(char * str);

void printTokens(char ** array,int size);

int classToStruct();

int openBrace(char * str);

int closeBrace(char * str);

int delimiter(char  c);


int isRealClass(char **  array, int i);


char ** reduceWhiteSpace(char *** array, int size, int * newSize);

int countBlanks(char ** array, int size);

int isWhiteChar(char c);
