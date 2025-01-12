#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

typedef struct {
	int dimensionSize;
	int inputSize;
	float* weights;
	int* trainDataOutput;
	float* predictedOutputs;
	int** inputs;
	float error;
	float learningRate;
	int epochs;
} Perceptron;

void initializeWeights(Perceptron* p){
	p->weights = malloc(p->dimensionSize * sizeof(float));
	for(int i = 0; i < p-> dimensionSize; i++){
		p->weights[i] = 1.0;
	}
}

void initializeInputs(Perceptron* p){
	p->inputs = malloc(p->inputSize * sizeof(int*));
	for(int i = 0; i < p->inputSize; i++) {
		p->inputs[i] = malloc(p->dimensionSize * sizeof(int));
	}
}

Perceptron createPerceptron(int dimensionSize, int inputSize, float learningRate){
	Perceptron perceptron;
	perceptron.dimensionSize = dimensionSize;
	perceptron.inputSize = inputSize;
	perceptron.learningRate = learningRate;
	perceptron.epochs = 0;
	perceptron.predictedOutputs = malloc(sizeof(float) * inputSize);
	initializeWeights(&perceptron);
	initializeInputs(&perceptron);
	return perceptron;
}

Perceptron createNeuron(int dimensionSize){
	Perceptron perceptron;
	perceptron.dimensionSize = dimensionSize;
	initializeWeights(&perceptron);
	return perceptron;
}

void readInputData(char* fileName, Perceptron* p){
	FILE *fptr;
	char line[256];
	int lineCount = 0;
	fptr = fopen(fileName, "r");
	p->trainDataOutput = malloc(p->inputSize * sizeof(int));
	while(fgets(line, sizeof(line), fptr)) {
		char* strValue = strtok(line, ",");
		int dimCount = 0;
		while(strValue != NULL && lineCount < p->inputSize) {
			int value = atoi(strValue);
			strValue = strtok(NULL, ",");
			if(dimCount < p->dimensionSize) {
				p->inputs[lineCount][dimCount] = value;
			} else if(dimCount == p->dimensionSize) { 
				p->trainDataOutput[lineCount] = value;
			} else {
				break;
			}
			dimCount++;
		}
		lineCount++;
	}
}


void calculateError(Perceptron* p) {
	float sumOfDifferencesSq = 0, diff = 0;
	for(int i = 0; i < p->inputSize; i++){
		diff = p->predictedOutputs[i] - p->trainDataOutput[i];
		sumOfDifferencesSq += (diff * diff);
	}
	p->error = sumOfDifferencesSq / p->inputSize;
}

void calculateOutput(Perceptron* p){
	float result;
	for(int i = 0; i < p->inputSize; i++){
		result = 0;
		for(int j = 0; j < p->dimensionSize; j++) {
			result += p->weights[j] * p->inputs[i][j];
		}
		p->predictedOutputs[i] = result;
	}
}

void updateWeight(Perceptron* p){
	for(int i = 0; i < p->inputSize; i++){
		for(int j = 0; j < p->dimensionSize; j++){
			float deltaW = (p->predictedOutputs[i] - p->trainDataOutput[i])  * p->inputs[i][j];
			p->weights[j] += (-1.0 * deltaW * p->learningRate);
		}
	}
	p->epochs += 1;
}

void printModel(Perceptron p) {
	printf("%d ====> Weights: {", p.epochs);
	for(int i = 0; i < p.dimensionSize; i++) {
		printf("W%d: %.5f", i, p.weights[i]);
		if(i == p.dimensionSize - 1) {
			printf("}, ");
		} else {
			printf(", ");
		}
	}
	printf("LearningRate: %.3f, Error: %.3f\n", p.learningRate, p.error);
}

void predict(Perceptron p){
	for(int i = 0; i < p.inputSize; i++) {
		printf("PRED: %f, ACTUAL: %d\n", p.predictedOutputs[i], p.trainDataOutput[i]);
	}
	printf("ERROR: %f", p.error);
	printf("\n\n");
}


void epoch(Perceptron* p){
	if(p->epochs == 0 || p->epochs % 5 == 0) {
		printModel(*p);
	}
	calculateOutput(p);
	calculateError(p);
	updateWeight(p);
}
