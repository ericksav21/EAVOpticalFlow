#ifndef PARAMETER_H
#define PARAMETER_H

#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
#include <string>
#include <cstring>

using namespace std;

class Parameter {
private:
	int argc;
	char **argv;
public:
	Parameter(int argc, char **argv);
	~Parameter();
	void print_help();
	map<string, string> process();
};

#endif