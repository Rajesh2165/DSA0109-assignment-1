#include <iostream>
#include <iomanip>
#include <string>

// Courier Parcel Struct
struct Parcel {
    double weightKg;
    bool express;
    bool insured;
};

// 1. Overloaded function for weight in grams (int)
double charge(int weightGrams) {
    std::cout << "[Called charge(int weightGrams)] ";
    // Base rate: Rs 0.05 per gram
    return weightGrams * 0.05;
}

// 2. Overloaded function for weight in kg (double) with default arguments from the right
double charge(double weightKg, bool express = false, bool insured = false) {
    std::cout << "[Called charge(double, bool=" << express << ", bool=" << insured << ")] ";
    double fee = weightKg * 50.0; // Rs 50 per kg
    if (express) fee += 100.0;   // Rs 100 express fee
    if (insured) fee += 50.0;    // Rs 50 insurance fee
    return fee;
}

// 3. Overloaded function for Parcel object
double charge(const Parcel& p) {
    std::cout << "[Called charge(const Parcel&)] ";
    return charge(p.weightKg, p.express, p.insured);
}

int main() {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "=== Q3: DEFAULT ARGUMENTS AND FUNCTION OVERLOADING ===\n\n";

    std::cout << "Testing 6 distinct calls to verify overload resolution:\n";

    // Call 1: charge(2) -> Exact match with int (weight in grams)
    std::cout << "1. charge(2): ";
    double c1 = charge(2);
    std::cout << "-> Rs " << c1 << '\n';

    // Call 2: charge(2.0f) -> float standard conversion to double
    std::cout << "2. charge(2.0f): ";
    double c2 = charge(2.0f);
    std::cout << "-> Rs " << c2 << '\n';

    // Call 3: charge(2.5) -> double literal, uses default arguments
    std::cout << "3. charge(2.5): ";
    double c3 = charge(2.5);
    std::cout << "-> Rs " << c3 << '\n';

    // Call 4: charge(2.5, true) -> double, express=true, default insured=false
    std::cout << "4. charge(2.5, true): ";
    double c4 = charge(2.5, true);
    std::cout << "-> Rs " << c4 << '\n';

    // Call 5: charge(2.5, true, true) -> double, express=true, insured=true
    std::cout << "5. charge(2.5, true, true): ";
    double c5 = charge(2.5, true, true);
    std::cout << "-> Rs " << c5 << '\n';

    // Call 6: charge(Parcel) -> exact match with Parcel overload
    Parcel p{3.5, true, false};
    std::cout << "6. charge(Parcel{3.5kg, express=true, insured=false}): ";
    double c6 = charge(p);
    std::cout << "-> Rs " << c6 << '\n';

    return 0;
}
