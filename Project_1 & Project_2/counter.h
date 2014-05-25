#ifndef COUNTER_H
#define COUNTER_H

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class counter {

public :
	counter(string desc);
	void increment();
	void printCurrent();
	void printAll();
	uint64_t at(int index);
	string desc();
	int size();
	void next();

private:
	string description;
	vector<uint64_t> * runs;
	int index;
};

#endif