#include "CS.h"
#include "Checks.h"
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
    out << "\nID: " << c.GetID() << "\n";
    out << "Name: " << c.name << "\n";
    out << "Count workshops: " << c.count_workshops << "\n";
    out << "Active workshops: " << c.active_workshops << "\n";
    out << "Class: " << c.cs_class << "\n";
    return out;
}

istream& operator >> (istream& in, CS& c) {
    c.name = inputName(in, "Type name: ");
    c.count_workshops = inputPositiveInt(in, "Type count of workshops (positive): ");

    while (true) {
        c.active_workshops = inputInt(in, "Type count of active workshops: ", 0, c.count_workshops);
        break;
    }

    c.cs_class = inputChar(in, "Type class ('A', 'B', 'C' or 'D'): ", 'A', 'D');
    return in;
}