#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>

using namespace std;

bool isNumber(const string& str) {
    if (str.empty()) return false;
    size_t start = 0;
    if (str[0] == '+' || str[0] == '-') {
        start = 1;
    }
    for (size_t i = start; i < str.size(); ++i) {
        if (!isdigit(str[i])) {
            return false;
        }
    }
    return true;
}

void processFile(const string& inputFileName) {
    ifstream inputFile(inputFileName);

    if (!inputFile.is_open()) {
        cerr << "Не вдалося відкрити вхідний файл." << endl;
        return;
    }

    string line;
    while (getline(inputFile, line)) {
        stringstream ss(line);
        string token;
        int count = 0;

        while (getline(ss, token, ' ')) {
            if (isNumber(token)) {
                count++;
            }
        }

        if (count <= 60) {
            cout << line << endl;
        }
    }

    inputFile.close();
}

int main() {
    string inputFileName = "input.txt";

    processFile(inputFileName);

    return 0;
}
