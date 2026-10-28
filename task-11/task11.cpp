#include <iostream>
#include <iomanip>

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

class FareEngine {
private:
    long long fares[3];
    int peakSurchargePercent;

public:
    FareEngine(long long inner, long long middle, long long outer, int peakPct) {
        fares[0] = inner;
        fares[1] = middle;
        fares[2] = outer;
        peakSurchargePercent = peakPct;
    }

    void reviseFares(long long inner, long long middle, long long outer, int peakPct) {
        fares[0] = inner;
        fares[1] = middle;
        fares[2] = outer;
        peakSurchargePercent = peakPct;
    }

    bool isPeak(int hour) const {
        return (hour >= 8 && hour < 10) || (hour >= 17 && hour < 20);
    }

    long long calculateFare(Zone z, int hour) const {
        int idx = 0;
        if (z == Zone::Inner) {
            idx = 0;
        } else if (z == Zone::Middle) {
            idx = 1;
        } else if (z == Zone::Outer) {
            idx = 2;
        }

        long long base = fares[idx];
        if (isPeak(hour)) {
            base += (base * peakSurchargePercent) / 100;
        }
        return base;
    }
};

int main() {
    FareEngine engine(1000, 2000, 3000, 20);
    SmartCard card(301, 10000);

    std::cout << "=== RECOMMENDED FINAL DESIGN FOR METRO GATE SYSTEM ===\n";
    std::cout << "Card ID: " << card.getId() << "\n";
    std::cout << "Initial Card Balance: Rs " << (card.getBalance() / 100) << "."
              << std::setw(2) << std::setfill('0') << (card.getBalance() % 100) << "\n\n";

    long long fare1 = engine.calculateFare(Zone::Outer, 9);
    std::cout << "Trip 1: Outer Zone, 9:00 AM (Peak)\n";
    std::cout << "Calculated Fare: Rs " << (fare1 / 100) << "."
              << std::setw(2) << std::setfill('0') << (fare1 % 100) << "\n";

    if (card.deduct(fare1)) {
        std::cout << "Trip 1 Approved. Balance: Rs " << (card.getBalance() / 100) << "."
                  << std::setw(2) << std::setfill('0') << (card.getBalance() % 100) << "\n\n";
    }

    std::cout << "Executing Fare Revision: Inner=Rs 12, Middle=Rs 22, Outer=Rs 35...\n";
    engine.reviseFares(1200, 2200, 3500, 20);

    long long fare2 = engine.calculateFare(Zone::Outer, 9);
    std::cout << "Trip 2 After Revision: Outer Zone, 9:00 AM (Peak)\n";
    std::cout << "Revised Fare: Rs " << (fare2 / 100) << "."
              << std::setw(2) << std::setfill('0') << (fare2 % 100) << "\n";

    if (card.deduct(fare2)) {
        std::cout << "Trip 2 Approved. Balance: Rs " << (card.getBalance() / 100) << "."
                  << std::setw(2) << std::setfill('0') << (card.getBalance() % 100) << "\n";
    } else {
        std::cout << "Trip 2 Denied: Minimum balance of Rs 50 required.\n";
    }

    return 0;
}
