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
			cout << left << setw(8) << "��� " << setw(40) << "��� " << "�����" << endl;
			for (int i = 0; i < reports.size(); i++) {
				cout << left << setw(8) << reports[i].getKey() <<" " << setw(40) << reports[i].getName() << " " << reports[i].getBonus() << endl;
			}
		}
		if (type == "file") {
			if (name.empty())
				name = "�����.csv";
			ofstream outFile;
			outFile.open(name);
			if (outFile.is_open()) {
				outFile << fixed;
				outFile.precision(2);
				outFile<< "���" <<";"<< "���" <<";"<< "�����" << endl;
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
		cout << "������� ������� ��������� ����" << endl;
		return false;
	}
	if (Date::checkDate(lastDate)) {
		endReportDate = Date::getDate(lastDate);
	}
	else {
		cout << "������� ������� �������� ����" << endl;
		return false;
	}

	if (endReportDate < startReportDate) {
		cout << "��������� ���� ������ ��������" << endl;
		return false;
	}

	toLowString(outType);

	if (outType != "file" && outType != "console" && outType != "����" && outType != "�������") {
		cout << "�������� ��� ������" << endl;
		return false;
	}
	else {
		if (outType == "file" || outType == "����")
			outType = "file";
		else outType = "console";
	}
		return true;
}



int main(int argc, char** argv) {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);


	//�������� ����������
	if (argc != 4) {

		cout << "��������� ���� ���������� (��� ������, ��������� ����, �������� ����)" << endl;
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
	//�������� ���������� �� ������������

	while (!Init()) {
		
		cout << "��������� ���� ���������� (��� ������, ��������� ����, �������� ����)" << endl;
		
		cin >> outType >> firstDate >> lastDate;
		system("cls");
	}
	
	
	Parser p("����������.csv", "��������.csv");
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
