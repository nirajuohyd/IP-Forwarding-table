#include"rt.h"

/*main function definition*/
int main(int argc, char *argv[]){
	
	FILE *fp_route_entry,*fp_input,*fp_output;
	char str[16];

	if(argc < 4){			      
		printf("Three Command line argument required\n");
		printf("1.routing_entry 2.Traffic 3.output\n");
		exit(0);
	}
	
	fp_route_entry=openfile(argv[1],"r");
	fp_input=openfile(argv[2],"r");
	fp_output=openfile(argv[3],"w");
	readFile(fp_route_entry);
	search(fp_input, fp_output);

	return 0;
}
