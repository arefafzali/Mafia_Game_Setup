#ifndef HEADERS_H_
#define HEADERS_H_

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;

int cToi(char n);

int sToi(string name);

bool check_strings(string fname,string sname);

struct instanceOfRoles{
	int count=0;
	string name;
};

#endif