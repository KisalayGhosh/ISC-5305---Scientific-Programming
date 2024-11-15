CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra

all: main.x benchmark_main.x simpson_adaptive_nonrecursive.x simpson_adaptive_recursive.x simpson_nonadaptive_nonrecursive.x simpson_nonadaptive_recursive.x trapezoidal_adaptive_nonrecursive.x trapezoidal_adaptive_recursive.x trapezoidal_nonadaptive_nonrecursive.x trapezoidal_nonadaptive_recursive.x

main.x: main.cpp Integration.h IntegrationMethods.h
	$(CXX) $(CXXFLAGS) main.cpp -o main.x

benchmark_main.x: benchmark_main.cpp Integration.h IntegrationMethods.h
	$(CXX) $(CXXFLAGS) benchmark_main.cpp -o benchmark_main.x

simpson_adaptive_nonrecursive.x: simpson_adaptive_nonrecursive.cpp
	$(CXX) $(CXXFLAGS) simpson_adaptive_nonrecursive.cpp -o simpson_adaptive_nonrecursive.x

simpson_adaptive_recursive.x: simpson_adaptive_recursive.cpp
	$(CXX) $(CXXFLAGS) simpson_adaptive_recursive.cpp -o simpson_adaptive_recursive.x

simpson_nonadaptive_nonrecursive.x: simpson_nonadaptive_nonrecursive.cpp
	$(CXX) $(CXXFLAGS) simpson_nonadaptive_nonrecursive.cpp -o simpson_nonadaptive_nonrecursive.x

simpson_nonadaptive_recursive.x: simpson_nonadaptive_recursive.cpp
	$(CXX) $(CXXFLAGS) simpson_nonadaptive_recursive.cpp -o simpson_nonadaptive_recursive.x

trapezoidal_adaptive_nonrecursive.x: trapezoidal_adaptive_nonrecursive.cpp
	$(CXX) $(CXXFLAGS) trapezoidal_adaptive_nonrecursive.cpp -o trapezoidal_adaptive_nonrecursive.x

trapezoidal_adaptive_recursive.x: trapezoidal_adaptive_recursive.cpp
	$(CXX) $(CXXFLAGS) trapezoidal_adaptive_recursive.cpp -o trapezoidal_adaptive_recursive.x

trapezoidal_nonadaptive_nonrecursive.x: trapezoidal_nonadaptive_nonrecursive.cpp
	$(CXX) $(CXXFLAGS) trapezoidal_nonadaptive_nonrecursive.cpp -o trapezoidal_nonadaptive_nonrecursive.x

trapezoidal_nonadaptive_recursive.x: trapezoidal_nonadaptive_recursive.cpp
	$(CXX) $(CXXFLAGS) trapezoidal_nonadaptive_recursive.cpp -o trapezoidal_nonadaptive_recursive.x

clean:
	rm -f *.o *.x
