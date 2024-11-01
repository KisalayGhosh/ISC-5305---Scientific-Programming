CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

all: polynomial_main tests

polynomial_main: main.o
	$(CXX) $(CXXFLAGS) -o polynomial_main main.o

tests: test.o
	$(CXX) $(CXXFLAGS) -o tests test.o

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

test.o: test.cpp
	$(CXX) $(CXXFLAGS) -c test.cpp

clean:
	rm -f *.o polynomial_main tests
