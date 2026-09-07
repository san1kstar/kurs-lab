// Starikov_Laba.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
using namespace std;

struct Pipe {
    string Pipe_name;
    double lenght;
    int diametr;
    bool status;
};

struct CS {
    string CS_name;
    int count_workshops;
    int active_workskops;
    char CS_class;
};

void zapusk() {
    cout << "App menu.\n";
    cout << "Choose a nomber for processing a command.\n";
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
    cout << "Enter the length of the pipe.\n";
    cin >> p.lenght;
    cout << "Enter the pipe status. (0 - passive, 1 - active)\n";
    cin >> p.status;
    cout << "You add a new pipe!\n";
}

void add_CS() {
    CS c;
    cout << "Give a name to the CS\n";
    cin >> c.CS_name;
    cout << "Enter the count of workshops in CS\n";
    cin >> c.count_workshops;
    cout << "Enter the count of active workshops in CS\n";
    cin >> c.active_workskops;
    cout << "Give a class to the CS (A, B, C, D)\n";
    cin >> c.CS_class;
    cout << "You add a new CS!\n";
}

int main()
{
    while (true) {
        string w;
        int user;
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
