#include "project_2.h"

counter merge_sort_Comps("merge_sort comparisons");
counter adap_merge_sort_Comps("adap_merge_sort comparisons");
counter adap20_merge_sort_Comps("adap20_merge_sort comparisons");
counter heap_sort_Comps("heap_sort comparisons");
counter heap_sort_Swaps("heap_sort exchanges");
counter quicksort1_Comps("quick_sort1 comparisons");
counter quicksort1_Swaps("quick_sort1 exchanges");
counter quickToInsertSortTime_Comps("quickToInsertSortTime comparisons");
counter quickToInsertSortTime_Swaps("quickToInsertSortTime exchanges");
counter quickMedianOfThreeSort_Comps("quickMedianOfThreeSort comparisons");
counter quickMedianOfThreeSort_Swaps("quickMedianOfThreeSort exchanges");
counter quickMedianOfThreeToInsertionSort_Comps("quickMedianOfThreeToInsertionSort comparisons");
counter quickMedianOfThreeToInsertionSort_Swaps("quickMedianOfThreeToInsertionSort exchanges");
counter shellSort_Comps("shellSort comparisons");
counter shellSort_Swaps("shellSort exchanges");

timer mergeSortTime("merge sort time");
timer adapMergeSortTime("adap merge sort time");
timer adap20SortTime("adap20 sort time");
timer heapSortTime("heap sort time");
timer shellSortTimer("shellSort time");
timer quickSort1Time("vanilla quicksort time");
timer quickToInsertSortTime("quick to insertion sort time");
timer quickMedianOfThreeSortTime("quick median of three sort time");
timer quickMedianOfThreeToInsertionSortTime("quick median of three to insertion sort time");

vector<int> project2getSampleSizes() {
	vector<int> project_2_sizes;
	project_2_sizes.push_back(2500);
	project_2_sizes.push_back(12500);
	project_2_sizes.push_back(62500);
	project_2_sizes.push_back(31250);
	return project_2_sizes;
}

vector<SAMPLETYPE> project2getSampleTypes() {
	vector<SAMPLETYPE> project_2_sample_types;
	project_2_sample_types.push_back(RANDOM);
	project_2_sample_types.push_back(TWENTY_PERCENT);
	project_2_sample_types.push_back(FIFTY_PERCENT);
	return project_2_sample_types;
}

vector<counter> * project2CounterVector() {
	vector<counter> * counters = new vector<counter>();

	counters->push_back(merge_sort_Comps);
	counters->push_back(adap_merge_sort_Comps);
	counters->push_back(adap20_merge_sort_Comps);

	counters->push_back(heap_sort_Comps);
	counters->push_back(heap_sort_Swaps);

	counters->push_back(quicksort1_Comps);
	counters->push_back(quicksort1_Swaps);
	counters->push_back(quickToInsertSortTime_Swaps);
	counters->push_back(quickToInsertSortTime_Comps);
	counters->push_back(quickMedianOfThreeSort_Comps);
	counters->push_back(quickMedianOfThreeSort_Swaps);
	counters->push_back(quickMedianOfThreeToInsertionSort_Comps);
	counters->push_back(quickMedianOfThreeToInsertionSort_Swaps);

	counters->push_back(shellSort_Comps);
	counters->push_back(shellSort_Swaps);

	return counters;
} 

vector<timer> * project2TimerVector() {
	vector<timer> * timers = new vector<timer>();

	timers->push_back(mergeSortTime);
	timers->push_back(adapMergeSortTime);
	timers->push_back(adap20SortTime);
	timers->push_back(heapSortTime);
	timers->push_back(quickSort1Time);
	timers->push_back(quickToInsertSortTime);
	return timers;
} 

void merge_sort(pair<int*, int> p) {
	merge_sort_Comps.next();
	mergeSortTime.next();
	mergeSortTime.start();
	merge_sort(p.first, p.second, 0, p.second - 1);
	mergeSortTime.stop();
}

void merge_sort(int ary [], int size, int low, int high) {
	if (low < high) {
		int middle = (low + high)/2;			// divide: get the middle element
		merge_sort(ary, size, low, middle);		// merge_sort the left part of the array
		merge_sort(ary, size, middle + 1, high);// merge_sort the right part of the array
		merge(ary, size, low, middle, high);	// combine the sub arrays
	}
}

void merge (int ary [], int size, int low, int middle, int high) {
	
	int temp[size];
	for (int i = low; i <= high; i++) {
		temp[i] = ary[i];
	}

	int i = low;
	int j = middle + 1;
	int k = low;

	while ( i <= middle && j <= high) {
		if (temp[i] <= temp[j]) {
			ary[k] = temp[i];
			i++;
		} else {
			ary[k] = temp[j];
			j++;
		}
		k++;
		merge_sort_Comps.increment();
	}

	while (i <= middle) {
		ary[k] = temp[i];
		k++;
		i++;
	}
}

void adap_merge_sort(pair<int*, int> p) {
	adap_merge_sort_Comps.next();
	adapMergeSortTime.next();
	adapMergeSortTime.start();
	adap_merge_sort(p.first, p.second, 0, p.second - 1);
	adapMergeSortTime.start();
}

void adap_merge_sort(int ary [], int size, int low, int high) {
	if (high <= low + 100 - 1) {
		merge_to_insertion(ary, high - low + 1);
		return;
	} else if (low < high) {
		int middle = (low + high)/2;			// divide: get the middle element
		adap_merge_sort(ary, size, low, middle);		// merge_sort the left part of the array
		adap_merge_sort(ary, size, middle + 1, high);// merge_sort the right part of the array
		adap_merge(ary, size, low, middle, high);	// combine the sub arrays
	}
}

void adap_merge (int ary [], int size, int low, int middle, int high) {
	
	int temp[size];
	for (int i = low; i <= high; i++) {
		temp[i] = ary[i];
	}

	int i = low;
	int j = middle + 1;
	int k = low;

	while ( i <= middle && j <= high) {
		if (temp[i] <= temp[j]) {
			ary[k] = temp[i];
			i++;
		} else {
			ary[k] = temp[j];
			j++;
		}
		k++;
		adap_merge_sort_Comps.increment();
	}

	while (i <= middle) {
		ary[k] = temp[i];
		k++;
		i++;
	}
}

void merge_to_insertion(int ary [], int size) {
	int i, j, key;
	for (i = 1; i < size; i++) {
		key = ary[i];
		j = i - 1;
		while (j >= 0 && ary[j] > key) {
			adap_merge_sort_Comps.increment();
			ary[j + 1] = ary[j];
			j = j - 1;
		}
		ary[j + 1] = key;
	}
}

void adap20_merge_sort(pair<int*, int> p) {
	adap20_merge_sort_Comps.next();
	adap20SortTime.next();
	adap20SortTime.start();
	adap20_merge_sort(p.first, p.second, 0, p.second - 1);
	adap20SortTime.stop();
}

void adap20_merge_sort(int ary [], int size, int low, int high) {
	if (high <= low + 20 - 1) {
		merge_to_insertion(ary, high - low + 1);
		return;
	} else if (low < high) {
		int middle = (low + high)/2;					// divide: get the middle element
		adap20_merge_sort(ary, size, low, middle);		// merge_sort the left part of the array
		adap20_merge_sort(ary, size, middle + 1, high);	// merge_sort the right part of the array
		adap20_merge(ary, size, low, middle, high);		// combine the sub arrays
	}
}

void adap20_merge (int ary [], int size, int low, int middle, int high) {
	
	int temp[size];
	for (int i = low; i <= high; i++) {
		temp[i] = ary[i];
	}

	int i = low;
	int j = middle + 1;
	int k = low;

	while ( i <= middle && j <= high) {
		if (temp[i] <= temp[j]) {
			ary[k] = temp[i];
			i++;
		} else {
			ary[k] = temp[j];
			j++;
		}
		k++;
		adap20_merge_sort_Comps.increment();
	}

	while (i <= middle) {
		ary[k] = temp[i];
		k++;
		i++;
	}
}

void merge20_to_insertion(int ary [], int size) {
	int i, j, key;
	for (i = 1; i < size; i++) {
		key = ary[i];
		j = i - 1;
		while (j >= 0 && ary[j] > key) {
			adap20_merge_sort_Comps.increment();
			ary[j + 1] = ary[j];
			j = j - 1;
		}
		ary[j + 1] = key;
	}
}

// Heapsort
void heap_sort(pair<int*, int> p) {
	heap_sort_Comps.next();
	heap_sort_Swaps.next();
	heapSortTime.next();
	heapSortTime.start();

	heap_sort(p.first, p.second);
	
	heapSortTime.stop();
}

void heap_sort(int ary [], int size) {
	build_maxHeap(ary, size);
	for (int i = size - 1; i >= 1; i--) {
		heap_sort_Swaps.increment();
		swap(ary[0], ary[i]);
		size -= 1;
		max_heapify(ary, 0, size);
	}
}

void build_maxHeap(int ary [], int size) {
	for(int i = size/2; i >= 0; i--)
        max_heapify(ary, i, size);
}

void max_heapify(int ary [], int i, int size) {
	
	int leftChild_index = 2 * i + 1;
	int rightChild_index = 2 * i + 2;

	int largest_index;

	heap_sort_Comps.increment();
	if (leftChild_index < size && ary[leftChild_index] > ary[i])
		largest_index = leftChild_index;
	else
		largest_index = i;

	heap_sort_Comps.increment();
	if (rightChild_index < size && ary[rightChild_index] > ary[largest_index])
		largest_index = rightChild_index;
	
	if (largest_index != i) {
		heap_sort_Swaps.increment();
		swap(ary[i], ary[largest_index]);
		max_heapify(ary, largest_index, size);
	}
}

void quickSort(pair<int*, int> p) {
	quickSort1Time.next();
	quickSort1Time.start();
	quicksort1_Comps.next();
	quicksort1_Swaps.next();
	quickSort(p.first, 0, p.second-1);
	quickSort1Time.stop();
}

int partition(int* a, int p, int r, int value)
{
    int pivot = value;
    if (value == -1) pivot = a[r];

    while ( p < r )
    {
    	quicksort1_Comps.increment();
        while ( a[p] < pivot ) p++;
        quicksort1_Comps.increment();
        while ( a[r] > pivot ) r--;
        quicksort1_Comps.increment();
        if ( a[p] == a[r] ) p++;

        if ( p < r ) {
        	quicksort1_Swaps.increment();
            swap(a[p], a[r]);
        } else {
        	break;
        }
    }
    return r;
}

void quickSort( int *a, int first, int last ) {
    if(first < last) {
        int pivotElement = partition(a, first, last, -1);
        quickSort(a, first, pivotElement-1);
        quickSort(a, pivotElement+1, last);
    }
}

void quickToInsertSort(pair<int*, int> p) {
	quickToInsertSortTime.next();
	quickToInsertSortTime.start();

	quickToInsertSortTime_Comps.next();
	quickToInsertSortTime_Swaps.next();

	quickToInsertSort( p.first, 0, p.second-1);
	
	quickToInsertSortTime.stop();
}

void insertion_sort(int ary [], int first, int last) {
	int i, j, key;
	for (i = first + 1; i <= last; i++) {
		key = ary[i];
		j = i - 1;
		while (j >= first && ary[j] > key) {
			quickToInsertSortTime_Comps.increment();
			ary[j + 1] = ary[j];
			j = j - 1;
		}
		ary[j + 1] = key;
	}
}

int partition2(int* a, int p, int r, int value)
{
    int pivot = value;
    if (value == -1) pivot = a[r];

    while ( p < r )
    {
    	quickToInsertSortTime_Comps.increment();
        while ( a[p] < pivot ) p++;
        quickToInsertSortTime_Comps.increment();
        while ( a[r] > pivot ) r--;
        quickToInsertSortTime_Comps.increment();
        if ( a[p] == a[r] ) p++;

        if ( p < r ) {
        	quickToInsertSortTime_Swaps.increment();
            swap(a[p], a[r]);
        } else {
        	break;
        }
    }
    return r;
}

void quickToInsertSort( int *a, int first, int last ) {
 	if (last - first < 50) {
 		insertion_sort(a, first, last);
 	} else if(first < last) {
        int pivotElement = partition2(a, first, last, -1);
        quickToInsertSort(a, first, pivotElement-1);
        quickToInsertSort(a, pivotElement+1, last);
    }
}

int partition3(int* a, int p, int r, int value)
{
    int pivot = value;
    if (value == -1) pivot = a[r];

    while ( p < r )
    {
    	quickMedianOfThreeSort_Comps.increment();
        while ( a[p] < pivot ) p++;
        quickMedianOfThreeSort_Comps.increment();
        while ( a[r] > pivot ) r--;
        quickMedianOfThreeSort_Comps.increment();
        if ( a[p] == a[r] ) p++;

        if ( p < r ) {
        	quickMedianOfThreeSort_Swaps.increment();
            swap(a[p], a[r]);
        } else {
        	break;
        }
    }
    return r;
}

//TODO: make random, not just first/last/middle
int medianOfThree(int * a, int first, int last) {
    return max(min(a[first],a[last]), min(max(a[first],a[last]), a[(first + last)/2]));
}

void quickMedianOfThreeSort( pair<int*, int> p ) {
	quickMedianOfThreeSort_Comps.next();
	quickMedianOfThreeSort_Swaps.next();
	
	quickMedianOfThreeSortTime.next();
	quickMedianOfThreeSortTime.start();
	
	quickMedianOfThreeSort(p.first, 0, p.second-1);
	
	quickMedianOfThreeSortTime.stop();
}

void quickMedianOfThreeSort( int *a, int first, int last ) {
    if(first < last) {
    	int value = medianOfThree(a, first, last);
        int pivotElement = partition3(a, first, last, value);
        quickMedianOfThreeSort(a, first, pivotElement-1);
        quickMedianOfThreeSort(a, pivotElement+1, last);
    }
}

void insertion_sort2(int ary [], int first, int last) {
	int i, j, key;
	for (i = first + 1; i <= last; i++) {
		key = ary[i];
		j = i - 1;
		while (j >= first && ary[j] > key) {
			quickMedianOfThreeToInsertionSort_Comps.increment();
			ary[j + 1] = ary[j];
			j = j - 1;
		}
		ary[j + 1] = key;
	}
}

int partition4(int* a, int p, int r, int value)
{
    int pivot = value;
    if (value == -1) pivot = a[r];

    while ( p < r )
    {
    	quickMedianOfThreeToInsertionSort_Comps.increment();
        while ( a[p] < pivot ) p++;
        quickMedianOfThreeToInsertionSort_Comps.increment();
        while ( a[r] > pivot ) r--;
        quickMedianOfThreeToInsertionSort_Comps.increment();
        if ( a[p] == a[r] ) p++;

        if ( p < r ) {
        	quickMedianOfThreeToInsertionSort_Swaps.increment();
            swap(a[p], a[r]);
        } else {
        	break;
        }
    }
    return r;
}

void quickMedianOfThreeToInsertionSort( pair<int*, int> p ) {
	quickMedianOfThreeToInsertionSort_Comps.next();
	quickMedianOfThreeToInsertionSort_Swaps.next();

	quickMedianOfThreeToInsertionSortTime.next();
	quickMedianOfThreeToInsertionSortTime.start();
	
	quickMedianOfThreeToInsertionSort(p.first, 0, p.second-1);
	
	quickMedianOfThreeToInsertionSortTime.stop();
}

void quickMedianOfThreeToInsertionSort( int *a, int first, int last ) {
    if (last - first < 50) {
 		insertion_sort2(a, first, last);
 	} else if(first < last) {
    	int value = medianOfThree(a, first, last);
        int pivotElement = partition4(a, first, last, value);
        quickMedianOfThreeToInsertionSort(a, first, pivotElement-1);
        quickMedianOfThreeToInsertionSort(a, pivotElement+1, last);
    }
}

void shellSort(pair<int*, int> p) {
	shellSortTimer.start();
	shellSortTimer.next();

	shellSort_Comps.next();
	shellSort_Swaps.next();

	shellSort(p.first, p.second);
	shellSortTimer.stop();
}

/*
void shellSort(int * a, int size) {
    int n = size;
    for (int incr = n/2; incr > 0; incr /= 2) {
        for (int i = incr; i < n; i++) {
        	shellSort_Comps.increment();
            for (int j = i - incr; j >= 0 && a[j] > a[j+incr]; j -= incr) {
                swap(a[j],a[j+incr]);
                shellSort_Swaps.increment();
            }
        }
    }
}
*/

void shellSort(int * a, int size) {
    int inner, outer, temp;
    int interval = 2;

    while (interval <= size/2) {
    	interval = interval * 2 - 1;
    }
    
	while (interval > 0) {
		for (outer = interval; outer < size; outer++) {
			temp = a[outer];
			inner = outer;
			shellSort_Comps.increment();
			while (inner > interval - 1 && a[inner-interval] >= temp) {
				a[inner] = a[inner - outer];
				inner -= interval;
			}
			if (inner != outer)
			{
				a[inner] = temp;
				shellSort_Swaps.increment();
			}
		}
		interval = (interval)/1024;
	}
}

