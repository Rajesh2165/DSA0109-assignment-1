#include <iostream>
#include <iomanip>
#include <string>

class SavingsAccount {
private:
    long long accountNumber;
    double balance;
    static const int MAX_TX = 10;
    double transactions[MAX_TX];
    int count; // Number of recorded transactions (up to MAX_TX)

    void recordTransaction(double amount) {
        if (count < MAX_TX) {
            transactions[count++] = amount;
        } else {
            // Shifting implementation: discard oldest transaction (index 0)
            for (int i = 0; i < MAX_TX - 1; ++i) {
                transactions[i] = transactions[i + 1];
            }
            transactions[MAX_TX - 1] = amount;
        }
    }

public:
    // Constructor defined inside class
    SavingsAccount(long long accNo, double initialBalance)
        : accountNumber(accNo), balance(initialBalance), count(0) {
        recordTransaction(initialBalance);
    }

    // Member function defined inside class
    bool deposit(double amount) {
        if (amount <= 0) return false;
        balance += amount;
        recordTransaction(amount);
        return true;
    }

    // Member functions declared here, defined outside using scope resolution operator ::
    bool withdraw(double amount);
    void miniStatement() const;
};

// Definition of withdraw outside class
bool SavingsAccount::withdraw(double amount) {
    if (amount <= 0 || amount > balance) {
        std::cout << "[Withdrawal Failed: Insufficient funds or invalid amount: " << amount << "]\n";
        return false;
    }
    balance -= amount;
    recordTransaction(-amount);
    return true;
}

// Definition of miniStatement outside class
void SavingsAccount::miniStatement() const {
    std::cout << "\n--------------------------------------------\n";
    std::cout << "MINI-STATEMENT FOR ACCOUNT: " << accountNumber << '\n';
    std::cout << "Current Balance: Rs " << std::fixed << std::setprecision(2) << balance << '\n';
    std::cout << "Last " << count << " Transactions:\n";
    for (int i = 0; i < count; ++i) {
        std::cout << "  [" << (i + 1) << "] ";
        if (transactions[i] >= 0) {
            std::cout << "CREDIT : +Rs " << transactions[i] << '\n';
        } else {
            std::cout << "DEBIT  : -Rs " << -transactions[i] << '\n';
        }
    }
    std::cout << "--------------------------------------------\n";
}

int main() {
    std::cout << "=== Q4: SPECIFYING A CLASS WITH AN ARRAY INSIDE IT ===\n";

    SavingsAccount acc(19251124901LL, 5000.0);

    // Perform a series of 12 transactions to observe behavior when 11th and 12th arrive
    std::cout << "\nExecuting 12 transactions on Account 19251124901...\n";
    acc.deposit(1000.0);  // tx 2
    acc.withdraw(500.0);  // tx 3
    acc.deposit(2000.0);  // tx 4
    acc.withdraw(300.0);  // tx 5
    acc.deposit(1500.0);  // tx 6
    acc.withdraw(700.0);  // tx 7
    acc.deposit(2500.0);  // tx 8
    acc.withdraw(400.0);  // tx 9
    acc.deposit(800.0);   // tx 10 (buffer full)
    
    std::cout << "\nBuffer full after 10 transactions. Now adding 11th and 12th transactions:\n";
    acc.deposit(999.0);   // tx 11 (displaces initial deposit 5000)
    acc.withdraw(250.0);  // tx 12 (displaces 1000 deposit)

    acc.miniStatement();

    return 0;
}
