#include <iostream>

void applyByValue(long long fee, int percent) {
    fee -= fee * percent / 100;
}

void applyConcession(long long& fee, int percent) {
    // TODO 1: Reduce the caller's fee by percent using integer arithmetic (call by reference)
    fee -= fee * percent / 100;
}

void applyByPointer(long long* fee, int percent) {
    if (fee != nullptr) {
        *fee -= (*fee) * percent / 100;
    }
}

void change(int a, int& b, int* c) {
    a += 10;
    (void)a; // Demonstrates modification to local stack copy only
    b += 10;
    *c += 10;
}

int& bigger(int& p, int& q) {
    return p > q ? p : q;
}

void show(int x, int y = 5, int z = 10) {
    std::cout << x + y + z << ' ';
}

void runPredictionSection() {
    std::cout << "--- PREDICT THE OUTPUT SECTION ---\n";
    int a = 1, b = 2, c = 3;
    change(a, b, &c);
    std::cout << a << ' ' << b << ' ' << c << '\n';

    bigger(a, c) = 100;
    std::cout << a << ' ' << c << '\n';

    show(1);
    show(1, 2);
    show(1, 2, 3);
    std::cout << '\n';
}

void runConcessionSection() {
    std::cout << "--- COMPLETE THE CODE & CONCESSION UPDATER ---\n";
    long long hostelFee = 45000;
    applyByValue(hostelFee, 10);
    std::cout << "after call by value : " << hostelFee << '\n';

    applyConcession(hostelFee, 10);
    std::cout << "after call by reference: " << hostelFee << '\n';

    // Demonstrate call by pointer
    applyByPointer(&hostelFee, 15);
    std::cout << "after call by pointer  : " << hostelFee << '\n';
}

int main() {
    runPredictionSection();
    std::cout << '\n';
    runConcessionSection();
    return 0;
}
