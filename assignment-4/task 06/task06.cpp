#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <memory>

// --- STAGE 2: ABSTRACT BASE CLASS HIERARCHY ---
class Vehicle {
protected:
    std::string regNo;
    double dailyRate;
    bool isRented;

public:
    Vehicle(const std::string& reg, double rate)
        : regNo(reg), dailyRate(rate), isRented(false) {}

    virtual ~Vehicle() = default;

    virtual std::string getCategory() const = 0;
    virtual double calculateCharge(int days, int lateDays = 0) const = 0;

    virtual bool rentVehicle() {
        if (!isRented) {
            isRented = true;
            return true;
        }
        return false;
    }

    virtual double returnVehicle(int days, int lateDays = 0) {
        if (isRented) {
            isRented = false;
            return calculateCharge(days, lateDays);
        }
        return 0.0;
    }

    virtual void display() const {
        std::cout << "Reg: " << std::left << std::setw(12) << regNo 
                  << " | Type: " << std::setw(14) << getCategory()
                  << " | Daily Rate: Rs " << std::setw(8) << dailyRate
                  << " | Status: " << (isRented ? "RENTED" : "AVAILABLE");
    }

    std::string getRegNo() const { return regNo; }
    bool getStatus() const { return isRented; }
};

// Non-motorized vehicle
class Bicycle : public Vehicle {
public:
    Bicycle(const std::string& reg, double rate = 150.0)
        : Vehicle(reg, rate) {}

    std::string getCategory() const override { return "Bicycle"; }

    double calculateCharge(int days, int lateDays = 0) const override {
        // Late penalty: 1.5x daily rate per late day
        return (days * dailyRate) + (lateDays * dailyRate * 1.5);
    }
};

// Motorized vehicle base class
class MotorVehicle : public Vehicle {
protected:
    double fuelLevel; // In Litres or Percentage
    std::string serviceDueDate;

public:
    MotorVehicle(const std::string& reg, double rate, double fuel, const std::string& serviceDate)
        : Vehicle(reg, rate), fuelLevel(fuel), serviceDueDate(serviceDate) {}

    void display() const override {
        Vehicle::display();
        std::cout << " | Fuel/Charge: " << fuelLevel << " | Service Due: " << serviceDueDate;
    }
};

class TwoWheeler : public MotorVehicle {
public:
    TwoWheeler(const std::string& reg, double rate, double fuel, const std::string& serviceDate)
        : MotorVehicle(reg, rate, fuel, serviceDate) {}

    std::string getCategory() const override { return "Two-Wheeler"; }

    double calculateCharge(int days, int lateDays = 0) const override {
        // Base rate + helmet fee Rs 50 + late penalty 1.5x
        return (days * dailyRate) + 50.0 + (lateDays * dailyRate * 1.5);
    }
};

class Car : public MotorVehicle {
protected:
    int seatingCapacity;

public:
    Car(const std::string& reg, double rate, double fuel, const std::string& serviceDate, int seats)
        : MotorVehicle(reg, rate, fuel, serviceDate), seatingCapacity(seats) {}

    std::string getCategory() const override { return "Car"; }

    double calculateCharge(int days, int lateDays = 0) const override {
        // Base charge + insurance flat Rs 200 + late penalty 2.0x
        return (days * dailyRate) + 200.0 + (lateDays * dailyRate * 2.0);
    }

    void display() const override {
        MotorVehicle::display();
        std::cout << " | Seats: " << seatingCapacity;
    }
};

class ElectricCar : public Car {
private:
    double batteryKWh;

public:
    ElectricCar(const std::string& reg, double rate, double chargePct, const std::string& serviceDate,
                int seats, double kWh)
        : Car(reg, rate, chargePct, serviceDate, seats), batteryKWh(kWh) {}

    std::string getCategory() const override { return "Electric Car"; }

    double calculateCharge(int days, int lateDays = 0) const override {
        // Green discount 10% on base daily rate + Rs 15 per kWh charging surcharge + late penalty 2.0x
        double base = days * dailyRate * 0.90;
        double rechargeFee = batteryKWh * 15.0;
        double lateFee = lateDays * dailyRate * 2.0;
        return base + rechargeFee + lateFee;
    }

    void display() const override {
        Car::display();
        std::cout << " | Battery: " << batteryKWh << " kWh";
    }
};

// --- DEMONSTRATING OPEN-CLOSED PRINCIPLE: EXTENDING WITH NEW VEHICLE TYPE ---
// ElectricBus added WITHOUT modifying any of the above existing classes!
class ElectricBus : public MotorVehicle {
private:
    int passengerCapacity;
    double batteryKWh;

public:
    ElectricBus(const std::string& reg, double rate, double chargePct, const std::string& serviceDate,
                int passengers, double kWh)
        : MotorVehicle(reg, rate, chargePct, serviceDate),
          passengerCapacity(passengers), batteryKWh(kWh) {}

    std::string getCategory() const override { return "Electric Bus"; }

    double calculateCharge(int days, int lateDays = 0) const override {
        // Commercial fleet surcharge Rs 500 + battery kWh rate + late penalty 2.5x
        return (days * dailyRate) + 500.0 + (batteryKWh * 20.0) + (lateDays * dailyRate * 2.5);
    }

    void display() const override {
        MotorVehicle::display();
        std::cout << " | Capacity: " << passengerCapacity << " passengers | Battery: " << batteryKWh << " kWh";
    }
};

int main() {
    std::cout << "=== TASK 6: DESIGN CHALLENGE - VEHICLE RENTAL FLEET ===\n\n";

    std::vector<std::unique_ptr<Vehicle>> fleet;
    fleet.push_back(std::make_unique<Bicycle>("TN-01-B101", 150.0));
    fleet.push_back(std::make_unique<TwoWheeler>("TN-02-TW202", 450.0, 8.5, "2026-12-01"));
    fleet.push_back(std::make_unique<Car>("TN-03-C303", 2200.0, 35.0, "2026-12-15", 5));
    fleet.push_back(std::make_unique<ElectricCar>("TN-04-EC404", 2800.0, 95.0, "2027-01-10", 5, 40.0));
    // New class added seamlessly
    fleet.push_back(std::make_unique<ElectricBus>("TN-05-EB505", 8500.0, 90.0, "2027-02-20", 40, 200.0));

    std::cout << "--- 1. CURRENT FLEET ROSTER ---\n";
    for (const auto& v : fleet) {
        v->display();
        std::cout << '\n';
    }

    std::cout << "\n--- 2. RENTING ALL VEHICLES ---\n";
    for (const auto& v : fleet) {
        v->rentVehicle();
        std::cout << "Rented " << v->getCategory() << " [" << v->getRegNo() << "] successfully.\n";
    }

    std::cout << "\n--- 3. RETURNING VEHICLES WITH USAGE AND LATE CHARGES ---\n";
    std::cout << std::fixed << std::setprecision(2);
    // Return bicycle: 3 days, 0 late
    double bFee = fleet[0]->returnVehicle(3, 0);
    std::cout << "Returned " << fleet[0]->getCategory() << " (3 days on-time): Total Bill = Rs " << bFee << '\n';

    // Return car: 4 days rented, 2 days late
    double cFee = fleet[2]->returnVehicle(4, 2);
    std::cout << "Returned " << fleet[2]->getCategory() << " (4 days + 2 days late): Total Bill = Rs " << cFee << '\n';

    // Return electric car: 2 days, 1 day late
    double ecFee = fleet[3]->returnVehicle(2, 1);
    std::cout << "Returned " << fleet[3]->getCategory() << " (2 days + 1 day late): Total Bill = Rs " << ecFee << '\n';

    // Return new Electric Bus: 5 days, 0 late
    double busFee = fleet[4]->returnVehicle(5, 0);
    std::cout << "Returned NEW " << fleet[4]->getCategory() << " (5 days on-time): Total Bill = Rs " << busFee << '\n';

    return 0;
}
