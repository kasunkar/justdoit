/*cis*2750
Kasun Karunagoda
0830717
Assignment 1
*/

#define TOKEN_SIZE 64
#define FN_PER_CLASS 32
#define MAX 256 


char ** getArray(int size);

char ** getList(int size);

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

void showWhiteSpace(char ** array,int size);

int isQuotes(char c);

int isEscaped(char c);