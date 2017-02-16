#define INPUT 256
#define LARGE_BUFFER 2048
struct userPost
{
	char * username;
	char * streamname;
	char * date;
	char * text;
};

void readInput(char ** streamname,char ** text);
struct userPost * formatEntry(char * username, char * streamname, char * date, char *  text);
void getTimeDate(char ** DT);
void submitPost(struct userPost * post);
void freeUserPost(struct userPost * post);
void printPost(struct userPost * post);

int addUser(char * username, char * list);
int removeUser(char * username, char * list);

int isNum(char str);
int indexOfSpace(char * str);

int userExists(char * file, char * username);

