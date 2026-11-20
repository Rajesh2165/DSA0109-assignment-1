#include <iostream>
#include <iomanip>
#include <string>
#include <chrono>

// --- PREDICTION CODE ---
struct Counter {
    int v;
    Counter& operator++() { ++v; return *this; } // prefix
    Counter operator++(int) { Counter old = *this; ++v; return old; } // postfix
};

void runPredictionSection() {
    std::cout << "--- 1. PREDICT THE OUTPUT (Counter Prefix vs Postfix) ---\n";
    Counter c{5};
    Counter a = c++;
    Counter b = ++c;
    std::cout << a.v << ' ' << b.v << ' ' << c.v << '\n';
}

// --- TRACK TIME WITH PREFIX/POSTFIX ++ AND COMPARISONS ---
class TrackTime {
private:
    int hours;
    int minutes;
    int seconds;

    void normalize() {
        if (seconds >= 60) {
            minutes += seconds / 60;
            seconds %= 60;
        }
        if (minutes >= 60) {
            hours += minutes / 60;
            minutes %= 60;
        }
    }

public:
    TrackTime(int h = 0, int m = 0, int s = 0)
        : hours(h), minutes(m), seconds(s) {
        normalize();
    }

    // Prefix increment: ++t (advances by 1 second, returns reference to *this)
    TrackTime& operator++() {
        ++seconds;
        normalize();
        return *this;
    }

    // Postfix increment: t++ (advances by 1 second, returns copy of old state)
    TrackTime operator++(int) {
        TrackTime old = *this;
        ++seconds;
        normalize();
        return old;
    }

    bool operator==(const TrackTime& o) const {
        return hours == o.hours && minutes == o.minutes && seconds == o.seconds;
    }

    bool operator<(const TrackTime& o) const {
        if (hours != o.hours) return hours < o.hours;
        if (minutes != o.minutes) return minutes < o.minutes;
        return seconds < o.seconds;
    }

    void print() const {
        std::cout << std::setfill('0') << std::setw(2) << hours << ':'
                  << std::setfill('0') << std::setw(2) << minutes << ':'
                  << std::setfill('0') << std::setw(2) << seconds << std::setfill(' ');
    }
};

// --- PLAYLIST CLASS WITH BOUNDS-CHECKED SUBSCRIPT OPERATOR [] ---
class Playlist {
private:
    static const int MAX_TRACKS = 5;
    std::string tracks[MAX_TRACKS];
    int count;

public:
    Playlist() : count(0) {}

    void addTrack(const std::string& title) {
        if (count < MAX_TRACKS) {
            tracks[count++] = title;
        }
    }

    int size() const { return count; }

    // Non-const operator[]
    std::string& operator[](int index) {
        if (index < 0 || index >= count) {
            std::cout << "[Error: Subscript " << index << " out of range (size: " << count << ")] ";
            static std::string errorSlot = "INVALID_TRACK";
            return errorSlot;
        }
        return tracks[index];
    }

    // Const operator[]
    const std::string& operator[](int index) const {
        if (index < 0 || index >= count) {
            std::cout << "[Error: Const Subscript " << index << " out of range (size: " << count << ")] ";
            static const std::string errorSlot = "INVALID_TRACK";
            return errorSlot;
        }
        return tracks[index];
    }
};

int main() {
    std::cout << "=== Q5: OVERLOADING INCREMENT, COMPARISON AND SUBSCRIPT OPERATORS ===\n\n";

    runPredictionSection();

    std::cout << "\n--- 2. TIME INCREMENT & ROLL-OVER (59:59 -> 1:00:00) ---\n";
    TrackTime timer(0, 59, 58);
    std::cout << "Initial Time: "; timer.print(); std::cout << '\n';

    TrackTime post = timer++;
    std::cout << "After timer++ (returned old): "; post.print(); 
    std::cout << " | Current timer: "; timer.print(); std::cout << '\n';

    TrackTime pre = ++timer; // Rolls over to 1:00:00
    std::cout << "After ++timer (returned new): "; pre.print(); 
    std::cout << " | Current timer: "; timer.print(); std::cout << '\n';

    std::cout << "\n--- 3. PLAYLIST OPERATOR [] AND RANGE CHECKING ---\n";
    Playlist pl;
    pl.addTrack("Track 1: Symphony of Strings");
    pl.addTrack("Track 2: Binary Blues");
    pl.addTrack("Track 3: Algorithm Allegro");

    std::cout << "Valid access pl[1]: " << pl[1] << '\n';
    
    // Bounds check violations
    std::cout << "Invalid access pl[-1]: ";
    std::cout << pl[-1] << '\n';

    std::cout << "Invalid access pl[pl.size()]: ";
    std::cout << pl[pl.size()] << '\n';

    std::cout << "\n--- 4. BENCHMARK: 10,000,000 PREFIX VS POSTFIX INCREMENTS ---\n";
    const int ITERATIONS = 10000000;
    Counter c1{0};
    auto t0 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < ITERATIONS; ++i) {
        ++c1; // prefix: no temporary copy
    }
    auto t1 = std::chrono::high_resolution_clock::now();
    auto preMs = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();

    Counter c2{0};
    auto t2 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < ITERATIONS; ++i) {
        c2++; // postfix: creates and returns copy
    }
    auto t3 = std::chrono::high_resolution_clock::now();
    auto postMs = std::chrono::duration_cast<std::chrono::milliseconds>(t3 - t2).count();

    std::cout << "10,000,000 Prefix increments (++c): " << preMs << " ms\n";
    std::cout << "10,000,000 Postfix increments (c++): " << postMs << " ms\n";

    return 0;
}
