/**
 * \file Date.h
 * \brief Declaration of the Date class.
 * This class represents a calendar date
 * which has seperate day, month and year
 * and includes the output desired for a full date.
 * 
 * \author Wong Liang Jun
 * \version 1.0.1
 * \date February 25, 2024
 * 
 */

#pragma once
#include <iostream>
#include <string>

/**
 * \brief A class representing a date.
 * 
 * This class provides functionalities to work with dates,
 * including setting and getting individual components.
 */
class Date {
    private:
        /**
         \brief The day of month in date.
         */
        unsigned m_day;

        /**
         \brief The month in date as a numeral. 
         */
        unsigned m_month;

        /**
         \brief The year in date.
         */
        unsigned m_year;

        /**
         \brief Full date output including day, month and year. 
         */
        std::string m_FullDate;
    public:
        /**
         \brief Default constructor for the Date class.
         Initializes a Date object with default values.
         Where day is set to 1,
         Month is set to 1 and 
         Year is set to 0.
         */
        Date();

        /**
         \brief Parameterized constructor for the Date class.
         Initializes a Date object with the specified day, month, year,
         and full date as a string.
         \param day The day component of the date.
         \param month The month component of the date.
         \param year The year component of the date.
         \param Date The full date string.
         */
        Date(const unsigned& day, const unsigned& month, const unsigned& year, const std::string& Date);

        /**
         \brief Getter function for a day in a date.
         \return The day component of the date.
         \todo Returning the name of the day as one of the 7 days in a week. Uses <ctime> potentially. 
         */
        unsigned Getday() const;

        /**
         \brief Getter function for the month in a date. 
         \throw Error if month is not within 1 to 12. 
         \return The month component of the date.
         */
        unsigned Getmonth() const;

        /**
         \brief Getter function for the year in a date.
         \return The year component of the date.
         */
        unsigned GetYear() const;

        /**
         \brief Getter function for the full date as a string.
         \return full date string, including day, month and year. 
         */
        std::string GetDate() const;

        /**
         \brief Set the day of month of the date object.
         \param day The day of month to set.
         */
        void SetDay(unsigned day);

        /**
         \brief Setter function for the month as a numeral. 
         \param month The month component to set.
         */
        void SetMonth(unsigned month);

        /**
         \brief Setter function for the year 
         \param year The year component to set.
         */
        void SetYear(unsigned year);

        /**
         \brief Setter function for the full date string.
         \note Does not format the desired date format!
         \param date The date string to put into the Date object.
         */
        void SetDate(std::string& date);

        /**
         \brief Returns the name of the month for a given month number.
                Invalid month is denied and closes the program. 
         \param month The month number from an input stream
         \return month in named form. 
         \throw When the month in numeral is not anywhere from 1 to 12. 
         */
        std::string Getmonthname(const unsigned& month);

};

/**
 \brief Overloaded output stream insertion operator for the Date class.
 \param os The output stream to which the date will be inserted.
 \param date The Date object 
 \return A reference to the output stream after outputing data.
 */
std::ostream & operator <<( std::ostream & os, const Date & date );

/**
 \brief Overloaded input stream extraction operator for the Date class
 \param input The input stream from which to extract data.
 \param date The Date object to store the extracted data.
 \return A reference to the input stream
 \warning Formats the date structure in this function.
 \todo Seperate the formatting from the overloaded function into the class itself. 
 */
std::istream & operator >>( std::istream & input, Date & date );

/**
 \brief Overloaded greater than operator for the Date class
 \param lhs The left-hand-side Date object for comparison.
 \param rhs The right-hand-side Date object for comparison.
 \return True if lhs > rhs, else false.
 */
bool operator>(const Date &lhs,const Date &rhs);

/**
 \brief Overloaded lesser than operator for the Date class.
 \param lhs The left-hand-side Date object for comparison.
 \param rhs The right-hand-side Date object for comparison.
 \return True if lhs < rhs, else false.
 */
bool operator<(const Date &lhs,const Date &rhs);

/**
 \brief Overloaded input stream extraction operator for the Date class
 \param lhs The left-hand-side Date object for comparison.
 \param rhs The right-hand-side Date object for comparison.
 \return True if lhs == rhs, else false
 */
bool operator==(const Date &lhs,const Date &rhs); 
