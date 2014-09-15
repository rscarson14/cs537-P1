#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>

int main(int argc, char* argv[]){
	
	char* in_file = NULL;
	char* out_file = NULL;
	int fd_in;
	int fd_out;
	int opterr = 0;
	int c;	

	assert(argc == 5);

	while((c = getopt(argc, argv, "i:o:")) != -1){
		switch(c){
			case 'i':
				printf("arg i = %s\n", optarg);
				in_file = optarg;
				break;
			case 'o':
				printf("arg o = %s\n", optarg);
				out_file = optarg;
				break;
			default:
				fprintf(stderr, "Error: Invalid command line option %c\r\n", c);
				break;
		}
	}

	printf("Input file = %s\n", in_file);
	printf("Output file = %s\n", out_file);

	if((fd_in = open(in_file, O_RDONLY)) < 0){
		fprintf(stderr, "Error opening file %s for reading\n", in_file);
	}

	if((fd_out = open(out_file, O_CREAT | O_RDWR | O_TRUNC, S_IWUSR | S_IRUSR)) < 0){
		fprintf(stderr, "Error opening file %s for writing\n", out_file);
	}

	close(fd_in);
	close(fd_out);

	return 0;
}
