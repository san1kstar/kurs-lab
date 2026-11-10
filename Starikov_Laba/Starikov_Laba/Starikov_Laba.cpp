#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include <format>
#include <unordered_map>
#include "Checks.h"
#include "Pipe.h"
#include "CS.h"

using namespace std;

void launching() {
    cout << "\nMENU\n";
    cout << "1 - Add pipe\n";
    cout << "2 - Add CS\n";
    cout << "3 - View all objects\n";
    cout << "4 - Find & Manage\n";
    cout << "5 - Save to file\n";
    cout << "6 - Load from file\n";
    cout << "0 - Exit\n";
}

void AddPipe(unordered_map<int, Pipe>& pipes) {
    Pipe p;
    cin >> p;
    pipes.emplace(p.GetID(), p);
    cout << "Pipe added with ID: " << p.GetID() << "\n";
}

void AddCS(unordered_map<int, CS>& css) {
    CS c;
    cin >> c;
    css.emplace(c.GetID(), c);
    cout << "CS added with ID: " << c.GetID() << "\n";
}

void view(unordered_map<int, Pipe>& pipes, unordered_map<int, CS>& css) {
    cout << "\nPIPES\n";
    if (pipes.empty()) {
        cout << "No pipes.\n";
    }
    else {
        for (auto& pair : pipes) {
            cout << pair.second;
        }
    }

    cout << "\nCS\n";
    if (css.empty()) {
        cout << "No CS.\n";
    }
    else {
        for (auto& pair : css) {
            cout << pair.second;
        }
    }
}

void editPipe(unordered_map<int, Pipe>& pipes, int id) {
    int s = inputInt(cin, "Enter new status (1 - working, 0 - broken): ", 0, 1);
    bool new_status = (s == 1);

    if (pipes.find(id) != pipes.end()) {
        pipes[id].SetWorking(new_status);
        cout << "Pipe #" << id << " updated.\n";
    }
    else {
        cout << "Pipe #" << id << " not found.\n";
    }
}

void deletePipe(unordered_map<int, Pipe>& pipes, int id) {
    if (pipes.erase(id)) {
        cout << "Pipe #" << id << " deleted.\n";
    }
    else {
        cout << "Pipe #" << id << " not found.\n";
    }
}

void editCS(unordered_map<int, CS>& css, int id) {
    int new_active = inputInt(cin, "Enter new active count: ", 0, 10000);

    if (css.find(id) != css.end()) {
        if (new_active <= css[id].GetWorkshops()) {
            css[id].SetActive(new_active);
            cout << "CS #" << id << " updated.\n";
        }
        else {
            cout << "Error: active > total for CS #" << id << "\n";
        }
    }
    else {
        cout << "CS #" << id << " not found.\n";
    }
}

void deleteCS(unordered_map<int, CS>& css, int id) {
    if (css.erase(id)) {
        cout << "CS #" << id << " deleted.\n";
    }
    else {
        cout << "CS #" << id << " not found.\n";
    }
}

vector<int> SearchPipesByID(unordered_map<int, Pipe>& pipes) {
    int id = inputInt(cin, "Enter Pipe ID: ", 1, Pipe::GetMaxID());
    vector<int> res;
    if (pipes.find(id) != pipes.end()) {
        res.push_back(id);
    }
    return res;
}

vector<int> SearchPipesByName(unordered_map<int, Pipe>& pipes) {
    string name = inputName(cin, "Enter name (substring): ");
    vector<int> res;
    for (const auto& [id, p] : pipes) {
        if (p.GetName().find(name) != string::npos) {
            res.push_back(id);
        }
    }
    return res;
}

vector<int> SearchPipesByStatus(unordered_map<int, Pipe>& pipes) {
    int st = inputInt(cin, "Enter status (1 - working, 0 - broken): ", 0, 1);
    bool target_status = (st == 1);
    vector<int> res;
    for (const auto& [id, p] : pipes) {
        if (p.IsWorking() == target_status) {
            res.push_back(id);
        }
    }
    return res;
}

vector<int> SearchCSSByID(unordered_map<int, CS>& css) {
    int id = inputInt(cin, "Enter CS ID: ", 1, CS::GetMaxID());
    vector<int> res;
    if (css.find(id) != css.end()) {
        res.push_back(id);
    }
    return res;
}

vector<int> SearchCSSByName(unordered_map<int, CS>& css) {
    string name = inputName(cin, "Enter name (substring): ");
    vector<int> res;
    for (const auto& [id, c] : css) {
        if (c.GetName().find(name) != string::npos) {
            res.push_back(id);
        }
    }
    return res;
}

vector<int> SearchCSSByPercent(unordered_map<int, CS>& css) {
    int percent = inputInt(cin, "Enter min unused percent (0-100): ", 0, 100);
    vector<int> res;
    for (const auto& [id, c] : css) {
        if (c.GetUnusedPercent() >= percent) {
            res.push_back(id);
        }
    }
    return res;
}

void manage_pipes(unordered_map<int, Pipe>& pipes, vector<int>& found_ids) {
    cout << "Found: " << found_ids.size() << "\n";
    for (int id : found_ids) {
        cout << id << " ";
    }
    cout << "\n";

    int pick = inputInt(cin, "1 - Apply to ALL, 2 - Choose ID: ", 1, 2);
    vector<int> targets;

    if (pick == 1) {
        targets = found_ids;
    }
    else {
        targets.push_back(inputInt(cin, "Enter ID: ", 1, Pipe::GetMaxID()));
    }

    int action = inputInt(cin, "1 - Edit status, 2 - Delete: ", 1, 2);

    for (int id : targets) {
        if (action == 1) {
            editPipe(pipes, id);
        }
        else {
            deletePipe(pipes, id);
        }
    }
}

void manage_css(unordered_map<int, CS>& css, vector<int>& found_ids) {
    cout << "Found: " << found_ids.size() << "\n";
    for (int id : found_ids) {
        cout << id << " ";
    }
    cout << "\n";

    int pick = inputInt(cin, "1 - Apply to ALL, 2 - Choose ID: ", 1, 2);
    vector<int> targets;

    if (pick == 1) {
        targets = found_ids;
    }
    else {
        targets.push_back(inputInt(cin, "Enter ID: ", 1, CS::GetMaxID()));
    }

    int action = inputInt(cin, "1 - Edit active, 2 - Delete: ", 1, 2);

    for (int id : targets) {
        if (action == 1) {
            editCS(css, id);
        }
        else {
            deleteCS(css, id);
        }
    }
}

void SearchAndManage(unordered_map<int, Pipe>& pipes, unordered_map<int, CS>& css) {
    int type = inputInt(cin, "1 - Pipe, 2 - CS: ", 1, 2);
    int mode = inputInt(cin, "1 - ID, 2 - Name, 3 - Filter: ", 1, 3);

    vector<int> found;

    if (type == 1) {
        if (mode == 1) {
            found = SearchPipesByID(pipes);
        }
        else if (mode == 2) {
            found = SearchPipesByName(pipes);
        }
        else if (mode == 3) {
            found = SearchPipesByStatus(pipes);
        }

        if (found.empty()) {
            cout << "Nothing found.\n";
            return;
        }
        manage_pipes(pipes, found);
    }
    else {
        if (mode == 1) {
            found = SearchCSSByID(css);
        }
        else if (mode == 2) {
            found = SearchCSSByName(css);
        }
        else if (mode == 3) {
            found = SearchCSSByPercent(css);
        }

        if (found.empty()) {
            cout << "Nothing found.\n";
            return;
        }
        manage_css(css, found);
    }
}


void saveToFile(const unordered_map<int, Pipe>& pipes, const unordered_map<int, CS>& css) {
    string filename = inputFileName(cin, "Enter filename to save: ");
    ofstream fout(filename);
    if (!fout.is_open()) {
        cout << "Error opening file.\n";
        return;
    }
    for (const auto& [id, p] : pipes) {
        fout << p;
    }
    for (const auto& [id, c] : css) {
        fout << c;
    }
    cout << "Saved.\n";
}

void loadFromFile(unordered_map<int, Pipe>& pipes, unordered_map<int, CS>& css) {
    string filename = inputFileName(cin, "Enter filename to load: ");
    ifstream fin(filename);
    if (!fin.is_open()) {
        cout << "Error opening file.\n";
        return;
    }

    pipes.clear();
    css.clear();

    int max_p = 0;
    int max_c = 0;
    string marker;

    while (getline(fin, marker)) {
        if (marker == "P") {
            string line;
            getline(fin, line);
            int id = stoi(line);

            Pipe p(id);
            fin >> p;

            pipes.emplace(id, p);

            if (id > max_p) {
                max_p = id;
            }
        }
        else if (marker == "C") {
            string line;
            getline(fin, line);
            int id = stoi(line);

            CS c(id);
            fin >> c;

            css.emplace(id, c);

            if (id > max_c) {
                max_c = id;
            }
        }
    }

    Pipe::SetMaxID(max_p);
    CS::SetMaxID(max_c);

    fin.close();
    cout << "Loaded.\n";
}

int main() {
    redirect_output_wrapper cerr_out(cerr);
    string timestamp = std::format("{:%d_%m_%Y %H_%M_%OS}", chrono::system_clock::now());
    ofstream logfile("log_" + timestamp + ".txt");
    if (logfile) {
        cerr_out.redirect(logfile);
    }

    unordered_map<int, Pipe> pipes;
    unordered_map<int, CS> css;

    while (true) {
        launching();

        int choice = inputInt(cin, "Your choice: ", 0, 6);

        switch (choice) {
        case 0:
            return 0;
        case 1:
            AddPipe(pipes);
            break;
        case 2:
            AddCS(css);
            break;
        case 3:
            view(pipes, css);
            break;
        case 4:
            SearchAndManage(pipes, css);
            break;
        case 5:
            saveToFile(pipes, css);
            break;
        case 6:
            loadFromFile(pipes, css);
            break;
        }
    }
}