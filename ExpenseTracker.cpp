// -------------------------------------------
// MSCS 632 Advanced Programming Languages
// Group Project
// Expense Tracker App
// -------------------------------------------

#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
using namespace std;

// Structure to hold individual expense data
struct Expense
{
    string date;        // Date in YYYY-MM-DD format
    float amount;       // Expense amount (must be positive)
    string category;    // Category of the expense (e.g., Food, Transport)
    string description; // Brief description of the expense
};

// Constants for array management
const int INITIAL_CAPACITY = 10; // Starting size for dynamic array
const int MAX_CATEGORIES = 50;   // Maximum number of unique categories

// ============================================================================
// UTILITY FUNCTIONS
// ============================================================================

/**
 * Displays the welcome banner for the application
 */
void printBanner()
{
    string banner = "---------------------------------------------------------------\n"
                    "||                                                           ||\n"
                    "||     Welcome to your personal expense tracking system!     ||\n"
                    "||                                                           ||\n"
                    "---------------------------------------------------------------\n";
    cout << banner << endl;
}

/**
 * Displays message when no expenses are found
 */
void noExpenseMessage()
{
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

/**
 * Displays the header for expense summary
 */
void printSummary()
{
    cout << "-------------------------------------------------------------------------" << endl;
    cout << "||                                                                     ||" << endl;
    cout << "||                          EXPENSE SUMMARY                            ||" << endl;
    cout << "||                                                                     ||" << endl;
    cout << "-------------------------------------------------------------------------" << endl;
    cout << "\nCategory Breakdown" << endl;
}

// ============================================================================
// INPUT VALIDATION FUNCTIONS
// ============================================================================

/**
 * Gets a valid positive amount from user input
 * @return Valid positive float amount
 */
float getValidAmount()
{
    float amount;
    while (true)
    {
        cout << "Enter amount: ";
        // Check if input is a valid number
        if (cin >> amount)
        {
            // Ensure amount is positive
            if (amount > 0)
            {
                return amount;
            }
            else
            {
                cout << "Error: Amount must be positive. Please try again.\n";
            }
        }
        else
        {
            // Handle invalid input (non-numeric)
            cout << "Error: Please enter a valid number.\n";
            cin.clear();                                         // Clear error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
        }
    }
}

/**
 * Gets a valid menu choice within specified range
 * @param min Minimum valid choice
 * @param max Maximum valid choice
 * @return Valid integer choice within range
 */
int getValidChoice(int min, int max)
{
    int choice;
    while (true)
    {
        // Check if input is a valid integer
        if (cin >> choice)
        {
            // Check if choice is within valid range
            if (choice >= min && choice <= max)
            {
                return choice;
            }
            else
            {
                cout << "Error: Please enter a number between " << min << " and " << max << ": ";
            }
        }
        else
        {
            // Handle invalid input (non-integer)
            cout << "Error: Please enter a valid number: ";
            cin.clear();                                         // Clear error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
        }
    }
}

/**
 * Validates date format (YYYY-MM-DD)
 * @param date String to validate
 * @return true if date format is valid, false otherwise
 */
bool isValidDate(const string &date)
{
    // Check length (YYYY-MM-DD = 10 characters)
    if (date.length() != 10)
        return false;

    // Check for dashes in correct positions
    if (date[4] != '-' || date[7] != '-')
        return false;

    // Check if year, month, day positions contain only digits
    for (int i = 0; i < 10; i++)
    {
        if (i == 4 || i == 7)
            continue; // Skip dash positions
        if (!isdigit(date[i]))
            return false;
    }
    return true;
}

/**
 * Gets a valid date from user input
 * @return Valid date string in YYYY-MM-DD format
 */
string getValidDate()
{
    string date;
    while (true)
    {
        cout << "Enter date (YYYY-MM-DD): ";
        cin >> date;
        // Validate date format
        if (isValidDate(date))
        {
            return date;
        }
        else
        {
            cout << "Error: Invalid date format. Please use YYYY-MM-DD format.\n";
        }
    }
}

// ============================================================================
// EXPENSE TRACKER CLASS
// ============================================================================

class ExpenseTracker
{
public:
    /**
     * Constructor - initializes the expense tracker with empty array
     */
    ExpenseTracker()
    {
        capacity = INITIAL_CAPACITY;
        size = 0;
        expenses = new Expense *[capacity]; // Dynamic array of pointers
    }

    /**
     * Destructor - cleans up dynamically allocated memory
     */
    ~ExpenseTracker()
    {
        // Free each allocated Expense object
        for (int i = 0; i < size; ++i)
        {
            delete expenses[i];
        }
        // Free the array of pointers
        delete[] expenses;
    }

    /**
     * Adds a new expense to the tracker
     * @param date Date of expense (YYYY-MM-DD format)
     * @param amount Amount of expense (positive value)
     * @param category Category of expense
     * @param description Description of expense
     */
    void addExpenses(string date, float amount, string category, string description)
    {
        try
        {
            // Resize array if needed
            if (size >= capacity)
            {
                resize();
            }

            // Validate required inputs
            if (category.empty())
            {
                cout << "Error: Category cannot be empty.\n";
                return;
            }
            if (description.empty())
            {
                cout << "Error: Description cannot be empty.\n";
                return;
            }

            // Create new expense and add to array
            Expense *newExpense = new Expense{date, amount, category, description};
            expenses[size++] = newExpense;
            cout << "\nExpense added successfully!\n";
        }
        catch (const bad_alloc &e)
        {
            // Handle memory allocation failure
            cout << "Error: Memory allocation failed. Cannot add expense.\n";
        }
        catch (const exception &e)
        {
            // Handle any other exceptions
            cout << "Error adding expense: " << e.what() << "\n";
        }
    }

    /**
     * Displays expenses based on filter choice
     * @param filterChoice 1=All, 2=Date range, 3=Category
     */
    void getExpenses(int filterChoice)
    {
        // Check if any expenses exist
        if (size == 0)
        {
            noExpenseMessage();
            return;
        }

        // Route to appropriate filter function
        switch (filterChoice)
        {
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

    /**
     * Displays summary of expenses grouped by category
     */
    void getSummary()
    {
        // Check if any expenses exist
        if (size == 0)
        {
            noExpenseMessage();
            return;
        }

        printSummary();

        // Arrays to store unique categories and their totals
        string uniqueCategories[MAX_CATEGORIES];
        float totals[MAX_CATEGORIES] = {0};
        int categoryCount = 0;
        float totalExpenses = 0.0f;

        // Process each expense to calculate category totals
        for (int i = 0; i < size; ++i)
        {
            bool found = false;

            // Check if category already exists
            for (int j = 0; j < categoryCount; ++j)
            {
                if (expenses[i]->category == uniqueCategories[j])
                {
                    totals[j] += expenses[i]->amount;
                    found = true;
                    break;
                }
            }

            // Add new category if not found
            if (!found)
            {
                if (categoryCount < MAX_CATEGORIES)
                {
                    uniqueCategories[categoryCount] = expenses[i]->category;
                    totals[categoryCount] = expenses[i]->amount;
                    categoryCount++;
                }
                else
                {
                    cout << "Warning: Maximum categories exceeded. Some categories may not be displayed.\n";
                }
            }

            // Add to overall total
            totalExpenses += expenses[i]->amount;
        }

        // Display category breakdown
        for (int i = 0; i < categoryCount; ++i)
        {
            cout << " - " << uniqueCategories[i] << ": $" << fixed << setprecision(2) << totals[i] << endl;
        }

        // Display total expenses
        cout << "\nTotal Expenses: $" << fixed << setprecision(2) << totalExpenses << endl;
    }

private:
    // Member variables
    Expense **expenses; // Dynamic array of pointers to Expense objects
    int capacity;       // Current capacity of the array
    int size;           // Current number of expenses stored

    /**
     * Doubles the capacity of the expenses array
     * Called when array becomes full
     */
    void resize()
    {
        try
        {
            // Double the capacity
            capacity *= 2;

            // Create new larger array
            Expense **newArr = new Expense *[capacity];

            // Copy existing pointers to new array
            for (int i = 0; i < size; ++i)
            {
                newArr[i] = expenses[i];
            }

            // Delete old array and update pointer
            delete[] expenses;
            expenses = newArr;
        }
        catch (const bad_alloc &e)
        {
            // Handle memory allocation failure
            cout << "Error: Memory allocation failed during resize.\n";
            throw; // Re-throw to handle in calling function
        }
    }

    /**
     * Prints all expenses without filtering
     */
    void printAllExpenses()
    {
        cout << "\n--- All Expenses ---\n";
        for (int i = 0; i < size; ++i)
        {
            cout << "Date: " << expenses[i]->date
                 << ", Amount: $" << fixed << setprecision(2) << expenses[i]->amount
                 << ", Category: " << expenses[i]->category
                 << ", Description: " << expenses[i]->description << endl;
        }
    }

    /**
     * Filters and displays expenses within a date range
     */
    void filterByDateRange()
    {
        // Get valid start and end dates from user
        string startDate = getValidDate();
        string endDate = getValidDate();

        // Ensure start date is before end date
        if (startDate > endDate)
        {
            cout << "Warning: Start date is after end date. Swapping dates.\n";
            swap(startDate, endDate);
        }

        cout << "\n--- Expenses from " << startDate << " to " << endDate << " ---\n";
        bool found = false;

        // Check each expense against date range
        for (int i = 0; i < size; ++i)
        {
            if (expenses[i]->date >= startDate && expenses[i]->date <= endDate)
            {
                cout << "Date: " << expenses[i]->date
                     << ", Amount: $" << fixed << setprecision(2) << expenses[i]->amount
                     << ", Category: " << expenses[i]->category
                     << ", Description: " << expenses[i]->description << endl;
                found = true;
            }
        }

        // Inform user if no expenses found in range
        if (!found)
        {
            cout << "No expenses found in the specified date range.\n";
        }
    }

    /**
     * Filters and displays expenses by category
     */
    void filterByCategory()
    {
        string categoryItem;
        cout << "Enter category to filter by: ";
        cin.ignore(); // Clear any leftover input from previous cin operations
        getline(cin, categoryItem);

        // Validate category input
        if (categoryItem.empty())
        {
            cout << "Error: Category cannot be empty.\n";
            return;
        }

        cout << "\n--- Expenses in category: " << categoryItem << " ---\n";
        bool found = false;

        // Check each expense for matching category
        for (int i = 0; i < size; ++i)
        {
            if (expenses[i]->category == categoryItem)
            {
                cout << "Date: " << expenses[i]->date
                     << ", Amount: $" << fixed << setprecision(2) << expenses[i]->amount
                     << ", Description: " << expenses[i]->description << endl;
                found = true;
            }
        }

        // Inform user if no expenses found in category
        if (!found)
        {
            cout << "No expenses found in category: " << categoryItem << "\n";
        }
    }
};

// ============================================================================
// MAIN FUNCTION
// ============================================================================

/**
 * Main program entry point
 * Handles the main menu loop and user interactions
 */
int main()
{
    // Display welcome banner
    printBanner();

    // Create expense tracker instance
    ExpenseTracker et;

    // Variables for user input
    int choice;
    string date;
    float amount;
    string category;
    string description;
    int filterChoice;

    // Main program loop
    while (true)
    {
        // Display main menu
        cout << "\n=== Expense Tracker Menu ===" << endl;
        cout << "1. Add Expense" << endl;
        cout << "2. View Expenses" << endl;
        cout << "3. Get Summary" << endl;
        cout << "4. Exit" << endl;

        // Get user's menu choice
        cout << "\nEnter your choice (1-4): ";
        choice = getValidChoice(1, 4);

        // Process user's choice
        switch (choice)
        {
        case 1: // Add new expense
            date = getValidDate();
            amount = getValidAmount();
            cin.ignore(); // Clear input buffer before getline
            cout << "Enter category: ";
            getline(cin, category);
            cout << "Enter description: ";
            getline(cin, description);
            et.addExpenses(date, amount, category, description);
            break;

        case 2: // View expenses with filtering options
            cout << "\nFilter options:" << endl;
            cout << "1. View all expenses" << endl;
            cout << "2. Filter by date range" << endl;
            cout << "3. Filter by category" << endl;
            cout << "Enter filter choice (1-3): ";
            filterChoice = getValidChoice(1, 3);
            et.getExpenses(filterChoice);
            break;

        case 3: // Display expense summary
            et.getSummary();
            break;

        case 4: // Exit program
            cout << "Thanks for using Expense Tracker!" << endl;
            cout << "Goodbye!" << endl;
            return 0;

        default: // Should never reach here due to input validation
            cout << "Invalid choice! Please try again." << endl;
        }
    }
}