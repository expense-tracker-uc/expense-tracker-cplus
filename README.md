# C++ Expense Tracker
A simple console-based expense tracking application written in C++. This application helps you track your daily expenses, categorize them, and generate summaries. It is designed for educational purposes and demonstrates manual memory management, input handling, and object-oriented programming.

## Features
- Add expenses with date, amount, category, and description.
- In-memory storage using dynamic array of pointers (manual memory management).
- Filter and view expenses by date range, category, or all entries.
- Generate summaries total by category, or a grand total of all expenses.

## Requirements
- C++11 or higher.
- Standard libraries only (no external dependencies).

## Usage
1. Compile the program using a C++ compiler (e.g., g++):
```
g++ ExpenseTracker.cpp -o ExpenseTracker
```
2. Run the program.
```
./ExpenseTracker
```
Follow the on-screen menu options:
   1. Add Expense
   2. View Expenses
   3. Get Summary
   4. Exit

## Data Storage
- Structure: Custom Expense struct.
- Storage mechanism: Dynamic array (``Expense**``) that resizes as needed.
- Memory is manually allocated (``new``) and deallocated (``delete``) in the class destructor.
- All data is stored in memory; it is lost upon exiting the program.

## Example Data Entry
```
Enter date (YYYY-MM-DD): 2025-05-21
Enter amount: 45.75
Enter category: Utilities
Enter description: Internet bill
```

## Example Summary Output
```
Category Breakdown
 - Food: $120.50
 - Utilities: $45.75
 - Transport: $30.00

Total Expenses: $196.25
```

## Error Handling
The application includes error handling for:
- Invalid date formats.
- Invalid user inputs.

## Components

**1. User Interface Layer**
  - Displays menu and banners.
  - Handles user prompts and input.
  - Utility functions:
    - ``printBanner()``: Displays welcome message.
    - ``printSummary()`` Formats summary display.
    - ``noExpenseMessage()``: Handles empty state.
   
**2. Business Logic Layer - ``ExpenseTracker`` class**
  - Core application logic.
  - Manages:
    - Dynamic memory allocation.
    - Filtering logic.
    - Summary generation.
  - Key methods:
    - ``addExpenses()``: Adds new expenses.
    - ``getExpenses(filterChoice)``: Retrieves and filters expenses.
    - ``getSummary()``: Generates expense summaries.
    - ``resize()``: (expands internal array when full).
   
  **3. Data Layer**
    - Uses a dynamic array of ``Expense*`` pointers.
    - Manual memory handling using ``new`` and ``delete``.
    - Resizable array simulates behavior similar to vectors

  ## Design Principles
  - Single Responsibility
    - UI logic, business logic, and data storage are cleanly separated.
  - Encapsulation
    - Class hides internal data members and exposes controlled interfaces.
  - Manual Memory Management
    - Demonstrates raw pointer management (without ``vector`` or ``shared_ptr``).
    - Educational example of heap allocation and deallocation.
   
  ## Error Handling
  
  **1. Input Validation**
  - Validates:
    - Numeric input (e.g., amount, menu choice).
    - Non-empty strings for category and description.
  - Rejects invalid input and re-prompts the user.

   **2. Empty State Handling**
   - Gracefully informs users when no expenses are found.

  ## Future Extensibility
  This design can be extended with:
  - File based or database storage.
  - Sorting or graphical summaries.
  - Budgeting features.
  - GUI or web-base interface.
  - Smart pointers for safer memory handling.

  ## Educational Value
  This project demonstrates:
  - Object-oriented design in C++.
  - Dynamic memory management.
  - Input validation and console I/O.
  - Manual array resizing (mimicking ``vector``).
  - Clean program architecture with separation of concerns.