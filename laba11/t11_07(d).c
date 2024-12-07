#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double findMaxByAbs(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Помилка: не вдалося відкрити файл!\n");
        exit(EXIT_FAILURE);
    }

    double num, maxAbs = 0.0;

    while (fscanf(file, "%lf", &num) == 1) {
        if (fabs(num) > maxAbs) {
            maxAbs = fabs(num);
        }
    }

    fclose(file);
    return maxAbs;
}

int main() {
    char filename[256];
    printf("Введіть ім'я файлу: ");
    scanf("%s", filename);

    double maxAbs = findMaxByAbs(filename);

    printf("Найбільший за модулем компонент у файлі: %.2f\n", maxAbs);

    return 0;
}
