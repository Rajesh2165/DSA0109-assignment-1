#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

// --- REPAIRED DESIGN: HIERARCHY WITH COMMON ABSTRACT BASE CLASS ---
class Staff {
protected:
    std::string name;
    int id;

public:
    Staff(const std::string& n, int i) : name(n), id(i) {}
    virtual ~Staff() = default; // Essential virtual destructor for polymorphic base

    virtual double pay() const = 0; // Pure virtual function

    virtual void printDetails() const {
        std::cout << "ID: " << id << " | Name: " << std::left << std::setw(16) << name 
                  << " | Pay: Rs " << std::fixed << std::setprecision(2) << pay() << '\n';
    }

    std::string getName() const { return name; }
    int getId() const { return id; }
};

// Salaried Staff base class factoring out Dearness Allowance (DA) rule
class RegularStaff : public Staff {
protected:
    double basic;
    static constexpr double DA_RATE = 0.42; // Centralized DA constant (42%)

public:
    RegularStaff(const std::string& n, int i, double b)
        : Staff(n, i), basic(b) {}

    double getBasicPay() const { return basic; }
    double getDA() const { return basic * DA_RATE; }
};

class Professor : public RegularStaff {
private:
    double researchAllowance;

public:
    Professor(const std::string& n, int i, double b, double research)
        : RegularStaff(n, i, b), researchAllowance(research) {}

    double pay() const override {
        return basic + getDA() + researchAllowance;
    }
};

class LabAssistant : public RegularStaff {
public:
    LabAssistant(const std::string& n, int i, double b)
        : RegularStaff(n, i, b) {}

    double pay() const override {
        return basic + getDA();
    }
};

class GuestFaculty : public Staff {
private:
    double hours;
    double hourlyRate;

public:
    GuestFaculty(const std::string& n, int i, double h, double r)
        : Staff(n, i), hours(h), hourlyRate(r) {}

    double pay() const override {
        return hours * hourlyRate;
    }
};

int main() {
    std::cout << "=== TASK 1: CLASS DESIGN REVIEW & REPAIRED HIERARCHY ===\n\n";

    std::vector<Staff*> payroll;
    payroll.push_back(new Professor("Dr. Ramanathan", 101, 80000.0, 15000.0));
    payroll.push_back(new LabAssistant("Mr. Suresh", 202, 35000.0));
    payroll.push_back(new GuestFaculty("Ms. Ananya", 303, 40.0, 1200.0));

    std::cout << "--- Processing All Staff Uniformly in One Polymorphic Loop ---\n";
    double totalDisbursement = 0.0;
    for (const Staff* s : payroll) {
        s->printDetails();
        totalDisbursement += s->pay();
    }

    std::cout << "---------------------------------------------------------\n";
    std::cout << "Total Payroll Disbursement: Rs " << std::fixed << std::setprecision(2) 
              << totalDisbursement << "\n\n";

    // Clean up heap allocations
    for (Staff* s : payroll) {
        delete s;
    }

    return 0;
}
