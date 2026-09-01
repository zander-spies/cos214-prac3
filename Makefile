# EventFlow — COS 214 Practical 3
# Builds the `eventflow` executable with: make
CXX      = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic -g
TARGET   = eventflow
SRCS     = $(wildcard *.cpp)
OBJS     = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

docs:
	doxygen Doxyfile

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all run docs clean
