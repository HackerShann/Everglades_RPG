#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
using namespace std;

const int SIZE = 5;
const int NUM_DANGERS = 10;

string dangerName[] = { "Hungry Alligator", "Swarm of Giant Mosquitos", "Venomous Spider", "Python" };
char dangerFill[] = { 'A', 'M', 'S', 'P' };

char everglades[SIZE][SIZE];
int rangerX, rangerY;
int touristsX, touristsY;
int timeLeft = 12; // Arbitrary time limit for the game

void initializeEverglades() {
    // Initialize the map with '*'
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            everglades[i][j] = '*';
        }
    }

    // Set the ranger's initial position at the top-left corner
    rangerX = 0;
    rangerY = 0;

    // Set the tourists' initial position at the bottom-right corner
    touristsX = SIZE - 1;
    touristsY = SIZE - 1;

    // You can add code to place dangers randomly on the map here
}

void printEverglades() {
    cout << "   ";
    for (int i = 0; i < SIZE; i++) {
        cout << "  " << i << " ";
    }
    cout << endl;

    for (int i = 0; i < SIZE; i++) {
        cout << i << "  ";
        for (int j = 0; j < SIZE; j++) {
            if (i == rangerX && j == rangerY) {
                cout << "| R ";
            }
            else if (i == touristsX && j == touristsY) {
                cout << "| T ";
            }
            else {
                cout << "| " << everglades[i][j] << " ";
            }
        }
        cout << "|" << endl;
    }
}

void showRules() {
    // Your code to display the rules of the game
    cout << "=== Rules of the Everglades Game ===" << endl;
    cout << "1. The Ranger (R) starts at the top-left corner of the map." << endl;
    cout << "2. The goal is to rescue the tourists (T) at the bottom-right corner." << endl;
    cout << "3. Move the Ranger using row and column coordinates (0-4)." << endl;
    cout << "4. Encounter dangers denoted by letters like A, M, S, P on the map." << endl;
    cout << "5. You have limited gongs (turns) to reach the tourists." << endl;
    cout << "6. Dangers may require waiting, fighting, or moving strategically." << endl;
    cout << "7. Waiting costs 5 gongs, winning a fight costs 2 gongs, and losing costs 3 gongs." << endl;
}

void encounterDanger(int x, int y) {
    // Example implementation for handling danger encounter
    // For demonstration purposes, simply displaying a message
    cout << "Danger encountered at position (" << x << ", " << y << ")!" << endl;
    cout << endl;

    // Prompt Ranger with options
    cout << "Choose your next move" << endl;
    cout << "\t1. Wait until it leaves." << endl;
    cout << "\t2. Fight it." << endl;
    int option;
    cout << "Move: ";
    cin >> option;
    cout << endl;

    switch (option) {
    case 1:
        cout << "Ranger decides to wait for the danger to pass." << endl;
        // Decrease time by 5 turns (if timeLeft > 5)
        timeLeft = (timeLeft > 5) ? timeLeft - 5 : 0;
        break;
    case 2:
        cout << "Ranger decides to fight the danger." << endl;
        // Add logic for fighting
        // For example:
        // Simulate a fight - assuming Ranger wins the fight
        if (rand() % 2 == 0) {
            cout << "Ranger wins the fight!" << endl;
            cout << endl;
            timeLeft = (timeLeft > 2) ? timeLeft - 2 : 0;
            // Update Ranger's position to the desired cell
            int row, col;
            cout << "Enter the desired cell (row & col): ";
            cin >> row >> col;
            rangerX = row;
            rangerY = col;
        }
        else {
            cout << "Ranger loses the fight." << endl;
            cout << endl;
            timeLeft = (timeLeft > 3) ? timeLeft - 3 : 0;
            cout << "Ranger has to wait for the danger to pass." << endl;
            cout << endl;
        }
        break;
    default:
        cout << "Invalid option. Ranger chooses to wait." << endl;
        // Default action: Ranger waits
        break;
    }
}

void moveRanger(int x, int y) {
    // Check if the new position is within bounds
    if (x >= 0 && x < SIZE && y >= 0 && y < SIZE) {
        // Update ranger's position
        rangerX = x;
        rangerY = y;

        // Check if the ranger encounters any danger at the new position
        encounterDanger(x, y);
    }
    else {
        cout << "Out of bounds! Cannot move there." << endl;
        cout << endl;
    }
}

void playGame() {
    initializeEverglades();
    printEverglades();

    while (timeLeft > 0) {
        int rowMove, colMove;

        cout << endl;
        cout << "Gongs Left: " << timeLeft << endl;
        cout << endl;
        cout << "Enter next cell (row & col): ";
        cin >> rowMove;
        cin >> colMove;

        if (everglades[rowMove][colMove] == '*') {
            // If the Ranger moves to a cell without danger, only lose 1 turn
            timeLeft--;
        }

        moveRanger(rowMove, colMove);

        if (rangerX == touristsX && rangerY == touristsY) {
            cout << "Congratulations! You rescued the tourists!" << endl;
            break;
        }

        if (timeLeft <= 0) {
            cout << "Time is up! The tourists are lost forever." << endl;
            break;
        }

        printEverglades();
    }
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    int choice;
    do {
        cout << "Lost in the Everglades ..." << endl;
        cout << endl;
        cout << "1. See rules\n2. Play game\n3. Quit" << endl;
        cout << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cout << endl;

        switch (choice) {
        case 1:
            showRules();
            break;
        case 2:
            playGame();
            break;
        case 3:
            cout << "Exiting the game... Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice. Please enter again." << endl;
        }
    } while (choice != 3);

    return 0;
}