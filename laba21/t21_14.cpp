#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>
#include <map>

struct Date {
    int day;
    int month;
    int year;

    bool operator<(const Date& other) const {
        if(year != other.year)
            return year < other.year;
        if(month != other.month)
            return month < other.month;
        return day < other.day;
    }

    bool operator==(const Date& other) const {
        return day == other.day && month == other.month && year == other.year;
    }
};

int month_to_number(const std::string& month_str) {
    static std::map<std::string, int> month_map = {
            {"January", 1}, {"February", 2}, {"March", 3}, {"April", 4},
            {"May", 5}, {"June", 6}, {"July", 7}, {"August", 8},
            {"September", 9}, {"October", 10}, {"November", 11}, {"December", 12}
    };


    try {
        int month_num = std::stoi(month_str);
        if(month_num >=1 && month_num <=12)
            return month_num;
    } catch (...) {
    }


    std::string month_cap = month_str;
    if(!month_cap.empty())
        month_cap[0] = toupper(month_cap[0]);

    auto it = month_map.find(month_cap);
    if(it != month_map.end())
        return it->second;

    return 0;
}

void read_dates(const std::string& filename){
    std::vector<Date> dates;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Не вдалося відкрити файл: " << filename << std::endl;
        return;
    }

    std::string token;
    while(std::getline(file,token,',')){
        int day, year;
        std::string month_str;

        std::stringstream ss(token);

        std::string perk;

        try {
            getline(ss, perk,'.');
            day = std::stoi(perk);
        } catch (...){
            std::cerr << "проблеми з днем" << token << std::endl;
        }


        getline(ss, month_str,'.');
        int month = month_to_number(month_str);

        try {
            getline(ss, perk,'.');
            year = std::stoi(perk);
        } catch (...){
            std::cerr << "проблеми з місяцем" << token << std::endl;
        }

        dates.push_back(Date{day, month, year});

    }

    file.close();

    std::sort(dates.begin(), dates.end());

    auto last = std::unique(dates.begin(), dates.end());
    dates.erase(last, dates.end());

    std::map<int, std::string> number_to_month = {
            {1, "January"}, {2, "February"}, {3, "March"}, {4, "April"},
            {5, "May"}, {6, "June"}, {7, "July"}, {8, "August"},
            {9, "September"}, {10, "October"}, {11, "November"}, {12, "December"}
    };

    for(const auto& date: dates){
        if(number_to_month.find(date.month) != number_to_month.end()){
            std::cout << date.year << "/"
                      << number_to_month[date.month] << "/"
                      << date.day << std::endl;
        } else {
            std::cout << date.year << "/"
                      << date.month << "/"
                      << date.day << std::endl;
        }
    }
}

int main(){
    read_dates("input.txt");
    return 0;
}