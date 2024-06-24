#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

bool isXMLFile(const string &filePath) {
    ifstream file(filePath);
    if (!file.is_open()) return false;
    string line;
    while (getline(file, line)) {
        if (line.find("<?xml") != string::npos) {
            return true;
        }
    }
    return false;
}

bool isJSONFile(const string &filePath) {
    ifstream file(filePath);
    if (!file.is_open()) return false;
    string line;
    while (getline(file, line)) {
        line.erase(remove_if(line.begin(), line.end(), ::isspace), line.end());
        if (!line.empty() && (line[0] == '{' || line[0] == '[')) {
            return true;
        }
    }
    return false;
}

void printSection(const string &section) {
    const int numberOfHashtags = 4 + section.size();
    string hashtags(numberOfHashtags, '#');

    cout << endl;
    cout << hashtags << endl;
    cout << "# "<< section << " #\n";
    cout << hashtags << endl;
    cout << endl;
}