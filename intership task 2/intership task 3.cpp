#include <iostream>
#include <cstdlib>  // for rand() and srand()
#include <ctime>    // for time()

using namespace std;

int main() {
    // Seed for random number
    srand((unsigned int)time(0));

    // Generate random number between 1 and 100
    int randomNumber = (rand() % 100) + 1;   

    int guess = 0;
    int attempts = 0;

    cout << "=== Number Guessing Game ===" << endl;

    // Loop until user guesses correctly
    do {
    	cout << "Enter your guess (1-100): ";
        cin >> guess;

        attempts++;

        if (guess > randomNumber) {
            cout << "Too high! Try again." << endl;
        }
        else if (guess < randomNumber) {
            cout << "Too low! Try again." << endl;
        }
        else {
            cout << "------Correct------"<<endl;
			cout<<" You guessed the number in " << attempts << " attempts." << endl;
        }
	}
    while (guess != randomNumber);

    return 0;
}
