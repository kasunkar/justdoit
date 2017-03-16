#define S_BUF 128
#define L_BUF 1024

int indexOf(char * str, char c);
char *  getParaVal(char * str, char * paraName);
int isDelimiter(char c);
char * getQuotedVal(char * str);
int countDots(char * str);
char * getSizePara(char * str);
void printVal(char * str);
char * getNextTag(char * line,int *start);

