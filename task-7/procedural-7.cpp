#include <iostream>

enum class Zone { Inner, Middle, Outer };

long long calculateFare(Zone z, bool isPeak) {
    long long fare = 0;
    if (z == Zone::Inner) {
        fare = 1000;
    } else if (z == Zone::Middle) {
        fare = 2000;
    } else if (z == Zone::Outer) {
        fare = 3000;
    }
    if (isPeak) {
        fare += (fare * 20) / 100;
    }
    return fare;
}

bool canTravel(long long balance, long long fare) {
    return (balance - fare) >= 5000;
}

bool deduct(long long& balance, long long fare) {
    if (canTravel(balance, fare)) {
        balance -= fare;
        return true;
    }
    return false;
}

int main() {
    long long balance = 10000;
    Zone z = Zone::Outer;
    bool isPeak = true;

    long long f = calculateFare(z, isPeak);
    std::cout << "Procedural Approach:\n";
    std::cout << "Initial Balance: " << balance << " paise\n";
    std::cout << "Fare: " << f << " paise\n";

    if (deduct(balance, f)) {
        std::cout << "Deduction Successful. New Balance: " << balance << " paise\n";
    } else {
        std::cout << "Deduction Failed: Insufficient Balance\n";
    }

    balance = -500;
    std::cout << "Vulnerability in Procedural: Balance can be directly altered to: " << balance << " paise\n";

    return 0;
}
