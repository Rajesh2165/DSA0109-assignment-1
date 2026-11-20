#include <iostream>
#include <stdexcept>
#include <string>

// --- TASK A5 PREDICTION: STACK UNWINDING & RAII ---
namespace TaskA5 {
    struct Guard {
        std::string n;
        explicit Guard(const std::string& s) : n(s) {}
        ~Guard() { std::cout << '~' << n << ' '; }
    };

    void f() {
        Guard g("f");
        throw 42;
    }

    void runPrediction() {
        std::cout << "--- 1. TASK A5: PREDICT THE OUTPUT (Stack Unwinding) ---\n";
        try {
            Guard m("main");
            f();
            std::cout << "not printed ";
        } catch (int x) {
            std::cout << "caught " << x;
        } catch (...) {
            std::cout << "other";
        }
        std::cout << "\n\n";
    }
}

// --- TASK B2 PREDICTION: PROCESS & RETHROW ---
namespace TaskB2Prediction {
    void validate(double amount) {
        if (amount < 0) throw std::invalid_argument("negative");
        if (amount > 1e6) throw std::out_of_range("too large");
        std::cout << "ok ";
    }

    void process(double amount) {
        try {
            validate(amount);
        } catch (const std::out_of_range& e) {
            std::cout << "[log " << e.what() << "] ";
            throw; // Rethrow to let caller handle
        }
    }

    void runPrediction() {
        std::cout << "--- 2. TASK B2: PREDICT THE OUTPUT (Partial Handling & throw;) ---\n";
        for (double a : {100.0, -5.0, 2e6}) {
            try {
                process(a);
                std::cout << "done ";
            } catch (const std::exception& e) {
                std::cout << "caught " << e.what() << ' ';
            }
        }
        std::cout << "\n\n";
    }
}

// --- TASK B2: COMPLETE THE CODE (Insurance Claim Approval & Audit) ---
class ClaimError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

double approve(double billed, double cover) {
    // TODO 1: Throw std::invalid_argument("negative amount") if billed or cover is
    // negative; throw ClaimError("exceeds cover") if billed > cover; otherwise return billed
    if (billed < 0 || cover < 0) {
        throw std::invalid_argument("negative amount");
    }
    if (billed > cover) {
        throw ClaimError("exceeds cover");
    }
    return billed;
}

double settle(double billed, double cover) {
    try {
        return approve(billed, cover);
    } catch (const ClaimError& e) {
        // TODO 2: Print "audit: " followed by the message, then rethrow the SAME exception
        std::cout << "audit: " << e.what() << '\n';
        throw;
    }
}

void runCompleteTheCode() {
    std::cout << "--- 3. TASK B2: COMPLETE THE CODE EXECUTION ---\n";
    double cases[][2] = {{40000, 50000}, {60000, 50000}, {-1, 50000}};
    for (auto& c : cases) {
        try {
            double paid = settle(c[0], c[1]);
            std::cout << "approved " << paid << '\n';
        } catch (const ClaimError& e) {
            std::cout << "claim rejected: " << e.what() << '\n';
        } catch (const std::exception& e) {
            std::cout << "error: " << e.what() << '\n';
        }
    }
}

int main() {
    std::cout << "=== TASK 02: ENGINEER ERROR CONDITIONS & RECOVERY ===\n\n";

    TaskA5::runPrediction();
    TaskB2Prediction::runPrediction();
    runCompleteTheCode();

    return 0;
}
