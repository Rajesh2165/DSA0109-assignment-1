#include <iostream>

enum class Zone {
    Inner,
    Middle,
    Outer
};

class SmartCard {
private:
    int cardId;
    long long balancePaise;

public:
    SmartCard(int id, long long initialBalance) {
        cardId = id;
        balancePaise = initialBalance;
    }

    int getId() const {
        return cardId;
    }

    long long getBalance() const {
        return balancePaise;
    }

    bool canTravel(long long farePaise) const {
        return (balancePaise - farePaise) >= 5000;
    }

    bool deductFare(long long farePaise) {
        if (canTravel(farePaise)) {
            balancePaise -= farePaise;
            return true;
        }
        return false;
    }

    void recharge(long long amountPaise) {
        if (amountPaise > 0) {
            balancePaise += amountPaise;
        }
    }
};

class Passenger {
private:
    int passengerId;
    bool isSenior;
    bool isStudent;

public:
    Passenger(int id, bool senior, bool student) {
        passengerId = id;
        isSenior = senior;
        isStudent = student;
    }

    bool hasConcession() const {
        return isSenior || isStudent;
    }
};

class FareTable {
public:
    static long long calculateFare(Zone z, bool isPeak, bool concession) {
        long long baseFare = 0;
        if (z == Zone::Inner) {
            baseFare = 1000;
        } else if (z == Zone::Middle) {
            baseFare = 2000;
        } else if (z == Zone::Outer) {
            baseFare = 3000;
        }

        long long totalFare = baseFare;
        if (isPeak) {
            totalFare += (baseFare * 20) / 100;
        }
        if (concession) {
            totalFare = (totalFare * 50) / 100;
        }
        return totalFare;
    }
};

class Journey {
private:
    Zone destinationZone;
    int hour;

public:
    Journey(Zone z, int h) {
        destinationZone = z;
        hour = h;
    }

    bool isPeak() const {
        return (hour >= 8 && hour < 10) || (hour >= 17 && hour < 20);
    }

    Zone getZone() const {
        return destinationZone;
    }
};

int main() {
    SmartCard card(101, 10000);
    Passenger passenger(1, false, false);
    Journey journey(Zone::Outer, 9);

    std::cout << "Card ID: " << card.getId() << "\n";
    std::cout << "Initial Balance (Paise): " << card.getBalance() << "\n";

    long long fare = FareTable::calculateFare(journey.getZone(), journey.isPeak(), passenger.hasConcession());
    std::cout << "Calculated Fare (Paise): " << fare << "\n";

    if (card.deductFare(fare)) {
        std::cout << "Journey Approved. New Balance (Paise): " << card.getBalance() << "\n";
    } else {
        std::cout << "Journey Denied: Insufficient Balance\n";
    }

    return 0;
}
