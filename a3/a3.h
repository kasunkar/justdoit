#define S_BUF 128
char *  getSizePara(char * str);
char *  getLinkPara(char * str);
char *  getTextPara(char * str);
char *  getFilePara(char * str);
char *  getNamePara(char * str);
char *  getActionPara(char * str);
char *  getValuePara(char * str);

int indexOf(char * str, char c);
char *  getParaVal(char * str, char * paraName);
int isDelimiter(char c);
char * getQuotedVal(char * str);