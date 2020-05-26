#ifndef WORKER_H
#define WORKER_H
#include <cstring>
#include <iostream>
#include "Contract.h"
#include "Report.h"
#include "boost/date_time/gregorian/gregorian.hpp"
using namespace std;
using namespace boost::gregorian;

class Worker
{
    public:
        Worker(int, string, date, date, vector<int>,long double);
        ~Worker();
        Report getReport(vector<Contract> &, date, date);
        void print();
        int getKey();
        string getName();
        date getStartDate();
        date getEndDate();
        long double getSalary();


    protected:

    private:
        int key;
        string name;
        date startDate, endDate;
        vector <int> bonusKeys;
        long double salary;
};

#endif // WORKER_H
