#include <iostream>
#include <string>

// --- TASK A2 PREDICTION CODE ---
namespace TaskA2 {
    struct Bill {
        virtual ~Bill() { std::cout << "~Bill "; }
        virtual double total() const = 0;
        void show() const { std::cout << total() << ' '; }
    };

    struct OPBill : Bill {
        ~OPBill() override { std::cout << "~OPBill "; }
        double total() const override { return 500; }
    };

    void runPrediction() {
        std::cout << "--- 1. TASK A2: PREDICT THE OUTPUT (Runtime Binding & Virtual Destructor) ---\n";
        Bill* b = new OPBill;
        b->show();
        delete b;
        std::cout << '\n';
    }
}

// --- TASK B1: COMPLETE THE CODE (Polymorphic Billing Hierarchy) ---
class Bill {
protected:
    std::string patient;

public:
    explicit Bill(const std::string& p) : patient(p) {}
    virtual ~Bill() = default;

    // TODO 1: Declare a pure virtual function total() const returning double, and a
    // virtual function type() const returning "Bill"
    virtual double total() const = 0;
    virtual std::string type() const { return "Bill"; }

    void print() const {
        std::cout << type() << ' ' << patient << ": " << total() << '\n';
    }

    std::string getPatient() const { return patient; }
};

class OutPatient : public Bill {
    double consultation, tests;

public:
    OutPatient(const std::string& p, double c, double t)
        : Bill(p), consultation(c), tests(t) {}

    // TODO 2: Override total() as consultation + tests, and type() as "OP"
    double total() const override {
        return consultation + tests;
    }

    std::string type() const override {
        return "OP";
    }
};

class InPatient : public Bill {
    int days;
    double perDay, surgery;

public:
    InPatient(const std::string& p, int d, double rate, double s)
        : Bill(p), days(d), perDay(rate), surgery(s) {}

    // TODO 3: Override total() as days * perDay + surgery, and type() as "IP"
    double total() const override {
        return (days * perDay) + surgery;
    }

    std::string type() const override {
        return "IP";
    }
};

int main() {
    std::cout << "=== TASK 01: IMPLEMENT AND VALIDATE POLYMORPHIC BILLING ===\n\n";

    TaskA2::runPrediction();

    std::cout << "\n--- 2. TASK B1: COMPLETE THE CODE EXECUTION ---\n";
    Bill* bills[] = {
        new OutPatient("Ravi", 500, 1200),
        new InPatient("Meena", 3, 2500, 40000)
    };

    double sum = 0;
    for (Bill* b : bills) {
        b->print(); // runtime polymorphism
        sum += b->total();
    }
    std::cout << "Total " << sum << '\n';

    for (Bill* b : bills) {
        delete b; // virtual destructor runs the right destructor
    }

    return 0;
}
