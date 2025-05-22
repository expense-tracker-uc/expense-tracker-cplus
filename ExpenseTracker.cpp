// -------------------------------------------
// MSCS 632 Advanced Programming Languages
// Group Project
// Expense Tracker App
// -------------------------------------------

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

struct Expense {
    string date;
    float amount;
    string category;
    string description;
};

const int INITIAL_CAPACITY = 10;
const int MAX_CATEGORIES = 50;

// Utility functions

void printBanner() {
    string banner = "---------------------------------------------------------------\n"
                    "||                                                           ||\n"
                    "||     Welcome to your personal expense tracking system!     ||\n"
                    "||                                                           ||\n"
                    "---------------------------------------------------------------\n";
    cout << banner << endl;
}

void noExpenseMessage() {
    string message = "-------------------------------------------------------------------------\n"
                    "||                                                                     ||\n"
                    "||                         No Expenses Found!                          ||\n"
                    "||                                                                     ||\n"
                    "||  You haven't recorded any expenses yet.                             ||\n"
                    "||  Use option 1 from the main menu to add your first expense.         ||\n"
                    "||                                                                     ||\n"
                    "-------------------------------------------------------------------------\n";
    cout << message << endl;
}

void printSummary() {
    cout << "-------------------------------------------------------------------------" << endl;
    cout << "||                                                                     ||" << endl;
    cout << "||                          EXPENSE SUMMARY                            ||" << endl;
    cout << "||                                                                     ||" << endl;
    cout << "-------------------------------------------------------------------------" << endl;
    cout << "\nCategory Breakdown" << endl;
}

class ExpenseTracker {
    public:
        // Constructor
        ExpenseTracker() {
            capacity = INITIAL_CAPACITY;
            size = 0;
            expenses = new Expense*[capacity];
        }

        // Destructor
        ~ExpenseTracker() {
            // Free each allocated Expense
            for (int i = 0; i < size; ++i) {
                delete expenses[i];
            }
            delete[] expenses;
        }

        void addExpenses(string date, float amount, string category, string description) {
            if (size >= capacity) {
                resize();
            }
            Expense* newExpense = new Expense{date, amount, category, description};
            expenses[size++] = newExpense;
            cout << "\nExpense added successfully!\n";
        }

        void getExpenses(int filterChoice) {
            if (size == 0) {
                noExpenseMessage();
                return;
            }
            switch (filterChoice) {
                case 1:
                    printAllExpenses();
                    break;
                case 2:
                    filterByDateRange();
                    break;
                case 3:
                    filterByCategory();
                    break;
                default:
                    cout << "Invalid filter option.\n";
            }
        }

        void getSummary() {
            if (size == 0) {
                noExpenseMessage();
                return;
            }
            
            printSummary();
            
            // Count categories and totals manually
            string uniqueCategories[MAX_CATEGORIES];
            float totals[MAX_CATEGORIES] = {0};
            int categoryCount = 0;
            float totalExpenses = 0.0f;

            for (int i = 0; i < size; ++i) {
                bool found = false;
                for (int j = 0; j < categoryCount; ++j) {
                    if (expenses[i]->category == uniqueCategories[j]) {
                        totals[j] += expenses[i]->amount;
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    uniqueCategories[categoryCount] = expenses[i]->category;
                    totals[categoryCount] = expenses[i]->amount;
                    categoryCount++;
                }
                totalExpenses += expenses[i]->amount;
            }

            for (int i = 0; i < categoryCount; ++i) {
                cout << " - " << uniqueCategories[i] << ": $" << fixed << setprecision(2) << totals[i] << endl;
            }

            cout << "\nTotal Expenses: $" << fixed << setprecision(2) << totalExpenses << endl;
        }

    private:
        // Variables
        Expense** expenses; // Array of pointers to Expense
        int capacity;
        int size;

        // Functions
        void resize() {
            capacity *= 2;
            Expense** newArr = new Expense*[capacity];
            for (int i = 0; i < size; ++i) {
                newArr[i] = expenses[i];
            }
            delete[] expenses;
            expenses = newArr;
        }

        void printAllExpenses() {
            cout << "\n--- All Expenses ---\n";
            for (int i = 0; i < size; ++i) {
                cout << "Date: " << expenses[i]->date
                     << ", Amount: $" << fixed << setprecision(2) << expenses[i]->amount
                     << ", Category: " << expenses[i]->category
                     << ", Description: " << expenses[i]->description << endl;
            }
        }

        void filterByDateRange() {
            string startDate, endDate;
            cout << "Enter start date (YYYY-MM-DD): ";
            cin >> startDate;
            cout << "Enter end date (YYYY-MM-DD): ";
            cin >> endDate;
            cout << "\n--- Expenses from " << startDate << " to " << endDate << "--\n";
            for (int i = 0; i < size; ++i) {
                if (expenses[i]->date >= startDate && expenses[i]->date <= endDate) {
                    cout << "Date: " << expenses[i]->date
                         << ", Amount: $" << fixed << setprecision(2) << expenses[i]->amount
                         << ", Category: " << expenses[i]->category
                         << ", Description: " << expenses[i]->description << endl;
                }
            }
        }

        void filterByCategory() {
            string categoryItem;
            cout << "Enter category to filter by: ";
            cin >> categoryItem;
            cout << "\n--- Expenses in category: " << categoryItem << " ---\n";
            for (int i = 0; i < size; ++i) {
                if (expenses[i]->category == categoryItem) {
                    cout << "Date: " << expenses[i]->date
                         << ", Amount: $" << fixed << setprecision(2) << expenses[i]->amount
                         << ", Description: " << expenses[i]->description << endl;
                }
            }
        }
};

int main() {
    printBanner();
    ExpenseTracker et;

    int choice;
    string date;
    float amount;
    string category;
    string description;
    int filterChoice;

    while(1) {
        cout << "\n=== Expense Tracker Menu ===" << endl;
        cout << "1. Add Expense" << endl;
        cout << "2. View Expenses" << endl;
        cout << "3. Get Summary" << endl;
        cout << "4. Exit" << endl;

        cout << "\nEnter your choice (1-4): ";
        cin >> choice;

        switch(choice) {
            case 1:
                cout << "Enter date (YYYY-MM-DD): ";
                cin >> date;
                cout << "Enter amount: ";
                cin >> amount;
                cin.ignore();
                cout << "Enter category: ";
                getline(cin, category);
                cout << "Enter description: ";
                getline(cin, description);
                et.addExpenses(date, amount, category, description);
                break;
            case 2:
                cout << "\nFilter options:" << endl;
                cout << "1. View all expenses" << endl;
                cout << "2. Filter by date range" << endl;
                cout << "3. Filter by category" << endl;
                cout << "Enter filter choice (1-3): ";
                cin >> filterChoice;
                et.getExpenses(filterChoice);
                break;
            case 3:
                et.getSummary();
                break;
            case 4:
                cout << "Thanks for using Expense Tracker!" << endl;
                cout << "Goodbye!" << endl;
                return 0;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    }
}