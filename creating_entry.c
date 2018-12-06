#include "rt.h"

/***** Head of Link list *****/ 
FT *head=NULL;

/*****Open file in specified mode and return File pointer*****/ 
FILE * openfile(const char *fname, char *mode){
	FILE *fp=NULL;
	fp=fopen(fname,mode);
	if(fp==NULL){
		printf("failed to open file %s \n",fname);
		exit(0);
	}
	else{
		return fp;
	}
}

/***************************************************************
*Parse a line to get destination address, subnet mask, getway address and port
*return a new allocated list node
***************************************************************/
FT * getNew(char *lptr){

	char dest[17],mask[17],getway[17],e_port[6];
	FT *ptr=NULL;
	sscanf(lptr,"%s%s%s%s",dest,mask,getway,e_port);
	dest[strlen(dest)-1]='\0';
	mask[strlen(mask)-1]='\0';
	getway[strlen(getway)-1]='\0';
	ptr=(FT*)malloc(sizeof(FT));
	if(ptr==NULL){
		printf("Memory not available");
		exit(0);
	}
	else{
		ptr->destination=inet_addr(dest);
		ptr->mask=inet_addr(mask);
		strcpy(ptr->getway,getway);
		strcpy(ptr->port,e_port);
		ptr->next=NULL;
	}
return ptr;
}

/***** read a new line each time called *****/
void readFile(FILE *fp){
	char line[MAX];
	
	while((fgets(line,MAX,fp))!=NULL){
		FT *new=getNew(line);
		addToList(new);
		memset(line,0,MAX);

	}

}

/*******************************************************************
*add node in list in sorted order on subnet mask value
*longest mask node come first
*******************************************************************/
void addToList(FT *ptr){
	FT *temp=NULL,*prev=NULL;
	
	if(head==NULL){
		head=ptr;
	}
	else if((ptr->mask)>=(head->mask)){

		ptr->next=head;
		head=ptr;
	}
	else{
		
		temp=head;
		while( ( temp!=NULL) && (ptr->mask) < (temp->mask)){
			prev=temp;
			temp=temp->next;
			
		}
		
		prev->next=ptr;
		ptr->next=temp;
	}
	
	
}

/***** Match a IP in list and print gateway and port address in output file *****/
void match(char *traffic, FILE *fp_output){
	in_addr_t ip,m,d;
	ip=inet_addr(traffic);
	FT *temp=NULL;
	temp=head;
	while(temp!=NULL){
		m=temp->mask;
		d=temp->destination;
		if(d==(m&ip)){
			fprintf(fp_output,"%-17s %-5s \n",temp->getway,temp->port);
			break;
		}
		temp=temp->next;
	}
}
	
/***** Read Traffice from file and match in routing table *****/
void search(FILE *fp_input, FILE *fp_output){
	
	int c=0;
	char ipaddr[16];
	while((c=fscanf(fp_input,"%s",ipaddr))!=EOF){
		match(ipaddr,fp_output);
	}
}

