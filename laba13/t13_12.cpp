#include <iostream>
#include <string>
#include <cctype>

using namespace std;

string capitalizeWords(const string& input) {
    string result = input;
    bool newWord = true;

    for (size_t i = 0; i < result.length(); ++i) {
        if (isspace(result[i])) {
            newWord = true;
        } else if (newWord) {
            result[i] = toupper(result[i]);
            newWord = false;
        } else {
            result[i] = tolower(result[i]);
        }
    }
    return result;
}

int main() {
    string input;
    cout << "Введіть рядок: ";
    getline(cin, input);
    string output = capitalizeWords(input);
    cout << "Результат: " << output << endl;
    return 0;
}
