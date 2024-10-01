# Compiler and flags
CXX = g++ 
CXXFLAGS = -std=c++14 -O2

# Targets
all: root_finding root_finding_float

# Executable for root_finding
root_finding: main.o
	$(CXX) $(CXXFLAGS) -o root_finding main.o

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

# Executable for root_finding_float
root_finding_float: main1.o
	$(CXX) $(CXXFLAGS) -o root_finding_float main1.o

main1.o: main1.cpp
	$(CXX) $(CXXFLAGS) -c main1.cpp

# Clean rule
clean:
	rm -f *.o root_finding root_finding_float
