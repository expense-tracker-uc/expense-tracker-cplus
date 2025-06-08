// ===================================================================
// MSCS 632 Advanced Programming Languages
// Group Project - Expense Tracker Testing Suite
// C++ Implementation Tests
// ===================================================================

#include <iostream>
#include <cassert>
#include <string>
#include <iomanip>
using namespace std;

// Copy necessary structures and functions for testing
struct Expense
{
    string date;
    float amount;
    string category;
    string description;
};

// Copy of isValidDate function from main code
bool isValidDate(const string &date)
{
    if (date.length() != 10)
        return false;
    if (date[4] != '-' || date[7] != '-')
        return false;
    for (int i = 0; i < 10; i++)
    {
        if (i == 4 || i == 7)
            continue;
        if (!isdigit(date[i]))
            return false;
    }
    return true;
}

// Simplified ExpenseTracker for testing
class TestableExpenseTracker
{
private:
    Expense **expenses;
    int capacity;
    int size;

    void resize()
    {
        capacity *= 2;
        Expense **newArr = new Expense *[capacity];
        for (int i = 0; i < size; ++i)
        {
            newArr[i] = expenses[i];
        }
        delete[] expenses;
        expenses = newArr;
    }

public:
    TestableExpenseTracker() : capacity(10), size(0)
    {
        expenses = new Expense *[capacity];
    }

    ~TestableExpenseTracker()
    {
        for (int i = 0; i < size; ++i)
        {
            delete expenses[i];
        }
        delete[] expenses;
    }

    bool addExpense(const string &date, float amount, const string &category, const string &description)
    {
        if (!isValidDate(date) || amount <= 0 || category.empty() || description.empty())
            return false;

        if (size >= capacity)
            resize();

        expenses[size++] = new Expense{date, amount, category, description};
        return true;
    }

    int getSize() const { return size; }

    float getTotalAmount() const
    {
        float total = 0.0f;
        for (int i = 0; i < size; ++i)
        {
            total += expenses[i]->amount;
        }
        return total;
    }

    int countByCategory(const string &category) const
    {
        int count = 0;
        for (int i = 0; i < size; ++i)
        {
            if (expenses[i]->category == category)
                count++;
        }
        return count;
    }

    int countByDateRange(const string &startDate, const string &endDate) const
    {
        int count = 0;
        for (int i = 0; i < size; ++i)
        {
            if (expenses[i]->date >= startDate && expenses[i]->date <= endDate)
                count++;
        }
        return count;
    }
};

// Simple test helpers
int tests_run = 0;
int tests_passed = 0;

void test_assert(bool condition, const string &test_name)
{
    tests_run++;
    if (condition)
    {
        tests_passed++;
        cout << "✓ " << test_name << endl;
    }
    else
    {
        cout << "✗ " << test_name << " FAILED" << endl;
    }
}

void test_float_equal(float expected, float actual, const string &test_name)
{
    tests_run++;
    if (abs(expected - actual) < 0.01)
    {
        tests_passed++;
        cout << "✓ " << test_name << endl;
    }
    else
    {
        cout << "✗ " << test_name << " FAILED (Expected: " << expected << ", Got: " << actual << ")" << endl;
    }
}

// ===================================================================
// TEST FUNCTIONS
// ===================================================================

void test_date_validation()
{
    cout << "\n--- Date Validation Tests ---" << endl;

    test_assert(isValidDate("2025-05-01"), "Valid date format");
    test_assert(isValidDate("2025-12-31"), "Valid date end of year");
    test_assert(!isValidDate("2025/05/01"), "Invalid separator rejected");
    test_assert(!isValidDate("05-01-2025"), "Wrong order rejected");
    test_assert(!isValidDate("2025-5-1"), "Missing zeros rejected");
    test_assert(!isValidDate("invalid"), "Non-date string rejected");
    test_assert(!isValidDate(""), "Empty string rejected");
}

void test_basic_operations()
{
    cout << "\n--- Basic Operations Tests ---" << endl;

    TestableExpenseTracker tracker;

    test_assert(tracker.getSize() == 0, "Empty tracker initialization");
    test_float_equal(0.0f, tracker.getTotalAmount(), "Empty tracker total");

    test_assert(tracker.addExpense("2025-05-01", 15.99f, "Food", "Lunch"), "Add valid expense");
    test_assert(tracker.getSize() == 1, "Size after adding expense");
    test_float_equal(15.99f, tracker.getTotalAmount(), "Total after adding expense");
}

void test_invalid_inputs()
{
    cout << "\n--- Invalid Input Tests ---" << endl;

    TestableExpenseTracker tracker;

    test_assert(!tracker.addExpense("invalid-date", 10.0f, "Test", "Test"), "Reject invalid date");
    test_assert(!tracker.addExpense("2025-05-01", -5.0f, "Test", "Test"), "Reject negative amount");
    test_assert(!tracker.addExpense("2025-05-01", 10.0f, "", "Test"), "Reject empty category");
    test_assert(!tracker.addExpense("2025-05-01", 10.0f, "Test", ""), "Reject empty description");
    test_assert(tracker.getSize() == 0, "No invalid expenses added");
}

void test_filtering()
{
    cout << "\n--- Filtering Tests ---" << endl;

    TestableExpenseTracker tracker;

    // Add test data
    tracker.addExpense("2025-05-01", 15.99f, "Food", "Lunch");
    tracker.addExpense("2025-05-02", 50.00f, "Transport", "Gas");
    tracker.addExpense("2025-05-03", 25.50f, "Food", "Dinner");
    tracker.addExpense("2025-05-05", 100.00f, "Entertainment", "Concert");

    test_assert(tracker.countByCategory("Food") == 2, "Filter by Food category");
    test_assert(tracker.countByCategory("Transport") == 1, "Filter by Transport category");
    test_assert(tracker.countByCategory("NonExistent") == 0, "Filter by non-existent category");

    test_assert(tracker.countByDateRange("2025-05-01", "2025-05-03") == 3, "Date range filter (inclusive)");
    test_assert(tracker.countByDateRange("2025-05-02", "2025-05-04") == 2, "Date range filter (partial)");
    test_assert(tracker.countByDateRange("2025-05-06", "2025-05-07") == 0, "Date range filter (no matches)");
}

void test_memory_management()
{
    cout << "\n--- Memory Management Tests ---" << endl;

    TestableExpenseTracker tracker;

    // Test dynamic resizing by adding more than initial capacity
    for (int i = 1; i <= 15; ++i)
    {
        string date = "2025-05-" + (i < 10 ? "0" + to_string(i) : to_string(i));
        tracker.addExpense(date, 10.0f, "Test", "Test expense");
    }

    test_assert(tracker.getSize() == 15, "Dynamic array resize handling");
    test_float_equal(150.0f, tracker.getTotalAmount(), "Data integrity after resize");
}

void test_edge_cases()
{
    cout << "\n--- Edge Case Tests ---" << endl;

    TestableExpenseTracker tracker;

    test_assert(tracker.addExpense("2025-01-01", 0.01f, "Test", "Min amount"), "Minimum positive amount");
    test_assert(tracker.addExpense("2025-12-31", 9999.99f, "Test", "Large amount"), "Large amount handling");
    test_assert(tracker.addExpense("2025-05-01", 10.0f, "A", "B"), "Single character strings");
}

void test_integration()
{
    cout << "\n--- Integration Test ---" << endl;

    TestableExpenseTracker tracker;

    // Complete workflow test
    tracker.addExpense("2025-05-01", 15.99f, "Food", "Lunch");
    tracker.addExpense("2025-05-02", 50.00f, "Transport", "Gas");

    test_assert(tracker.getSize() == 2, "Integration: expense count");
    test_assert(tracker.countByCategory("Food") == 1, "Integration: category filtering");
    test_float_equal(65.99f, tracker.getTotalAmount(), "Integration: total calculation");
}

// ===================================================================
// MAIN TEST RUNNER
// ===================================================================

int main()
{
    cout << "C++ EXPENSE TRACKER TEST SUITE" << endl;
    cout << string(50, '=') << endl;

    // Run all test suites
    test_date_validation();
    test_basic_operations();
    test_invalid_inputs();
    test_filtering();
    test_memory_management();
    test_edge_cases();
    test_integration();

    // Print summary
    cout << "\n"
         << string(50, '=') << endl;
    cout << "TEST SUMMARY: " << tests_passed << "/" << tests_run << " tests passed" << endl;
    if (tests_passed == tests_run)
    {
        cout << "🎉 ALL TESTS PASSED!" << endl;
    }
    else
    {
        cout << "❌ " << (tests_run - tests_passed) << " tests failed" << endl;
    }
    cout << string(50, '=') << endl;

    return (tests_passed == tests_run) ? 0 : 1;
}