#pragma once
#include <iostream>
#include <fstream>
#include <string>

class CS {
    int id;
    static int MaxID;
    std::string name;
    int count_workshops;
    int active_workshops;
    char cs_class;

public:
    CS();
    explicit CS(int id_);

    int GetID() const { return id; }
    std::string GetName() const { return name; }
    int GetWorkshops() const { return count_workshops; }
    int GetActive() const { return active_workshops; }
    char GetClass() const { return cs_class; }
    void SetActive(int val) { active_workshops = val; }
    int GetUnusedPercent() const { return count_workshops ? ((count_workshops - active_workshops) * 100) / count_workshops : 0; }

    static int GetMaxID() { return MaxID; }
    static void SetMaxID(int max_val) { MaxID = max_val; }

    friend std::ostream& operator << (std::ostream& out, const CS& c);
    friend std::istream& operator >> (std::istream& in, CS& c);
    friend std::ofstream& operator << (std::ofstream& out, const CS& c);
    friend std::ifstream& operator >> (std::ifstream& in, CS& c);
};