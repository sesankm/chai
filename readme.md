# Chai

Building ML/AI models from scratch in C

## Usage
#### Required Args
- `-f` input data filePath
- `-d` dimension of input data
- `-t` size of training data

#### Optional Args
- `-l` learning rate
- `-e` number of epochs

Example
```
make
./NN -finput.csv -d2 -t4 -l.001 -e1000
```

### Resources
- [Wikipedia - Perceptron](https://en.wikipedia.org/wiki/Perceptron) 
- [Wikipedia - Feedforward Neural Network](https://en.wikipedia.org/wiki/Feedforward_neural_network) 
- [Sebastian Raschka's Slides on Gradient Descent](https://sebastianraschka.com/pdf/lecture-notes/stat453ss21/L05_gradient-descent_slides.pdf)