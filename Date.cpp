#include "Date.h"

Date::Date() {
    m_day = 1;
    m_month = 1;
    m_year = 0;
    m_FullDate = "No Date";
}

Date::Date(const unsigned& day, const unsigned& month, const unsigned& year, const std::string& date) {
    m_day = day;
    m_month = month;
    m_year = year;
    m_FullDate = date;
}

unsigned Date::Getday() const {
    return m_day;
}

unsigned Date::Getmonth() const {
    return m_month;
}

std::string Date::Getmonthname(const unsigned& month) {
    switch (month) {
        case 1:     return "January";   break;
        case 2:     return "February";  break;
        case 3:     return "March";     break;
        case 4:     return "April";     break;
        case 5:     return "May";       break;
        case 6:     return "June";      break;
        case 7:     return "July";      break;
        case 8:     return "August";    break;
        case 9:     return "September"; break;
        case 10:    return "October";   break;
        case 11:    return "November";  break;
        case 12:    return "December";  break;
        default:    std::cout << "Invalid month detected. Please check the data again." << std::endl; exit(-1);
    }
}

unsigned Date::GetYear() const {
    return m_year;
}

std::string Date::GetDate() const {
    return m_FullDate;
}

void Date::SetDay(unsigned day) {
    m_day = day;
}

void Date::SetMonth(unsigned month) {
    if (month<1 || month>12) {
        std::cout << "Invalid month detected. Please check the data again." << std::endl;
        exit(-1);
    } else {
        m_month = month;
    }
}

void Date::SetYear(unsigned year) {
    m_year = year;
}

void Date::SetDate(std::string& fulldate) {
    m_FullDate = fulldate;
}

bool operator>(const Date &lhs,const Date &rhs) {
    if (lhs.GetYear() > rhs.GetYear())
        return true;
    else if (lhs.GetYear() < rhs.GetYear())
        return false;
    else {
        if (lhs.Getmonth() > rhs.Getmonth())
            return true;
        else if (lhs.Getmonth() < rhs.Getmonth())
            return false;
        else {
            return lhs.Getday() > rhs.Getmonth();
        }
    }
}

bool operator<(const Date &lhs,const Date &rhs) {
    return !(lhs > rhs) && !(lhs == rhs);
}

bool operator==(const Date &lhs,const Date &rhs) {
    return lhs.GetYear() == rhs.GetYear() && lhs.Getmonth() == rhs.Getmonth() && lhs.Getday() == rhs.Getday();
}

std::ostream & operator <<( std::ostream & os, const Date & date ) {
    os << date.Getday() << "/" << date.Getmonth() << "/" << date.GetYear();
    return os;
}

std::istream & operator >>( std::istream & input, Date& date ) {

    std::string line;
    getline(input, line,'/');
    date.SetDay(stoi(line));

    getline(input,line,'/');
    date.SetMonth(stoi(line));

    getline(input,line, ' ');
    date.SetYear(stoi(line));

    std::string fulldate;
    fulldate = std::to_string(date.Getday()) + " " + date.Getmonthname(date.Getmonth()) + " " +std::to_string(date.GetYear());

    date.SetDate(fulldate);

    return input;
}



