# Compiler
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11

# Target executable
TARGET = simulation

# Source files
SRCS = AddressDecoder.cc Block.cc Cache.cc Memory.cc PerformanceCounter.cc Set.cc Simulation.cc

# Header files (not compiled directly, but good to track)
HDRS = AddressDecoder.h Block.h Cache.h Memory.h PerformanceCounter.h Set.h

# Object files
OBJS = $(SRCS:.cc=.o)

# Default rule
all: $(TARGET)

# Linking the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compilation rule
%.o: %.cc $(HDRS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -f $(OBJS) $(TARGET)

# Run simulation
run: $(TARGET)
	./$(TARGET)

