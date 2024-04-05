#include <iostream>
#include <string>
#include <sstream>
#include "Time.h"

// g++ -Wall -g -std=c++11 -ftime-report TimeTest.cpp Time.cpp -o TimeTest

int main() {

    Time time;
    time.Sethour(10);
    time.Setminute(25);
    std::cout << time << std::endl;

    Time time2;
    std::string thing;
    thing = "9:25";
    std::istringstream iss(thing);
    iss >> time2;
    std::cout << time2 << std::endl;

    std::cout << time2.Gethour() << " " << time2.Getminute() << std::endl;

    std::cout << std::boolalpha << (time>time2) << std::endl;

    return 0;
}