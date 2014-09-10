#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


int main(int argc, char* argv[]){
	
	char* in_file = NULL;
	char* out_file = NULL;
	int opterr = 0;
	int c;	

	while((c = getopt(argc, argv, "io:")) != -1){
		switch(c){
			case 'i':
				printf("arg i\r\n");
				in_file = optarg;
				break;
			case 'o':
				printf("arg o\r\n");
				out_file = optarg;
				break;
			default:
				fprintf(stderr, "Error: Invalid command line option %c\r\n", c);
				break;
		}
	}


	return 0;
}
