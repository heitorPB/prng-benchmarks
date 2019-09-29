SRCs = $(wildcard *.cpp)
OBJS = $(SRCs:.cpp=.o)

WFLAGS = -Wall -Wextra -Wshadow -Wold-style-cast -Weffc++
CPPFLAGS = -O2 -march=native -std=c++17

BIN = benchmark

OUT = results-$(CXX)

.cpp.o:
	$(CXX) $(WFLAGS) $(CPPFLAGS) -c $^ -o $@

all: $(OBJS)
	$(CXX) $(WFLAGS) $(CPPFLAGS) $(OBJS) -o $(BIN)

clean:
	rm -f $(OBJS) $(BIN)

plots:
	./$(BIN) > $(OUT).csv
	python plot_results.py $(OUT).csv --output $(OUT).png