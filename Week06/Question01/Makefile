CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic
TARGET = scientific_program
SRC = main.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)
