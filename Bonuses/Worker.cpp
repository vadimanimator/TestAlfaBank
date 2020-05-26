#include "Worker.h"

Worker::Worker(int key, string name, date startDate, date endDate , vector<int> bonusKeys, long double salary)
{
    this->key = key;
    this->name = name;
    this->startDate = startDate;
    this->endDate = endDate;
    this->bonusKeys = bonusKeys;
    this->salary = salary;
}
Worker::~Worker()
{
    //dtor
}

int Worker::getKey() {
    return this->key;
}
string Worker::getName() {
    return this->name;
}
date Worker::getStartDate() {
    return this->startDate;
}
date Worker::getEndDate() {
    return this->endDate;
}
long double Worker::getSalary() {
    return this->salary;
}

 Report Worker::getReport(vector<Contract> &contracts, date startReportDate, date endReportDate) {
    long double bonus = 0;
    if (this->bonusKeys.empty()) return Report(getKey(), getName(),bonus);
    else {
        for (int i = 0; i < this->bonusKeys.size(); i++) {//проходим по списку бонусов

            if (this->bonusKeys[i] == 1) {//5% суммы договора
                long double temp = 0;
                for (int j = 0; j < contracts.size(); j++) {
                    if (contracts[j].getWorkerKey() == getKey() && contracts[j].getContractDate() >= getStartDate() && (getEndDate().is_not_a_date() || contracts[j].getContractDate() <= getEndDate())) {
                        temp += contracts[j].getContractSum()/20;
                    }
                }
                bonus += temp;
            }
            if (this->bonusKeys[i] == 2) {//10%, но не более 100 000
                long double temp = 0;
                for (int j = 0; j < contracts.size(); j++) {
                    if (contracts[j].getWorkerKey() == getKey() && contracts[j].getContractDate() >= getStartDate() && (getEndDate().is_not_a_date() || contracts[j].getContractDate() <= getEndDate())) {
                        if (contracts[j].getContractSum() / 10 < 100000)
                            temp += contracts[j].getContractSum() / 10;
                        else
                            temp += 100000;
                    }
                }
                bonus += temp;
            }
            if (this->bonusKeys[i] == 3) {//7%, если проработал больше 2 лет на момент заключения договора
                long double temp = 0;
                for (int j = 0; j < contracts.size(); j++) {
                    if (contracts[j].getWorkerKey() == getKey() && contracts[j].getContractDate() >= getStartDate() && (getEndDate().is_not_a_date() || contracts[j].getContractDate() <= getEndDate())) {
                        if (contracts[j].getContractDate() >= getStartDate() + years(2)) {
                            temp += contracts[j].getContractSum() / 100 * 7;
                           
                        }
                    }
                }
                bonus += temp;
            }
           
            if (this->bonusKeys[i] == 4) {//2% оклада за каждый полный месяц
                long double temp = 0;
                date firstDate, endDate;
                //получаем период расчета
                firstDate = getStartDate() >= startReportDate ? getStartDate() : startReportDate;
                endDate = getEndDate() <= endReportDate ? getEndDate() : endReportDate;
                //Проверка
                if (firstDate.day() != 1) {
                    
                        firstDate = firstDate.end_of_month() + days(1);
                }
                while (firstDate <= endDate) {
                    firstDate += months(1);
                    if (firstDate <= endDate)
                    temp += getSalary() / 50;
                }
                            
                 
                bonus += temp;
            }
        }


        return Report(getKey(), getName(), bonus);
    }
}
void Worker::print() {
    
    cout<<left <<setw(8)<< getKey() << " " <<  setw(40) <<getName() << " " << this->salary << endl;
}