// Starikov_Laba.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

struct Pipe {
    string Pipe_name;
    double lenght;
    float diametr;
    char status;
};

struct CS {
    string CS_name;
    int count_workshops;
    int active_workskops;
    char CS_class;
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

void add_pipe() {
    Pipe p;
    cout << "Give a name to the pipe.\n";
    cin >> p.Pipe_name;
    cout << "Enter the pipe diameter.\n";
    cin >> p.diametr;
    while (p.diametr <= 0) {
        cout << "ERROR: diametr must be positive! Enter again\n";
        cin >> p.diametr;
    }
    cout << "Enter the length of the pipe.\n";
    cin >> p.lenght;
    while (p.lenght <= 0) {
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
    cout << "You add a new pipe!\n\n";
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
cin >> c.CS_name;
cout << "Enter the count of workshops in CS\n";
cin >> c.count_workshops;
while (c.count_workshops <= 0) {
    cout << "ERROR: count of workshops must be positive\n";
    cin >> c.count_workshops;
}
cout << "Enter the count of active workshops in CS\n";
cin >> c.active_workskops;
while (c.active_workskops < 0 || c.active_workskops > c.count_workshops) {
    if (c.active_workskops < 0) {
        cout << "ERROR: count of active workshops must be > 0\n";
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
    cout << "\nWhat do you want to edit?\n";
    cout << "1 - Name\n";
    cout << "2 - Diameter\n";
    cout << "3 - Length\n";
    cout << "4 - Status\n";
    cout << "0 - Cancel\n";
    int f;
    cin >> f;
    if (f == 0) {
        return;
    }
    else if (f == 1) {
        cout << "new name\n";
        cin >> pipes[0].Pipe_name;
    }
    else if (f == 2) {
        cout << "new diametr\n";
        cin >> pipes[0].diametr;
        while (pipes[0].diametr <= 0) {
            cout << "ERROR: diametr must be positive! Enter again\n";
            cin >> pipes[0].diametr;
        }
    }
    else if (f == 3) {
        cout << "new lenght\n";
        cin >> pipes[0].lenght;
        while (pipes[0].lenght <= 0) {
            cout << "ERROR: lenght must be positive! Enter again\n";
            cin >> pipes[0].lenght;
        }
    }
    else if (f == 4) {
        cout << "new status (P - passive, A - active)\n";
        cin >> pipes[0].status;
        while (pipes[0].status != 'P' && pipes[0].status != 'A') {
            cout << "status of pipe must be 'P' or 'A'\n";
            cin >> pipes[0].status;
        }
    }
    else {
        cout << "error\n";
    }
}

void edit_CS() {
    if (css.empty()) {
        cout << "No added CS\n";
        return;
    }
    cout << "\nWhat do you want to edit?\n";
    cout << "1 - Name\n";
    cout << "2 - count workshops\n";
    cout << "3 - active workshops\n";
    cout << "4 - Class\n";
    cout << "0 - Cancel\n";
    int f;
    cin >> f;
    if (f == 0) {
        return;
    }
    else if (f == 1) {
        cout << "new name\n";
        cin >> css[0].CS_name;
    }
    else if (f == 2) {
        cout << "new count workshops\n";
        cin >> css[0].count_workshops;
        while (css[0].count_workshops <= 0) {
            cout << "error\n";
            cin >> css[0].count_workshops;
        }
    }
    else if (f == 3) {
        cout << "new count active workshops\n";
        cin >> css[0].active_workskops;
        while (css[0].active_workskops > css[0].count_workshops || css[0].active_workskops < 0) {
            if (css[0].active_workskops < 0) {
                cout << "error\n";
                cin >> css[0].active_workskops;
            }
            else {
                cout << "error\n";
                cin >> css[0].active_workskops;
            }
        }
    }
    else if (f == 4) {
        cout << "new class\n";
        cin >> css[0].CS_class;
        while (css[0].CS_class != 'A' && css[0].CS_class != 'B' && css[0].CS_class != 'C' && css[0].CS_class != 'D') {
            cout << "error (A,B,C,D)\n";
            cin >> css[0].CS_class;
        }
    }
    else {
        cout << "error\n";
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
    if (in >> p.Pipe_name >> p.diametr >> p.lenght >> p.status) {
        pipes.push_back(p);
    }

    CS c;
    if (in >> c.CS_name >> c.count_workshops >> c.active_workskops >> c.CS_class) {
        css.push_back(c);
    }
    in.close();
    cout << "data was downloading\n";
}

int main()
{
    while (true) {
        string w;
        cout << "press 'w' for begin work\n";
        cin >> w;
        if (w == "w") {
            while (true) {
                zapusk();
                int user;
                cin >> user;

                if (user == 1) {
                    add_pipe();
                }

                else if (user == 2) {
                    add_CS();
                }

                else if (user == 3) {
                    view_objects();
                }

                else if (user == 4) {
                    edit_pipe();
                }

                else if (user == 5) {
                    edit_CS();
                }

                else if (user == 6) {
                    save();
                }

                else if (user == 7) {
                    download();
                }

                else if (user == 0) {
                    cout << "Work is over.\n";
                    return 0;
                }

                else {
                    cout << "Invalid command, try again\n";
                }
            }
        }
        else {
            cout << "Invalid key. Press 'w' to continue.\n";
        }
    }
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
