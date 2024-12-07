#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

string replaceWordsWithDigits(const string& input) {
    unordered_map<string, char> wordToDigit;
    wordToDigit.insert(make_pair("one", '1'));
    wordToDigit.insert(make_pair("two", '2'));
    wordToDigit.insert(make_pair("three", '3'));
    wordToDigit.insert(make_pair("four", '4'));
    wordToDigit.insert(make_pair("five", '5'));
    wordToDigit.insert(make_pair("six", '6'));
    wordToDigit.insert(make_pair("seven", '7'));
    wordToDigit.insert(make_pair("eight", '8'));
    wordToDigit.insert(make_pair("nine", '9'));

    string result;
    string word;
    for (size_t i = 0; i <= input.length(); ++i) {
        if (i == input.length() || isspace(input[i]) || ispunct(input[i])) {
            if (!word.empty() && wordToDigit.count(word)) {
                result += wordToDigit[word];
            } else {
                result += word;
            }
            if (i < input.length()) {
                result += input[i];
            }
            word.clear();
        } else {
            word += tolower(input[i]);
        }
    }
    return result;
}

int main() {
    string input;
    cout << "Введіть рядок: ";
    getline(cin, input);

    string output = replaceWordsWithDigits(input);
    cout << "Результат: " << output << endl;
    return 0;
}
