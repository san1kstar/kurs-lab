#include "Pipe.h"
#include "Checks.h"
using namespace std;

int Pipe::MaxID = 0;

Pipe::Pipe() {
    id = ++MaxID;
    name = "";
    length = 0.0;
    diameter = 0.0f;
    status = 'P';
}

ostream& operator << (ostream& out, const Pipe& p) {
    out << "\nID: " << p.GetID() << "\n";
    out << "Name: " << p.name << "\n";
    out << "Length: " << p.length << "\n";
    out << "Diameter: " << p.diameter << "\n";
    out << "Status: " << p.status << "\n";
    return out;
}

istream& operator >> (istream& in, Pipe& p) {
    p.name = inputName(in, "Type name: ");
    p.length = inputPositiveDouble(in, "Type length (positive): ");
    p.diameter = (float)inputPositiveDouble(in, "Type diameter (positive): ");
    p.status = inputChar(in, "Type status ('P' - passive, 'A' - active): ", 'A', 'P');
    return in;
}   