#include "game.h"
#include <iostream>
#include <fstream> // Obsługa plików
#include <cstdlib>
#include <ctime>
#include <conio.h> // Windows: _kbhit(), _getch()
#include <algorithm>
#include <windows.h> // Windows: Sleep()
#include <vector>

using namespace std;

// Funkcja pomocnicza do sortowania wyników (malejąco)
bool compareScores(const PlayerScore& a, const PlayerScore& b) {
    return a.score > b.score;
}

Game::Game() : snake(WIDTH/2, HEIGHT/2), score(0), gameOver(false) {
    srand(time(0));

    // Wyczyść ekran i zapytaj o imię
    system("cls");
    cout << "\033[36m" << "Witaj w grze SNAKE!\n" << "\033[0m";
    cout << "Podaj swoje imie (bez spacji): ";
    cin >> playerName;

    generateFood();
    loadLeaderBoard(); // Wczytaj poprzednie wyniki
}

void Game::loadLeaderBoard() {
    leaderBoard.clear();
    ifstream file("leaderboard.txt");
    if (file.is_open()) {
        PlayerScore ps;
        while (file >> ps.name >> ps.score) {
            leaderBoard.push_back(ps);
        }
        file.close();
    }
    // Sortuj wyniki po wczytaniu
    sort(leaderBoard.begin(), leaderBoard.end(), compareScores);
}

void Game::saveLeaderBoard() {
    ofstream file("leaderboard.txt");
    if (file.is_open()) {
        // Zapisz tylko top 5
        for (size_t i = 0; i < leaderBoard.size() && i < 5; i++) {
            file << leaderBoard[i].name << " " << leaderBoard[i].score << endl;
        }
        file.close();
    }
}

void Game::updateLeaderBoard() {
    // Dodaj aktualny wynik do listy
    PlayerScore current;
    current.name = playerName;
    current.score = score;
    leaderBoard.push_back(current);

    // Posortuj ponownie
    sort(leaderBoard.begin(), leaderBoard.end(), compareScores);

    // Jeśli lista jest dłuższa niż 5, usuń nadmiar
    if (leaderBoard.size() > 5) {
        leaderBoard.resize(5);
    }

    // Zapisz do pliku
    saveLeaderBoard();
}

void Game::generateFood() {
    do {
        food.x = rand() % WIDTH;
        food.y = rand() % HEIGHT;
    } while (find(snake.getBody().begin(),
            snake.getBody().end(), food) != snake.getBody().end());
}

void Game::render() {
    // Przesunięcie kursora na górę zamiast system("cls") - eliminuje migotanie
    printf("\033[H"); 

    // Definicje kolorów ANSI
    string RED     = "\033[31m";
    string GREEN   = "\033[32m";
    string YELLOW  = "\033[33m";
    string CYAN    = "\033[36m";
    string RESET   = "\033[0m";

    // Górna krawędź
    cout << YELLOW;
    for (int i = 0; i < WIDTH + 2; i++) cout << "#";
    cout << RESET << "\n";

    // Plansza gry
    for (int y = 0; y < HEIGHT; y++) {
        cout << YELLOW << "#" << RESET; // Lewa krawędź
        for (int x = 0; x < WIDTH; x++) {
            Point current(x, y);
            if (current == snake.getHead()) {
                cout << GREEN << "O" << RESET; // Głowa węża
            } else if (find(snake.getBody().begin(),
                       snake.getBody().end(), current) != snake.getBody().end()) {
                cout << GREEN << "o" << RESET; // Ciało węża
            } else if (current == food) {
                cout << RED << "*" << RESET;   // Jedzenie
            } else {
                cout << " ";
            }
        }
        cout << YELLOW << "#" << RESET << "\n"; // Prawa krawędź
    }

    // Dolna krawędź
    cout << YELLOW;
    for (int i = 0; i < WIDTH + 2; i++) cout << "#";
    cout << RESET << "\n";

    // Wyświetlanie wyniku i imienia gracza
    cout << CYAN << "Gracz: " << YELLOW << playerName 
         << CYAN << " | Wynik: " << YELLOW << score 
         << CYAN << " | Q - wyjscie" << RESET << "\n";
}

void Game::handleInput() {
    if (_kbhit()) { 
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
    // Wyczyszczenie po wpisaniu imienia, przed renderowaniem planszy
    system("cls");
    
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

        // Sprawdź kolizje ze ścianą lub sobą
        if (snake.checkCollision(WIDTH, HEIGHT) ||
            snake.checkSelfCollision()) {
            gameOver = true;
        }

        Sleep(100); 
    }

    // Po zakończeniu gry zaktualizuj tabelę
    updateLeaderBoard();

    // Ekran końcowy
    cout << "\033[31m" << "\n=== KONIEC GRY ===\n" << "\033[0m";
    cout << "Twoj wynik: " << "\033[33m" << score << "\033[0m" << "\n\n";

    // Wyświetl tabelę wyników
    cout << "\033[35m" << "--- TABELA WYNIKOW (TOP 5) ---\n" << "\033[0m";
    for (size_t i = 0; i < leaderBoard.size(); i++) {
        cout << i + 1 << ". " << leaderBoard[i].name << ": " << leaderBoard[i].score << endl;
    }
    
    cout << "\nNacisnij dowolny klawisz, aby zakonczyc...";
    _getch(); // Czekaj na klawisz
}
