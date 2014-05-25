#ifndef PROJECT_1_H
#define PROJECT_1_H

#include "util.h"

extern counter bubbleComps;
extern counter bubbleSwaps;
extern counter adapBubbleComps;
extern counter adapBubbleSwaps;
extern counter insertionComps;
extern counter selectionComps;
extern counter selectionSwaps;
extern counter sequencialComps;
extern counter orderedSequencialComps;
extern counter adapSequence1Comps;
extern counter adapSequence2Comps;


void 	bubble_sort					(int ary [], int size);		// function performs Bubble Sort.
void 	bubble_sort					(pair<int*, int>);			// function performs Bubble Sort.
void	adap_bubble_sort			(int ary [], int size);		// function performs Adaptive Bubble Sort.
void	adap_bubble_sort			(pair<int*, int>);			// function performs Adaptive Bubble Sort.
void  	insertion_sort				(int ary [], int size);		// function performs Insertion Sort.
void  	insertion_sort				(pair<int*, int>);			// function performs Insertion Sort.
void 	selection_sort				(int ary [], int size);		// function performs Selection Sort.
void  	selection_sort				(pair<int*, int>);			// function performs Selection Sort.
int		sequencial_search			(int ary [], int, int);		// function perform Sequencial Search.
int		sequencial_search			(pair<int*, int>, int);		// function perform Sequencial Search.
int		ordered_sequencial_search	(int ary [], int, int);		// function perform ordered Sequencial Search.
int		ordered_sequencial_search	(pair<int*, int>, int);		// function perform ordered Sequencial Search.
//int 	adap_sequencial_search1		(int *ary, int size, int);	// function perform apaptive sequencial search 1.
//int 	adap_sequencial_search1		(pair<int*, int> p, int);	// function perform apaptive sequencial search 1.
int 	adap_sequencial_search2		(int ary [], int, int);		// function perform apaptive sequencial search 2.
int 	adap_sequencial_search2		(pair<int*, int>, int);		// function perform apaptive sequencial search 2.

int adap_sequencial_search1_list(list<int> & a, int key);

vector<int> project1getSampleSizes();
vector<SAMPLETYPE> project1getSampleTypes();
vector<counter> * project1CounterVector();

#endif