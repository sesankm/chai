#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "perceptron.h"

int parseArgs(int, char**, char**, int*, int*, float*, int*);

int main(int argc, char** argv){
	char* fileName = malloc(sizeof(char) * 250);
	int dimSize = 0;
	int trainDataSize = 0;
	float learningRate = 0.005;
	int numEpochs = 1000;

	if(parseArgs(argc, argv, &fileName, &dimSize, &trainDataSize, &learningRate, &numEpochs) < 0) {
		return -1;
	}

	Perceptron p = createPerceptron(dimSize, trainDataSize, learningRate);
	readInputData(fileName, &p);
	p.error = 1;

	for(int i = 0; i < numEpochs; i++) {
		epoch(&p);
	}

	predict(p);
	return 0;
}


int parseArgs(int argc, char** argv, char** fileName, int* dimSize, int* trainDataSize, float* learningRate, int* numEpochs){
	if(argc < 4 || argc > 6) {
		printf("Error: Invalid usage.\n");
		printf("Examples: \n");
		printf("\t./NN -f{testDataFilePath} -d{dimensionSize} -t{trainDataSize}\n");
		printf("\t./NN -f{testDataFilePath} -d{dimensionSize} -t{trainDataSize} -l{learningRate}\n");
		printf("\t./NN -f{testDataFilePath} -d{dimensionSize} -t{trainDataSize} -l{learningRate} -e{numEpochs}\n");
		return -1;
	}

	char* buffer = malloc(sizeof(char) * 20);
	for(int i = 1; i < argc; i++) {
		if(strstr(argv[i], "-f") != NULL) {
			strncpy(*fileName, argv[i] + 2, strlen(argv[i]) - 2);
		}
		else if(strstr(argv[i], "-d") != NULL) {
			strncpy(buffer, argv[i] + 2, strlen(argv[i]) - 2);
			*dimSize = atoi(buffer);
			memset(buffer, 0, 20);
		}
		else if(strstr(argv[i], "-t") != NULL) {
			strncpy(buffer, argv[i] + 2, strlen(argv[i]) - 2);
			*trainDataSize = atoi(buffer);
			memset(buffer, 0, 20);
		}
		else if(strstr(argv[i], "-l") != NULL) {
			strncpy(buffer, argv[i] + 2, strlen(argv[i]) - 2);
			*learningRate = atof(buffer);
			memset(buffer, 0, 20);
		}
		else if(strstr(argv[i], "-e") != NULL) {
			strncpy(buffer, argv[i] + 2, strlen(argv[i]) - 2);
			*numEpochs = atoi(buffer);
			memset(buffer, 0, 20);
		}
	}

	if(strlen(*fileName) == 0 || *dimSize == 0 || *trainDataSize == 0) {
		printf("Error: Invalid usage - file name, dimensionSize and trainDataSize are required arguments.\n");
		printf("Example: \n");
		printf("\t./NN -f{testDataFilePath} -d{dimensionSize} -t{trainDataSize}\n");
		return -1;
	}

	return 0;
}
