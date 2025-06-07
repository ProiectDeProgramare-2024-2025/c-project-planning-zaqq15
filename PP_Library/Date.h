#ifndef DATE_H
#define DATE_H

#include <string>

class Date {
private:
    int day;
    int month;
    int year;

public:
    // Constructors
    Date();
    Date(int day, int month, int year);
    
    // Getters
    int getDay() const;
    int getMonth() const;
    int getYear() const;
    
    // Setters
    void setDay(int day);
    void setMonth(int month);
    void setYear(int year);
    
    // Utility methods
    std::string toString() const;
    bool isValid() const;
    static Date getCurrentDate();
};

#endif