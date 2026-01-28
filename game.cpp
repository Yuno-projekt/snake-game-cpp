#include "game.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h> // dla Windows: _kbhit(), _getch()
// dla Linux użyj: ncurses library
using namespace std;
Game::Game() : snake(WIDTH/2, HEIGHT/2), score(0), gameOver(false) {
srand(time(0));
generateFood();
}
void Game::generateFood() {
do {
food.x = rand() % WIDTH;
food.y = rand() % HEIGHT;
} while (find(snake.getBody().begin(),
snake.getBody().end(), food) != snake.getBody().end());
}
void Game::render() {
system("clear"); // Linux/Mac (Windows: "cls")
// Górna krawędź
for (int i = 0; i < WIDTH + 2; i++) cout << "#";
cout << "\n";
// Plansza gry
for (int y = 0; y < HEIGHT; y++) {
cout << "#";
for (int x = 0; x < WIDTH; x++) {
Point current(x, y);
if (current == snake.getHead()) {
cout << "O"; // Głowa węża
} else if (find(snake.getBody().begin(),
snake.getBody().end(), current) != snake.getBody().end()) {
cout << "o"; // Ciało węża
} else if (current == food) {
cout << "*"; // Jedzenie
} else {
cout << " ";
}
}
cout << "#\n";
}
// Dolna krawędź
for (int i = 0; i < WIDTH + 2; i++) cout << "#";
cout << "\n";
cout << "Wynik: " << score << " | Sterowanie: WASD | Q - wyjście\n";
}
void Game::handleInput() {
if (_kbhit()) { // Sprawdź czy klawisz został naciśnięty
char key = _getch();
switch(key) {
case 'w': case 'W': snake.changeDirection(UP); break;
case 's': case 'S': snake.changeDirection(DOWN); break;
case 'a': case 'A': snake.changeDirection(LEFT); break;
case 'd': case 'D': snake.changeDirection(RIGHT); break;
case 'q': case 'Q': gameOver = true; break;
}
}
}
void Game::run() {
while (!gameOver) {
render();
handleInput();
snake.move();
// Sprawdź kolizję z jedzeniem
if (snake.getHead() == food) {
snake.grow();
score += 10;
generateFood();
}
// Sprawdź kolizje
if (snake.checkCollision(WIDTH, HEIGHT) ||
snake.checkSelfCollision()) {
gameOver = true;
}
// Delay dla kontroli prędkości
#ifdef _WIN32
Sleep(100); // Windows
#else
usleep(100000); // Linux/Mac (100ms)
#endif
}
cout << "\n=== GAME OVER ===\n";
cout << "Końcowy wynik: " << score << "\n";
}
