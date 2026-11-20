#include <iostream>
#include <iomanip>
#include <cmath>
#include <chrono>

class Time {
    int h, m;
public:
    Time(int hh = 0, int mm = 0) : h(hh), m(mm) {}

    friend int minutesBetween(const Time& a, const Time& b);
    friend bool earlier(const Time& a, const Time& b);

    // Member function alternative
    int minutesTo(const Time& other) const {
        return std::abs((h * 60 + m) - (other.h * 60 + other.m));
    }

    bool isEarlier(const Time& other) const {
        if (h != other.h) return h < other.h;
        return m < other.m;
    }
};

// Friend function implementations
int minutesBetween(const Time& a, const Time& b) {
    // TODO 1: Using the private members h and m, return the absolute difference between
    // the two times in minutes
    int diff = (a.h * 60 + a.m) - (b.h * 60 + b.m);
    return (diff < 0) ? -diff : diff;
}

bool earlier(const Time& a, const Time& b) {
    // TODO 2: Return true if a is earlier in the day than b
    if (a.h != b.h) return a.h < b.h;
    return a.m < b.m;
}

int main() {
    std::cout << "=== Q6: FRIEND FUNCTIONS AND INLINE FUNCTIONS ===\n\n";

    std::cout << "--- 1. EXPECTED OUTPUT TEST ---\n";
    Time departure(9, 45), arrival(13, 10);
    std::cout << minutesBetween(departure, arrival) << ' '
              << std::boolalpha << earlier(arrival, departure) << '\n';

    std::cout << "\n--- 2. EDGE CASE CORRECTNESS TESTS ---\n";
    // Same time twice
    Time t1(10, 30), t2(10, 30);
    std::cout << "Same time twice (10:30, 10:30):\n";
    std::cout << "  minutesBetween: " << minutesBetween(t1, t2)
              << ", earlier: " << earlier(t1, t2) << '\n';

    // Either side of noon
    Time morning(11, 45), afternoon(12, 15);
    std::cout << "Across noon (11:45, 12:15):\n";
    std::cout << "  minutesBetween: " << minutesBetween(morning, afternoon)
              << ", earlier: " << earlier(morning, afternoon) << '\n';

    // Member function alternative verification
    std::cout << "\n--- 3. ALTERNATIVE MEMBER FUNCTION VERIFICATION ---\n";
    std::cout << "departure.minutesTo(arrival): " << departure.minutesTo(arrival)
              << ", arrival.isEarlier(departure): " << arrival.isEarlier(departure) << '\n';

    std::cout << "\n--- 4. GROWTH INVESTIGATION (10,000,000 CALLS) ---\n";
    const int ITERATIONS = 10000000;
    auto start = std::chrono::high_resolution_clock::now();
    long long checksum = 0;
    for (int i = 0; i < ITERATIONS; ++i) {
        Time ta(i % 24, i % 60);
        Time tb((i + 5) % 24, (i + 15) % 60);
        checksum += minutesBetween(ta, tb);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "Completed " << ITERATIONS << " calls in " << elapsed << " ms. Checksum: " << checksum << '\n';

    return 0;
}
