#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

template <typename T>
class Matrix {
private:
    vector<vector<T>> data;
    size_t rows, cols;

public:
    Matrix(size_t r, size_t c, const T& init = T()) : rows(r), cols(c), data(r, vector<T>(c, init)) {}

    Matrix(const vector<vector<T>>& values) : rows(values.size()), cols(values[0].size()), data(values) {
        for (const auto& row : values) {
            if (row.size() != cols) {
                throw invalid_argument("Усі рядки мають бути однакової довжини.");
            }
        }
    }

    size_t getRows() const { return rows; }
    size_t getCols() const { return cols; }

    vector<T>& operator[](size_t index) { return data[index]; }
    const vector<T>& operator[](size_t index) const { return data[index]; }

    friend ostream& operator<<(ostream& os, const Matrix& matrix) {
        for (size_t i = 0; i < matrix.rows; ++i) {
            for (size_t j = 0; j < matrix.cols; ++j) {
                os << matrix.data[i][j] << " ";
            }
            os << endl;
        }
        return os;
    }

    friend Matrix operator+(const Matrix& a, const Matrix& b) {
        if (a.rows != b.rows || a.cols != b.cols) {
            throw invalid_argument("Розміри матриць мають бути однаковими для додавання.");
        }
        Matrix result(a.rows, a.cols);
        for (size_t i = 0; i < a.rows; ++i) {
            for (size_t j = 0; j < a.cols; ++j) {
                result.data[i][j] = a.data[i][j] + b.data[i][j];
            }
        }
        return result;
    }

    friend vector<T> operator*(const Matrix& matrix, const vector<T>& vec) {
        if (matrix.cols != vec.size()) {
            throw invalid_argument("Кількість стовпців матриці має дорівнювати розміру вектора.");
        }
        vector<T> result(matrix.rows, T());
        for (size_t i = 0; i < matrix.rows; ++i) {
            T sum = T();
            for (size_t j = 0; j < matrix.cols; ++j) {
                sum += matrix.data[i][j] * vec[j];
            }
            result[i] = sum;
        }
        return result;
    }

    friend Matrix operator*(const Matrix& a, const Matrix& b) {
        if (a.cols != b.rows) {
            throw invalid_argument("Кількість стовпців першої матриці має дорівнювати кількості рядків другої.");
        }
        Matrix result(a.rows, b.cols, T());
        for (size_t i = 0; i < a.rows; ++i) {
            for (size_t j = 0; j < b.cols; ++j) {
                for (size_t k = 0; k < a.cols; ++k) {
                    result.data[i][j] += a.data[i][k] * b.data[k][j];
                }
            }
        }
        return result;
    }
};

int main() {
    try {
        Matrix<int> mat1({{1, 2}, {3, 4}});
        Matrix<int> mat2({{5, 6}, {7, 8}});
        vector<int> vec = {1, 2};

        Matrix<int> sum = mat1 + mat2;
        cout << "Результат додавання матриць:\n" << sum;

        vector<int> result = mat1 * vec;
        cout << "Результат множення матриці на вектор:\n";
        for (int val : result) {
            cout << val << " ";
        }
        cout << endl;

        Matrix<int> prod = mat1 * mat2;
        cout << "Результат множення матриць:\n" << prod;

    } catch (const invalid_argument& e) {
        cout << "Помилка: " << e.what() << endl;
    }

    return 0;
}
