#include "Date.h"

Date::Date() {
	//ctor
}

Date::~Date() {
	//dtor
}
date Date::getDate(const string &date) {
	bool b = true;
	short dots = 0;
	int day = NULL, month = NULL, year = NULL;
	string temp = "";
	for (unsigned int i = 0; i < date.size(); i++) {
		if (date[i] != '.') {
			temp += date[i];
			if (date[i] < '0' && date[i] > '9')
				b = false;
		}
		if (date[i] == '.') {
			if (dots == 0) {
				try {
					if (stoi(temp) < 1 || stoi(temp) > 31)
						b = false;
					day = stoi(temp);
					dots++;
					temp = "";
				}
				catch (std::invalid_argument) {
					b = false;
				}
			}
			if (dots == 1) {
				try {
					if (stoi(temp) < 1 || stoi(temp) > 12)
						b = false;
					month = stoi(temp);
					dots++;
					temp = "";
				}
				catch (std::invalid_argument) {
					b = false;
				}
			}
		}
	}

	try {
		if (stoi(temp) < 1400 || stoi(temp) > 9999)
			b = false;
		year = stoi(temp);
		dots++;
		temp = "";
	}
	catch (std::invalid_argument) {
		b = false;
	}
	
		boost::gregorian::date tmp(year, month, day);



		return tmp;

	

}
bool Date::checkDate(const string &date) {
	bool b = true;
	short dots = 0;
	int day = NULL, month = NULL, year = NULL;
	string temp = "";
	for (unsigned int i = 0; i < date.size(); i++) {
		if (date[i] != '.') {
			temp += date[i];
			if (date[i] < '0' && date[i] > '9')
				b = false;
		}
		if (date[i] == '.') {
			if (dots == 0) {
				try {
					if (stoi(temp) < 1 || stoi(temp) > 31)
						b = false;
					day = stoi(temp);
					dots++;
					temp = "";
				}
				catch (std::invalid_argument) {
					b = false;
				}
			}
			if (dots == 1) {
				try {
					if (stoi(temp) < 1 || stoi(temp) > 12)
						b = false;
					month = stoi(temp);
					dots++;
					temp = "";
				}
				catch (std::invalid_argument) {
					b = false;
				}
			}
		}
	}

	try {
		if (stoi(temp) < 1400 || stoi(temp) > 9999)
			b = false;
		year = stoi(temp);
		dots++;
		temp = "";
	}
	catch (std::invalid_argument) {
		b = false;
	}
	if (day != NULL && month != NULL && year != NULL) {
		return true;
	}
	else
		return false;

}
string Date::toString(const date &d) {
	std::ostringstream ss;
	
	date_facet* us_facet = new date_facet();
	ss.imbue(std::locale(std::locale::classic(), us_facet));
	string s = "";
	us_facet->format("%mm.%dd.%Y");
	ss << d;
	s = ss.str();
	return s;
}