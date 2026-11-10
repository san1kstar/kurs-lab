#include "Pipe.h"
#include "Checks.h"

int Pipe::MaxID = 0;

Pipe::Pipe() : id(++MaxID), length(0), diameter(0), working(true) {}
Pipe::Pipe(int id_) : id(id_), length(0), diameter(0), working(true) {}

std::ostream& operator << (std::ostream& out, const Pipe& p) {
    out << "Id:       " << p.id << "\n";
    out << "Name:     " << p.name << "\n";
    out << "Length:   " << p.length << " km\n";
    out << "Diameter: " << p.diameter << " mm\n";
    out << "Status:   " << (p.working ? "working" : "broken") << "\n\n";
    return out;
}

std::istream& operator >> (std::istream& in, Pipe& p) {
    p.name = inputName(in, "Name: ");
    p.length = inputPositiveDouble(in, "Length in km: ");
    p.diameter = inputInt(in, "Diameter in mm: ", 1, 100000);
    int st = inputInt(in, "Select status (1 - working, 0 - broken): ", 0, 1);
    p.working = (st == 1);
    return in;
}

std::ofstream& operator << (std::ofstream& out, const Pipe& p) {
    out << "P\n";
    out << p.id << "\n"
        << p.name << "\n"
        << p.length << "\n"
        << p.diameter << "\n"
        << p.working << "\n";
    return out;
}

std::ifstream& operator >> (std::ifstream& in, Pipe& p) {
    std::string line;
    if (!std::getline(in, p.name)) return in;
    if (!std::getline(in, line)) return in;
    p.length = std::stod(line);
    if (!std::getline(in, line)) return in;
    p.diameter = std::stoi(line);
    if (!std::getline(in, line)) return in;
    p.working = (std::stoi(line) != 0);
    return in;
}