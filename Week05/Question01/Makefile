CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

all: brain_mesh

brain_mesh: main.o
	$(CXX) $(CXXFLAGS) -o brain_mesh main.o

main.o: main.cpp brain_mesh.h brain_mesh.hxx
	$(CXX) $(CXXFLAGS) -c main.cpp

clean:
	rm -f *.o brain_mesh
