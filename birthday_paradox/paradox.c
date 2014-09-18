#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <stdint.h>

float birthday_paradox(int);
const float NUM_TRIALS = 1000.0;

int main(int argc, char* argv[]){
	
	char *in_file = NULL;
	char *out_file = NULL;
	FILE *in_f, *out_f;
	int opterr = 0;
	int c;
	int N_people;
	float probability;

	if(argc != 5){
		fprintf(stderr, "Usage: paradox -i inputfile -o outputfile\n");
	}

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
				fprintf(stderr, "Usage: paradox -i inputfile -o outputfile\n");
				exit(1);
				break;
		}
	}

	printf("Input file = %s\n", in_file);
	printf("Output file = %s\n", out_file);
	printf("Number of Trials = %f\n", NUM_TRIALS);

	in_f = fopen(in_file, "r");
	if( in_f == NULL){
		fprintf(stderr, "Error: Cannot open file %s\n", in_file);
		exit(1);
	}
	
	out_f = fopen(out_file, "w+");	
	if(out_f == NULL){
		fprintf(stderr, "Error: Cannot open file %s\n", out_file);
		exit(1);
	}

	while((fscanf(in_f, "%d", &N_people)) > 0){
		printf("Number of people: %d\n", N_people);
		probability = birthday_paradox(N_people);
		printf("\tprobability = %.2f\n", probability);
		fprintf(out_f, "%.2f\n", probability);
	}	

	fclose(in_f);
	fclose(out_f);

	return 0;
}

float birthday_paradox(int N_people){
	int gen, i, j, k;	
	int gen_buff[N_people];
	float pos = 0;
	uint8_t match = 0;	
	float probability = 0.0;
	
	srand(getpid() % N_people);

	printf("pid = %i\n", getpid());
	
	// Perform NUM_TRIALS (1000)
	for(i = 0; i < 1000; i++){
		match = 0;
		j = 0;

		while((j < N_people) && (!match)){
			k = 0;
			
			
			gen = (rand() % 365) + 1;
			
			//printf("%i\n", gen);
			while((k < j) && (!match)){
				if(gen_buff[k] == gen){
					match = 1;
					pos = pos + 1;
				}
				k++;
			}
			gen_buff[j] = gen;
			j++;
		}
	}
	
	printf("Positive = %f\n", pos); 

	probability = pos / NUM_TRIALS;	

	return probability;
}
