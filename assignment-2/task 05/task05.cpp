#include <iostream>
#include <string>

// --- PREDICTION CODE ---
class Token {
    static int next;
    int id;
public:
    Token() { id = ++next; }
    int get() const { return id; }
    static int issued() { return next - 100; }
};
int Token::next = 100;

void runPrediction() {
    std::cout << "--- 1. PREDICT THE OUTPUT (Token Class) ---\n";
    Token counter[3];
    Token extra;
    std::cout << counter[0].get() << ' ' << counter[2].get() << ' ' << extra.get()
              << ' ' << Token::issued() << '\n';
}

// --- COMPLETE THE CODE: BUS TICKET ---
class BusTicket {
    static int issued; // shared by all BusTicket objects
    static const int CAPACITY = 3;
    int seat;
    std::string name;
public:
    explicit BusTicket(const std::string& n) : seat(0), name(n) {
        // TODO 1: If fewer than CAPACITY tickets have been issued, increase issued and
        // give this ticket the next seat number; otherwise leave seat as 0 (waiting list)
        if (issued < CAPACITY) {
            seat = ++issued;
        }
    }

    static int count() {
        // TODO 2: Return the number of seats issued so far
        return issued;
    }

    void print() const {
        std::cout << name << ": "
                  << (seat ? "Seat " + std::to_string(seat) : std::string("Waiting"))
                  << '\n';
    }

    static void reset() {
        issued = 0;
    }
};

int BusTicket::issued = 0; // definition of the static data member

void issueTicketsBatch(const std::string& batchName) {
    std::cout << "\nIssuing batch: " << batchName << '\n';
    BusTicket t1("Passenger_A");
    BusTicket t2("Passenger_B");
    t1.print();
    t2.print();
    std::cout << "Current Total Issued: " << BusTicket::count() << '\n';
}

int main() {
    std::cout << "=== Q5: STATIC MEMBERS AND ARRAYS OF OBJECTS ===\n\n";

    runPrediction();

    std::cout << "\n--- 2. COMPLETE THE CODE (BusTicket Class) ---\n";
    BusTicket trip[4] = {
        BusTicket("Asha"),
        BusTicket("Bala"),
        BusTicket("Chitra"),
        BusTicket("Dev")
    };

    for (const BusTicket& t : trip) {
        t.print();
    }
    std::cout << "Issued: " << BusTicket::count() << '\n';

    std::cout << "\n--- 3. TICKETS CREATED INSIDE A FUNCTION CALLED TWICE ---\n";
    BusTicket::reset();
    std::cout << "[Reset BusTicket::issued to 0 for batch experiment]\n";
    issueTicketsBatch("Morning Trip Call 1");
    issueTicketsBatch("Morning Trip Call 2"); // Note: exceeds capacity 3, will show persistence across calls

    return 0;
}
