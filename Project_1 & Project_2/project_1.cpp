#include "project_1.h"

counter bubbleComps("bubble comparisons");
counter bubbleSwaps("bubble exchanges");
counter adapBubbleComps("adap. bubble sort comparisons");
counter adapBubbleSwaps("adap. bubble sort exchanges");
counter insertionComps("insertion sort comparisons");
counter selectionComps("selection sort comparisons");
counter selectionSwaps("selection sort exchanges");
counter sequencialComps("sequencial search comparisons");
counter orderedSequencialComps("ordered sequencial search comparisons");
counter adapSequence1Comps("adap_sequencial_search1 comparisons");
counter adapSequence2Comps("adap_sequencial_search2 comparisons");

vector<int> project1getSampleSizes() {
	vector<int> project_1_sizes;
	project_1_sizes.push_back(500);
	project_1_sizes.push_back(2500);
	project_1_sizes.push_back(12500);
	project_1_sizes.push_back(62500);
	return project_1_sizes;
}

vector<SAMPLETYPE> project1getSampleTypes() {
	vector<SAMPLETYPE> project_1_sample_types;
	project_1_sample_types.push_back(RANDOM);
	project_1_sample_types.push_back(REVERSE);
	project_1_sample_types.push_back(TWENTY_PERCENT);
	return project_1_sample_types;
}

vector<counter> * project1CounterVector() {
	vector<counter> * counters = new vector<counter>();

	counters->push_back(bubbleComps);
	counters->push_back(bubbleSwaps);
	counters->push_back(adapBubbleComps);
	counters->push_back(adapBubbleSwaps);
	counters->push_back(selectionComps);
	counters->push_back(selectionSwaps);
	counters->push_back(insertionComps);

	counters->push_back(sequencialComps);
	counters->push_back(orderedSequencialComps);
	counters->push_back(adapSequence1Comps);
	counters->push_back(adapSequence2Comps);

	return counters;
}

void bubble_sort(pair<int *, int> p) {
	bubble_sort(p.first, p.second);
}

// bubble sort important steps are comparisons and exchanges.
void bubble_sort(int ary [], int size)
{
	bubbleComps.next();
	bubbleSwaps.next();
	int i, j, temp;
	for (i = 1; i <= size; i++) {
		for (j = 0; j < size - 1; j++) {
			bubbleComps.increment();
			if (ary[j] > ary[j+1]) {
				bubbleSwaps.increment();
				temp = ary[j];
				ary[j] = ary[j+1];
				ary[j+1] = temp;
			}
		}
	}
}

void adap_bubble_sort(pair<int *, int> p) {
	adap_bubble_sort(p.first, p.second);
}

void adap_bubble_sort(int ary [], int size) {
	adapBubbleComps.next();
	adapBubbleSwaps.next();
	
	int i, j, temp;
	bool flag = true;
	for (i = 1; (i <= size) && flag; i++) {
		flag = false;
		for (j = 0; j < size - 1; j++) {
			adapBubbleComps.increment();
			if (ary[j] > ary[j+1]) {
				adapBubbleSwaps.increment();
				temp = ary[j];
				ary[j] = ary[j+1];
				ary[j+1] = temp;
				flag = true;						
			}
		}
	}
}

void insertion_sort(pair<int *, int> p) {
	insertion_sort(p.first, p.second);
}

void insertion_sort(int ary [], int size) {
	insertionComps.next();
	int i, j, key;
	for (i = 1; i < size; i++) {
		key = ary[i];
		j = i - 1;
		while (j >= 0 && ary[j] > key) {
			insertionComps.increment();
			ary[j + 1] = ary[j];
			j = j - 1;
		}
		ary[j + 1] = key;
	}
}

void selection_sort(pair<int *, int> p) {
	selection_sort(p.first, p.second);
}

void selection_sort(int ary [], int size) {
	selectionComps.next();
	selectionSwaps.next();
	int i, j, min;
	for (i = 0; i < size - 1; i++) {				// loop goes from 0 - (n-1)
		min = i; 									// index of the minimum 
		for (j = i + 1; j < size; j++) {
			selectionComps.increment();
			if (ary[j] < ary[min]) {
				min = j;
			}
		}
		if (min != i) {
			selectionSwaps.increment();
			swap(ary[min],ary[i]);
		}
	}
}

int sequencial_search(pair<int*, int>p, int key) {
	return sequencial_search(p.first, p.second, key);
}

int sequencial_search(int ary [], int size, int key) {
	sequencialComps.next();
	for (int i = 0; i < size; i++) {
		sequencialComps.increment();
		if (ary[i] == key) return i;
	}
	return -1;
}

int ordered_sequencial_search(pair<int*, int>p, int key) {
	return ordered_sequencial_search(p.first, p.second, key);
}

int ordered_sequencial_search(int ary [], int size, int key) {
	orderedSequencialComps.next();
	for (int i = 0; i < size; i++) {
		orderedSequencialComps.increment();
		if (ary[i] == key) return i;
		else if (ary[i] > key) return -1;
	}
	return -1;
}

/*
int adap_sequencial_search1(pair<int*, int>p, int key) {
	return adap_sequencial_search1(p.first, p.second, key);
}*/

int adap_sequencial_search1_list(list<int> & a, int key) {
	adapSequence1Comps.next();
	int i = 0;
	for (list<int>::iterator it=a.begin(); it != a.end(); ++it) {
    	adapSequence1Comps.increment();
    	i++;
    	if (*it == key) {
    		a.push_front(*it);
    		a.erase(it);
    		return i;
    	}
	}
	return -1;
}

int adap_sequencial_search2(pair<int*, int>p, int key) {
	return adap_sequencial_search2(p.first, p.second, key);
}

int adap_sequencial_search2(int ary [], int size, int key) {
	adapSequence2Comps.next();
	for (int i = 0; i < size; i++) {
		adapSequence2Comps.increment();
		if (ary[i] == key) {
			if (i != 0) swap(ary[i-1], ary[i]);
			return i;
		}
	}
	return -1;
}
