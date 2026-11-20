#include <iostream>
#include <iomanip>
#include <cmath>

class Money {
private:
    long long paise;

public:
    Money(long long rupees = 0, int p = 0) : paise(rupees * 100 + p) {}

    // TODO 1: Overload + as a member function that returns a new Money object
    Money operator+(const Money& other) const {
        Money result;
        result.paise = paise + other.paise;
        return result;
    }

    // Overload - as member function
    Money operator-(const Money& other) const {
        Money result;
        result.paise = paise - other.paise;
        return result;
    }

    // Overload += as member function returning reference to *this
    Money& operator+=(const Money& other) {
        paise += other.paise;
        return *this;
    }

    // TODO 2: Overload == as a member
    bool operator==(const Money& other) const {
        return paise == other.paise;
    }

    // Overload < as a member
    bool operator<(const Money& other) const {
        return paise < other.paise;
    }

    // Overload << as a friend that prints formatted "Rs 200.00"
    friend std::ostream& operator<<(std::ostream& os, const Money& m) {
        long long totalPaise = m.paise;
        bool isNegative = totalPaise < 0;
        totalPaise = std::abs(totalPaise);
        long long r = totalPaise / 100;
        int p = totalPaise % 100;

        if (isNegative) os << "-";
        os << "Rs " << r << '.' << (p < 10 ? "0" : "") << p;
        return os;
    }

    long long getPaise() const { return paise; }
};

int main() {
    std::cout << "=== Q4: OVERLOADING ARITHMETIC AND STREAM OPERATORS ===\n\n";

    std::cout << "--- 1. RUNNING EXPECTED OUTPUT VERIFICATION ---\n";
    Money a(120, 75), b(79, 25);
    Money c = a + b;
    std::cout << c << '\n' << std::boolalpha << (c == Money(200)) << '\n';

    std::cout << "\n--- 2. PAISE CARRYING INTO RUPEES (Rs 0.75 + Rs 0.50) ---\n";
    Money item1(0, 75);
    Money item2(0, 50);
    Money sum = item1 + item2;
    std::cout << item1 << " + " << item2 << " = " << sum << '\n';

    std::cout << "\n--- 3. SUBTRACTION AND NEGATIVE AMOUNT HANDLING ---\n";
    Money wallet(50, 0);
    Money bill(75, 50);
    Money deficit = wallet - bill;
    std::cout << wallet << " - " << bill << " = " << deficit << '\n';

    std::cout << "\n--- 4. OPERATOR += AND ORDERING COMPARISON ---\n";
    Money balance(100, 0);
    balance += Money(25, 50);
    std::cout << "Balance after += Rs 25.50: " << balance << '\n';
    std::cout << "Is Rs 50.00 < Rs 100.00? " << (Money(50, 0) < Money(100, 0)) << '\n';

    return 0;
}
