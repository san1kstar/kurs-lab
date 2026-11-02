#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <format>
#include <vector>
#include <unordered_map>
#include "Checks.h"
#include "Pipe.h"
#include "CS.h"

using namespace std;

void launching() {
    cout << "\nApp menu:\n";
    cout << "1 - Add pipe\n";
    cout << "2 - Add Compression station\n";
    cout << "3 - View all items\n";
    cout << "4 - Find object\n";
    cout << "5 - Save to file\n";
    cout << "6 - Download from file\n";
    cout << "0 - Exit\n";
}

void view_pipe(unordered_map<int, Pipe>& pipes) {
    cout << "\nPIPES\n";
    if (pipes.empty()) {
        cout << "No added pipes.\n";
    }
    else {
        for (auto& pair : pipes) {
            cout << pair.second;
        }
    }
}

void view_cs(unordered_map<int, CS>& css) {
    cout << "\nCS\n";
    if (css.empty()) {
        cout << "No added CS.\n";
    }
    else {
        for (auto& pair : css) {
            cout << pair.second;
        }
    }
}

void viewAll(unordered_map<int, Pipe>& pipes, unordered_map<int, CS>& css) {
    view_pipe(pipes);
    view_cs(css);
}

void AddPipe(unordered_map<int, Pipe>& pipes) {
    Pipe p;
    cin >> p;
    int id = p.GetID();
    pipes.emplace(id, p);
    cout << "Pipe added with ID: " << id << "\n";
}

void AddCS(unordered_map<int, CS>& css) {
    CS c;
    cin >> c;
    int id = c.GetID();
    css.emplace(id, c);
    cout << "CS added with ID: " << id << "\n";
}

int chooseTargets(int found_count) {
    cout << "1 - Apply to ALL found\n";
    cout << "2 - Choose specific ID\n";
    return inputInt(cin, "Your choice: ", 1, 2);
}

bool find_pipes(unordered_map<int, Pipe>& pipes, int mode, int id, string name, char status, vector<int>& found_ids) {
    found_ids.clear();
    cout << "Found Pipes: ";
    for (auto& pair : pipes) {
        bool match = false;
        switch (mode) {
        case 1: match = (pair.second.GetID() == id); break;
        case 2: match = (pair.second.name.find(name) != string::npos); break;
        case 3: match = (pair.second.status == status); break;
        }
        if (match) {
            cout << pair.second.GetID() << " ";
            found_ids.push_back(pair.second.GetID());
        }
    }
    cout << endl;
    return !found_ids.empty();
}

bool find_css(unordered_map<int, CS>& css, int mode, int id, string name, int percent, vector<int>& found_ids) {
    found_ids.clear();
    cout << "Found CS: ";
    for (auto& pair : css) {
        bool match = false;
        switch (mode) {
        case 1: match = (pair.second.GetID() == id); break;
        case 2: match = (pair.second.name.find(name) != string::npos); break;
        case 3: match = (pair.second.GetUnusedPercent() >= percent); break;
        }
        if (match) {
            cout << pair.second.GetID() << " ";
            found_ids.push_back(pair.second.GetID());
        }
    }
    cout << endl;
    return !found_ids.empty();
}

void manage_pipes(unordered_map<int, Pipe>& pipes, vector<int>& found_ids) {
    int pick = chooseTargets(found_ids.size());
    vector<int> targets;

    if (pick == 1) {
        targets = found_ids;
    }
    else {
        int id = inputInt(cin, "Enter ID: ", 1, Pipe::MaxID);
        targets.push_back(id);
    }

    cout << "1 - Edit status\n";
    cout << "2 - Delete\n";
    int action = inputInt(cin, "Your choice: ", 1, 2);

    if (action == 1) {
        char new_status = inputChar(cin, "Enter new status (P - passive, A - active): ", 'A', 'P');
        for (int id : targets) {
            if (pipes.find(id) != pipes.end()) {
                pipes[id].status = new_status;
                cout << "Pipe #" << id << " updated (status -> " << new_status << ").\n";
            }
            else {
                cout << "Pipe #" << id << " not found.\n";
            }
        }
    }
    else {
        for (int id : targets) {
            if (pipes.erase(id)) {
                cout << "Pipe #" << id << " deleted.\n";
            }
            else {
                cout << "Pipe #" << id << " not found.\n";
            }
        }
    }
}

void manage_css(unordered_map<int, CS>& css, vector<int>& found_ids) {
    int pick = chooseTargets(found_ids.size());
    vector<int> targets;

    if (pick == 1) {
        targets = found_ids;
    }
    else {
        int id = inputInt(cin, "Enter ID: ", 1, CS::MaxID);
        targets.push_back(id);
    }

    cout << "1 - Edit active workshops\n";
    cout << "2 - Delete\n";
    int action = inputInt(cin, "Your choice: ", 1, 2);

    if (action == 1) {
        int new_active = inputInt(cin, "Enter new active workshops count: ", 0, 1000);
        for (int id : targets) {
            if (css.find(id) != css.end()) {
                if (new_active <= css[id].count_workshops) {
                    css[id].active_workshops = new_active;
                    cout << "CS #" << id << " updated (active -> " << new_active << ").\n";
                }
                else {
                    cout << "Error: new active > total workshops for CS #" << id << "\n";
                }
            }
            else {
                cout << "CS #" << id << " not found.\n";
            }
        }
    }
    else {
        for (int id : targets) {
            if (css.erase(id)) {
                cout << "CS #" << id << " deleted.\n";
            }
            else {
                cout << "CS #" << id << " not found.\n";
            }
        }
    }
}

void SearchAndManage(unordered_map<int, Pipe>& pipes, unordered_map<int, CS>& css) {
    cout << "\nSEARCH\n";
    cout << "What to search?\n1. Pipe\n2. CS\n";
    int type = inputInt(cin, "Your choice: ", 1, 2);

    int search_mode = 0;
    int search_id = -1;
    string search_name = "";
    char search_status = ' ';
    int search_percent = -1;
    vector<int> found_ids;

    if (type == 1) {
        cout << "Search by:\n1. ID\n2. Name\n3. Status 'P'\n";
        search_mode = inputInt(cin, "Your choice: ", 1, 3);
        switch (search_mode) {
        case 1: search_id = inputInt(cin, "Enter ID: ", 1, Pipe::MaxID); break;
        case 2: search_name = inputName(cin, "Enter name: "); break;
        case 3: search_status = inputChar(cin, "Enter status (P/A): ", 'A', 'P'); break;
        }
        if (!find_pipes(pipes, search_mode, search_id, search_name, search_status, found_ids)) {
            cout << "No objects found.\n";
            return;
        }
        manage_pipes(pipes, found_ids);
    }
    else {
        cout << "Search by:\n1. ID\n2. Name)\n3. Unused percent >= X%\n";
        search_mode = inputInt(cin, "Your choice: ", 1, 3);
        switch (search_mode) {
        case 1: search_id = inputInt(cin, "Enter ID: ", 1, CS::MaxID); break;
        case 2: search_name = inputName(cin, "Enter name: "); break;
        case 3: search_percent = inputInt(cin, "Enter min unused percent: ", 0, 100); break;
        }
        if (!find_css(css, search_mode, search_id, search_name, search_percent, found_ids)) {
            cout << "No objects found.\n";
            return;
        }
        manage_css(css, found_ids);
    }
}

void save_pipe(ofstream& fout, const unordered_map<int, Pipe>& pipes) {
    fout << "PIPES" << endl;
    fout << pipes.size() << endl;
    for (const auto& [id, p] : pipes) {
        fout << p.GetID() << endl << p.name << endl
            << p.length << endl << p.diameter << endl << p.status << endl;
    }
}

void save_cs(ofstream& fout, const unordered_map<int, CS>& css) {
    fout << "CS" << endl;
    fout << css.size() << endl;
    for (const auto& [id, c] : css) {
        fout << c.GetID() << endl << c.name << endl
            << c.count_workshops << endl << c.active_workshops << endl << c.cs_class << endl;
    }
}

void saveToFile(const unordered_map<int, Pipe>& pipes, const unordered_map<int, CS>& css) {
    string filename = inputFileName(cin, "Enter the file name to save to: ");
    ofstream fout(filename);
    if (!fout.is_open()) {
        cout << "Error: could not open file " << filename << "\n";
        return;
    }
    save_pipe(fout, pipes);
    save_cs(fout, css);
    fout.close();
    cout << "Writing to the file " << filename << " is complete.\n";
}

int load_pipe(ifstream& fin, unordered_map<int, Pipe>& pipes) {
    int max_id = 0;
    int count;
    fin >> count;
    fin.ignore();
    for (int i = 0; i < count; i++) {
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
    int count;
    fin >> count;
    fin.ignore();
    for (int i = 0; i < count; i++) {
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

void loadFromFile(unordered_map<int, Pipe>& pipes, unordered_map<int, CS>& css) {
    string filename = inputFileName(cin, "Enter the file name to load from: ");
    ifstream fin(filename);
    if (!fin.is_open()) {
        cout << "Error: could not open file " << filename << "\n";
        return;
    }
    pipes.clear();
    css.clear();
    int max_pipe_id = 0, max_cs_id = 0;
    string marker;
    while (getline(fin, marker)) {
        if (marker == "PIPES") max_pipe_id = load_pipe(fin, pipes);
        else if (marker == "CS") max_cs_id = load_cs(fin, css);
    }
    if (max_pipe_id > 0) Pipe::SetMaxID(max_pipe_id);
    if (max_cs_id > 0) CS::SetMaxID(max_cs_id);
    fin.close();
    cout << "Reading from the file " << filename << " is complete.\n";
}

int main() {
    redirect_output_wrapper cerr_out(cerr);
    string timestamp = std::format("{:%d_%m_%Y %H_%M_%OS}", chrono::system_clock::now());
    ofstream logfile("log_" + timestamp + ".txt");
    if (logfile)
        cerr_out.redirect(logfile);

    unordered_map<int, Pipe> pipes;
    unordered_map<int, CS> css;

    while (true) {
        launching();
        int choice = inputInt(cin, "Enter a number to execute a command: ", 0, 6);
        switch (choice) {
        case 0: return 0;
        case 1: AddPipe(pipes); break;
        case 2: AddCS(css); break;
        case 3: viewAll(pipes, css); break;
        case 4: SearchAndManage(pipes, css); break;
        case 5: saveToFile(pipes, css); break;
        case 6: loadFromFile(pipes, css); break;
        }
    }
}