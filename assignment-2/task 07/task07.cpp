#include <iostream>
#include <iomanip>
#include <chrono>

// --- ORIGINAL DESIGN: Fixed Array with Linear Shifting ---
class ShiftingSavingsAccount {
private:
    long long accountNumber;
    double balance;
    int capacity;
    double* transactions;
    int count;

public:
    ShiftingSavingsAccount(long long accNo, double initialBalance, int cap = 50)
        : accountNumber(accNo), balance(initialBalance), capacity(cap), count(0) {
        transactions = new double[capacity];
        recordTransaction(initialBalance);
    }

    ~ShiftingSavingsAccount() {
        delete[] transactions;
    }

    void recordTransaction(double amount) {
        if (count < capacity) {
            transactions[count++] = amount;
        } else {
            // O(k) linear shift
            for (int i = 0; i < capacity - 1; ++i) {
                transactions[i] = transactions[i + 1];
            }
            transactions[capacity - 1] = amount;
        }
    }

    void deposit(double amount) {
        balance += amount;
        recordTransaction(amount);
    }

    double getBalance() const { return balance; }
};

// --- REVISED DESIGN: Dynamic Circular Ring Buffer (O(1) Insertion) ---
class CircularSavingsAccount {
private:
    long long accountNumber;
    double balance;
    int capacity;
    double* buffer;
    int head; // Points to oldest transaction
    int size; // Current number of stored transactions

public:
    CircularSavingsAccount(long long accNo, double initialBalance, int cap = 50)
        : accountNumber(accNo), balance(initialBalance), capacity(cap), head(0), size(0) {
        buffer = new double[capacity];
        recordTransaction(initialBalance);
    }

    ~CircularSavingsAccount() {
        delete[] buffer;
    }

    // Copy Constructor (Rule of Three)
    CircularSavingsAccount(const CircularSavingsAccount& other)
        : accountNumber(other.accountNumber), balance(other.balance),
          capacity(other.capacity), head(other.head), size(other.size) {
        buffer = new double[capacity];
        for (int i = 0; i < capacity; ++i) buffer[i] = other.buffer[i];
    }

    // Copy Assignment Operator
    CircularSavingsAccount& operator=(const CircularSavingsAccount& other) {
        if (this != &other) {
            delete[] buffer;
            accountNumber = other.accountNumber;
            balance = other.balance;
            capacity = other.capacity;
            head = other.head;
            size = other.size;
            buffer = new double[capacity];
            for (int i = 0; i < capacity; ++i) buffer[i] = other.buffer[i];
        }
        return *this;
    }

    // O(1) Insertion via modulo arithmetic
    void recordTransaction(double amount) {
        if (size < capacity) {
            int writeIdx = (head + size) % capacity;
            buffer[writeIdx] = amount;
            ++size;
        } else {
            buffer[head] = amount;
            head = (head + 1) % capacity;
        }
    }

    void deposit(double amount) {
        balance += amount;
        recordTransaction(amount);
    }

    void miniStatement() const {
        std::cout << "\n--------------------------------------------\n";
        std::cout << "CIRCULAR MINI-STATEMENT FOR ACCOUNT: " << accountNumber << '\n';
        std::cout << "Current Balance: Rs " << std::fixed << std::setprecision(2) << balance << '\n';
        std::cout << "Displaying last " << size << " transactions (Capacity: " << capacity << "):\n";
        for (int i = 0; i < size; ++i) {
            int idx = (head + i) % capacity;
            std::cout << "  [" << (i + 1) << "] ";
            if (buffer[idx] >= 0) {
                std::cout << "CREDIT : +Rs " << buffer[idx] << '\n';
            } else {
                std::cout << "DEBIT  : -Rs " << -buffer[idx] << '\n';
            }
        }
        std::cout << "--------------------------------------------\n";
    }

    double getBalance() const { return balance; }
};

int main() {
    std::cout << "=== Q7: DAY-4 DESIGN CHALLENGE - DIAGNOSE, REDESIGN AND VALIDATE ===\n\n";

    std::cout << "--- 1. CORRECTNESS VERIFICATION (LAST 50 TRANSACTIONS) ---\n";
    CircularSavingsAccount circAcc(19251124901LL, 10000.0, 50);

    for (int i = 1; i <= 60; ++i) {
        circAcc.deposit(100.0 * i);
    }
    circAcc.miniStatement();

    std::cout << "\n--- 2. BENCHMARK COMPARISON: 1,000,000 TRANSACTIONS (CAPACITY = 50) ---\n";
    const int TEST_TX_COUNT = 1000000;
    const int CAPACITY = 50;

    // Benchmark Original Shifting Design
    {
        ShiftingSavingsAccount shiftAcc(19251124901LL, 5000.0, CAPACITY);
        auto t0 = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < TEST_TX_COUNT; ++i) {
            shiftAcc.deposit(10.0);
        }
        auto t1 = std::chrono::high_resolution_clock::now();
        auto shiftMs = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();
        std::cout << "Original Shifting Design [O(k)]:  " << shiftMs << " ms\n";
    }

    // Benchmark Revised Circular Ring Buffer Design
    {
        CircularSavingsAccount circBench(19251124901LL, 5000.0, CAPACITY);
        auto t0 = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < TEST_TX_COUNT; ++i) {
            circBench.deposit(10.0);
        }
        auto t1 = std::chrono::high_resolution_clock::now();
        auto circMs = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();
        std::cout << "Revised Circular Design [O(1)]:   " << circMs << " ms\n";
    }

    std::cout << "\nValidation Conclusion: Circular buffer successfully reduces O(k) linear memory shifts to O(1) pointer updates!\n";

    return 0;
}
