# File: Makefile

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

# Source files
SRCS = main.cpp shapes.cpp scene.cpp ray_project1.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Executable name
TARGET = main

# Default build
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

# Clean object files and binary
clean:
	rm -f $(OBJS) $(TARGET)
