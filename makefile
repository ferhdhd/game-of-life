CXX = g++
CXXFLAGS = -std=c++17
LDFLAGS = -lz3

TARGET = game_of_life
SOURCES = game_of_life.cpp csp_functions.cpp
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

%.o: %.cpp csp_functions.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all clean
