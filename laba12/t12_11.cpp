#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    string inputFileName;
    inputFileName = "input1.txt";
    string outputFileName;
    outputFileName = "output.txt";

    ifstream inputFile(inputFileName);
    if (!inputFile.is_open()) {
        cerr << "Помилка: не вдалося відкрити файл " << inputFileName << endl;
        return 1;
    }

    const int INITIAL_SIZE = 100;
    double* numbers = new double[INITIAL_SIZE];
    int size = 0;
    int capacity = INITIAL_SIZE;
    char delimiter = ';';
    double number;
    int maxPrecision = 0;

    string line;
    while (getline(inputFile, line, delimiter)) {
        stringstream ss(line);
        if (ss >> number) {
            if (size == capacity) {
                capacity *= 2;
                double* newNumbers = new double[capacity];
                for (int i = 0; i < size; ++i) {
                    newNumbers[i] = numbers[i];
                }
                delete[] numbers;
                numbers = newNumbers;
            }
            numbers[size++] = number;
            size_t dotPos = line.find('.');
            if (dotPos != string::npos) {
                size_t precision = line.size() - dotPos - 1;
                maxPrecision = max(maxPrecision, static_cast<int>(precision));
            }
        }
    }
    inputFile.close();

    ofstream outputFile(outputFileName);
    if (!outputFile.is_open()) {
        cerr << "Помилка: не вдалося створити файл " << outputFileName << endl;
        delete[] numbers;
        return 1;
    }

    for (int i = 0; i < size; ++i) {
        outputFile << fixed << setprecision(maxPrecision) << fabs(numbers[i]) << endl;
    }
    outputFile.close();

    delete[] numbers;

    cout << "Результат записано у файл " << outputFileName << endl;

    return 0;
}
