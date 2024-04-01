/**
 * \file Time.h
 * \brief Declaration of the Time class.
 * This class represents the time of day
 * which has seperate hours and minutes.
 * and includes the output desired for the full time output in 24h Format.
 * 
 * \author Wong Liang Jun
 * \version 1.0.0
 * \date February 25, 2024
 * 
 */

#pragma once
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

/**
 * \brief A class representing time of day.
 * 
 * This class provides functionalities to work with time,
 * BUT does not represent a clock, and will not count down automatically.
 */
class Time {
    private:
        /**
         \brief The hour denoted in time.
         */
        unsigned m_hour;

        /**
         \brief The minute denoted in time. 
         */
        unsigned m_minute;

        // /**
        //  \brief The second denoted in time.
        //  */
        // unsigned m_second;
        // not used in this assignment.

        /**
         \brief Full time output including hour, minute
         */
        std::string m_FullTime;
    public:
        /**
         \brief Default constructor for the Time class.
         Initializes a time object with default values.
         Where hour is set to 00,
         Minute is set to 00 and 
         */
        Time();

        /**
         \brief Parameterized constructor for the Time class.
         Initializes a Time object with the specified hours and minutes
         and a string of a full time display.
         \param hour The hour component of Time
         \param minute The month component of the date.
         \param WholeTime The full date string.
         */
        Time(const unsigned& hour, const unsigned& minute, const std::string& WholeTime);

        /**
         \brief Getter function for the hour of the day.
         \return The hour from Time object.
         */
        unsigned Gethour() const;

        /**
         \brief Getter function for the minutes in a day.
         \return The minute variable in Time object.
         */
        unsigned Getminute() const;

        /**
         \brief Getter function for the full time as a string.
         \return full date string, consisting hours and minutes.
         */
        std::string GetFullTime() const;

        /**
         \brief Set the hour of the day.
         \throw Error if it is not within 0 to 23. 
         \param day The hour in time. 
         */
        void Sethour(unsigned hour);

        /**
         \brief Setter function for minutes.
         \throw Error if it is not within 0 to 59.
         \param month The minute in time.
         */
        void Setminute(unsigned minute);

        /**
         \brief Setter function for the full time string.
         \param date The time string as a whole.
         */
        void SetFullTime(const std::string& fulltime);

        /// @brief Formats the minutes to a 2 digit string for display. 
        /// @return the minute variable in a string format of 2 digits.
        /// @param minute A referenced minute to convert. 
        std::string FormatMinutes(const unsigned& minute);

        //TODO change from 24h to 12h time somewhere here

};

/**
 \brief Overloaded output stream insertion operator for the Time class.
 \param os The output stream to which the date will be inserted.
 \param date The Time object 
 \return A reference to the output stream after outputing data.
 */
std::ostream & operator <<( std::ostream & os, const Time & time );

/**
 \brief Overloaded input stream extraction operator for the Time class.
 \param input The input stream from which to extract data.
 \param date The Time object to store the extracted data.
 \return A reference to the input stream
 \todo Seperate the formatting from the overloaded function into the class itself. 
 */
std::istream & operator >>( std::istream & input, Time & time );

/**
 \brief Overloaded lesser than operator for the Date class.
 \param lhs The left-hand-side Date object for comparison.
 \param rhs The right-hand-side Date object for comparison.
 \return True if lhs < rhs, else false.
 */
bool operator>(const Time &lhs,const Time &rhs);

/**
 \brief Overloaded lesser than operator for the Time class.
 \param lhs The left-hand-side Time object for comparison.
 \param rhs The right-hand-side Time object for comparison.
 \return True if lhs < rhs, else false.
 */
bool operator<(const Time &lhs,const Time &rhs);

/**
 \brief Overloaded lesser than operator for the Time class.
 \param lhs The left-hand-side Time object for comparison.
 \param rhs The right-hand-side Time object for comparison.
 \return True if lhs < rhs, else false.
 */
bool operator==(const Time &lhs,const Time &rhs);