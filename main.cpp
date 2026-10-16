
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
#include <iomanip>
using namespace std;

struct Patient {
    int id;
    string name;
    int age;
    string disease;
    string doctor;
    double bill;
};

struct Doctor {
    int id;
    string name;
    string specialization;
};

struct Appointment {
    int patientId;
    int doctorId;
    string date;
};

vector<Patient> patients;
vector<Doctor> doctors;
vector<Appointment> appointments;

void savePatients() {
    ofstream file("patients.txt");

    for (const auto& p : patients) {
        file << p.id << '\n'
             << p.name << '\n'
             << p.age << '\n'
             << p.disease << '\n'
             << p.doctor << '\n'
             << p.bill << '\n';
    }
}

void loadPatients() {
    ifstream file("patients.txt");
    Patient p;

    while (file >> p.id) {
        file.ignore(numeric_limits<streamsize>::max(), '\n');

        if (!getline(file, p.name) ||
            !(file >> p.age))
            break;

        file.ignore(numeric_limits<streamsize>::max(), '\n');

        if (!getline(file, p.disease) ||
            !getline(file, p.doctor) ||
            !(file >> p.bill))
            break;

        file.ignore(numeric_limits<streamsize>::max(), '\n');
        patients.push_back(p);
    }
}

void addPatient() {
    Patient p;

    cout << "Enter patient ID: ";
    if (!(cin >> p.id)) {
        cout << "Invalid ID.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    for (const auto& existing : patients) {
        if (existing.id == p.id) {
            cout << "Patient ID already exists.\n";
            return;
        }
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter patient name: ";
    getline(cin, p.name);

    cout << "Enter age: ";
    if (!(cin >> p.age) || p.age < 0 || p.age > 130) {
        cout << "Invalid age.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter disease/complaint: ";
    getline(cin, p.disease);

    cout << "Enter assigned doctor: ";
    getline(cin, p.doctor);

    cout << "Enter bill amount: ";
    if (!(cin >> p.bill) || p.bill < 0) {
        cout << "Invalid bill amount.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    patients.push_back(p);
    savePatients();

    cout << "Patient registered successfully!\n";
}

void viewPatients() {
    if (patients.empty()) {
        cout << "No patient records available.\n";
        return;
    }

    cout << "\n--- Patient Records ---\n";

    for (const auto& p : patients) {
        cout << "\nPatient ID: " << p.id
             << "\nName: " << p.name
             << "\nAge: " << p.age
             << "\nComplaint: " << p.disease
             << "\nDoctor: " << p.doctor
             << "\nBill: Rs. " << fixed
             << setprecision(2) << p.bill
             << "\n-------------------------\n";
    }
}

void searchPatient() {
    int id;
    cout << "Enter patient ID: ";

    if (!(cin >> id)) {
        cout << "Invalid ID.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    for (const auto& p : patients) {
        if (p.id == id) {
            cout << "\nPatient found!\n"
                 << "Name: " << p.name
                 << "\nAge: " << p.age
                 << "\nComplaint: " << p.disease
                 << "\nDoctor: " << p.doctor
                 << "\nBill: Rs. " << p.bill << '\n';
            return;
        }
    }

    cout << "Patient not found.\n";
}

void addDoctor() {
    Doctor d;

    cout << "Enter doctor ID: ";
    if (!(cin >> d.id)) {
        cout << "Invalid ID.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    for (const auto& existing : doctors) {
        if (existing.id == d.id) {
            cout << "Doctor ID already exists.\n";
            return;
        }
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter doctor name: ";
    getline(cin, d.name);

    cout << "Enter specialization: ";
    getline(cin, d.specialization);

    doctors.push_back(d);
    cout << "Doctor registered successfully!\n";
}

void viewDoctors() {
    if (doctors.empty()) {
        cout << "No doctors registered in this session.\n";
        return;
    }

    cout << "\n--- Doctor Directory ---\n";

    for (const auto& d : doctors) {
        cout << "ID: " << d.id
             << "\nName: " << d.name
             << "\nSpecialization: " << d.specialization
             << "\n-------------------------\n";
    }
}

void bookAppointment() {
    int patientId, doctorId;
    string date;

    cout << "Enter patient ID: ";
    if (!(cin >> patientId)) {
        cout << "Invalid patient ID.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    bool patientFound = false;
    for (const auto& p : patients) {
        if (p.id == patientId) {
            patientFound = true;
            break;
        }
    }

    if (!patientFound) {
        cout << "Register the patient first.\n";
        return;
    }

    cout << "Enter doctor ID: ";
    if (!(cin >> doctorId)) {
        cout << "Invalid doctor ID.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    bool doctorFound = false;
    for (const auto& d : doctors) {
        if (d.id == doctorId) {
            doctorFound = true;
            break;
        }
    }

    if (!doctorFound) {
        cout << "Register the doctor first.\n";
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter appointment date (DD-MM-YYYY): ";
    getline(cin, date);

    appointments.push_back({patientId, doctorId, date});
    cout << "Appointment booked successfully!\n";
}

void viewAppointments() {
    if (appointments.empty()) {
        cout << "No appointments in this session.\n";
        return;
    }

    cout << "\n--- Appointments ---\n";

    for (const auto& a : appointments) {
        cout << "Patient ID: " << a.patientId
             << "\nDoctor ID: " << a.doctorId
             << "\nDate: " << a.date
             << "\n-------------------------\n";
    }
}

void showMenu() {
    cout << "\n===== HOSPITAL MANAGEMENT =====\n"
         << "1. Register Patient\n"
         << "2. View Patients\n"
         << "3. Search Patient\n"
         << "4. Register Doctor\n"
         << "5. View Doctors\n"
         << "6. Book Appointment\n"
         << "7. View Appointments\n"
         << "8. Exit\n"
         << "Choose an option: ";
}

int main() {
    loadPatients();

    int choice;

    do {
        showMenu();

        if (!(cin >> choice)) {
            cout << "Please enter a valid menu number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1: addPatient(); break;
            case 2: viewPatients(); break;
            case 3: searchPatient(); break;
            case 4: addDoctor(); break;
            case 5: viewDoctors(); break;
            case 6: bookAppointment(); break;
            case 7: viewAppointments(); break;
            case 8: cout << "Exiting system. Goodbye!\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 8);

    return 0;
}
