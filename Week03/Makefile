# Compiler
CXX = g++
CXXFLAGS = -Wall -g -std=c++11

# Object files
OBJS = main.o grid3d_1d_array.o grid3d_vector.o grid3d_new.o
OBJS_test = test_grid.o grid3d_1d_array.o grid3d_vector.o grid3d_new.o

# Build homework target
homework.x: $(OBJS)
	$(CXX) $(CXXFLAGS) -o homework.x $(OBJS)

# Build test target
test_grid.x: $(OBJS_test)
	$(CXX) $(CXXFLAGS) -o test_grid.x $(OBJS_test)

# Pattern rule for compiling .cpp files to .o files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

# Dependencies for main code
main.o: grid3d_1d_array.h grid3d_vector.h grid3d_new.h
grid3d_1d_array.o: grid3d_1d_array.h
grid3d_vector.o: grid3d_vector.h
grid3d_new.o: grid3d_new.h

# Dependencies for test
test_grid.o: test_grid.cpp grid3d_1d_array.h grid3d_vector.h grid3d_new.h

# Clean up
clean:
	rm -f homework.x test_grid.x *.o
