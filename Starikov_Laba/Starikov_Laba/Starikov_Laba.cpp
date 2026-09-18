// Starikov_Laba.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
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
while (c.active_workskops <= 0 || c.active_workskops > c.count_workshops) {
    if (c.active_workskops <= 0) {
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
        for (size_t i = 0;i < pipes.size(); i++) {
            cout << "Pipe #" << i + 1 << "\n";
            cout << "Name: " << pipes[i].Pipe_name << "\n";
            cout << "Diametr: " << pipes[i].diametr << "\n";
            cout << "Lenght: " << pipes[i].lenght << "\n";
            if (pipes[i].status == 'P') {
                cout << "Status: Passive\n";
            }
            else {
                cout << "Status: Active\n";
            }
        }
    }
    cout << "Your CSs:\n\n";
    if (css.empty()) {
        cout << "No added CSs\n";
    }
    else {
        for (size_t i = 0;i < css.size(); i++) {
            cout << "CS #" << i + 1 << "\n";
            cout << "Name: " << css[i].CS_name << "\n";
            cout << "Count workshops: " << css[i].count_workshops << "\n";
            cout << "Active workshops: " << css[i].active_workskops << "\n";
            cout << "Class: " << css[i].CS_class << "\n";
        }
    }
}

void edit_pipe() {
    if (pipes.empty()) {
        cout << "No added pipes\n";
        return;
    }
    cout << "Avalibale pipes: \n";
    for (int i = 0;i < pipes.size();i++) {
        cout << i + 1 << " - " << pipes[i].Pipe_name << "\n";
    }
    int num;
    cout << "Choose the number of pipe to edit (0 - cancel)\n";
    cin >> num;

    while (num < 0 || num >(int)pipes.size()) {
        cout << "error\n";
        cin >> num;
    }
    if (num == 0) {
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
    int index = num - 1;
    if (f == 0) {
        return;
    }
    else if (f == 1) {
        cout << "new name\n";
        cin >> pipes[index].Pipe_name;
    }
    else {
        cout << "error\n";
    }
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
