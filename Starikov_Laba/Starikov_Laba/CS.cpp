#include "CS.h"
using namespace std;

int CS::MaxID = 0;

CS::CS() {
    id = ++MaxID;
    name = "";
    count_workshops = 0;
    active_workshops = 0;
    cs_class = 'A';
}

ostream& operator << (ostream& out, const CS& c) {
    out << "ID: " << c.GetID() << "\n";
    out << "Name: " << c.name << "\n";
    out << "Count workshops: " << c.count_workshops << "\n";
    out << "Active workshops: " << c.active_workshops << "\n";
    out << "Class: " << c.cs_class << "\n";
    return out;
}

istream& operator >> (istream& in, CS& c) {
    cout << "Type name: ";
    in.ignore();
    getline(in, c.name);
    while (c.name == "") {
        cout << "Name cannot be empty. Enter again:\n";
        getline(in, c.name);
    }
    cout << "Type count of workshops:\n";
    in >> c.count_workshops;
    while (c.count_workshops <= 0 || in.fail()) {
        in.clear();
        in.ignore(10000, '\n');
        cout << "Count must be positive! Enter again:\n";
        in >> c.count_workshops;
    }
    cout << "Type count of active workshops (0-" << c.count_workshops << "):\n";
    in >> c.active_workshops;
    while (c.active_workshops < 0 || c.active_workshops > c.count_workshops || in.fail()) {
        in.clear();
        in.ignore(10000, '\n');
        cout << "Active workshops must be between 0 and " << c.count_workshops << ". Enter again:\n";
        in >> c.active_workshops;
    }
    cout << "Type class ('A', 'B', 'C' or 'D'):\n";
    in >> c.cs_class;
    while (c.cs_class != 'A' && c.cs_class != 'B' && c.cs_class != 'C' && c.cs_class != 'D') {
        in.clear();
        in.ignore(10000, '\n');
        cout << "Class must be 'A', 'B', 'C' or 'D'. Enter again:\n";
        in >> c.cs_class;
    }
    return in;
}