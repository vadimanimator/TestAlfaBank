#include "Parser.h"

Parser::Parser(string workers, string contracts) {
	this->workersFile = workers;
	this->contractsFile = contracts;
}
Parser::~Parser() {
	
}
vector <Worker> Parser::getWorkers() {
	string line;
	vector <Worker> workers;


	ifstream file(this->workersFile);
	if (file.is_open()) {
		getline(file, line);//заголовки
		while (getline(file, line)) {
			//обработка строки
			int key = NULL;
			string name = "";
			date startDate, endDate;
			vector <int> bonusKeys;
			long int salary = 0;

			int dots = 0;
			string temp = "";
			for (unsigned int i = 0; i < line.size(); i++) {

				if (line[i] != ';') {
					temp += line[i];
				}

				if (line[i] == ';') {
					if (dots == 0) {//код сотрудника
						try {
							key = stoi(temp);
						}
						catch (invalid_argument) {

						}
					}
					if (dots == 1) {//имя
						name = temp;

					}
					if (dots == 2) {//дата приема
						if (!temp.empty())
							if (Date::checkDate(temp))
								startDate = Date::getDate(temp);

					}
					if (dots == 3) {//дата увольнения
						if (!temp.empty())
							if (Date::checkDate(temp))
								endDate = Date::getDate(temp);

					}
					if (dots == 4) {//коды бонусов
						if (!temp.empty()) {
							string temp2 = "";
							for (int j = 0; j < temp.size(); j++) {
								if (temp[j] != ',') {
									temp2 += temp[j];
								}
								if (temp[j] == ',') {
									try {
										int k = stoi(temp2);
										bonusKeys.push_back(k);
										temp2 = "";
									}
									catch (invalid_argument) {}
								}
							}
							if (!temp2.empty()) {
								try {
									int k = stoi(temp2);
									bonusKeys.push_back(k);
								}
								catch (invalid_argument) {}
							}

						}

					}
					dots++;
					temp = "";
				}
			}
			if (!temp.empty()) {//оклад
				try {
					salary = stoi(temp);
				}
				catch (invalid_argument) {}
			}
			temp = "";

			if (key != NULL && startDate.is_not_a_date() == false && dots == 5) {

				workers.push_back(Worker(key, name, startDate, endDate, bonusKeys, salary));
			}

		}
	}
	file.close();
	return workers;
}
vector <Worker> Parser::getWorkers(date start_date, date end_date) {
	string line;
	vector <Worker> workers;

	
	ifstream file(this->workersFile);
	if (file.is_open()) {
		getline(file, line);//заголовки
		while (getline(file, line)) {
			//обработка строки
			int key = NULL;
			string name = "";
			date startDate, endDate;
			vector <int> bonusKeys;
			long int salary = 0;

			int dots = 0;
			string temp = "";
			for (unsigned int i = 0; i < line.size(); i++) {

				if (line[i] != ';') {
					temp += line[i];
				}

				if (line[i] == ';') {
					if (dots == 0) {//код сотрудника
						try {
							key = stoi(temp);
						}
						catch (invalid_argument) {
							
						}
					}
					if (dots == 1) {//имя
						name = temp;
						
					}
					if (dots == 2 ) {//дата приема
						if(!temp.empty())
							if (Date::checkDate(temp))
						startDate = Date::getDate(temp);
						
					}
					if (dots == 3) {//дата увольнения
						if (!temp.empty())
							if(Date::checkDate(temp))
							endDate = Date::getDate(temp);
						
					}
					if (dots == 4) {//коды бонусов
						if (!temp.empty()) {
							string temp2 = "";
							for (int j = 0; j < temp.size(); j++) {
								if (temp[j] != ',') {
									temp2 += temp[j];
								}
								if (temp[j] == ',') {
									try {
										int k = stoi(temp2);
										bonusKeys.push_back(k);
										temp2 = "";
									}
									catch (invalid_argument) {}
								}
							}
							if (!temp2.empty()) {
								try {
									int k = stoi(temp2);
									bonusKeys.push_back(k);
								}
								catch (invalid_argument) {}
							}

						}
						
					}
					dots++;
					temp = "";
				}
			}
			if (!temp.empty()) {//оклад
				try {
					salary = stoi(temp);
				}
				catch (invalid_argument) {}
			}
			temp = "";
			
			if (key != NULL && dots == 5 && (!startDate.is_not_a_date() && startDate <= end_date) && (endDate.is_not_a_date() || endDate>=start_date) ) {
				
				workers.push_back(Worker(key, name, startDate, endDate, bonusKeys, salary));
			}
			
		}
	}
	file.close();
	return workers;
 }
vector <Contract> Parser::getContracts() {
	string line;
	vector <Contract> contracts;


	ifstream file(this->contractsFile);
	if (file.is_open()) {
		getline(file, line);//заголовки
		while (getline(file, line)) {
			//обработка строки
			int key = NULL;
			int workerKey = NULL;
			date contractDate;
			long double contractSum = 0;

			int dots = 0;
			string temp = "";
			for (unsigned int i = 0; i < line.size(); i++) {

				if (line[i] != ';') {
					temp += line[i];
				}

				if (line[i] == ';') {
					if (dots == 0) {//код договора
						try {
							key = stoi(temp);
						}
						catch (invalid_argument) {}
					}
					if (dots == 1) {//код сотрудника
						try {
							workerKey = stoi(temp);
						}
						catch (invalid_argument) {}
					}
					if (dots == 2) {//дата договора
						if (!temp.empty())
							if (Date::checkDate(temp))
							contractDate = Date::getDate(temp);

					}
					
					dots++;
					temp = "";
				}
			}
			if (!temp.empty()) {//сумма договора
				try {
					contractSum = stoi(temp);
				}
				catch (invalid_argument) {}
			}
			temp = "";

			if (key != NULL && workerKey != NULL && contractDate.is_not_a_date() == false && dots == 3) {

				contracts.push_back(Contract(key, workerKey, contractDate, contractSum));
			}

		}
	}
	file.close();
	return contracts;
 }