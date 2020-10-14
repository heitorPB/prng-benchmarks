SRCs = $(wildcard *.cpp)
OBJS = $(SRCs:.cpp=.o)

WFLAGS = -Wall -Wextra -Wshadow -Wold-style-cast -Weffc++
CPPFLAGS = -O3 -march=native -mtune=native -std=c++17

BIN = benchmark

.cpp.o:
	$(CXX) $(WFLAGS) $(CPPFLAGS) -c $^ -o $@

all: $(OBJS)
	$(CXX) $(WFLAGS) $(CPPFLAGS) $(OBJS) -o $(BIN)

clean:
	rm -f $(OBJS) $(BIN)