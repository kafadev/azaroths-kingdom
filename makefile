CXX := g++-13
CXXFLAGS := -g -I/usr/include/SDL2 -D_REENTRANT
LDFLAGS := -lSDL2

SRC := \
    $(wildcard ui/*.cpp) \
    $(wildcard tiles/*.cpp)

OBJ := $(SRC:.cpp=.o)

TARGET := game

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
