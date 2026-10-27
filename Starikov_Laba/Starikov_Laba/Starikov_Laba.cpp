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

void view_pipe(unordered_map<int, Pipe>& pipes) {
    cout << "\nYOUR PIPES" << endl;
    if (pipes.empty()) {
        cout << "No added pipes." << endl;
    }
    else {
        for (auto& pair : pipes) {
            cout << "\nID: " << pair.second.GetID() << "\n";
            cout << "Name: " << pair.second.name << "\n";
            cout << "Length: " << pair.second.length << "\n";
            cout << "Diameter: " << pair.second.diameter << "\n";
            cout << "Status: " << pair.second.status << "\n";
        }
    }
}

void view_cs(unordered_map<int, CS>& css) {
    cout << "\nYOUR CS" << endl;
    if (css.empty()) {
        cout << "No added CS." << endl;
    }
    else {
        for (auto& pair : css) {
            cout << "\nID: " << pair.second.GetID() << "\n";
            cout << "Name: " << pair.second.name << "\n";
            cout << "Count workshops: " << pair.second.count_workshops << "\n";
            cout << "Active workshops: " << pair.second.active_workshops << "\n";
            cout << "Class: " << pair.second.cs_class << "\n";
        }
    }
}

void view(unordered_map<int, Pipe>& pipes, unordered_map<int, CS>& css) {
    cout << "your object:\n";
    view_pipe(pipes);
    view_cs(css);
}

void AddPipe(unordered_map<int, Pipe>& pipes) {
    Pipe p;
    cin >> p;
    pipes.insert(make_pair(p.GetID(), p));
    cout << "Pipe added with ID: " << p.GetID() << endl;
}

void AddCS(unordered_map<int, CS>& css) {
    CS c;
    cin >> c;
    css.insert(make_pair(c.GetID(), c));
    cout << "CS added with ID: " << c.GetID() << endl;
}

void save_pipe(ofstream& fout,const unordered_map<int, Pipe>& pipes) {
    fout << "PIPES" << endl;
    fout << pipes.size() << endl;
    for (auto& pair : pipes) {
        const Pipe& p = pair.second;
        fout << p.GetID() << endl
            << p.name << endl
            << p.length << endl
            << p.diameter << endl
            << p.status << endl;
    }
}

void save_cs(ofstream& fout,const unordered_map<int, CS>& css) {
    fout << "CS" << endl;
    fout <<css.size()<< endl;
    for (auto& pair : css) {
        const CS& c = pair.second;
        fout << c.GetID() << endl
            << c.name << endl
            << c.count_workshops << endl
            << c.active_workshops << endl
            << c.cs_class << endl;
    }
}

void save(unordered_map<int, Pipe>& pipes, unordered_map<int, CS>& css) {
    string filename;
    cout << "Enter filename to save: ";
    filename = line_with_space();

    ofstream fout(filename);
    if (!fout.is_open()) {
        cout << "Error opening file!\n";
        return;
    }

    save_pipe(fout, pipes);
    save_cs(fout, css);

    fout.close();
    cout << "Saved successfully!\n";
}

int load_pipe(ifstream& fin, unordered_map<int, Pipe>& pipes) {
    int max_id = 0;
    int pipe_count;
    fin >> pipe_count;
    fin.ignore();

    for (int i = 0; i < pipe_count; i++) {
        Pipe p;
        int tmp_id;
        fin >> tmp_id;
        fin.ignore();
        getline(fin, p.name);
        fin >> p.length >> p.diameter >> p.status;
        fin.ignore();

        pipes.insert(make_pair(tmp_id, p));
        if (tmp_id > max_id) max_id = tmp_id;
    }
    return max_id;
}

int load_cs(ifstream& fin, unordered_map<int, CS>& css) {
    int max_id = 0;
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

        css.insert(make_pair(tmp_id, c));
        if (tmp_id > max_id) max_id = tmp_id;
    }
    return max_id;
}

void load(unordered_map<int, Pipe>& pipes, unordered_map<int, CS>& css) {
    string filename;
    cout << "Enter filename to load: ";
    filename = line_with_space();

    ifstream fin(filename);
    if (!fin.is_open()) {
        cout << "Error opening file!\n";
        return;
    }

    pipes.clear();
    css.clear();

    int max_pipe_id = 0;
    int max_cs_id = 0;
    string marker;

    while (getline(fin, marker)) {
        if (marker == "PIPES") {
            max_pipe_id = load_pipe(fin, pipes);
        }
        else if (marker == "CS") {
            max_cs_id = load_cs(fin, css);
        }
    }

    if (max_pipe_id > 0) Pipe::SetMaxID(max_pipe_id);
    if (max_cs_id > 0) CS::SetMaxID(max_cs_id);

    fin.close();
    cout << "Loaded successfully!\n";
}

bool find_pipes(unordered_map<int, Pipe>& pipes, int mode, int id, string name, char status) {
    bool found = false;
    cout << "Found Pipes: ";
    for (auto& pair : pipes) {
        Pipe& p = pair.second;
        bool match = false;
        switch (mode) {
        case 1: match = (p.GetID() == id); break;
        case 2: match = (p.name.find(name) != string::npos); break; // Поиск по подстроке
        case 3: match = (p.status == status); break;
        }
        if (match) {
            cout << p.GetID() << " ";
            found = true;
        }
    }
    cout << endl;
    return found;
}

// Поиск КС
bool find_css(unordered_map<int, CS>& css, int mode, int id, string name, int percent) {
    bool found = false;
    cout << "Found CS: ";
    for (auto& pair : css) {
        CS& c = pair.second;
        bool match = false;
        switch (mode) {
        case 1: match = (c.GetID() == id); break;
        case 2: match = (c.name.find(name) != string::npos); break; // Поиск по подстроке
        case 3: match = (c.GetUnusedPercent() >= percent); break;
        }
        if (match) {
            cout << c.GetID() << " ";
            found = true;
        }
    }
    cout << endl;
    return found;
}

void manage_pipes(unordered_map<int, Pipe>& pipes, int mode, int id, string name, char status, int action) {
    char new_status = ' ';
    if (action == 1) {
        cout << "Enter NEW status for ALL found pipes ('P' or 'A'): ";
        cin >> new_status;
        while (new_status != 'P' && new_status != 'A') {
            check();
            cout << "Status must be 'P' or 'A'. Enter again: ";
            cin >> new_status;
        }
    }

    for (auto& pair : pipes) {
        Pipe& p = pair.second;
        bool match = false;
        switch (mode) {
        case 1: match = (p.GetID() == id); break;
        case 2: match = (p.name.find(name) != string::npos); break;
        case 3: match = (p.status == status); break;
        }

        if (match) {
            switch (action) {
            case 1:
                p.status = new_status;
                cout << "Pipe #" << p.GetID() << " updated (status -> " << new_status << ").\n";
                break;
            case 2:
                pipes.erase(p.GetID());
                cout << "Pipe #" << p.GetID() << " deleted.\n";
                break;
            }
        }
    }
}

void manage_css(unordered_map<int, CS>& css, int mode, int id, string name, int percent, int action) {
    int new_active = -1;
    if (action == 1) {
        cout << "Enter NEW active workshops count for ALL found CS: ";
        cin >> new_active;
        while (cin.fail() || new_active < 0) {
            check();
            cout << "Count must be >= 0. Enter again: ";
            cin >> new_active;
        }
    }

    for (auto& pair : css) {
        CS& c = pair.second;
        bool match = false;
        switch (mode) {
        case 1: match = (c.GetID() == id); break;
        case 2: match = (c.name.find(name) != string::npos); break;
        case 3: match = (c.GetUnusedPercent() >= percent); break;
        }

        if (match) {
            switch (action) {
            case 1:
                if (new_active <= c.count_workshops) {
                    c.active_workshops = new_active;
                    cout << "CS #" << c.GetID() << " updated (active -> " << new_active << ").\n";
                }
                else {
                    cout << "Error: new active > total workshops for CS #" << c.GetID() << "\n";
                }
                break;
            case 2:
                css.erase(c.GetID());
                cout << "CS #" << c.GetID() << " deleted.\n";
                break;
            }
        }
    }
}

void SearchAndManage(unordered_map<int, Pipe>& pipes, unordered_map<int, CS>& css) {
    cout << "\nSEARCH & MANAGE\n";

    cout << "What to search?\n1. Pipe\n2. CS\nYour choice: ";
    int type;
    cin >> type;
    while (cin.fail() || (type != 1 && type != 2)) {
        check();
        cout << "Enter 1 or 2: ";
        cin >> type;
    }

    int search_mode = 0;
    int search_id = -1;
    string search_name = "";
    char search_status = ' ';
    int search_percent = -1;
    bool found = false;

    if (type == 1) {
        cout << "Search by:\n1. ID\n2. Name (substring)\n3. Status 'P' (в ремонте)\nYour choice: ";
        cin >> search_mode;
        switch (search_mode) {
        case 1: cout << "Enter ID: "; cin >> search_id; break;
        case 2: cout << "Enter name: "; search_name = line_with_space(); break;
        case 3: search_status = 'P'; break;
        default: cout << "Wrong mode!\n"; return;
        }
        found = find_pipes(pipes, search_mode, search_id, search_name, search_status);
    }
    else {
        cout << "Search by:\n1. ID\n2. Name (substring)\n3. Unused percent >= X%\nYour choice: ";
        cin >> search_mode;
        switch (search_mode) {
        case 1: cout << "Enter ID: "; cin >> search_id; break;
        case 2: cout << "Enter name: "; search_name = line_with_space(); break;
        case 3: cout << "Enter min unused percent: "; cin >> search_percent; break;
        default: cout << "Wrong mode!\n"; return;
        }
        found = find_css(css, search_mode, search_id, search_name, search_percent);
    }

    if (!found) {
        cout << "No objects found matching the criteria.\n";
        return;
    }

    cout << "\nWhat to do with found objects?\n";
    cout << "1. Edit ALL found\n";
    cout << "2. Delete ALL found\n";
    cout << "0. Cancel\nYour choice: ";
    int action;
    cin >> action;
    while (cin.fail() || (action < 0 || action > 2)) {
        check();
        cout << "Enter 0, 1 or 2: ";
        cin >> action;
    }

    switch (action) {
    case 0:
        return;
    case 1:
    case 2:
        if (type == 1) {
            manage_pipes(pipes, search_mode, search_id, search_name, search_status, action);
        }
        else {
            manage_css(css, search_mode, search_id, search_name, search_percent, action);
        }
        break;
    default:
        cout << "Wrong action!\n";
        break;
    }
    cout << "Done.\n";
}

void PrintMenu() {
    cout << "\n--- MENU ---\n";
    cout << "1. Add Pipe\n";
    cout << "2. Add CS\n";
    cout << "3. View\n";
    cout << "4. Save\n";
    cout << "5. Load\n";
    cout << "6. Search & Manage\n";
    cout << "0. Exit\n";
    cout << "Choose action: ";
}

int main() {
    unordered_map<int, Pipe> pipes;
    unordered_map<int, CS> css;

    while (true) {
        PrintMenu();
        int action;
        cin >> action;
        while (cin.fail()) {
            check();
            cout << "Enter a number: ";
            cin >> action;
        }

        switch (action) {
        case 1: AddPipe(pipes); break;
        case 2: AddCS(css); break;
        case 3: view(pipes, css); break;
        case 4: save(pipes, css); break;
        case 5: load(pipes, css); break;
        case 6: SearchAndManage(pipes, css); break;
        case 0: return 0;
        default: cout << "Wrong action!\n";
        }
    }
    return 0;
}