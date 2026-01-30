#include <iostream>
#include "game.h"
using namespace std;
void showMenu() {
cout << "\n========== SNAKE GAME ==========\n";
cout << "1. Nowa gra\n";
cout << "2. Zasady\n";
cout << "3. Wyjscie\n";
cout << "================================\n";
cout << "Akcja numer: ";
}
void showRules() {
cout << "\n=== ZASADY GRY ===\n";
cout << "- Steruj wezem uzywając klawiszy W, A, S, D\n";
cout << "- Zbieraj jedzenie (*) aby rosnac i zdobywac punkty\n";
cout << "- Unikaj kolizji z scianami i wlasnym cialem\n";
cout << "- Wcisnij Q aby zakonczyc gre\n";
cout << "\nWcisnij Enter aby wrocic...";
cin.ignore();
cin.get();
}
int main() {
int choice;
do {
showMenu();
cin >> choice;
switch(choice) {
case 1: {
Game game;
game.run();
break;
}
case 2:
showRules();
break;
case 3:
cout << "Do zobaczenia!\n";
break;
default:
cout << "Nieprawidlowy wybor!\n";
}
} while (choice != 3);
return 0;
}
