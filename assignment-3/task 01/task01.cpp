#include <iostream>
#include <string>

class Book {
private:
    std::string title;
    std::string author;
    int copies;

public:
    // Primary parameterised constructor using member initializer list
    Book(const std::string& t, const std::string& a, int c)
        : title(t), author(a), copies(c < 0 ? 0 : c) {
        if (c < 0) {
            std::cout << "[Validation Warning: Negative copies (" << c 
                      << ") corrected to 0 for '" << title << "']\n";
        }
    }

    // Delegating constructor for donated book (title only)
    explicit Book(const std::string& t)
        : Book(t, "Anonymous Donor", 1) {}

    // Delegating default constructor for empty record
    Book()
        : Book("Untitled", "None", 0) {}

    void print() const {
        std::cout << "Book Record -> Title: \"" << title 
                  << "\", Author: " << author 
                  << ", Copies Available: " << copies << '\n';
    }

    int getCopies() const { return copies; }
};

int main() {
    std::cout << "=== Q1: CONSTRUCTORS AND CONSTRUCTOR OVERLOADING ===\n\n";

    std::cout << "--- 1. Creating Books in Three Situations (Delegating Constructors) ---\n";
    // 1. Full details
    Book b1("The C++ Programming Language", "Bjarne Stroustrup", 5);
    b1.print();

    // 2. Donated book (only title)
    Book b2("Algorithms in C++");
    b2.print();

    // 3. Empty record to be filled later
    Book b3;
    b3.print();

    std::cout << "\n--- 2. Validating Invalid (Negative) Copies ---\n";
    Book b4("Corrupted Record", "Unknown", -4);
    b4.print();

    std::cout << "\n--- 3. Array of Book Objects (Requires Default Constructor) ---\n";
    Book catalog[3];
    for (int i = 0; i < 3; ++i) {
        std::cout << "Catalog[" << i << "]: ";
        catalog[i].print();
    }

    return 0;
}
