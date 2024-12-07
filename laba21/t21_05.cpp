#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
using namespace std;

int main() {
    cout << "Введіть рядок: ";
    string input;
    getline(cin, input);

    transform(input.begin(), input.end(), input.begin(), ::toupper);

    cout << "Рядок у верхньому регістрі: " << input << endl;
    return 0;
}
