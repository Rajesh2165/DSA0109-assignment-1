#include <iomanip>
#include <iostream>
#include <string>

class Cart {
    std::string items[10];
    double prices[10];
    int n = 0;
    double discount = 0; // percent

public:
    // TODO 1: add(): store the item and price if there is space, and return *this so
    // that calls can be chained
    Cart& add(const std::string& item, double price) {
        if (n < 10) {
            items[n] = item;
            prices[n] = price;
            ++n;
        }
        return *this;
    }

    // TODO 2: setDiscount(): use this-> to tell the member apart from the parameter
    // named discount, and return *this
    Cart& setDiscount(double discount) {
        this->discount = discount;
        return *this;
    }

    double total() const {
        double t = 0;
        for (int i = 0; i < n; ++i) t += prices[i];
        return t * (100 - discount) / 100;
    }

    int getItemCount() const { return n; }
};

int main() {
    std::cout << "=== TASK 5: POINTERS TO OBJECTS AND THE this POINTER ===\n\n";

    std::cout << "--- 1. RUNNING EXPECTED COMPLETE THE CODE ROUTINE ---\n";
    Cart c;
    c.add("Rice", 60).add("Dal", 120).setDiscount(10);
    Cart* p = &c; // pointer to an object
    p->add("Oil", 180);
    std::cout << std::fixed << std::setprecision(2) << p->total() << '\n';

    std::cout << "\n--- 2. DEMONSTRATING FOUR WAYS TO REACH AN OBJECT ---\n";
    // (a) Directly by name
    std::cout << "(a) Directly by name: Total = " << c.total() << '\n';

    // (b) Through pointer with ->
    std::cout << "(b) Through pointer (p->total()): Total = " << p->total() << '\n';

    // (c) Through reference
    Cart& ref = c;
    std::cout << "(c) Through reference (ref.total()): Total = " << ref.total() << '\n';

    // (d) Through dynamically allocated pointer (new/delete)
    Cart* heapCart = new Cart();
    heapCart->add("Sugar", 45).add("Tea", 150).setDiscount(5);
    std::cout << "(d) Heap pointer (new/delete): Total = " << heapCart->total() << '\n';
    delete heapCart;

    std::cout << "\n--- 3. FINDING CART WITH HIGHEST TOTAL (ARRAY OF POINTERS) ---\n";
    Cart c1, c2, c3;
    c1.add("Apples", 200).add("Bananas", 60);                  // Total: 260
    c2.add("Laptop Bag", 1500).setDiscount(10);                // Total: 1350
    c3.add("Headphones", 800).add("Mouse", 400).setDiscount(5); // Total: 1140

    Cart* activeCarts[3] = { &c1, &c2, &c3 };
    int highestIdx = 0;
    for (int i = 1; i < 3; ++i) {
        if (activeCarts[i]->total() > activeCarts[highestIdx]->total()) {
            highestIdx = i;
        }
    }

    std::cout << "Cart with highest total is Cart [" << highestIdx 
              << "] with Total = Rs " << activeCarts[highestIdx]->total() << '\n';

    return 0;
}
