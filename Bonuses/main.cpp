#include <iostream>
#include <clocale>
#include <cstring>
#include "Date.h"
#include <Windows.h>
#include "boost/date_time/gregorian/gregorian.hpp"
#include <fstream>
#include "Parser.h"
#include "Worker.h"
#include "Report.h"

using namespace std;
using namespace boost::gregorian;

date startReportDate, endReportDate;
string outType, firstDate, lastDate;
void toLowString(string& s) {
	for (unsigned int i = 0; i < s.size(); i++) {
		
		if (s[i] >= 65 && s[i] <= 90 || s[i] >= -64 && s[i] <= -33)
			s[i] += (char)(32);
		if (s[i] == -88)
			s[i] = (char)(-72);

	}

}

void printReports(vector <Report> &reports, string &type, string name) {
	if (!reports.empty()) {
		if (type == "console") {
			cout << fixed;
			cout.precision(2);
			cout << left << setw(8) << "Код " << setw(40) << "Имя " << "Бонус" << endl;
			for (int i = 0; i < reports.size(); i++) {
				cout << left << setw(8) << reports[i].getKey() <<" " << setw(40) << reports[i].getName() << " " << reports[i].getBonus() << endl;
			}
		}
		if (type == "file") {
			if (name.empty())
				name = "Отчет.csv";
			ofstream outFile;
			outFile.open(name);
			if (outFile.is_open()) {
				outFile << fixed;
				outFile.precision(2);
				outFile<< "Код" <<";"<< "Имя" <<";"<< "Бонус" << endl;
				for (int i = 0; i < reports.size(); i++) {
					outFile << reports[i].getKey() << ";" << reports[i].getName() << ";" << reports[i].getBonus() << endl;
				}
			}
			outFile.close();
		}
	}
}

bool Init() {
	if (Date::checkDate(firstDate)) {
		startReportDate = Date::getDate(firstDate);
	}
	else {
		cout << "Неверно введена начальная дата" << endl;
		return false;
	}
	if (Date::checkDate(lastDate)) {
		endReportDate = Date::getDate(lastDate);
	}
	else {
		cout << "Неверно введена конечная дата" << endl;
		return false;
	}

	if (endReportDate < startReportDate) {
		cout << "Начальная дата больше конечной" << endl;
		return false;
	}

	toLowString(outType);

	if (outType != "file" && outType != "console" && outType != "файл" && outType != "консоль") {
		cout << "Неверный тип вывода" << endl;
		return false;
	}
	else {
		if (outType == "file" || outType == "файл")
			outType = "file";
		else outType = "console";
	}
		return true;
}



int main(int argc, char** argv) {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);


	//Проверка параметров
	if (argc != 4) {

		cout << "Повторите ввод параметров (тип вывода, начальная дата, конечная дата)" << endl;
		cin >> outType >> firstDate >> lastDate;
		system("cls");
	}
	else {
		for (int i = 0; i < argc; i++) {
			cout << i + 1 << ". " << argv[i] << endl;
		}
		outType = argv[1];
		firstDate = argv[2];
		lastDate = argv[3];
	}
	//Проверка параметров на корректность

	while (!Init()) {
		
		cout << "Повторите ввод параметров (тип вывода, начальная дата, конечная дата)" << endl;
		
		cin >> outType >> firstDate >> lastDate;
		system("cls");
	}
	
	
	Parser p("Сотрудники.csv", "Договора.csv");
	vector<Worker> workers = p.getWorkers(startReportDate, endReportDate);
	vector<Contract> contracts = p.getContracts();
	vector<Report> reports;
	for (int i = 0; i < workers.size(); i++) {
		reports.push_back(workers[i].getReport(contracts, startReportDate, endReportDate));
	}
	printReports(reports, outType, firstDate + "-" + lastDate +".csv");
	system("pause");
	return 0;
}
