#include <iostream>
#include <iomanip>

void runSimulation(int journeyCount) {
    long long longTotalPaise = 0;
    double doubleTotalRupees = 0.0;
    int intTotalPaise = 0;

    int faresPaise[6] = {1000, 1200, 2000, 2400, 3000, 3600};
    double faresRupees[6] = {10.0, 12.0, 20.0, 24.0, 30.0, 36.0};

    for (int i = 0; i < journeyCount; ++i) {
        int idx = i % 6;
        longTotalPaise += faresPaise[idx];
        doubleTotalRupees += faresRupees[idx];
        intTotalPaise += faresPaise[idx];
    }

    double exactRupeesFromPaise = static_cast<double>(longTotalPaise) / 100.0;
    double differenceRupees = doubleTotalRupees - exactRupeesFromPaise;

    std::cout << "Simulation for " << journeyCount << " Journeys:\n";
    std::cout << "  long long Total (Paise): " << longTotalPaise << " (Rs " << std::fixed << std::setprecision(2) << exactRupeesFromPaise << ")\n";
    std::cout << "  double Total (Rupees)  : Rs " << std::fixed << std::setprecision(6) << doubleTotalRupees << "\n";
    std::cout << "  Difference (double - exact): Rs " << std::fixed << std::setprecision(6) << differenceRupees << "\n";
    std::cout << "  32-bit int Total (Paise): " << intTotalPaise;
    if (intTotalPaise < 0 || intTotalPaise != longTotalPaise) {
        std::cout << " [OVERFLOW DETECTED!]\n";
    } else {
        std::cout << " [OK]\n";
    }
    std::cout << "------------------------------------------------------------\n";
}

int main() {
    std::cout << "============================================================\n";
    std::cout << "  METRO NETWORK SCALE ANALYSIS (20K, 500K, 3M JOURNEYS)     \n";
    std::cout << "============================================================\n";

    runSimulation(20000);
    runSimulation(500000);
    runSimulation(3000000);

    return 0;
}
