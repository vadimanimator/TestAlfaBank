#pragma once
#include <iostream>
using namespace std;
class Report
{
public:
	Report(int, string, long double);
	int getKey();
	string getName();
	long double getBonus();

private:
	int key;
	string name;
	long double bonus;
};

