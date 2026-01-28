#include <iostream>
#include "game.h"
using namespace std;
void showMenu() {
cout << "\n========== SNAKE GAME ==========\n";
cout << "1. Nowa gra\n";
cout << "2. Zasady\n";
cout << "3. Wyjście\n";
cout << "================================\n";
cout << "Wybór: ";
}
void showRules() {
cout << "\n=== ZASADY GRY ===\n";
cout << "- Steruj wężem używając klawiszy W, A, S, D\n";
cout << "- Zbieraj jedzenie (*) aby rosnąć i zdobywać punkty\n";
cout << "- Unikaj ścian i własnego ciała\n";
cout << "- Wciśnij Q aby zakończyć grę\n";
cout << "\nWciśnij Enter aby wrócić...";
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
cout << "Nieprawidłowy wybór!\n";
}
} while (choice != 3);
return 0;
}
