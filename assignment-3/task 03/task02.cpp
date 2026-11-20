#include <iostream>
#include <string>

class Prescription {
private:
    int n;
    std::string* medicines; // dynamically allocated array

public:
    explicit Prescription(int count)
        : n(count), medicines(count > 0 ? new std::string[count] : nullptr) {}

    // TODO 1: Copy constructor: allocate a NEW array of the same size and copy every medicine (deep copy)
    Prescription(const Prescription& other)
        : n(other.n), medicines(other.n > 0 ? new std::string[other.n] : nullptr) {
        for (int i = 0; i < n; ++i) {
            medicines[i] = other.medicines[i];
        }
    }

    // TODO 2: Copy assignment: guard against self-assignment, build a new array, copy, release the old array and return *this
    Prescription& operator=(const Prescription& other) {
        if (this != &other) {
            std::string* newMeds = other.n > 0 ? new std::string[other.n] : nullptr;
            for (int i = 0; i < other.n; ++i) {
                newMeds[i] = other.medicines[i];
            }
            delete[] medicines;
            medicines = newMeds;
            n = other.n;
        }
        return *this;
    }

    // TODO 3: Release the dynamically allocated array
    ~Prescription() {
        delete[] medicines;
    }

    void set(int i, const std::string& m) {
        if (i >= 0 && i < n) medicines[i] = m;
    }

    std::string get(int i) const {
        if (i >= 0 && i < n) return medicines[i];
        return "";
    }

    int size() const { return n; }
};

void inspectByValue(Prescription temp) {
    std::cout << "[Inside inspectByValue (copied)]: " << temp.get(0) << '\n';
}

void inspectByConstRef(const Prescription& ref) {
    std::cout << "[Inside inspectByConstRef (no copy)]: " << ref.get(0) << '\n';
}

int main() {
    std::cout << "=== Q2: COPY CONSTRUCTORS - SHALLOW AND DEEP COPIES ===\n\n";

    std::cout << "--- 1. RUNNING COMPLETE THE CODE ROUTINE ---\n";
    Prescription p(2);
    p.set(0, "Paracetamol");
    p.set(1, "ORS");

    Prescription q = p; // copy constructor
    q.set(1, "Cetirizine");

    Prescription r(1);
    r = p; // copy assignment
    p.set(0, "Ibuprofen");

    std::cout << p.get(0) << ' ' << p.get(1) << " | "
              << q.get(0) << ' ' << q.get(1) << " | "
              << r.get(0) << ' ' << r.get(1) << '\n';

    std::cout << "\n--- 2. SELF-ASSIGNMENT TEST ---\n";
    p = p; // Must not corrupt memory
    std::cout << "After self-assignment (p = p): " << p.get(0) << ' ' << p.get(1) << " (Safe)\n";

    std::cout << "\n--- 3. PASS BY VALUE VS CONST REFERENCE ---\n";
    inspectByValue(p);
    inspectByConstRef(p);

    return 0;
}
