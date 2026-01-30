#ifndef GAME_H
#define GAME_H

#include "snake.h"
#include <vector>
#include <string>

// Struktura do przechowywania wyniku gracza
struct PlayerScore {
    std::string name;
    int score;
};

class Game {
private:
    static const int WIDTH = 40;
    static const int HEIGHT = 20;

    Snake snake;
    Point food;
    int score;
    bool gameOver;

    // Nowe zmienne do obsługi gracza i tabeli wyników
    std::string playerName;
    std::vector<PlayerScore> leaderBoard;

    // Funkcje prywatne
    void generateFood();
    void render();
    void handleInput();

    // Nowe funkcje do obsługi zapisu/odczytu
    void loadLeaderBoard();
    void saveLeaderBoard();
    void updateLeaderBoard();

public:
    Game();
    void run();
    int getScore() const { return score; }
};

#endif
