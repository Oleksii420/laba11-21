#include <iostream>
#include <vector>
#include <cmath>

class Figura3D {
public:
    virtual double getSideSurfaceArea() const = 0;
    virtual double getVolume() const = 0;
    virtual int getVertexCount() const = 0;
    virtual ~Figura3D() {}
};

class Parallelepiped : public Figura3D {
private:
    double length, width, height;

public:
    Parallelepiped(double l, double w, double h) : length(l), width(w), height(h) {}

    double getSideSurfaceArea() const override {
        return 2 * height * (length + width);
    }

    double getVolume() const override {
        return length * width * height;
    }

    int getVertexCount() const override {
        return 8;
    }
};

class Pyramid3 : public Figura3D {
private:
    double baseEdge, height;

public:
    Pyramid3(double b, double h) : baseEdge(b), height(h) {}

    double getSideSurfaceArea() const override {
        double slantHeight = sqrt(pow(height, 2) + pow(baseEdge / (2 * sqrt(3)), 2));
        return 3 * (baseEdge * slantHeight / 2);
    }

    double getVolume() const override {
        return (pow(baseEdge, 2) * sqrt(3) / 4) * height / 3;
    }

    int getVertexCount() const override {
        return 4;
    }
};

class Pyramid4 : public Figura3D {
private:
    double baseLength, baseWidth, height;

public:
    Pyramid4(double l, double w, double h) : baseLength(l), baseWidth(w), height(h) {}

    double getSideSurfaceArea() const override {
        double slantHeight1 = sqrt(pow(height, 2) + pow(baseLength / 2, 2));
        double slantHeight2 = sqrt(pow(height, 2) + pow(baseWidth / 2, 2));
        return baseLength * slantHeight2 + baseWidth * slantHeight1;
    }

    double getVolume() const override {
        return (baseLength * baseWidth * height) / 3;
    }

    int getVertexCount() const override {
        return 5;
    }
};

int main() {
    std::vector<Figura3D*> figures;
    int numFigures;

    std::cout << "Введіть кількість фігур: ";
    std::cin >> numFigures;

    for (int i = 0; i < numFigures; ++i) {
        int choice;
        std::cout << "\nВиберіть тип фігури (1 - Паралелепіпед, 2 - Трикутна піраміда, 3 - Чотирикутна піраміда): ";
        std::cin >> choice;

        if (choice == 1) {
            double l, w, h;
            std::cout << "Введіть довжину, ширину та висоту паралелепіпеда: ";
            std::cin >> l >> w >> h;
            figures.push_back(new Parallelepiped(l, w, h));
        } else if (choice == 2) {
            double b, h;
            std::cout << "Введіть довжину основи та висоту трикутної піраміди: ";
            std::cin >> b >> h;
            figures.push_back(new Pyramid3(b, h));
        } else if (choice == 3) {
            double l, w, h;
            std::cout << "Введіть довжину, ширину основи та висоту чотирикутної піраміди: ";
            std::cin >> l >> w >> h;
            figures.push_back(new Pyramid4(l, w, h));
        } else {
            std::cout << "Невірний вибір! Спробуйте ще раз.\n";
            --i;
        }
    }

    double totalVolume = 0;
    double totalSurfaceArea = 0;
    int totalVertices = 0;

    for (const auto& figure : figures) {
        totalVolume += figure->getVolume();
        totalSurfaceArea += figure->getSideSurfaceArea();
        totalVertices += figure->getVertexCount();
    }

    std::cout << "\nСумарний об'єм: " << totalVolume << "\n";
    std::cout << "Сумарна площа всіх граней: " << totalSurfaceArea << "\n";
    std::cout << "Загальна кількість вершин: " << totalVertices << "\n";

    for (auto& figure : figures) {
        delete figure;
    }

    return 0;
}
