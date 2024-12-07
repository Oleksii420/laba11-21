#include <iostream>
#include <vector>
#include <stdexcept>
#include <sstream>
#include <cmath>

using namespace std;

class PolynomialError : public runtime_error {
public:
    explicit PolynomialError(const string& message)
        : runtime_error("Помилка: " + message) {}
};

class Polynomial {
private:
    int degree;
    vector<double> coefficients;

    void validateDegree(int deg) {
        if (deg < 0) {
            throw PolynomialError("Ступінь полінома має бути невід'ємним цілим числом.");
        }
    }

    void validateCoefficients(const vector<double>& coeffs) {
        if (coeffs.empty()) {
            throw PolynomialError("Коефіцієнти полінома не можуть бути порожніми.");
        }
    }

public:
    Polynomial(int deg, const vector<double>& coeffs) {
        validateDegree(deg);
        validateCoefficients(coeffs);

        if (coeffs.size() != deg + 1) {
            throw PolynomialError("Кількість коефіцієнтів має дорівнювати ступеню + 1.");
        }

        degree = deg;
        coefficients = coeffs;
    }

    static Polynomial fromInput() {
        int deg;
        cout << "Введіть ступінь полінома: ";
        cin >> deg;

        if (cin.fail()) {
            throw PolynomialError("Ступінь має бути цілим числом.");
        }

        vector<double> coeffs(deg + 1);
        cout << "Введіть коефіцієнти полінома (від старшого до вільного):\n";
        for (int i = 0; i <= deg; ++i) {
            cin >> coeffs[i];
            if (cin.fail()) {
                throw PolynomialError("Коефіцієнти мають бути дійсними числами.");
            }
        }

        return Polynomial(deg, coeffs);
    }

    void print() const {
        for (int i = 0; i <= degree; ++i) {
            if (i > 0 && coefficients[i] >= 0) cout << "+";
            cout << coefficients[i];
            if (degree - i > 0) {
                cout << "x^" << (degree - i) << " ";
            }
        }
        cout << endl;
    }

    double evaluate(double x) const {
        double result = 0;
        for (int i = 0; i <= degree; ++i) {
            result += coefficients[i] * pow(x, degree - i);
        }
        return result;
    }

    Polynomial derivative() const {
        if (degree == 0) {
            return Polynomial(0, std::vector<double>{0});
        }

        std::vector<double> derivedCoeffs(degree);
        for (int i = 0; i < degree; ++i) {
            derivedCoeffs[i] = coefficients[i] * (degree - i);
        }

        return Polynomial(degree - 1, derivedCoeffs);
    }


    Polynomial operator+(const Polynomial& other) const {
        int maxDegree = max(degree, other.degree);
        vector<double> resultCoeffs(maxDegree + 1, 0);

        for (int i = 0; i <= degree; ++i) {
            resultCoeffs[maxDegree - i] += coefficients[degree - i];
        }

        for (int i = 0; i <= other.degree; ++i) {
            resultCoeffs[maxDegree - i] += other.coefficients[other.degree - i];
        }

        return Polynomial(maxDegree, resultCoeffs);
    }

    Polynomial operator-(const Polynomial& other) const {
        int maxDegree = max(degree, other.degree);
        vector<double> resultCoeffs(maxDegree + 1, 0);

        for (int i = 0; i <= degree; ++i) {
            resultCoeffs[maxDegree - i] += coefficients[degree - i];
        }

        for (int i = 0; i <= other.degree; ++i) {
            resultCoeffs[maxDegree - i] -= other.coefficients[other.degree - i];
        }

        return Polynomial(maxDegree, resultCoeffs);
    }

    Polynomial operator*(const Polynomial& other) const {
        int newDegree = degree + other.degree;
        vector<double> resultCoeffs(newDegree + 1, 0);

        for (int i = 0; i <= degree; ++i) {
            for (int j = 0; j <= other.degree; ++j) {
                resultCoeffs[i + j] += coefficients[i] * other.coefficients[j];
            }
        }

        return Polynomial(newDegree, resultCoeffs);
    }
};

int main() {
    try {
        cout << "Створення першого полінома:\n";
        Polynomial poly1 = Polynomial::fromInput();

        cout << "Створення другого полінома:\n";
        Polynomial poly2 = Polynomial::fromInput();

        cout << "\nПерший поліном: ";
        poly1.print();

        cout << "Другий поліном: ";
        poly2.print();

        cout << "\nСума поліномів: ";
        Polynomial sum = poly1 + poly2;
        sum.print();

        cout << "Різниця поліномів: ";
        Polynomial diff = poly1 - poly2;
        diff.print();

        cout << "Добуток поліномів: ";
        Polynomial prod = poly1 * poly2;
        prod.print();

        double x;
        cout << "\nВведіть точку x для обчислення значення полінома: ";
        cin >> x;

        if (cin.fail()) {
            throw PolynomialError("x має бути дійсним числом.");
        }

        cout << "Значення першого полінома у точці x: " << poly1.evaluate(x) << endl;
        cout << "Значення другого полінома у точці x: " << poly2.evaluate(x) << endl;

        cout << "\nПохідна першого полінома: ";
        Polynomial deriv1 = poly1.derivative();
        deriv1.print();

        cout << "Похідна другого полінома: ";
        Polynomial deriv2 = poly2.derivative();
        deriv2.print();

    } catch (const PolynomialError& e) {
        cerr << e.what() << endl;
    }

    return 0;
}
