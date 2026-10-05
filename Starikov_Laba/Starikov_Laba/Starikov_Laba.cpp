// Starikov_Laba.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <limits>
#include <string>
using namespace std;

struct Pipe {
    string Pipe_name = "";
    double lenght = 0.0;
    float diametr = 0.0f;
    char status = 'P';
};

struct CS {
    string CS_name = "";
    int count_workshops = 0;
    int active_workskops = 0;
    char CS_class = 'A';
};


void zapusk() {
    cout << "\nApp menu.\n";
    cout << "Choose a number for processing a command.\n";
    cout << "1 - Add pipe\n";
    cout << "2 - Add CS\n";
    cout << "3 - View all object\n";
    cout << "4 - Edit Pipe\n";
    cout << "5 - Edit CS\n";
    cout << "6 - Save\n";
    cout << "7 - Download\n";
    cout << "0 - Exit\n";
}

void check() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

string line_with_space() {
    string v;
    cin.ignore();
    getline(cin, v);
    return v;
}

void add_pipe(Pipe& p) {
    cout << "Give a name to the pipe.\n";
    p.Pipe_name = line_with_space();
    cout << "Enter the pipe diameter.\n";
    cin >> p.diametr;
    while (p.diametr <= 0 || cin.fail()) {
        check();
        cout << "diametr must be positive! Enter again\n";
        cin >> p.diametr;
    }
    cout << "Enter the length of the pipe.\n";
    cin >> p.lenght;
    while (p.lenght <= 0 || cin.fail()) {
        check();
        cout << "lenght must be positive! Enter again\n";
        cin >> p.lenght;
    }
    cout << "Enter the pipe status. (P - passive, A - active)\n";
    cin >> p.status;
    while (p.status != 'P' && p.status != 'A') {
        cout << "status of pipe must be 'P' or 'A'\n";
        cin >> p.status;
    }
    cout << "\nYou add a new pipe!\n\n";
    cout << "Pipe name: " << p.Pipe_name << "\n";
    cout << "Diametr: " << p.diametr << "\n";
    cout << "Lenght: " << p.lenght << "\n";
    if (p.status == 'P') {
        cout << "Status: passive\n";
    }
    else {
        cout << "Status: active\n";
    }
}

void add_CS(CS& c) {
cout << "Give a name to the CS\n";
c.CS_name = line_with_space();
cout << "Enter the count of workshops in CS\n";
cin >> c.count_workshops;
while (c.count_workshops <= 0 || cin.fail()) {
    check();
    cout << "count of workshops must be positive\n";
    cin >> c.count_workshops;
}
cout << "Enter the count of active workshops in CS\n";
cin >> c.active_workskops;
while (c.active_workskops < 0 || c.active_workskops > c.count_workshops || cin.fail()) {
    if (c.active_workskops < 0) {
        cout << "count of active workshops must be > 0\n";
    }
    else if (cin.fail()) {
        check();
    }
    else {
        cout << "total active workshops must be < count of workshops\n";
    }
    cin >> c.active_workskops;
}
cout << "Give a class to the CS (A, B, C, D)\n";
cin >> c.CS_class;
while (c.CS_class != 'A' && c.CS_class != 'B' && c.CS_class != 'C' && c.CS_class != 'D') {
    cout << "Class of CS must be 'A', 'B', 'C' or 'D'\n";
    cin >> c.CS_class;
}
cout << "You add a new CS!\n\n";
cout << "CS name: " << c.CS_name << "\n";
cout << "Count workshops: " << c.count_workshops << "\n";
cout << "Count active workshops: " << c.active_workskops << "\n";
cout << "CS class: " << c.CS_class << "\n";
}

void view_objects(Pipe&p, CS&c) {
    cout << "Your pipes:\n\n";
    if (p.Pipe_name == "") {
        cout << "No added pipes\n";
    }
    else {
        cout << "Name: " << p.Pipe_name << "\n";
        cout << "Diametr: " << p.diametr << "\n";
        cout << "Lenght: " << p.lenght << "\n";
        if (p.status == 'P') {
            cout << "Status: Passive\n";
        }
        else {
            cout << "Status: Active\n";
        }
    }
    cout << "Your CSs:\n\n";
    if (c.CS_name == "") {
        cout << "No added CSs\n";
    }
    else {
        cout << "Name: " << c.CS_name << "\n";
        cout << "Count workshops: " << c.count_workshops << "\n";
        cout << "Active workshops: " << c.active_workskops << "\n";
        cout << "Class: " << c.CS_class << "\n";
    }
}

void edit_pipe(Pipe&p) {
    if (p.Pipe_name == "") {
        cout << "No added pipes\n";
        return;
    }
    cout << "You may change pipe status(P - passive, A - active)\n";
    cout << "Status: " << p.status << "\n";
    cin >> p.status;
    while (p.status != 'P' && p.status != 'A') {
        cout << "status of pipe must be 'P' or 'A'\n";
        cin >> p.status;
    }
}

void edit_CS(CS&c) {
    if (c.CS_name == "") {
        cout << "No added CS\n";
        return;
    }
    cout << "You may change count of active workshops\n";
    cout << "Active workshops: " << c.active_workskops << "\n";
    cin >> c.active_workskops;
    while ((c.active_workskops > c.count_workshops) || cin.fail()) {
        if (cin.fail()) {
            check();
            cout << "error\n";
            cin >> c.active_workskops;
        }
        else {
            cout << "total active workshops must be < count of workshops\n";
            cin >> c.active_workskops;
        }
    }
}

void save(Pipe& p, CS& c) {
    ofstream out("save.txt");
    if (!out.is_open()) {
        cout << "error\n";
        return;
    }
    if (p.Pipe_name != "") {
        out << "PIPE ->\n";
        out << p.Pipe_name << "\n";
        out << p.diametr << "\n";
        out << p.lenght << "\n";
        out << p.status << "\n";
    }
    if (c.CS_name != "") {
        out << "CS ->\n";
        out << c.CS_name << "\n";
        out << c.count_workshops << "\n";
        out << c.active_workskops << "\n";
        out << c.CS_class << "\n";
    }
    out.close();
    cout << "data was saving\n";
}

void download(Pipe& p, CS& c) {
    ifstream in("save.txt");
    if (!in.is_open()) {
        cout << "error\n";
        return;
    }
    string m;
    while (getline(in, m)) {
        if (m == "PIPE ->") {
            getline(in, p.Pipe_name);
            in >> p.diametr;
            in >> p.lenght;
            in >> p.status;
            in.ignore();
        }
        else if (m == "CS ->") {
            getline(in, c.CS_name);
            in >> c.count_workshops;
            in >> c.active_workskops;
            in >> c.CS_class;
            in.ignore();
        }
    }
    in.close();
    cout << "data was downloading\n";
}

int main() {
    Pipe p;
    CS c;
    while (true) {
        string w;
        cout << "press w for begin work\n";
        cin >> w;
        if (w == "w") {
            while (true) {
                zapusk();
                int user;
                cin >> user;
                while (cin.fail()) {
                    check();
                    cout << "error\n";
                    cin >> user;
                }
                switch (user) {
                case 1: add_pipe(p); break;
                case 2: add_CS(c); break;
                case 3: view_objects(p,c); break;
                case 4: edit_pipe(p); break;
                case 5: edit_CS(c); break;
                case 6: save(p,c); break;
                case 7: download(p,c); break;
                case 0:
                    cout << "work is over\n";
                    return 0;
                default:
                    cout << "Invalid command, try again\n";
                }
            }
        }
        else {
            cout << "Invalid key, press w to start\n";
        }
    }
}
