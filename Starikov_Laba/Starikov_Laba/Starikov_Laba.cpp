#include <iostream>
#include <unordered_map>
#include <fstream>
#include "Pipe.h"
#include "CS.h"
using namespace std;

void check() {
    cin.clear();
    cin.ignore(10000, '\n');
}

string line_with_space() {
    string v;
    cin.ignore();
    getline(cin, v);
    return v;
}

// ============ ТРУБЫ ============
void AddPipe(unordered_map<int, Pipe>& pipes) {
    Pipe p;
    cin >> p;
    pipes.insert(make_pair(p.GetID(), p)); // <-- ID берем через геттер
    cout << "Pipe added with ID: " << p.GetID() << endl;
}

void ViewPipes(const unordered_map<int, Pipe>& pipes) {
    if (pipes.empty()) { cout << "No pipes.\n"; return; }
    for (auto& pair : pipes) cout << pair.second << endl;
}

void EditPipe(unordered_map<int, Pipe>& pipes) {
    if (pipes.empty()) { cout << "No pipes.\n"; return; }
    ViewPipes(pipes);
    cout << "Enter Pipe ID to edit: ";
    int id; cin >> id;
    while (cin.fail()) { check(); cout << "Enter a number: "; cin >> id; }

    auto it = pipes.find(id);
    if (it == pipes.end()) { cout << "Pipe not found!\n"; return; }
    cout << "Editing Pipe #" << id << endl;
    cin >> it->second;
}

void DeletePipe(unordered_map<int, Pipe>& pipes) {
    if (pipes.empty()) { cout << "No pipes.\n"; return; }
    ViewPipes(pipes);
    cout << "Enter Pipe ID to delete: ";
    int id; cin >> id;
    while (cin.fail()) { check(); cout << "Enter a number: "; cin >> id; }

    if (pipes.erase(id)) cout << "Pipe #" << id << " deleted.\n";
    else cout << "Pipe not found!\n";
}

// ============ КС ============
void AddCS(unordered_map<int, CS>& css) {
    CS c;
    cin >> c;
    css.insert(make_pair(c.GetID(), c)); // <-- ID берем через геттер
    cout << "CS added with ID: " << c.GetID() << endl;
}

void ViewCS(const unordered_map<int, CS>& css) {
    if (css.empty()) { cout << "No CS.\n"; return; }
    for (auto& pair : css) cout << pair.second << endl;
}

void EditCS(unordered_map<int, CS>& css) {
    if (css.empty()) { cout << "No CS.\n"; return; }
    ViewCS(css);
    cout << "Enter CS ID to edit: ";
    int id; cin >> id;
    while (cin.fail()) { check(); cout << "Enter a number: "; cin >> id; }

    auto it = css.find(id);
    if (it == css.end()) { cout << "CS not found!\n"; return; }
    cout << "Editing CS #" << id << endl;
    cin >> it->second;
}

void DeleteCS(unordered_map<int, CS>& css) {
    if (css.empty()) { cout << "No CS.\n"; return; }
    ViewCS(css);
    cout << "Enter CS ID to delete: ";
    int id; cin >> id;
    while (cin.fail()) { check(); cout << "Enter a number: "; cin >> id; }

    if (css.erase(id)) cout << "CS #" << id << " deleted.\n";
    else cout << "CS not found!\n";
}

// ============ ФАЙЛЫ ============
void SaveToFile(unordered_map<int, Pipe>& pipes,unordered_map<int, CS>& css) {
    string filename;
    cout << "Enter filename to save: ";
    filename = line_with_space();

    ofstream fout(filename);
    if (!fout.is_open()) { cout << "Error opening file!\n"; return; }

    fout << pipes.size() << endl;
    for (auto& pair : pipes) {
        Pipe& p = pair.second;
        fout << p.GetID() << endl << p.name << endl
            << p.length << endl << p.diameter << endl << p.status << endl;
    }

    fout << css.size() << endl;
    for (auto& pair : css) {
        CS& c = pair.second;
        fout << c.GetID() << endl << c.name << endl
            << c.count_workshops << endl << c.active_workshops << endl << c.cs_class << endl;
    }
    fout.close();
    cout << "Saved successfully!\n";
}

void LoadFromFile(unordered_map<int, Pipe>& pipes, unordered_map<int, CS>& css) {
    string filename;
    cout << "Enter filename to load: ";
    filename = line_with_space();

    ifstream fin(filename);
    if (!fin.is_open()) { cout << "Error opening file!\n"; return; }

    pipes.clear();
    css.clear();
    int max_pipe_id = 0;
    int max_cs_id = 0;

    int pipe_count;
    fin >> pipe_count;
    fin.ignore();
    for (int i = 0; i < pipe_count; i++) {
        Pipe p;
        int tmp_id; // Читаем ID во временную переменную (так как id приватный)
        fin >> tmp_id;
        fin.ignore();
        getline(fin, p.name);
        fin >> p.length >> p.diameter >> p.status;
        fin.ignore();

        // При загрузке мы не можем изменить p.id напрямую (он приватный).
        // Поэтому мы вставляем в map по ключу tmp_id.
        pipes[tmp_id] = p;
        if (tmp_id >= max_pipe_id) max_pipe_id = tmp_id + 1;
    }

    int cs_count;
    fin >> cs_count;
    fin.ignore();
    for (int i = 0; i < cs_count; i++) {
        CS c;
        int tmp_id;
        fin >> tmp_id;
        fin.ignore();
        getline(fin, c.name);
        fin >> c.count_workshops >> c.active_workshops >> c.cs_class;
        fin.ignore();
        css[tmp_id] = c;
        if (tmp_id >= max_cs_id) max_cs_id = tmp_id + 1;
    }

    Pipe::SetMaxID(max_pipe_id);
    CS::SetMaxID(max_cs_id);

    fin.close();
    cout << "Loaded successfully!\n";
}

// ============ МЕНЮ ============
void PrintMenu() {
    cout << "\n--- MENU ---\n";
    cout << "1. Add Pipe\n2. Add CS\n3. View\n4. Save\n5. Load\n6. Search & Manage\n0. Exit\nChoose action: ";
}

void SearchAndManage(unordered_map<int, Pipe>& pipes, unordered_map<int, CS>& css) {
    cout << "\n--- SEARCH & MANAGE ---\n";
    cout << "1. Edit Pipe by ID\n2. Delete Pipe by ID\n3. Edit CS by ID\n4. Delete CS by ID\n0. Back\nYour choice: ";
    int choice; cin >> choice;
    while (cin.fail()) { check(); cout << "Enter a number: "; cin >> choice; }
    switch (choice) {
    case 1: EditPipe(pipes); break;
    case 2: DeletePipe(pipes); break;
    case 3: EditCS(css); break;
    case 4: DeleteCS(css); break;
    }
}

int main() {
    unordered_map<int, Pipe> pipes;
    unordered_map<int, CS> css;

    while (true) {
        PrintMenu();
        int action; cin >> action;
        while (cin.fail()) { check(); cout << "Enter a number: "; cin >> action; }

        switch (action) {
        case 1: AddPipe(pipes); break;
        case 2: AddCS(css); break;
        case 3: ViewPipes(pipes); ViewCS(css); break;
        case 4: SaveToFile(pipes, css); break;
        case 5: LoadFromFile(pipes, css); break;
        case 6: SearchAndManage(pipes, css); break;
        case 0: return 0;
        default: cout << "Wrong action!\n";
        }
    }
    return 0;
}