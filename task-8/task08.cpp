#include <iostream>
#include <iomanip>

int readSafeInt() {
    int value;
    while (true) {
        if (std::cin >> value) {
            return value;
        }
        std::cin.clear();
        while (std::cin.get() != '\n') {
        }
        std::cout << "Invalid input detected. Please enter a valid number: ";
    }
}

int main() {
    std::cout << "Enter Card ID: ";
    int cardId = readSafeInt();

    std::cout << "Enter Initial Balance in Rupees: ";
    int balanceRupees = readSafeInt();
    long long balancePaise = static_cast<long long>(balanceRupees) * 100;

    std::cout << "Enter Zone (1=Inner, 2=Middle, 3=Outer): ";
    int zoneCode = readSafeInt();

    std::cout << "Enter Travel Hour (0-23): ";
    int hour = readSafeInt();

    long long baseFare = 0;
    if (zoneCode == 1) {
        baseFare = 1000;
    } else if (zoneCode == 2) {
        baseFare = 2000;
    } else if (zoneCode == 3) {
        baseFare = 3000;
    }

    bool isPeak = (hour >= 8 && hour < 10) || (hour >= 17 && hour < 20);
    long long finalFare = baseFare;
    if (isPeak) {
        finalFare += (baseFare * 20) / 100;
    }

    bool allowed = (balancePaise - finalFare) >= 5000;

    std::cout << "\n========================================\n";
    std::cout << "             METRO JOURNEY REPORT       \n";
    std::cout << "========================================\n";
    std::cout << "Card ID         : " << cardId << "\n";
    std::cout << "Zone Code       : " << zoneCode << "\n";
    std::cout << "Travel Hour     : " << hour << ":00 (" << (isPeak ? "Peak" : "Off-Peak") << ")\n";

    std::cout << "Starting Balance: Rs " << std::setw(6) << std::right << balancePaise / 100 << '.'
              << std::setw(2) << std::setfill('0') << balancePaise % 100 << std::setfill(' ') << "\n";

    std::cout << "Trip Fare       : Rs " << std::setw(6) << std::right << finalFare / 100 << '.'
              << std::setw(2) << std::setfill('0') << finalFare % 100 << std::setfill(' ') << "\n";

    if (allowed) {
        balancePaise -= finalFare;
        std::cout << "Gate Status     : ALLOWED\n";
    } else {
        std::cout << "Gate Status     : DENIED (Min Rs 50 required)\n";
    }

    std::cout << "Closing Balance : Rs " << std::setw(6) << std::right << balancePaise / 100 << '.'
              << std::setw(2) << std::setfill('0') << balancePaise % 100 << std::setfill(' ') << "\n";
    std::cout << "========================================\n";

    return 0;
}
