#pragma once
#include <cstring>
#include <iostream>
#include "boost/date_time/gregorian/gregorian.hpp"
using namespace std;
using namespace boost::gregorian;


class Contract
{
public:
	Contract(int, int, date, long double);
	int getWorkerKey();
	date getContractDate();
	 long double getContractSum();
private:
	int key;
	int workerKey;
	date contractDate;
	long double contractSum;
};

