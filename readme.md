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