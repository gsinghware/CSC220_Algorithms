#include "counter.h"

counter::counter(string desc) {
	description = desc;
	index = -1;
	runs = new vector<uint64_t>();
}

void counter::increment() {
	runs->at(index)++;
}

void counter::printCurrent() {
	cout << description << ": " << runs->at(index) << "\n";
}

void counter::printAll() {
	cout << description << ":\n";
	for (vector<uint64_t>::iterator it = runs->begin() ; it != runs->end(); ++it) {
		cout << (uint64_t)*it << "\n"; 
	}
}

uint64_t counter::at(int index) {
	return runs->at(index);
}

string counter::desc() {
	return description;
}

int counter::size() {
	return runs->size();
}

void counter::next() {
	runs->push_back(0);
	index++;
}


