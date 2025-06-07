# C++ Expense Tracker

A console-based expense tracking application written in C++ demonstrating manual memory management, structs, pointer operations, static typing, and low-level system control.

## Features

- Add expenses with date, amount, category, and description
- Dynamic memory allocation with manual memory management
- Filter and search expenses by:
  - Date range (string comparison for YYYY-MM-DD format)
  - Category (case-sensitive matching)
- Generate expense summaries:
  - Total expenses by category using fixed-size arrays
  - Overall total expenses with precise calculations
- Comprehensive input validation and error handling
- Formatted console output with manual string formatting

## Requirements

- C++ compiler (g++, clang++, or MSVC)
- C++11 standard or later
- No external dependencies required

## How to Run/Execute the Application

### Method 1: Direct Compilation and Execution
```bash
g++ -std=c++11 expense_tracker.cpp -o expense_tracker
./expense_tracker
```

### Method 2: Windows (Visual Studio/MSVC)
```cmd
cl /EHsc expense_tracker.cpp
expense_tracker.exe
```

### Method 3: Debug Mode
```bash
g++ -std=c++11 -g -Wall expense_tracker.cpp -o expense_tracker_debug
./expense_tracker_debug
```

## Running Tests

Execute the test suite to verify functionality:

```bash
# Compile tests
g++ -std=c++11 test_expense_tracker.cpp -o test_expense_tracker

# Run tests
./test_expense_tracker
```

### Test Coverage
The test suite includes:
- **Unit Tests**: Core functionality testing (add, view, filter, summary)
- **Memory Management Tests**: Dynamic array resizing and cleanup
- **Input Validation Tests**: Date format, boundary values, invalid inputs
- **Integration Tests**: Complete workflow testing
- **Edge Case Tests**: Boundary conditions and error scenarios

## Language-Specific Features Demonstrated

### 1. **Manual Memory Management**
- Dynamic memory allocation using `new` and `delete`
- Custom destructor for proper cleanup
- Manual array resizing with pointer copying

```cpp
// Dynamic array of pointers
Expense** expenses = new Expense*[capacity];

// Manual cleanup in destructor
~ExpenseTracker() {
    for (int i = 0; i < size; ++i) {
        delete expenses[i];
    }
    delete[] expenses;
}
```

### 2. **Structs and Data Modeling**
- Structured data representation
- Direct memory layout control
- Efficient data access patterns

```cpp
struct Expense {
    string date;        // YYYY-MM-DD format
    float amount;       // Positive monetary value
    string category;    // Expense category
    string description; // Expense description
};
```

### 3. **Pointer Operations and References**
- Array of pointers for efficient memory usage
- Pointer dereferencing for data access
- Reference parameters for efficient function calls

```cpp
Expense** expenses;  // Array of pointers to Expense objects
expenses[i]->amount  // Pointer dereferencing
```

### 4. **Static Typing and Compile-time Checking**
- Strong type system with compile-time validation
- Explicit type declarations
- Type safety enforcement

```cpp
float getValidAmount();              // Return type specified
bool isValidDate(const string &date); // Parameter type specified
```

### 5. **Low-level Input/Output Control**
- Manual input stream management
- Formatted output using iomanip
- Buffer management and error clearing

```cpp
cin.clear();                                         // Clear error flags
cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
cout << fixed << setprecision(2) << amount;          // Formatted output
```

## Usage Instructions

### Starting the Application
1. Compile using one of the methods above
2. Run the executable
3. The welcome banner will display
4. Main menu will appear with 4 options

### Menu Options

#### 1. Add Expense
```
Enter date (YYYY-MM-DD): 2025-05-01
Enter amount: 25.50
Enter category: Food
Enter description: Lunch at restaurant
```

#### 2. View Expenses
Choose from filtering options:
- **View all expenses**: Shows complete expense list in chronological order
- **Filter by date range**:
  ```
  Enter start date (YYYY-MM-DD): 2025-05-01
  Enter end date (YYYY-MM-DD): 2025-05-31
  ```
- **Filter by category** (case-sensitive):
  ```
  Enter category to filter by: Food
  ```

#### 3. Get Summary
Displays:
- Category breakdown with individual totals
- Overall total expenses
- Formatted output with currency symbols

#### 4. Exit
Properly deallocates memory and closes application

## Data Storage Architecture

Expenses are stored using C++'s manual memory management:

```cpp
// Dynamic array structure
Expense** expenses;  // Array of pointers to Expense structs
int capacity;        // Current array capacity
int size;           // Number of expenses stored

// Example expense allocation
Expense* newExpense = new Expense{
    "2025-05-01",    // date
    25.50f,          // amount
    "Food",          // category
    "Lunch"          // description
};
expenses[size++] = newExpense;
```

**Memory Management**: Manual allocation and deallocation with proper cleanup in destructor.

## Testing and Debugging

### Test Results Summary
✅ **All core functionality tested and working**:
- Expense addition with comprehensive validation
- Date format validation (YYYY-MM-DD strict format)
- Category filtering (case-sensitive exact matching)
- Date range filtering using string comparison
- Summary calculations with floating-point precision
- Dynamic memory management and array resizing

### Identified Issues and Status
1. **Memory Management**: ✅ **RESOLVED** - Implemented proper destructor and cleanup
2. **Input Validation**: ✅ **RESOLVED** - Added comprehensive validation for all inputs
3. **Dynamic Array Resizing**: ✅ **RESOLVED** - Implemented automatic capacity doubling
4. **Date Comparison Logic**: ✅ **RESOLVED** - Uses string comparison (works for YYYY-MM-DD)
5. **Case Sensitivity**: ⚠️ **KNOWN BEHAVIOR** - Category filtering is case-sensitive (by design)
6. **Data Persistence**: ⚠️ **KNOWN LIMITATION** - Data not persisted between sessions

### Debugging Process
1. **Manual Testing**: Each feature tested with various input scenarios and edge cases
2. **Memory Testing**: Valgrind/similar tools used to verify no memory leaks
3. **Automated Tests**: 25+ unit tests covering core functionality and edge cases
4. **Boundary Testing**: Tested with minimum/maximum values and invalid inputs
5. **Integration Testing**: Complete workflows tested end-to-end

### Memory Management Verification
- **No Memory Leaks**: All dynamically allocated memory properly deallocated
- **Proper Cleanup**: Destructor handles cleanup of both individual expenses and array
- **Safe Resizing**: Array expansion preserves existing data and cleans up old memory
- **Exception Safety**: Memory allocation failures handled gracefully

## Architecture Overview

### 1. **Data Layer (Struct-based)**
- **Structure**: `Expense` struct with fixed data layout
- **Purpose**: Efficient memory representation of expense data
- **Features**: Direct memory access, cache-friendly layout

### 2. **Business Logic Layer (ExpenseTracker Class)**
- **Methods**: `addExpenses()`, `getExpenses()`, `getSummary()`
- **Purpose**: Core application logic with manual resource management
- **Features**: Input validation, memory management, business rules

### 3. **Utility Layer (Global Functions)**
- **Functions**: `printBanner()`, `getValidAmount()`, `isValidDate()`, etc.
- **Purpose**: Reusable utility functions and input validation
- **Features**: Input sanitization, formatted output, error handling

### 4. **Memory Management Layer**
- **Structure**: Dynamic array of pointers with manual resizing
- **Purpose**: Efficient memory usage and growth management
- **Features**: Custom allocation, deallocation, and resizing logic

## Error Handling Strategy

### Input Validation
- **Date Format**: Strict YYYY-MM-DD validation with character-by-character checking
- **Amount Validation**: Positive number validation with error recovery
- **String Validation**: Non-empty category and description enforcement
- **Range Validation**: Menu choice validation with retry logic

### Memory Management Error Handling
- **Allocation Failures**: `bad_alloc` exception handling with graceful degradation
- **Cleanup Guarantee**: RAII principles with destructor-based cleanup
- **Resource Safety**: Exception-safe resource management

### User Experience
- **Clear Error Messages**: Specific error descriptions with correction guidance
- **Input Recovery**: Automatic retry on invalid input with cleared buffers
- **Graceful Failures**: No crashes on invalid input or memory issues

## Performance Characteristics

- **Memory Efficiency**: Pointer-based storage minimizes memory overhead
- **Search Performance**: Linear search O(n) suitable for personal expense tracking
- **Memory Growth**: Geometric growth (2x) for amortized O(1) insertion
- **Cache Performance**: Struct-based layout optimizes memory access patterns

## C++ Specific Advantages

1. **Memory Control**: Precise control over memory allocation and layout
2. **Performance**: Compiled code with minimal runtime overhead
3. **Type Safety**: Compile-time error detection and type checking
4. **Resource Management**: Deterministic cleanup with RAII principles
5. **System Integration**: Direct system calls and low-level operations

## Known Limitations

1. **Data Persistence**: No file I/O implementation (intentional for this version)
2. **Concurrent Access**: Single-threaded design, not thread-safe
3. **String Operations**: Basic string handling without advanced parsing
4. **Date Validation**: Format-only validation, no semantic date checking
5. **Scalability**: Linear search performance limits for very large datasets

## Future Enhancements for Final Deliverable

1. **File Persistence**: Binary file I/O for data storage
2. **STL Integration**: Optional STL containers for comparison
3. **Template Usage**: Generic programming for different data types
4. **Smart Pointers**: Modern C++ memory management alternatives
5. **Exception Specifications**: Enhanced exception handling with custom types

## Development Information

- **Language**: C++11 standard
- **Paradigm**: Object-oriented with procedural elements
- **Memory Model**: Manual memory management with RAII
- **Compilation**: Single translation unit, no external dependencies
- **Test Coverage**: 25+ tests covering functionality, memory management, and edge cases