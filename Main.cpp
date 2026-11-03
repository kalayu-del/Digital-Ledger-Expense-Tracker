#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

// Structure to group data related to a single expense item
struct Expense {
    string category;
    double amount;
};

int main() {
    const int MAX_EXPENSES = 100;
    Expense wallet[MAX_EXPENSES];
    int count = 0;

    // Load data from text file on startup
    ifstream infile("expenses.txt");
    if (infile.is_open()) {
        while (count < MAX_EXPENSES && infile >> wallet[count].category >> wallet[count].amount) {
            count++;
        }
        infile.close();
    }

    int choice;
    do {
        cout << "\n===============================";
        cout << "\n    POCKET EXPENSE TRACKER     ";
        cout << "\n===============================";
        cout << "\n1. Log New Expense";
        cout << "\n2. Display Statement & Total";
        cout << "\n3. Exit Ledger";
        cout << "\nChoice (1-3): ";
        cin >> choice;

        if (choice == 1) {
            if (count < MAX_EXPENSES) {
                cout << "\nEnter Category (e.g., Food, Rent, Gas): ";
                cin >> wallet[count].category;
                cout << "Enter Amount ($): ";
                cin >> wallet[count].amount;

                // Open file in append mode to log history permanently
                ofstream outfile("expenses.txt", ios::app);
                outfile << wallet[count].category << " " << wallet[count].amount << "\n";
                outfile.close();

                count++;
                cout << " Expense successfully recorded!\n";
            } else {
                cout << " Storage limit reached!\n";
            }
        } 
        else if (choice == 2) {
            if (count == 0) {
                cout << "\n No expense entries logged yet.\n";
            } else {
                double grandTotal = 0;
                cout << "\n" << left << setw(15) << "Category" << "Amount\n";
                cout << string(25, '-') << "\n";
                
                for (int i = 0; i < count; i++) {
                    cout << left << setw(15) << wallet[i].category 
                         << "$" << fixed << setprecision(2) << wallet[i].amount << "\n";
                    grandTotal += wallet[i].amount;
                }
                
                cout << string(25, '-') << "\n";
                cout << left << setw(15) << "TOTAL OUTFLOW:" << "$" << grandTotal << "\n";
            }
        }
    } while (choice != 3);

    cout << "\nGoodbye! Keeping tracking keeps you saving.\n";
    return 0;
}
