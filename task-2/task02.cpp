#include <iostream>

enum class Zone {
    Inner,
    Middle,
    Outer
};

constexpr long long FARE_INNER_PAISE = 1000;
constexpr long long FARE_MIDDLE_PAISE = 2000;
constexpr long long FARE_OUTER_PAISE = 3000;
constexpr int PEAK_SURCHARGE_PERCENT = 20;
constexpr long long MIN_BALANCE_PAISE = 5000;

long long getBaseFare(Zone zone) {
    if (zone == Zone::Inner) {
        return FARE_INNER_PAISE;
    } else if (zone == Zone::Middle) {
        return FARE_MIDDLE_PAISE;
    } else if (zone == Zone::Outer) {
        return FARE_OUTER_PAISE;
    }
    return 0;
}

long long calculateTripFare(Zone zone, bool isPeak) {
    long long base = getBaseFare(zone);
    if (isPeak) {
        return base + (base * PEAK_SURCHARGE_PERCENT) / 100;
    }
    return base;
}

int main() {
    Zone currentZone = Zone::Outer;
    bool peakTime = true;

    long long fare = calculateTripFare(currentZone, peakTime);

    std::cout << "Zone: Outer\n";
    std::cout << "Peak Surcharge Percent: " << PEAK_SURCHARGE_PERCENT << "%\n";
    std::cout << "Minimum Required Balance: " << MIN_BALANCE_PAISE << " paise\n";
    std::cout << "Calculated Fare: " << fare << " paise (" << (fare / 100) << " Rs)\n";

    return 0;
}
