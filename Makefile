# Makefile for Projektname

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -I./extern/ -std=c++11

# Source files
SRCS = main.cpp \
       source/readConsolInput.cpp \
       source/readVariables.cpp \
       source/checkInputFilesError.cpp \
       source/readAndCompareOptions.cpp \
       source/CTextToCPP.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Output executable
TARGET = main.exe

# Rule to build the executable
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

# Rule to compile source files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -f $(OBJS) $(TARGET)
