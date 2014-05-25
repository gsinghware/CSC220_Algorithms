#include "util.h"
#include "project_1.h"
#include "project_2.h"
#include <assert.h>
#include <list>

void project_1();
void project_2();
void testSort(void f(int *, int), int size);
char project_1_filename[] = "project_1.csv";
char project_2_filename[] = "project_2.csv";

int main() {
	//project_1();
	project_2();
}

void project_1() {
	int runs = 1;
	int range = 1000000; //range of random numers, one million
	for (int i = 0; i<runs; i++) {
		vector < pair<int*, int> > * samples = initSamples(project1getSampleSizes(), project1getSampleTypes());
        
        //performSearch(sequencial_search, samples);
        //performSearch(adap_sequencial_search1_list, samples);
        //performSearch(adap_sequencial_search2, samples);
        /*
        performSort(bubble_sort ,samples);
        performSort(adap_bubble_sort ,samples);
        performSort(insertion_sort ,samples);
        performSort(selection_sort ,samples);
		*/
		deallocSamples(samples);
	}

	printCountersToCSV(project_1_filename, project1CounterVector(), project1getSampleSizes(), project1getSampleTypes(), true);
}

void project_2() {
	int runs = 1;
	int range = 10000000; //range of random numers, ten million
	for (int i = 0; i<runs; i++) {
		vector < pair<int*, int> > * samples = initSamples(project2getSampleSizes(), project2getSampleTypes());
		
		/*performSort(merge_sort, samples);
		performSort(adap_merge_sort, samples);		// 100 keys to insertion sort
		performSort(adap20_merge_sort, samples);	// 20 keys to insertion sort
		
		performSort(heap_sort, samples);

		performSort(quickSort, samples);
		performSort(quickToInsertSort, samples);
		performSort(quickMedianOfThreeSort, samples);
		performSort(quickMedianOfThreeToInsertionSort,samples);
		*/
		performSort(shellSort, samples);

		deallocSamples(samples);
	}

	printCountersToCSV(project_2_filename, project2CounterVector(), project2getSampleSizes(), project2getSampleTypes(), true);
	printTimersToCSV(project_2_filename, project2TimerVector(), project2getSampleSizes(), project2getSampleTypes(), false);

}

void testSort(void f(int *, int), int size) {
	int * a = (int *) malloc(size * sizeof(int));
	srand(clock());
	createRandArray(a, size);
	cout << "testing sort...\n";
	f(a, size);
	assert(isSorted(a, size));
	cout << "passed.\n";
}