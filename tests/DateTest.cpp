#include <iostream>
#include <string>
#include <sstream>
#include "Date.h"

// g++ -Wall -g -std=c++11 -ftime-report DateTest.cpp Date.cpp -o DateTest

int main() {
    Date date;

    date.SetDay(4);
    date.SetMonth(5);
    date.SetYear(2015);

    std::cout << date << std::endl;

    Date date2;
    std::string thing;
    thing = "12/12/2016";
    std::istringstream iss(thing);

    iss >> date2;

    std::cout << date2 << std::endl;

    std::cout << date.Getmonthname(date.Getmonth()) << std::endl;
    std::cout << date2.Getmonthname(date2.Getmonth()) << std::endl;
    std::cout << date.Getday() << " " << date.Getmonth() << " " << date.GetYear() << std::endl;

    std::cout << std::boolalpha << (date>date2) << std::endl;

    return 0;
}