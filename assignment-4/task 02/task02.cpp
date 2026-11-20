#include <iostream>
#include <string>

// --- PREDICTION SNIPPET ---
namespace Prediction {
    struct Person { Person() { std::cout << "Person "; } };
    struct Student : virtual Person { Student() { std::cout << "Student "; } };
    struct Staff : virtual Person { Staff() { std::cout << "Staff "; } };
    struct TeachingAssistant : Student, Staff {
        TeachingAssistant() { std::cout << "TA "; }
    };

    void run() {
        std::cout << "--- 1. PREDICT THE OUTPUT: DIAMOND INHERITANCE RESOLUTION ---\n";
        TeachingAssistant ta;
        std::cout << '\n';
    }
}

// --- UNIVERSITY PEOPLE HIERARCHY ---
class Person {
protected:
    std::string name;
    int id;
    std::string phone;

public:
    Person(const std::string& n = "", int i = 0, const std::string& ph = "")
        : name(n), id(i), phone(ph) {}
    virtual ~Person() = default;

    virtual void display() const {
        std::cout << "ID: " << id << " | Name: " << name << " | Phone: " << phone;
    }
};

class Student : virtual public Person {
protected:
    std::string programme;
    double cgpa;

public:
    Student(const std::string& n, int i, const std::string& ph,
            const std::string& prog, double gpa)
        : Person(n, i, ph), programme(prog), cgpa(gpa) {}

    void display() const override {
        Person::display();
        std::cout << " | Programme: " << programme << " | CGPA: " << cgpa;
    }
};

class Staff : virtual public Person {
protected:
    std::string department;
    double salary;

public:
    Staff(const std::string& n, int i, const std::string& ph,
          const std::string& dept, double sal)
        : Person(n, i, ph), department(dept), salary(sal) {}

    void display() const override {
        Person::display();
        std::cout << " | Dept: " << department << " | Salary: Rs " << salary;
    }
};

class TeachingAssistant : public Student, public Staff {
private:
    int teachingHours;

public:
    // In virtual inheritance, most-derived class initializes the virtual base Person directly!
    TeachingAssistant(const std::string& n, int i, const std::string& ph,
                      const std::string& prog, double gpa,
                      const std::string& dept, double sal, int hours)
        : Person(n, i, ph),
          Student(n, i, ph, prog, gpa),
          Staff(n, i, ph, dept, sal),
          teachingHours(hours) {}

    void display() const override {
        Person::display();
        std::cout << " | Programme: " << programme << " (CGPA: " << cgpa << ")"
                  << " | Dept: " << department << " (Stipend: Rs " << salary << ")"
                  << " | TA Hours: " << teachingHours << '\n';
    }
};

class ResearchScholar : public Student {
private:
    double fellowshipAmount;

public:
    ResearchScholar(const std::string& n, int i, const std::string& ph,
                    const std::string& prog, double gpa, double fellowship)
        : Person(n, i, ph), Student(n, i, ph, prog, gpa),
          fellowshipAmount(fellowship) {}

    void display() const override {
        Student::display();
        std::cout << " | Fellowship: Rs " << fellowshipAmount << '\n';
    }
};

int main() {
    std::cout << "=== TASK 2: FROM REQUIREMENT TO HIERARCHY (DIAMOND RESOLUTION) ===\n\n";

    Prediction::run();

    std::cout << "\n--- 2. DEMONSTRATING UNIVERSITY PEOPLE MANAGEMENT ---\n";
    TeachingAssistant ta("Kavya M", 501, "+91-9840112233", "M.Tech CSE", 9.4, "Computer Science", 25000.0, 12);
    std::cout << "Teaching Assistant (Hybrid Virtual Inheritance):\n  ";
    ta.display();

    ResearchScholar rs("Rajesh V", 601, "+91-9876543210", "Ph.D AI", 9.8, 37000.0);
    std::cout << "\nResearch Scholar (Multilevel Inheritance):\n  ";
    rs.display();

    return 0;
}
