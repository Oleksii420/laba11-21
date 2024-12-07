#include <iostream>
#include <list>
#include <cmath>
#include <stdexcept>

using namespace std;

template <typename T>
class NumberStorage {
private:
    list<T> numbers;

public:
    void addNumber(const T& number) {
        numbers.push_back(number);
    }

    void removeNumber(const T& number) {
        auto it = find(numbers.begin(), numbers.end(), number);
        if (it != numbers.end()) {
            numbers.erase(it);
        } else {
            throw runtime_error("Число не знайдено для видалення.");
        }
    }

    T findClosest(const T& target) const {
        if (numbers.empty()) {
            throw runtime_error("Контейнер порожній. Немає чисел для пошуку.");
        }

        auto closest = numbers.begin();
        T minDifference = abs(*closest - target);

        for (auto it = numbers.begin(); it != numbers.end(); ++it) {
            T currentDifference = abs(*it - target);
            if (currentDifference < minDifference) {
                closest = it;
                minDifference = currentDifference;
            }
        }

        return *closest;
    }

    void print() const {
        cout << "Числа у контейнері: ";
        for (const auto& number : numbers) {
            cout << number << " ";
        }
        cout << endl;
    }
};

int main() {
    try {
        NumberStorage<int> storage;

        storage.addNumber(10);
        storage.addNumber(20);
        storage.addNumber(30);
        storage.addNumber(25);

        cout << "Після додавання чисел: ";
        storage.print();

        int target = 22;
        int closest = storage.findClosest(target);
        cout << "Найближче до " << target << ": " << closest << endl;

        storage.removeNumber(20);
        cout << "Після видалення числа 20: ";
        storage.print();

        closest = storage.findClosest(target);
        cout << "Найближче до " << target << " після видалення: " << closest << endl;

    } catch (const runtime_error& e) {
        cerr << e.what() << endl;
    }

    return 0;
}
