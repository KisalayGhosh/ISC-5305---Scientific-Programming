CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra -pthread

all: adaptive.x nonadaptive.x

adaptive.x: adaptive_integration.cpp globals.cpp adaptive_main.cpp
	$(CXX) $(CXXFLAGS) adaptive_integration.cpp globals.cpp adaptive_main.cpp -o adaptive.x

nonadaptive.x: non_adaptive_integration.cpp globals.cpp nonadaptive_main.cpp
	$(CXX) $(CXXFLAGS) non_adaptive_integration.cpp globals.cpp nonadaptive_main.cpp -o nonadaptive.x

clean:
	rm -f *.o adaptive.x nonadaptive.x
