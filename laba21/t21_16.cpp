#include <iostream>
#include <vector>

using namespace std;

template <typename InputIt, typename OutputIt, typename UnaryOperation, typename UnaryPredicate>
OutputIt transform_if(InputIt first, InputIt last, OutputIt d_first, UnaryOperation op, UnaryPredicate pred) {
    while (first != last) {
        if (pred(*first)) {
            *d_first = op(*first);
            ++d_first;
        }
        ++first;
    }
    return d_first;
}

int main() {
    vector<int> input = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector<int> output;

    auto is_even = [](int x) { return x % 2 == 0; };
    auto square = [](int x) { return x * x; };

    cout << "Вхідний вектор: ";
    for (int x : input) cout << x << " ";
    cout << endl;

    transform_if(input.begin(), input.end(), back_inserter(output), square, is_even);

    cout << "Результат transform_if (квадрати лише парних чисел): ";
    for (int x : output) cout << x << " ";
    cout << endl;

    return 0;
}
