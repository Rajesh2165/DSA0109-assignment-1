#include <iostream>

enum class Zone { Inner, Middle, Outer };

class SmartCard {
private:
    int cardId;
    long long balancePaise;
    static constexpr long long MIN_BALANCE_PAISE = 5000;

public:
    SmartCard(int id, long long initialBalance) {
        cardId = id;
        balancePaise = (initialBalance >= 0) ? initialBalance : 0;
    }

    int getId() const {
        return cardId;
    }

    long long getBalance() const {
        return balancePaise;
    }

    bool canTravel(long long fare) const {
        return (balancePaise - fare) >= MIN_BALANCE_PAISE;
    }

    bool deduct(long long fare) {
        if (canTravel(fare)) {
            balancePaise -= fare;
            return true;
        }
        return false;
    }

    void recharge(long long amount) {
        if (amount > 0) {
            balancePaise += amount;
        }
    }
};

class FareCalculator {
public:
    static long long calculateFare(Zone z, bool isPeak) {
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
};

int main() {
    SmartCard card(201, 10000);
    Zone z = Zone::Outer;
    bool isPeak = true;

    long long f = FareCalculator::calculateFare(z, isPeak);
    std::cout << "Object-Oriented Approach:\n";
    std::cout << "Card ID: " << card.getId() << "\n";
    std::cout << "Initial Balance: " << card.getBalance() << " paise\n";
    std::cout << "Fare: " << f << " paise\n";

    if (card.deduct(f)) {
        std::cout << "Deduction Successful. New Balance: " << card.getBalance() << " paise\n";
    } else {
        std::cout << "Deduction Failed: Insufficient Balance\n";
    }

    long long heavyFare = 5000;
    if (!card.deduct(heavyFare)) {
        std::cout << "Deduction of " << heavyFare << " paise Denied. Balance preserved at: " << card.getBalance() << " paise\n";
    }

    return 0;
}
