makefile
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
TARGET = snake_game
OBJS = main.o game.o snake.o
all: $(TARGET)
$(TARGET): $(OBJS)
$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)
main.o: main.cpp game.h
$(CXX) $(CXXFLAGS) -c main.cpp
game.o: game.cpp game.h snake.h
$(CXX) $(CXXFLAGS) -c game.cpp
snake.o: snake.cpp snake.h
$(CXX) $(CXXFLAGS) -c snake.cpp
clean:
rm -f $(OBJS) $(TARGET)
run: $(TARGET)
./$(TARGET)
