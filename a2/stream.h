#define INPUT 256

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
