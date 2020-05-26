#ifndef DATE_H
#define DATE_H
#include <ctime>
#include <string>
#include <iostream>
#include <sstream>
#include "boost/date_time/gregorian/gregorian.hpp"
using namespace std;
using namespace boost::gregorian;

class Date
{
    public:
        Date();
        ~Date();

       static date getDate (const string &);
       static bool checkDate(const string &);
       static string toString(const date &);
    protected:

    private:
};

#endif // DATE_H
