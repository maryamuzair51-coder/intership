#include <iostream>
using namespace std;

int main() {

    // Initial setup
    double balance = 1000.0;
    int choice;
    double amount;

    int password = 1234;
    int count = 0;
    int pin;

    bool istrue = true;

    // Main loop
    do {
        cout << "  ---------- Welcome to ATM Simulation  ---------  " << endl;


        cout << "Enter Your Pin: ";
        cin >> pin;

        // Check PIN
        if (pin == password) {

            cout << "\nLogin Successful!\n";

            // Menu
            cout << "\n===== ATM MENU =====" << endl;
            cout << "1. Check Balance" << endl;
            cout << "2. Deposit Money" << endl;
            cout << "3. Withdraw Money" << endl;
            cout << "4. Exit" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {

                case 1: // Check balance
                    cout << "Your current balance is: $" << balance << endl;
                    break;

                case 2: // Deposit
                    cout << "Enter amount to deposit: ";
                    cin >> amount;
                    if (amount > 0) {
                        balance += amount;
                        cout << "Deposit successful!" << endl;
                    } else {
                        cout << "Invalid amount!" << endl;
                    }
                    break;

                case 3: // Withdraw
                    cout << "Enter amount to withdraw: ";
                    cin >> amount;
                    if (amount > balance) {
                        cout << "Insufficient balance!" << endl;
                    } 
                    else if (amount <= 0) {
                        cout << "Invalid amount!" << endl;
                    } 
                    else {
                        balance -= amount;
                        cout << "Withdrawal successful!" << endl;
                    }
                    break;

                case 4: // Exit
                    cout << "Thank you for using the ATM. Goodbye!" << endl;
                    istrue = false;
                    break;

                default:
                    cout << "Invalid choice! Try again." << endl;
            }

        } else {
            // Wrong PIN handling
            count++;
            cout << "Wrong PIN! Attempt " << count << "/3\n";

            if (count == 3) {
                cout << "Too many incorrect attempts. Card blocked!" << endl;
                istrue = false;
            }
        }

    } while (istrue);

    return 0;
}
