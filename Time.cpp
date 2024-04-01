#include "Time.h"

Time::Time() {
    m_hour = 0;
    m_minute = 0;
    m_FullTime = "00:00";
}

Time::Time(const unsigned& hour, const unsigned& minute, const std::string& WholeTime) {
    m_hour = hour;
    m_minute = minute;
    m_FullTime = WholeTime;
}

unsigned Time::Gethour() const {
    return m_hour;
}

unsigned Time::Getminute() const {
    return m_minute;
}

std::string Time::GetFullTime() const {
    return m_FullTime;
}

void Time::Sethour(unsigned hour) {
    if (hour > 23) {
        std::cerr << "Hour input wrong!";
    }
    m_hour = hour;
}

void Time::Setminute(unsigned minute) {
    if (minute > 59) {
        std::cerr << "Minute input wrong!";
    }
    m_minute = minute;
}

void Time::SetFullTime(const std::string& fulltime) {
    m_FullTime = fulltime;
}

std::string Time::FormatMinutes(const unsigned& minute) {
    std::stringstream ss;
    ss << std::setw(2) << std::setfill('0') << minute;
    return ss.str();
}

std::ostream & operator <<( std::ostream & os, const Time & time ) { // this is for output 
    os << " Time: " << time.GetFullTime();
    return os;
}

std::istream & operator >>( std::istream & input, Time & time ) { // this is for input
    std::string line;
    getline(input, line, ':');
    time.Sethour(stoi(line));

    getline(input, line, ',');
    time.Setminute(stoi(line));

    time.SetFullTime(std::to_string(time.Gethour()) + ":" + time.FormatMinutes(time.Getminute()));

    return input;
}

bool operator>(const Time &lhs,const Time &rhs) {
    if (lhs.Gethour() > rhs.Gethour())
        return true;
    else if (lhs.Gethour() < rhs.Gethour())
        return false;
    else {
            return lhs.Getminute() > rhs.Getminute();
    }
}

bool operator<(const Time &lhs,const Time &rhs) {
    return !(lhs > rhs) && !(lhs == rhs);
}

bool operator==(const Time &lhs,const Time &rhs) {
    return lhs.Gethour() == rhs.Gethour() && lhs.Getminute() == rhs.Getminute();
}