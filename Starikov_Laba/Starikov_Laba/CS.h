#pragma once
#include <iostream>
#include <string>

class CS {
    int id;
public:
    static int MaxID;
    std::string name;
    int count_workshops;
    int active_workshops;
    char cs_class;

    CS();

    int GetID() const { return id; }
    static void SetMaxID(int new_id) { MaxID = new_id; }

    int GetUnusedPercent() const {
        if (count_workshops == 0) return 0;
        return ((count_workshops - active_workshops) * 100) / count_workshops;
    }

    friend std::ostream& operator << (std::ostream& out, const CS& c);
    friend std::istream& operator >> (std::istream& in, CS& c);
};