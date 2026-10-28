#include <iostream>
#include <iomanip>

enum class Zone { Inner, Middle, Outer, Airport };

class SmartCard {
protected:
    int cardId;
    long long balancePaise;
    static constexpr long long MIN_BALANCE_PAISE = 5000;

public:
    SmartCard(int id, long long initialBalance) {
        cardId = id;
        balancePaise = (initialBalance >= 0) ? initialBalance : 0;
    }

    virtual ~SmartCard() {}

    int getId() const {
        return cardId;
    }

    long long getBalance() const {
        return balancePaise;
    }

    bool canTravel(long long fare) const {
        return (balancePaise - fare) >= MIN_BALANCE_PAISE;
    }

    virtual bool deduct(long long fare) {
        if (canTravel(fare)) {
            balancePaise -= fare;
            return true;
        }
        return false;
    }

    virtual bool coversZone(Zone) const {
        return false;
    }
};

class MonthlyPassCard : public SmartCard {
private:
    Zone coveredZone1;
    Zone coveredZone2;

public:
    MonthlyPassCard(int id, long long initialBalance, Zone z1, Zone z2)
        : SmartCard(id, initialBalance) {
        coveredZone1 = z1;
        coveredZone2 = z2;
    }

    bool coversZone(Zone z) const override {
        return (z == coveredZone1 || z == coveredZone2);
    }

    bool deduct(long long fare) override {
        if (fare == 0) {
            return true;
        }
        return SmartCard::deduct(fare);
    }
};

class MetroFareEngine {
public:
    static long long calculateFare(Zone z, int hour, bool isWeekend, const SmartCard& card) {
        if (card.coversZone(z)) {
            return 0;
        }

        long long base = 0;
        switch (z) {
            case Zone::Inner:
                base = 1000;
                break;
            case Zone::Middle:
                base = 2000;
                break;
            case Zone::Outer:
                base = 3000;
                break;
            case Zone::Airport:
                base = 6000;
                break;
        }

        if (isWeekend) {
            base -= (base * 10) / 100;
            return base;
        }

        bool isPeak = (hour >= 8 && hour < 10) || (hour >= 17 && hour < 20);
        if (isPeak) {
            base += (base * 20) / 100;
        }

        return base;
    }
};

int main() {
    std::cout << "=== TASK 12: DAY-4 DESIGN CHALLENGE IMPLEMENTATION ===\n\n";

    SmartCard regularCard(501, 20000);
    MonthlyPassCard passCard(601, 10000, Zone::Inner, Zone::Middle);

    std::cout << "Test 1: Regular Card - Airport Zone on Weekday Peak (9:00 AM)\n";
    long long fare1 = MetroFareEngine::calculateFare(Zone::Airport, 9, false, regularCard);
    std::cout << "Calculated Fare: Rs " << fare1 / 100 << "." << std::setw(2) << std::setfill('0') << fare1 % 100 << "\n";
    if (regularCard.deduct(fare1)) {
        std::cout << "Deduction Approved.\n";
    } else {
        std::cout << "Deduction Denied (Low Balance).\n";
    }
    std::cout << "Remaining Balance: Rs " << regularCard.getBalance() / 100 << "."
              << std::setw(2) << std::setfill('0') << regularCard.getBalance() % 100 << "\n\n";

    std::cout << "Test 2: Regular Card - Airport Zone on Weekend (10% Discount, No Peak Surcharge)\n";
    long long fare2 = MetroFareEngine::calculateFare(Zone::Airport, 9, true, regularCard);
    std::cout << "Calculated Fare: Rs " << fare2 / 100 << "." << std::setw(2) << std::setfill('0') << fare2 % 100 << "\n";
    if (regularCard.deduct(fare2)) {
        std::cout << "Deduction Approved.\n";
    } else {
        std::cout << "Deduction Denied (Low Balance).\n";
    }
    std::cout << "Remaining Balance: Rs " << regularCard.getBalance() / 100 << "."
              << std::setw(2) << std::setfill('0') << regularCard.getBalance() % 100 << "\n\n";

    std::cout << "Test 3: Monthly Pass Card (Covers Inner & Middle) - Journey in Inner Zone\n";
    long long fare3 = MetroFareEngine::calculateFare(Zone::Inner, 9, false, passCard);
    std::cout << "Calculated Fare: Rs " << fare3 / 100 << "." << std::setw(2) << std::setfill('0') << fare3 % 100 << "\n";
    if (passCard.deduct(fare3)) {
        std::cout << "Pass Validated. Zero Fare Deducted.\n";
    } else {
        std::cout << "Pass Validation Failed.\n";
    }
    std::cout << "Remaining Balance: Rs " << passCard.getBalance() / 100 << "."
              << std::setw(2) << std::setfill('0') << passCard.getBalance() % 100 << "\n\n";

    std::cout << "Test 4: Monthly Pass Card - Journey in Airport Zone (Uncovered Zone)\n";
    long long fare4 = MetroFareEngine::calculateFare(Zone::Airport, 9, false, passCard);
    std::cout << "Calculated Fare: Rs " << fare4 / 100 << "." << std::setw(2) << std::setfill('0') << fare4 % 100 << "\n";
    if (passCard.deduct(fare4)) {
        std::cout << "Deduction Approved from Stored Balance.\n";
    } else {
        std::cout << "Deduction Denied: Stored balance insufficient to leave Rs 50 minimum.\n";
    }
    std::cout << "Remaining Balance: Rs " << passCard.getBalance() / 100 << "."
              << std::setw(2) << std::setfill('0') << passCard.getBalance() % 100 << "\n";

    return 0;
}
