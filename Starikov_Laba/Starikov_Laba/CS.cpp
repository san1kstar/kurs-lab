#include "CS.h"
#include "Checks.h"

int CS::MaxID = 0;

CS::CS() : id(++MaxID), count_workshops(0), active_workshops(0), cs_class('A') {}
CS::CS(int id_) : id(id_), count_workshops(0), active_workshops(0), cs_class('A') {}

std::ostream& operator << (std::ostream& out, const CS& c) {
    out << "Id: " << c.id << "\n";
    out << "Name: " << c.name << "\n";
    out << "Workshops: " << c.count_workshops << "\n";
    out << "Active: " << c.active_workshops << "\n";
    out << "Class: " << c.cs_class << "\n\n";
    return out;
}

std::istream& operator >> (std::istream& in, CS& c) {
    c.name = inputName(in, "Name: ");
    c.count_workshops = inputInt(in, "Count of workshops: ", 1, 10000);
    c.active_workshops = inputInt(in, "Count of active workshops: ", 0, c.count_workshops);
    c.cs_class = inputNumber<char>(in, "Class ('A' 'B' 'C' 'D'): ", 'A', 'D');
    return in;
}

std::ofstream& operator << (std::ofstream& out, const CS& c) {
    out << "C\n";
    out << c.id << "\n"
        << c.name << "\n"
        << c.count_workshops << "\n"
        << c.active_workshops << "\n"
        << c.cs_class << "\n";
    return out;
}

std::ifstream& operator >> (std::ifstream& in, CS& c) {
    std::string line;
    if (!std::getline(in, c.name)) return in;
    if (!std::getline(in, line)) return in;
    c.count_workshops = std::stoi(line);
    if (!std::getline(in, line)) return in;
    c.active_workshops = std::stoi(line);
    if (!std::getline(in, line)) return in;
    c.cs_class = line[0];
    return in;
}