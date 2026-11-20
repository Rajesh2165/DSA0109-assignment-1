#include <iostream>
#include <vector>

// 1. Function returning reference to an array element
int& getHighestMark(int marks[], int size) {
    int maxIdx = 0;
    for (int i = 1; i < size; ++i) {
        if (marks[i] > marks[maxIdx]) {
            maxIdx = i;
        }
    }
    return marks[maxIdx];
}

// 2. Demonstration of returning reference vs const reference vs copy
int& getRef(int arr[], int idx) {
    return arr[idx];
}

const int& getConstRef(const int arr[], int idx) {
    return arr[idx];
}

int getCopy(int arr[], int idx) {
    return arr[idx];
}

// 3. Alternative concept: returning index and returning pointer
int getHighestIndex(const int marks[], int size) {
    int maxIdx = 0;
    for (int i = 1; i < size; ++i) {
        if (marks[i] > marks[maxIdx]) {
            maxIdx = i;
        }
    }
    return maxIdx;
}

int* getHighestPointer(int marks[], int size) {
    int maxIdx = 0;
    for (int i = 1; i < size; ++i) {
        if (marks[i] > marks[maxIdx]) {
            maxIdx = i;
        }
    }
    return &marks[maxIdx];
}

// Note: Function returning reference to local variable
// int& badLocal() {
//     int temp = 42;
//     return temp; // warning: reference to local variable 'temp' returned [-Wreturn-local-addr]
// }

int main() {
    std::cout << "=== Q2: RETURN BY REFERENCE AND ITS DANGERS ===\n\n";

    int marks[] = {78, 85, 92, 64, 88};
    int n = sizeof(marks) / sizeof(marks[0]);

    std::cout << "Original marks: ";
    for (int i = 0; i < n; ++i) std::cout << marks[i] << ' ';
    std::cout << "\nHighest mark: " << getHighestMark(marks, n) << '\n';

    // 1. Using return-by-reference on the left side of assignment / moderation
    std::cout << "\n--- Moderation of +2 directly to highest mark ---\n";
    getHighestMark(marks, n) += 2;
    std::cout << "Marks after moderation: ";
    for (int i = 0; i < n; ++i) std::cout << marks[i] << ' ';
    std::cout << '\n';

    getHighestMark(marks, n) = 100;
    std::cout << "Marks after setting highest to 100: ";
    for (int i = 0; i < n; ++i) std::cout << marks[i] << ' ';
    std::cout << '\n';

    // 2. Comparing Ref, Const Ref, and Copy
    std::cout << "\n--- Comparison: Reference vs Const Reference vs Copy ---\n";
    getRef(marks, 0) = 80; // Valid: lvalue reference can be modified
    std::cout << "Modified index 0 via getRef to: " << marks[0] << '\n';
    std::cout << "Read via getConstRef: " << getConstRef(marks, 0) << " (read-only)\n";
    std::cout << "Read via getCopy: " << getCopy(marks, 0) << " (independent copy)\n";

    // 3. Alternative Concepts: Index and Pointer
    std::cout << "\n--- Alternative Concepts: Index vs Pointer ---\n";
    int idx = getHighestIndex(marks, n);
    std::cout << "Highest mark via index [" << idx << "]: " << marks[idx] << '\n';
    int* ptr = getHighestPointer(marks, n);
    std::cout << "Highest mark via pointer: " << *ptr << '\n';

    // 4. Vector Reallocation Danger Demonstration
    std::cout << "\n--- Vector Growth & Reference Invalidation ---\n";
    std::vector<int> v = {78, 85, 92};
    std::cout << "Vector initial capacity: " << v.capacity() << '\n';
    int* oldAddr = &v[0];
    int& refToFirst = v[0];
    std::cout << "Initial address of v[0]: " << oldAddr << ", value: " << refToFirst << '\n';

    // Add elements to force reallocation
    v.push_back(64);
    v.push_back(88);
    v.push_back(95);

    std::cout << "Vector capacity after pushes: " << v.capacity() << '\n';
    std::cout << "New address of v[0]: " << &v[0] << '\n';
    if (&v[0] != oldAddr) {
        std::cout << "Vector reallocated buffer! Pointers and references obtained before growth are now dangling.\n";
        std::cout << "Index access v[0] remains safe: " << v[0] << '\n';
    }

    return 0;
}
