#include <iostream>
#include <vector>
#include <stdexcept>
#include <cstdlib>
#include <ctime>

using namespace std;

template <typename T>
class BlackBox {
private:
    static const int MAX_SIZE = 100;
    vector<T> elements;

public:
    BlackBox() {
        elements.reserve(MAX_SIZE);
        srand(static_cast<unsigned>(time(0)));
    }

    BlackBox(const T* array, size_t size) {
        if (size > MAX_SIZE) {
            throw runtime_error("Розмір масиву перевищує максимальний ліміт.");
        }
        elements.reserve(MAX_SIZE);
        elements.assign(array, array + size);
        srand(static_cast<unsigned>(time(0)));
    }

    void push(const T& element) {
        if (elements.size() >= MAX_SIZE) {
            throw runtime_error("BlackBox переповнений. Немає місця для нового елемента.");
        }
        elements.push_back(element);
    }

    T pop() {
        if (elements.empty()) {
            throw runtime_error("BlackBox порожній. Немає елементів для видалення.");
        }
        size_t randomIndex = rand() % elements.size();
        T removedElement = elements[randomIndex];
        elements.erase(elements.begin() + randomIndex);
        return removedElement;
    }

    T xpop() const {
        if (elements.empty()) {
            throw runtime_error("BlackBox порожній. Немає елементів для отримання.");
        }
        size_t randomIndex = rand() % elements.size();
        return elements[randomIndex];
    }

    void print() const {
        cout << "Елементи в BlackBox: ";
        for (const auto& element : elements) {
            cout << element << " ";
        }
        cout << endl;
    }
};

int main() {
    try {
        int array[] = {1, 2, 3, 4, 5};
        BlackBox<int> box(array, 5);

        box.print();

        box.push(6);
        cout << "Після додавання елемента 6: ";
        box.print();

        int removed = box.pop();
        cout << "Видалений випадковий елемент: " << removed << endl;
        cout << "Після видалення: ";
        box.print();

        int randomElement = box.xpop();
        cout << "Випадковий елемент (без видалення): " << randomElement << endl;

    } catch (const runtime_error& e) {
        cerr << e.what() << endl;
    }

    return 0;
}
