#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>

#define NUM_TRIALS 1000

float birthday_paradox(int);

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
		printf("\tprobability = %f\n", probability);
		fprintf(out_f, "%f\n", probability);
	}	

	fclose(in_f);
	fclose(out_f);

	return 0;
}

float birthday_paradox(int N_people){
	int gen, i, j, k;	
	int gen_buff[N_people];
	float pos = 0;
	int match = 0;	
	float probability = 0.0;
	time_t t;
	
	// Perform NUM_TRIALS (1000)
	for(i = 0; i < NUM_TRIALS; i++){
		match = 0;
		j = 0;
		srand((unsigned) time(&t));

		// For each person, generate a random number and compare it to previously generated
		// numbers.
		while(j < N_people && !match){
			
			gen = (rand() % 365) + 1;

			// If there is a match, increment the positive counter and exit loop (set
			// match to 1);
			k = 0;
			while(k < j && !match){
				if(gen_buff[k] == gen){
					match = 1;
					printf("MATCH %i == %i\n", gen, gen_buff[k]);
				}
				k++;
			}
			gen_buff[j] = gen;
			j++;
		}
		if(match == 1){
			pos++;
		}		
	}
	
	for(i = 0; i < 1000; i++){
		printf("%i\n", gen_buff[i]);
	}
	
	printf("Positive = %f\n", pos); 

	probability = pos / (float) NUM_TRIALS;	

	return probability;
}
