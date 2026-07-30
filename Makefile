CC = g++
ASFLAGS = std=c++17
BIN = /bin/net
SRC = /src/sniffer.cp

all:
	$(CC) $(ASFLAGS) $(SRC) -o $(BIN)
clean:
	rm -rf $(BIN)
