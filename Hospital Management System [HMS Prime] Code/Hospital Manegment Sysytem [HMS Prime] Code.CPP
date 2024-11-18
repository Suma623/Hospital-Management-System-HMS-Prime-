#include <bits/stdc++.h>

using namespace std;

class Person {
protected:
    string name;
    int id;

public:
    Person(string name, int id) : name(name), id(id) {}
    virtual void display() const = 0;
    int getId() const { return id; }
};

class Patient : public Person {
public:
    Patient(string name, int id) : Person(name, id) {}

    void display() const override {
        cout << "Patient Name: " << name << ", ID: " << id << endl;
    }
};

class Doctor : public Person {
public:
    Doctor(string name, int id) : Person(name, id) {}

    void display() const override {
        cout << "Doctor Name: " << name << ", ID: " << id << endl;
    }
};

class Appointment {
    Patient patient;
    Doctor doctor;
    string dateTime;

public:
    Appointment(Patient p, Doctor d, string dt) : patient(p), doctor(d), dateTime(dt) {}

    void display() const {
        cout << "Appointment for ";
        patient.display();
        cout << " with ";
        doctor.display();
        cout << " on " << dateTime << endl;
    }
};

class Treatment {
    string description;
    double cost;

public:
    Treatment(string desc, double c) : description(desc), cost(c) {}

    double getCost() const {
        return cost;
    }

    void display() const {
        cout << "Treatment: " << description << ", Cost: $" << fixed << setprecision(2) << cost << endl;
    }
};

class Billing {
    vector<Treatment> treatments;

public:
    void addTreatment(const Treatment& treatment) {
        treatments.push_back(treatment);
    }

    double calculateTotal() const {
        double total = 0;
        for (const auto& treatment : treatments) {
            total += treatment.getCost();
        }
        return total;
    }

    void displayBill() const {
        cout << "\nBilling Summary:\n";
        for (const auto& treatment : treatments) {
            treatment.display();
        }
        cout << "Total Bill: $" << fixed << setprecision(2) << calculateTotal() << endl;
    }
};

class HMSException : public runtime_error {
public:
    HMSException(const string& message) : runtime_error(message) {}
};

void addPatient(vector<Patient>& patients) {
    string name;
    int id;

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
    cout << "Enter Patient Name: ";
    getline(cin, name);
    cout << "Enter Patient ID: ";
    cin >> id;

    patients.emplace_back(name, id);
    cout << "Patient added successfully.\n";
}

void addDoctor(vector<Doctor>& doctors) {
    string name;
    int id;

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
    cout << "Enter Doctor Name: ";
    getline(cin, name);
    cout << "Enter Doctor ID: ";
    cin >> id;

    doctors.emplace_back(name, id);
    cout << "Doctor added successfully.\n";
}

void addAppointment(const vector<Patient>& patients, const vector<Doctor>& doctors, vector<Appointment>& appointments) {
    int patientId, doctorId;
    string dateTime;

    cout << "Enter Patient ID for appointment: ";
    cin >> patientId;
    cout << "Enter Doctor ID for appointment: ";
    cin >> doctorId;
    cout << "Enter Appointment Date and Time (YYYY-MM-DD HH:MM AM/PM): ";
    cin.ignore();
    getline(cin, dateTime);

    const Patient* selectedPatient = nullptr;
    const Doctor* selectedDoctor = nullptr;

    for (const auto& p : patients) {
        if (p.getId() == patientId) {
            selectedPatient = &p;
            break;
        }
    }

    for (const auto& d : doctors) {
        if (d.getId() == doctorId) {
            selectedDoctor = &d;
            break;
        }
    }

    if (selectedPatient && selectedDoctor) {
        appointments.emplace_back(*selectedPatient, *selectedDoctor, dateTime);
        cout << "Appointment scheduled successfully.\n";
    } else {
        cout << "Invalid Patient or Doctor ID.\n";
    }
}

void addTreatment(Billing& bill) {
    string description;
    double cost;

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
    cout << "Enter Treatment Description: ";
    getline(cin, description);
    cout << "Enter Treatment Cost: ";
    cin >> cost;

    bill.addTreatment(Treatment(description, cost));
    cout << "Treatment added successfully.\n";
}

int main() {
    vector<Patient> patients;
    vector<Doctor> doctors;
    vector<Appointment> appointments;
    Billing bill;

    int choice;

    do {
        cout << "\n--- Hospital Management System ---\n";
        cout << "1. Add Patient\n";
        cout << "2. Add Doctor\n";
        cout << "3. Schedule Appointment\n";
        cout << "4. Add Treatment\n";
        cout << "5. Display Appointments\n";
        cout << "6. Display Billing\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addPatient(patients); break;
            case 2: addDoctor(doctors); break;
            case 3: addAppointment(patients, doctors, appointments); break;
            case 4: addTreatment(bill); break;
            case 5:
                for (const auto& appt : appointments) {
                    appt.display();
                }
                break;
            case 6: bill.displayBill(); break;
            case 7: cout << "Exiting system.\n"; break;
            default: cout << "Invalid choice. Please try again.\n"; break;
        }
    } while (choice != 0);

    return 0;
}