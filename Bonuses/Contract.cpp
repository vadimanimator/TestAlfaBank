#include "Contract.h"
Contract::Contract(int key, int workerKey, date contractDate, long double contractSum){
	this->key = key;
	this->workerKey = workerKey;
	this->contractDate = contractDate;
	this->contractSum = contractSum;
}
int Contract::getWorkerKey() {
	return this->workerKey;
}
date Contract::getContractDate() {
	return this->contractDate;
}
long double Contract::getContractSum() {
	return this->contractSum;
}