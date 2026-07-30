CC = g++
ASFLAGS = -std=c++17
BIN = bin/net
SRC = src/sniffer.cpp

all:
	@mkdir -p bin
	$(CC) $(ASFLAGS) $(SRC) -o $(BIN)
clean:
	rm -rf $(BIN)
