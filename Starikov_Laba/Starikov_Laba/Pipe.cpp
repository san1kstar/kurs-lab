#include "Pipe.h"
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
    out << "ID: " << p.GetID() << "\n";
    out << "Name: " << p.name << "\n";
    out << "Length: " << p.length << "\n";
    out << "Diameter: " << p.diameter << "\n";
    out << "Status: " << p.status << "\n";
    return out;
}

istream& operator >> (istream& in, Pipe& p) {
    cout << "Type name: ";
    in.ignore();
    getline(in, p.name);
    while (p.name == "") {
        cout << "Name cannot be empty. Enter again: ";
        getline(in, p.name);
    }
    cout << "Type length (positive): ";
    in >> p.length;
    while (p.length <= 0 || in.fail()) {
        in.clear();
        in.ignore(10000, '\n');
        cout << "Length must be positive! Enter again: ";
        in >> p.length;
    }
    cout << "Type diameter (positive): ";
    in >> p.diameter;
    while (p.diameter <= 0 || in.fail()) {
        in.clear();
        in.ignore(10000, '\n');
        cout << "Diameter must be positive! Enter again: ";
        in >> p.diameter;
    }
    cout << "Type status ('P' - passive, 'A' - active): ";
    in >> p.status;
    while (p.status != 'P' && p.status != 'A') {
        in.clear();
        in.ignore(10000, '\n');
        cout << "Status must be 'P' or 'A'. Enter again: ";
        in >> p.status;
    }
    return in;
}