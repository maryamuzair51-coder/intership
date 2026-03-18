#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Function to roll dice
int rollDice() {
    return rand() % 6 + 1;
}

int main() {
    srand(time(0));

    char choice;
    int rollCount = 0;
    int highest = 0;
    int lowest = 12;
    int sum = 0;

    do {
        int die1 = rollDice();
        int die2 = rollDice();
        int total = die1 + die2;

        rollCount++;
        sum += total;

        // Update highest & lowest
        if (total > highest)
            highest = total;

        if (total < lowest)
            lowest = total;

        cout << "\nYou rolled: " << die1 << " and " << die2 << endl;
        cout << "Total: " << total << endl;

        // Winning conditions
        if (die1 == 1 && die2 == 1)
            cout << "Snake Eyes!" << endl;

        if (total == 7 || total == 11)
            cout << "You Win!" << endl;

        cout << "\nRoll again? (y/n): ";
        cin >> choice;

    } while (choice == 'y' || choice == 'Y');

    // Show statistics
    
    cout << "\nGame Over!" << endl;
    cout << "Total Rolls: " << rollCount << endl;
    cout << "Highest Total: " << highest << endl;
    cout << "Lowest Total: " << lowest << endl;

    if (rollCount > 0)
        cout << "Average Total: " << (double)sum / rollCount << endl;

    cout << "\nThanks for playing!" << endl;

    return 0;
}
