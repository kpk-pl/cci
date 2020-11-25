ALL_TARGETS = $(shell echo src/*.cpp | sed 's/.cpp//g' | sed 's/src\///g')
VPATH := bin

all: $(ALL_TARGETS)

%: src/%.cpp
	g++ -O2 -Wall -Wextra -std=c++2a $< -I deps/googletest/googletest/include -L deps/googletest/build/lib -lgtest -lpthread -o bin/$@

gtest:
	cd deps/googletest && mkdir -p build
	cd deps/googletest/build && cmake .. && make

clean:
	rm -f bin/*

.PHONY: all clean
