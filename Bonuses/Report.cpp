#include "Report.h"
Report::Report(int key, string name, long double bonus) {
	this->key = key;
	this->name = name;
	this->bonus = bonus;
}
int Report::getKey() {
	return this->key;
}
string Report::getName() {
	return this->name;
}
long double Report::getBonus() {
	return this->bonus;
}