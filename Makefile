CXX = g++
ASFLAGS = -std=c++17
BIN = bin/net
SRC = src/sniffer.cpp

all:
	@mkdir -p bin
	$(CXX) $(ASFLAGS) $(SRC) -o $(BIN)
	@clear
clean:
	rm -rf $(BIN)
	rm -rf bin
	@clear
