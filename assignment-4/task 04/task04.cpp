#include <iostream>
#include <iomanip>
#include <vector>
#include <memory>

// --- PREDICTION SNIPPET ---
namespace Prediction {
    struct Account {
        double rate() const { return 3.5; }
        virtual double vrate() const { return 3.5; }
        virtual ~Account() = default;
    };

    struct SeniorAccount : Account {
        double rate() const { return 4.0; }
        double vrate() const override { return 4.0; }
    };

    void run() {
        std::cout << "--- 1. PREDICT THE OUTPUT: EARLY VS LATE BINDING & SLICING ---\n";
        SeniorAccount s;
        Account* p = &s;
        Account copy = s; // Object slicing occurs here
        std::cout << p->rate() << ' ' << p->vrate() << ' ' << copy.vrate() << '\n';
    }
}

// --- REPAIRED DESIGN WITH VIRTUAL FUNCTIONS & VIRTUAL DESTRUCTOR ---
class SafeAccount {
protected:
    double balance;

public:
    explicit SafeAccount(double bal = 0.0) : balance(bal) {}
    virtual ~SafeAccount() {
        // Virtual destructor guarantees derived destructors are called through base pointer
    }

    virtual double rate() const { return 3.5; }
    virtual std::string accountType() const { return "Standard Account"; }
    double getBalance() const { return balance; }
};

class SafeSeniorAccount : public SafeAccount {
private:
    double* transactionHistory;
    int txCount;

public:
    explicit SafeSeniorAccount(double bal = 0.0)
        : SafeAccount(bal), transactionHistory(new double[100]), txCount(0) {}

    ~SafeSeniorAccount() override {
        delete[] transactionHistory;
    }

    double rate() const override { return 4.0; } // Correct senior citizen rate
    std::string accountType() const override { return "Senior Citizen Account"; }
};

int main() {
    std::cout << "=== TASK 4: POINTERS TO DERIVED CLASSES (FORENSICS & REPAIR) ===\n\n";

    Prediction::run();

    std::cout << "\n--- 2. REPAIRED CODE EXECUTION (VIRTUAL DISPATCH & RAII) ---\n";
    std::vector<std::unique_ptr<SafeAccount>> accounts;
    accounts.push_back(std::make_unique<SafeAccount>(50000.0));
    accounts.push_back(std::make_unique<SafeSeniorAccount>(100000.0));

    std::cout << std::fixed << std::setprecision(2);
    for (const auto& acc : accounts) {
        std::cout << acc->accountType() << " | Balance: Rs " << acc->getBalance()
                  << " | Interest Rate: " << acc->rate() << "%\n";
    }

    std::cout << "\nMemory safely managed: unique_ptr + virtual destructor prevents leaks and slicing.\n";

    return 0;
}
