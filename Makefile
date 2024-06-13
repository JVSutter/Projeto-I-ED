# Variables
CXX = g++
CXXFLAGS = -Wall -std=c++11
OBJS = obj/main.o obj/solutions_utils.o obj/solutions.o
TARGET = bin/program

# Default target
all: $(TARGET)

# Linking
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compiling
obj/main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/solutions_utils.o: solutions/solutions_utils.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/solutions.o: solutions/solutions.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Cleaning
clean:
	rm -f $(OBJS) $(TARGET)