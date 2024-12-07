//
// Created by Volodymyr Avvakumov on 13.10.2024.
//

#include <iostream>
#include <limits>
#include <cmath>
#include <iomanip>


void input(double* arr, int &n, int max_size) {
    n = 0;
    double input;
    while (true) {
        std::cout << "enter a num or \"enter\" to finish: ";

        std::string line;
        std::getline(std::cin, line);

        if (line.empty()) {
            break;
        }


        input = std::stoi(line);
        if (n < max_size) {
            arr[n] = input;
            n++;
        } else {
            break;
        }

    }
}

void print_log(double num){
    if (num <= 0){
        std::cout << "None" << std::endl;
    }
    double lg = log(num);
    std::cout << "default 5 literals: ";
    std::cout << std::fixed << std::setprecision(4) << std::setw(5) << lg << std::endl;
    std::cout <<"scientific: ";
    std::cout << std::scientific << lg << std::endl;
}

void print_log_arr(double * arr, int size){
    for (int i = 0; i < size; i++){
        std::cout << arr[i] << " log == " << std::endl;
        print_log(arr[i]);
    }
}


int main(){
    int size;
    double* arr = new double[1000];
    input(arr, size, 1000);
    print_log_arr(arr, size);

    delete[] arr;
    return 0;
}