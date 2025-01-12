typedef struct {
	Perceptron* neurons;
} Layer;

typedef struct {
	Layer* layers;
	int inputDimension;
	int numLayers;
	int hiddenLayerSize;
} NeuralNetwork;

Layer createLayer(int layerSize, int previousLayerSize){
	Layer layer;
	layer.neurons = malloc(sizeof(Perceptron) * layerSize);
	for(int i = 0; i < layerSize; i++){
		layer.neurons[i] = createNeuron(previousLayerSize);
	}
	return layer;
}

NeuralNetwork createNeuralNetwork(int inputDimension, int numLayers, int hiddenLayerSize){
	NeuralNetwork nn;
	nn.numLayers = numLayers;
	nn.hiddenLayerSize = hiddenLayerSize;
	nn.layers = malloc(sizeof(Layer) * numLayers);
	nn.layers[0] = createLayer(inputDimension, 1);
	int prevLayerSize = inputDimension;
	for(int i = 1; i < numLayers; i++) {
		nn.layers[i] = createLayer(hiddenLayerSize, prevLayerSize);
		prevLayerSize = hiddenLayerSize;
	}
	return nn;
}

void printNeuralNetwork(NeuralNetwork nn){
	for(int i = 0; i < nn.numLayers; i++) {
		int numNeurons = sizeof(nn.layers[i].neurons) / sizeof(Perceptron);
		printf("Layer %d: %d nuerons", i, numNeurons);
		for(int j = 0; j < numNeurons; j++) {
			printf("%d\t", nn.layers[i].neurons[j].weights[0]);
		}
		printf("\n");
	}
}
