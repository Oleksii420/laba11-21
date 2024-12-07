#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

bool isIncluded(const vector<int>& v0, const vector<int>& vi) {
    unordered_map<int, int> v0_count, vi_count;

    for (int num : v0) {
        v0_count[num]++;
    }

    for (int num : vi) {
        vi_count[num]++;
    }

    for (const auto& [key, val] : v0_count) {
        if (vi_count[key] < val) {
            return false;
        }
    }
    return true;
}

int main() {
    cout << "Введіть кількість елементів у V0: ";
    int size_v0;
    cin >> size_v0;

    vector<int> V0(size_v0);
    cout << "Введіть елементи V0: ";
    for (int i = 0; i < size_v0; ++i) {
        cin >> V0[i];
    }

    cout << "Введіть кількість векторів N: ";
    int N;
    cin >> N;

    int count = 0;

    for (int i = 1; i <= N; ++i) {
        cout << "Введіть кількість елементів у V" << i << ": ";
        int size_vi;
        cin >> size_vi;

        vector<int> Vi(size_vi);
        cout << "Введіть елементи V" << i << ": ";
        for (int j = 0; j < size_vi; ++j) {
            cin >> Vi[j];
        }

        if (isIncluded(V0, Vi)) {
            count++;
        }
    }

    cout << "Кількість векторів Vi, що містять усі елементи V0: " << count << endl;

    return 0;
}
