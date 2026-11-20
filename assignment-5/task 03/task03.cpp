#include <iostream>
#include <iomanip>
#include <vector>
#include <chrono>
#include <random>
#include <stdexcept>

// --- APPROACH A: RUNTIME POLYMORPHISM VIA VIRTUAL FUNCTIONS ---
class PolymorphicBill {
public:
    virtual ~PolymorphicBill() = default;
    virtual double total() const = 0;
};

class PolyOPBill : public PolymorphicBill {
    double consultation, tests;
public:
    PolyOPBill(double c = 500.0, double t = 1200.0) : consultation(c), tests(t) {}
    double total() const override { return consultation + tests; }
};

class PolyIPBill : public PolymorphicBill {
    int days;
    double perDay, surgery;
public:
    PolyIPBill(int d = 3, double r = 2500.0, double s = 40000.0)
        : days(d), perDay(r), surgery(s) {}
    double total() const override { return (days * perDay) + surgery; }
};

// --- APPROACH B: PROCEDURAL STRUCT WITH ENUM TYPE AND SWITCH ---
enum class BillType { OP, IP };

struct SwitchBill {
    BillType type;
    double fee1; // consultation or perDay
    double fee2; // tests or surgery
    int days;

    double total() const {
        switch (type) {
            case BillType::OP:
                return fee1 + fee2;
            case BillType::IP:
                return (days * fee1) + fee2;
            default:
                return 0.0;
        }
    }
};

// --- EXCEPTION VS RETURN CODE VALIDATION BENCHMARK ---
enum class StatusCode { OK, NEGATIVE_AMOUNT, EXCEEDS_LIMIT };

// Validation via Return Code
StatusCode validateByCode(double amount) {
    if (amount < 0.0) return StatusCode::NEGATIVE_AMOUNT;
    if (amount > 1000000.0) return StatusCode::EXCEEDS_LIMIT;
    return StatusCode::OK;
}

// Validation via Exception
void validateByException(double amount) {
    if (amount < 0.0) throw std::invalid_argument("negative");
    if (amount > 1000000.0) throw std::out_of_range("exceeds limit");
}

int main() {
    std::cout << "=== TASK 03: VIRTUAL FUNCTIONS vs SWITCH vs EXCEPTIONS (THE COST) ===\n\n";

    // --- B3.1: CORRECTNESS ON SMALL DATA (10 BILLS) ---
    std::cout << "--- 1. B3.1: CORRECTNESS ON 10 BILLS ---\n";
    std::vector<PolymorphicBill*> polyBills;
    std::vector<SwitchBill> switchBills;

    for (int i = 0; i < 5; ++i) {
        polyBills.push_back(new PolyOPBill(500.0 + i * 10, 1200.0));
        switchBills.push_back({BillType::OP, 500.0 + i * 10, 1200.0, 0});

        polyBills.push_back(new PolyIPBill(3 + i, 2500.0, 40000.0));
        switchBills.push_back({BillType::IP, 2500.0, 40000.0, 3 + i});
    }

    double polyTotal10 = 0.0;
    for (const auto* b : polyBills) polyTotal10 += b->total();

    double switchTotal10 = 0.0;
    for (const auto& b : switchBills) switchTotal10 += b.total();

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Polymorphic Total (10 bills): Rs " << polyTotal10 << '\n';
    std::cout << "Switch-Based Total (10 bills): Rs " << switchTotal10 << '\n';
    std::cout << "Do both agree? " << std::boolalpha << (polyTotal10 == switchTotal10) << "\n\n";

    for (auto* b : polyBills) delete b;

    // --- B3.2: PERFORMANCE BENCHMARK (1,000, 1,000,000, and 10,000,000 BILLS) ---
    std::cout << "--- 2. B3.2: PERFORMANCE SCALING: VIRTUAL CALLS vs SWITCH DISPATCH ---\n";
    int testSizes[] = {1000, 1000000, 10000000};

    for (int N : testSizes) {
        std::cout << ">> Data Size: N = " << N << " bills\n";

        // Virtual Functions timing
        auto t0 = std::chrono::high_resolution_clock::now();
        double sumPoly = 0;
        PolyOPBill sampleOP(500, 1200);
        PolyIPBill sampleIP(3, 2500, 40000);
        PolymorphicBill* ptrs[2] = { &sampleOP, &sampleIP };
        for (int i = 0; i < N; ++i) {
            sumPoly += ptrs[i & 1]->total();
        }
        auto t1 = std::chrono::high_resolution_clock::now();
        auto polyMs = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();

        // Switch Statement timing
        auto t2 = std::chrono::high_resolution_clock::now();
        double sumSwitch = 0;
        SwitchBill sBills[2] = {
            {BillType::OP, 500, 1200, 0},
            {BillType::IP, 2500, 40000, 3}
        };
        for (int i = 0; i < N; ++i) {
            sumSwitch += sBills[i & 1].total();
        }
        auto t3 = std::chrono::high_resolution_clock::now();
        auto switchMs = std::chrono::duration_cast<std::chrono::milliseconds>(t3 - t2).count();

        std::cout << "   Virtual Dispatch Time: " << polyMs << " ms (Sum: " << sumPoly << ")\n";
        std::cout << "   Switch Dispatch Time:  " << switchMs << " ms (Sum: " << sumSwitch << ")\n";
    }

    // --- B3.3: COST OF EXCEPTIONS BENCHMARK (1,000,000 BILLS) ---
    std::cout << "\n--- 3. B3.3: COST OF EXCEPTIONS VS RETURN CODES (1,000,000 BILLS) ---\n";
    const int VALIDATION_COUNT = 1000000;
    double failureRatios[] = {0.0, 0.01, 0.50};

    for (double ratio : failureRatios) {
        std::cout << ">> Error Rate: " << (ratio * 100) << "%\n";

        // Generate synthetic test amounts
        std::vector<double> amounts(VALIDATION_COUNT);
        int failThreshold = static_cast<int>(VALIDATION_COUNT * ratio);
        for (int i = 0; i < VALIDATION_COUNT; ++i) {
            amounts[i] = (i < failThreshold) ? -50.0 : 1500.0;
        }

        // Benchmark Return Codes
        auto t0 = std::chrono::high_resolution_clock::now();
        int errCountCode = 0;
        for (int i = 0; i < VALIDATION_COUNT; ++i) {
            StatusCode status = validateByCode(amounts[i]);
            if (status != StatusCode::OK) {
                ++errCountCode;
            }
        }
        auto t1 = std::chrono::high_resolution_clock::now();
        auto codeMs = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();

        // Benchmark Exceptions
        auto t2 = std::chrono::high_resolution_clock::now();
        int errCountEx = 0;
        for (int i = 0; i < VALIDATION_COUNT; ++i) {
            try {
                validateByException(amounts[i]);
            } catch (const std::exception&) {
                ++errCountEx;
            }
        }
        auto t3 = std::chrono::high_resolution_clock::now();
        auto exMs = std::chrono::duration_cast<std::chrono::milliseconds>(t3 - t2).count();

        std::cout << "   Return Codes Time: " << codeMs << " ms (Errors: " << errCountCode << ")\n";
        std::cout << "   Exceptions Time:   " << exMs << " ms (Errors: " << errCountEx << ")\n";
    }

    return 0;
}
