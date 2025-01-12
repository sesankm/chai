CFLAGS = -Wall -g
TARGET = NN

all: 
	$(CC) $(CFGLAGS) -o $(TARGET) main.c -lm

clean:
	rm -f $(TARGET)

