#ifndef PARSER_H
#define PARSER_H
#include "Worker.h"
#include "Contract.h"
#include "Date.h"
#include <vector>
#include <fstream>


class Parser {
public:
	Parser(string, string);
	~Parser();
	
	vector <Worker> getWorkers();
	 vector <Worker> getWorkers(date, date);
	 vector <Contract> getContracts();
protected:

private:
	string workersFile, contractsFile;
};


#endif
