#include "timer.h"

timer::timer(string desc) {
	description = desc;
	index = -1;
	runs = new vector<uint64_t>();
}

int timer::now() {
	timeb tb;
    ftime(&tb);
    return tb.millitm + (tb.time & 0xfffff) * 1000;
}

void timer::start() {
    startTime = now();
}

void timer::stop() {
	runs->at(index) = now() - startTime;
}

void timer::printCurrent() {
	cout << description << ": " << runs->at(index) << "\n";
}

void timer::printAll() {
	cout << description << ":\n";
	for (vector<uint64_t>::iterator it = runs->begin() ; it != runs->end(); ++it) {
		cout << (uint64_t)*it << "\n"; 
	}
}

uint64_t timer::at(int index) {
	return runs->at(index);
}

string timer::desc() {
	return description;
}

int timer::size() {
	return runs->size();
}

void timer::next() {
	runs->push_back(0);
	index++;
}
