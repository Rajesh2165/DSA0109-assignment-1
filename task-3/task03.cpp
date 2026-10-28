#include <iostream>

int main() {
    std::cout << "Data Type Sizes (bytes):\n";
    std::cout << "sizeof(bool): " << sizeof(bool) << "\n";
    std::cout << "sizeof(char): " << sizeof(char) << "\n";
    std::cout << "sizeof(int): " << sizeof(int) << "\n";
    std::cout << "sizeof(long long): " << sizeof(long long) << "\n";
    std::cout << "sizeof(unsigned int): " << sizeof(unsigned int) << "\n";
    std::cout << "sizeof(float): " << sizeof(float) << "\n";
    std::cout << "sizeof(double): " << sizeof(double) << "\n\n";

    double doubleTotal = 0.0;
    for (int i = 0; i < 10; ++i) {
        doubleTotal += 0.1;
    }
    std::cout << "Float/Double precision issue:\n";
    std::cout << "Adding 0.1 ten times in double: " << doubleTotal << "\n";
    if (doubleTotal == 1.0) {
        std::cout << "doubleTotal == 1.0 is TRUE\n\n";
    } else {
        std::cout << "doubleTotal == 1.0 is FALSE (Precision Loss!)\n\n";
    }

    int intOverflowTotal = 0;
    long long longTotal = 0;
    int singleFare = 3600;
    int journeys = 3000000;

    for (int i = 0; i < journeys; ++i) {
        intOverflowTotal += singleFare;
        longTotal += singleFare;
    }

    std::cout << "Network Total for 3,000,000 journeys at 3600 paise:\n";
    std::cout << "Using 32-bit int: " << intOverflowTotal << " (Overflowed!)\n";
    std::cout << "Using 64-bit long long: " << longTotal << " paise (Exact)\n";

    return 0;
}
