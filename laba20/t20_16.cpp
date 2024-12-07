#include <iostream>
#include <vector>
#include <map>
using namespace std;

int main() {
    cout << "Введіть кількість елементів у векторі V: ";
    int n;
    cin >> n;

    cout << "Введіть елементи вектора V: ";
    vector<int> V(n);
    for (int i = 0; i < n; ++i) cin >> V[i];

    map<int, vector<int>> M;
    for (int x : V) {
        int key = abs(x) % 10;
        M[key].push_back(x);
    }

    cout << "Результат групування:\n";
    for (const auto& [key, values] : M) {
        cout << key << ":";
        for (size_t i = 0; i < values.size(); ++i) {
            if (i > 0) cout << ",";
            cout << values[i];
        }
        cout << endl;
    }

    return 0;
}
