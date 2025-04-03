CXX := g++-13
CXXFLAGS := -g -I/usr/include/SDL2 -D_REENTRANT
LDFLAGS := -lSDL2 -lSDL2_mixer

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

run: game
	@echo "Running game"
	./game

clean:
	rm -f $(OBJ) $(TARGET)
