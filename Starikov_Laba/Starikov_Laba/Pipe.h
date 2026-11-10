#pragma once
#include <iostream>
#include <fstream>
#include <string>

class Pipe {
    int id;
    static int MaxID;
    std::string name;
    double length;
    int diameter;
    bool working;

public:
    Pipe();
    explicit Pipe(int id_);

    int GetID() const { return id; }
    std::string GetName() const { return name; }
    double GetLength() const { return length; }
    int GetDiameter() const { return diameter; }
    bool IsWorking() const { return working; }
    void SetWorking(bool w) { working = w; }
    void ToggleStatus() { working = !working; }

    static int GetMaxID() { return MaxID; }
    static void SetMaxID(int max_val) { MaxID = max_val; }

    friend std::ostream& operator << (std::ostream& out, const Pipe& p);
    friend std::istream& operator >> (std::istream& in, Pipe& p);
    friend std::ofstream& operator << (std::ofstream& out, const Pipe& p);
    friend std::ifstream& operator >> (std::ifstream& in, Pipe& p);
};