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

vector<Pipe> pipes;
vector<CS> css;

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

void add_pipe() {
    Pipe p;
    cout << "Give a name to the pipe.\n";
    p.Pipe_name = line_with_space();
    cout << "Enter the pipe diameter.\n";
    cin >> p.diametr;
    while (p.diametr <= 0 || cin.fail()) {
        check();
        cout << "ERROR: diametr must be positive! Enter again\n";
        cin >> p.diametr;
    }
    cout << "Enter the length of the pipe.\n";
    cin >> p.lenght;
    while (p.lenght <= 0 || cin.fail()) {
        check();
        cout << "ERROR: lenght must be positive! Enter again\n";
        cin >> p.lenght;
    }
    cout << "Enter the pipe status. (P - passive, A - active)\n";
    cin >> p.status;
    while (p.status != 'P' && p.status != 'A') {
        cout << "ERROR: status of pipe must be 'P' or 'A'\n";
        cin >> p.status;
    }
    pipes.push_back(p);
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

void add_CS() {
CS c;
cout << "Give a name to the CS\n";
c.CS_name = line_with_space();
cout << "Enter the count of workshops in CS\n";
cin >> c.count_workshops;
while (c.count_workshops <= 0 || cin.fail()) {
    check();
    cout << "ERROR: count of workshops must be positive\n";
    cin >> c.count_workshops;
}
cout << "Enter the count of active workshops in CS\n";
cin >> c.active_workskops;
while (c.active_workskops < 0 || c.active_workskops > c.count_workshops || cin.fail()) {
    if (c.active_workskops < 0) {
        cout << "ERROR: count of active workshops must be > 0\n";
    }
    else if (cin.fail()) {
        check();
    }
    else {
        cout << "ERROR: total active workshops must be < count of workshops\n";
    }
    cin >> c.active_workskops;
}
cout << "Give a class to the CS (A, B, C, D)\n";
cin >> c.CS_class;
while (c.CS_class != 'A' && c.CS_class != 'B' && c.CS_class != 'C' && c.CS_class != 'D') {
    cout << "ERROR: Class of CS must be 'A', 'B', 'C' or 'D'\n";
    cin >> c.CS_class;
}
css.push_back(c);
cout << "You add a new CS!\n\n";
cout << "CS name: " << c.CS_name << "\n";
cout << "Count workshops: " << c.count_workshops << "\n";
cout << "Count active workshops: " << c.active_workskops << "\n";
cout << "CS class: " << c.CS_class << "\n";
}

void view_objects() {
    cout << "Your pipes:\n\n";
    if (pipes.empty()) {
        cout << "No added pipes\n";
    }
    else {
        cout << "Name: " << pipes[0].Pipe_name << "\n";
        cout << "Diametr: " << pipes[0].diametr << "\n";
        cout << "Lenght: " << pipes[0].lenght << "\n";
        if (pipes[0].status == 'P') {
            cout << "Status: Passive\n";
        }
        else {
            cout << "Status: Active\n";
        }
    }
    cout << "Your CSs:\n\n";
    if (css.empty()) {
        cout << "No added CSs\n";
    }
    else {
        cout << "Name: " << css[0].CS_name << "\n";
        cout << "Count workshops: " << css[0].count_workshops << "\n";
        cout << "Active workshops: " << css[0].active_workskops << "\n";
        cout << "Class: " << css[0].CS_class << "\n";
    }
}

void edit_pipe() {
    if (pipes.empty()) {
        cout << "No added pipes\n";
        return;
    }
    cout << "You may change pipe status(P - passive, A - active)\n";
    cout << "Status: " << pipes[0].status << "\n";
    cin >> pipes[0].status;
    while (pipes[0].status != 'P' && pipes[0].status != 'A') {
        cout << "ERROR: status of pipe must be 'P' or 'A'\n";
        cin >> pipes[0].status;
    }
}

void edit_CS() {
    if (css.empty()) {
        cout << "No added CS\n";
        return;
    }
    cout << "You may change count of active workshops\n";
    cout << "Active workshops: " << css[0].active_workskops << "\n";
    cin >> css[0].active_workskops;
    while ((css[0].active_workskops > css[0].count_workshops) || cin.fail()) {
        if (cin.fail()) {
            check();
            cout << "error\n";
            cin >> css[0].active_workskops;
        }
        else {
            cout << "error\n";
            cin >> css[0].active_workskops;
        }
    }
}

void save() {
    ofstream out("save.txt");
    if (!out.is_open()) {
        cout << "error\n";
        return;
    }
    if (!pipes.empty()) {
        out << pipes[0].Pipe_name << "\n";
        out << pipes[0].diametr << "\n";
        out << pipes[0].lenght << "\n";
        out << pipes[0].status << "\n";
    }
    if (!css.empty()) {
        out << css[0].CS_name << "\n";
        out << css[0].count_workshops << "\n";
        out << css[0].active_workskops << "\n";
        out << css[0].CS_class << "\n";
    }
    out.close();
    cout << "data was saving\n";
}

void download() {
    ifstream in("save.txt");
    if (!in.is_open()) {
        cout << "error\n";
        return;
    }
    pipes.clear();
    css.clear();
    Pipe p;
    if (getline(in, p.Pipe_name)) {
        in >> p.diametr;
        in >> p.lenght;
        in >> p.status;
        in.ignore();
        pipes.push_back(p);
    }

    CS c;
    if (getline(in, c.CS_name)){
        in >> c.count_workshops;
        in >> c.active_workskops;
        in >> c.CS_class;
        in.ignore();
        css.push_back(c);
    }
    in.close();
    cout << "data was downloading\n";
}

int main() {
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
                case 1: add_pipe(); break;
                case 2: add_CS(); break;
                case 3: view_objects(); break;
                case 4: edit_pipe(); break;
                case 5: edit_CS(); break;
                case 6: save(); break;
                case 7: download(); break;
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
