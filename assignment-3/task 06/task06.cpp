#include <iostream>
#include <cstring>

class Text {
private:
    char* str;
    int len;

public:
    static int copyCount;

    // Default constructor
    Text() : str(new char[1]{'\0'}), len(0) {}

    // Parameterised constructor
    Text(const char* s) {
        if (s == nullptr) {
            len = 0;
            str = new char[1]{'\0'};
        } else {
            len = std::strlen(s);
            str = new char[len + 1];
            std::strcpy(str, s);
        }
    }

    // Copy Constructor (Deep Copy)
    Text(const Text& other) : str(new char[other.len + 1]), len(other.len) {
        std::strcpy(str, other.str);
        ++copyCount;
    }

    // Copy Assignment Operator (Deep Copy + Self-Assignment Protection)
    Text& operator=(const Text& other) {
        if (this != &other) {
            char* newStr = new char[other.len + 1];
            std::strcpy(newStr, other.str);
            delete[] str;
            str = newStr;
            len = other.len;
        }
        return *this;
    }

    // Destructor
    ~Text() {
        delete[] str;
    }

    // Overload + for Concatenation
    Text operator+(const Text& other) const {
        Text result;
        delete[] result.str;
        result.len = len + other.len;
        result.str = new char[result.len + 1];
        std::strcpy(result.str, str);
        std::strcat(result.str, other.str);
        return result;
    }

    // Overload == for Comparison
    bool operator==(const Text& other) const {
        return (len == other.len) && (std::strcmp(str, other.str) == 0);
    }

    // Overload != for Comparison
    bool operator!=(const Text& other) const {
        return !(*this == other);
    }

    // Overload << as friend
    friend std::ostream& operator<<(std::ostream& os, const Text& t) {
        os << t.str;
        return os;
    }

    int length() const { return len; }
    const char* c_str() const { return str; }
};

int Text::copyCount = 0;

int main() {
    std::cout << "=== Q6: THE RULES OF OPERATOR OVERLOADING (SMS GATEWAY TEXT CLASS) ===\n\n";

    std::cout << "--- 1. BASIC OPERATIONS & CONCATENATION (+ and <<) ---\n";
    Text t1("Hello, ");
    Text t2("World!");
    Text combined = t1 + t2;
    std::cout << "t1: \"" << t1 << "\"\n";
    std::cout << "t2: \"" << t2 << "\"\n";
    std::cout << "t1 + t2: \"" << combined << "\" (Length: " << combined.length() << ")\n";

    std::cout << "\n--- 2. COMPARISON OPERATORS (== and !=) ---\n";
    Text t3("Hello, World!");
    std::cout << "combined == t3: " << std::boolalpha << (combined == t3) << '\n';
    std::cout << "t1 != t2: " << (t1 != t2) << '\n';

    std::cout << "\n--- 3. TESTING EMPTY STRINGS AND LONG MESSAGES ---\n";
    Text emptyText("");
    std::cout << "Empty text length: " << emptyText.length() << ", contents: \"" << emptyText << "\"\n";
    Text longMsg("ALERT: Critical server temperature threshold exceeded on node-cluster-04 at rack 12B. Immediate maintenance required.");
    std::cout << "Long message length: " << longMsg.length() << '\n';

    std::cout << "\n--- 4. SELF-ASSIGNMENT SAFETY (t1 = t1) ---\n";
    t1 = t1;
    std::cout << "After self-assignment t1: \"" << t1 << "\" (Safe)\n";

    std::cout << "\n--- 5. EVALUATING COPIES IN COMPOUND EXPRESSION (a + b + c) ---\n";
    Text::copyCount = 0;
    Text a("SMS_1: ");
    Text b("OTP is 849201. ");
    Text c("Valid for 5 mins.");
    Text fullSMS = a + b + c;
    std::cout << "Evaluated a + b + c -> \"" << fullSMS << "\"\n";
    std::cout << "Copies made during chaining: " << Text::copyCount << '\n';

    return 0;
}
