#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/*****Maximum length of single line*****/
#define MAX 100             

/*****Structure Table Declaration******/
struct forward_table {

	in_addr_t destination;
	in_addr_t mask;
	char getway[16];	
	char port[5];
	struct forward_table *next;
};

/*****FT is new Data Type in place of struct forward_table*****/
typedef struct forward_table FT; 

/****** FUNCTION PROTOTYPES ******/
FILE * openfile(const char *fname, char *mode);
FT * getNew(char *lptr);
void addToList(FT *ptr);
void readFile(FILE *fp);
void match(char *traffic, FILE *fp_output);
void search(FILE *fp_input, FILE *fp_output);
