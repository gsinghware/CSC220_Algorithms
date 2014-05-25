#ifndef TIMER_H
#define TIMER_H

#include <string>
#include <vector>
#include <iostream>
#include <sys/timeb.h>

using namespace std;

class timer {

public :
	timer(string desc);
	void start();
	void stop();
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
	int startTime;
	int now();
};

#endif