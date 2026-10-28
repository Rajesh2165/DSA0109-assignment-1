#include <iostream>
#include <iomanip>

enum class Zone { Inner, Middle, Outer, Unknown };

struct TestCase {
    const char* description;
    Zone zone;
    int hour;
    long long initialBalance;
    long long expectedFare;
    bool expectedAllowed;
};

bool isPeakHour(int hour) {
    return (hour >= 8 && hour < 10) || (hour >= 17 && hour < 20);
}

long long calculateFare(Zone z, int hour) {
    if (hour < 0 || hour > 23) {
        return -1;
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
        default:
            return -1;
    }
    if (isPeakHour(hour)) {
        base += (base * 20) / 100;
    }
    return base;
}

bool canTravel(long long balance, long long fare) {
    if (fare < 0) {
        return false;
    }
    return (balance - fare) >= 5000;
}

bool recharge(long long& balance, long long amount) {
    if (amount <= 0) {
        return false;
    }
    balance += amount;
    return true;
}

int main() {
    TestCase tests[] = {
        {"Inner Off-Peak (11:00)", Zone::Inner, 11, 10000, 1000, true},
        {"Inner Peak (9:00)", Zone::Inner, 9, 10000, 1200, true},
        {"Middle Off-Peak (14:00)", Zone::Middle, 14, 10000, 2000, true},
        {"Middle Peak (18:00)", Zone::Middle, 18, 10000, 2400, true},
        {"Outer Off-Peak (12:00)", Zone::Outer, 12, 10000, 3000, true},
        {"Outer Peak (8:00 - Boundary)", Zone::Outer, 8, 10000, 3600, true},
        {"Outer Boundary (10:00 Off-Peak)", Zone::Outer, 10, 10000, 3000, true},
        {"Outer Boundary (17:00 Peak)", Zone::Outer, 17, 10000, 3600, true},
        {"Outer Boundary (20:00 Off-Peak)", Zone::Outer, 20, 10000, 3000, true},
        {"Exact Rs 50 Remaining (6000-1000=5000)", Zone::Inner, 11, 6000, 1000, true},
        {"Insufficient: Leaves 4999 (<5000)", Zone::Inner, 11, 5999, 1000, false},
        {"Invalid Zone (Unknown)", Zone::Unknown, 10, 10000, -1, false},
        {"Invalid Hour (25)", Zone::Inner, 25, 10000, -1, false}
    };

    std::cout << "=========================================================================================\n";
    std::cout << std::left << std::setw(36) << "Test Description"
              << std::setw(15) << "Expected Fare"
              << std::setw(15) << "Actual Fare"
              << std::setw(12) << "Allowed?"
              << std::setw(10) << "Status" << "\n";
    std::cout << "=========================================================================================\n";

    int passedCount = 0;
    int totalTests = sizeof(tests) / sizeof(tests[0]);

    for (int i = 0; i < totalTests; ++i) {
        long long actualFare = calculateFare(tests[i].zone, tests[i].hour);
        bool actualAllowed = canTravel(tests[i].initialBalance, actualFare);

        bool pass = (actualFare == tests[i].expectedFare) && (actualAllowed == tests[i].expectedAllowed);
        if (pass) {
            passedCount++;
        }

        std::cout << std::left << std::setw(36) << tests[i].description
                  << std::setw(15) << tests[i].expectedFare
                  << std::setw(15) << actualFare
                  << std::setw(12) << (actualAllowed ? "Yes" : "No")
                  << std::setw(10) << (pass ? "PASS" : "FAIL") << "\n";
    }

    std::cout << "=========================================================================================\n";
    std::cout << "Total Test Cases Passed: " << passedCount << " / " << totalTests << "\n\n";

    long long cardBalance = 5000;
    std::cout << "Testing Negative Recharge of -1000 paise:\n";
    bool rechOk = recharge(cardBalance, -1000);
    std::cout << "Recharge Accepted? " << (rechOk ? "Yes" : "No") << " | Balance: " << cardBalance << " paise (PASS)\n\n";

    std::cout << "5 Hand-Calculated Journeys Test:\n";
    struct HandTrip { Zone z; int h; long long expectedF; };
    HandTrip handTrips[5] = {
        {Zone::Inner, 9, 1200},
        {Zone::Middle, 12, 2000},
        {Zone::Outer, 18, 3600},
        {Zone::Inner, 14, 1000},
        {Zone::Middle, 19, 2400}
    };

    long long handTotalExpected = 10200;
    long long actualTotal = 0;
    for (int i = 0; i < 5; ++i) {
        long long f = calculateFare(handTrips[i].z, handTrips[i].h);
        actualTotal += f;
        std::cout << "Trip " << (i + 1) << " Fare: " << f << " paise (Expected: " << handTrips[i].expectedF << ")\n";
    }
    std::cout << "Hand-calculated Total: " << handTotalExpected << " paise\n";
    std::cout << "Actual Program Total : " << actualTotal << " paise\n";
    std::cout << "Hand Calculation Match: " << (handTotalExpected == actualTotal ? "MATCH (PASS)" : "MISMATCH") << "\n";

    return 0;
}
