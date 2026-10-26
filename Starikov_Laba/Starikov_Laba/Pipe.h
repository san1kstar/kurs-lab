#pragma once
#include <iostream>
#include <string>

class Pipe {
    int id;
public:
    static int MaxID;
    std::string name;
    double length;
    float diameter;
    char status;

    Pipe();

    int GetID() const { return id; }
    static void SetMaxID(int new_id) { MaxID = new_id; }

    friend std::ostream& operator << (std::ostream& out, const Pipe& p);
    friend std::istream& operator >> (std::istream& in, Pipe& p);
};