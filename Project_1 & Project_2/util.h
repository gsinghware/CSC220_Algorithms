#ifndef UTIL_H
#define UTIL_H

using namespace std;

#include <stdlib.h>
#include <cstdlib>
#include <time.h>
#include <utility>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
#include <list>

#include "counter.h"
#include "timer.h"

using namespace std;

enum SAMPLETYPE { RANDOM, REVERSE, TWENTY_PERCENT, FIFTY_PERCENT };

void printCountersToCSV(char * filename, vector<counter> * counters, vector<int> sizes, vector<SAMPLETYPE> types, bool printHeader);
void printTimersToCSV(char * filename, vector<timer> * timers, vector<int> sizes, vector<SAMPLETYPE> types, bool printHeader);
vector < pair<int*, int> > * initSamples(vector<int> sizes, vector<SAMPLETYPE> types);
vector< pair<int*, int> > * copySamples(vector< pair<int*, int> > * p);
void deallocSamples(vector< pair<int*, int> > * victim);
void performSort(void f(pair<int*, int>), vector< pair<int*, int> > * samples);
void performSearch(int f(pair<int*, int>, int), vector< pair<int*, int> > * samples);
void performSearch(int f(list<int> &, int), vector< pair<int*, int> > *samples);

void printArray(pair<int*, int> p);
void printArray(int ary[], int size);
void printList(list<int> l);
void printSamples (vector< pair<int*, int> > * s);

void createTwentyPercentArray(int *a, int size);
void createFiftyPercentArray(int *a, int size);
void createRandArray(int *a, int size);
void createReverseArray(int *a, int size);
bool isSorted(int *a, int size);
int leftbiasIndex(int n);
int rightbiasIndex(int n);
int * createElementArray(int * elements, int n);
list<int> arrayToList(int * a, int size);
#endif