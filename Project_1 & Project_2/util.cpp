#include "util.h"
#include "project_1.h"

void printCountersToCSV(char * filename, vector<counter> * counters, vector<int> sizes, vector<SAMPLETYPE> types, bool printHeader) {
	ofstream myfile;
  	myfile.open (filename, fstream::app);

  	int oneTrial = sizes.size()*types.size();
  	if (printHeader) {
	  	myfile<<",";
	  	for (vector<int>::iterator i = sizes.begin() ; i != sizes.end(); ++i) {
			int size = *i;
			for (vector<SAMPLETYPE>::iterator j = types.begin() ; j != types.end(); ++j) {
				SAMPLETYPE type = *j;
				switch(type) {
					case RANDOM:
						myfile<<"Random ("<<size<<"),";
						break;
					case REVERSE:
						myfile<<"Reverse ("<<size<<"),";
						break;
					case TWENTY_PERCENT:
						myfile<<"Twenty percent sorted ("<<size<<"),";
						break;
					case FIFTY_PERCENT:
						myfile<<"Fifty percent sorted ("<<size<<"),";
						break;
					default:
						cout << "WAT\n";
						break;	
				}
			}
		}
		myfile<<"\n";
	}

	for (vector< counter>::iterator it = counters->begin() ; it != counters->end(); ++it) {
		counter cur = *it;
		int numTrials = cur.size()/oneTrial;
		cout << "numTrials: "<<numTrials<<"\n";
		cout << "curSize: "<<cur.size()<<"\n";
		cout << "oneTrial: "<<oneTrial<<"\n";

		for (int i = 0; i < numTrials;i++ ) {
			myfile << cur.desc()<<",";

			for (int j = 0; j < oneTrial; j ++) {
				myfile <<cur.at(j+oneTrial*i) <<",";
			}
			myfile<<"\n";
		}
		myfile<<"\n";
	}

  	myfile.close();
}

void printTimersToCSV(char * filename, vector<timer> * timers, vector<int> sizes, vector<SAMPLETYPE> types, bool printHeader) {
	ofstream myfile;
  	myfile.open (filename, fstream::app);

  	int oneTrial = sizes.size()*types.size();
  	if (printHeader) {
	  	myfile<<",";
	  	for (vector<int>::iterator i = sizes.begin() ; i != sizes.end(); ++i) {
			int size = *i;
			for (vector<SAMPLETYPE>::iterator j = types.begin() ; j != types.end(); ++j) {
				SAMPLETYPE type = *j;
				switch(type) {
					case RANDOM:
						myfile<<"Random ("<<size<<"),";
						break;
					case REVERSE:
						myfile<<"Reverse ("<<size<<"),";
						break;
					case TWENTY_PERCENT:
						myfile<<"Twenty percent sorted ("<<size<<"),";
						break;
					case FIFTY_PERCENT:
						myfile<<"Fifty percent sorted ("<<size<<"),";
						break;
					default:
						cout << "WAT\n";
						break;	
				}
			}
		}
		myfile<<"\n";
	}

	for (vector< timer>::iterator it = timers->begin() ; it != timers->end(); ++it) {
		timer cur = *it;
		int numTrials = cur.size()/oneTrial;
		for (int i = 0; i < numTrials;i++ ) {
			myfile << cur.desc()<<",";
			for (int j = 0; j < oneTrial; j ++) {
				//i+numTrials*j
				myfile <<cur.at(j+oneTrial*i) <<",";
			}
			myfile<<"\n";
		}
		myfile<<"\n";
	}

  	myfile.close();
}

int leftbiasIndex(int n) {
    srand(clock()*time(NULL));
	return (int)(((float)rand()/RAND_MAX) * ((float)rand()/RAND_MAX) * n );
}

int rightbiasIndex(int n) {
	srand(clock()*time(NULL));
	return (int)((1 - ((float)rand()/RAND_MAX) * ((float)rand()/RAND_MAX)) * n);
}

int * createElementArray(int * elements, int n) {
	int * toSearch = (int *) malloc(n * sizeof(int));
	for (int i = 0; i < n; i++) {
		toSearch[i] = elements[rightbiasIndex(n)];
	}
	return toSearch;
}

void performSearch(int f(pair<int*, int>, int), vector< pair<int*, int> > *samples) {	
	vector< pair<int*, int> > *victim = copySamples(samples); 
	for (vector<pair<int*,int> >::iterator it = victim->begin() ; it != victim->end(); ++it) {
        pair<int *, int> p = *it;
        cout<<"searching size: "<< p.second<<"\n";
        int * toSearch = createElementArray(p.first, p.second);      
        for (int i = 0; i < p.second*5; i++) {
            srand(clock());
            int ret = f(p, toSearch[ rand() % p.second]);
            if  (ret == -1) cout << "NOT FOUND 1\n";
        }
	}
	
	deallocSamples(victim);
}

void performSearch(int f(list<int> &, int), vector< pair<int*, int> > *samples) {
	vector< pair<int*, int> > *victim = copySamples(samples); 
	for (vector<pair<int*,int> >::iterator it = victim->begin() ; it != victim->end(); ++it) {
		pair<int *, int> p = *it;
		cout<<"searching size: "<< p.second<<"\n";
		int * toSearch = createElementArray(p.first, p.second);
		list<int> l = arrayToList(p.first, p.second);
		for (int i = 0; i < p.second*5; i++) {
			srand(clock());
			int ret = f(l, toSearch[ rand() % p.second]);
			if  (ret == -1) cout << "NOT FOUND 1\n";
		}
	}
	deallocSamples(victim);
}

void performSort(void f(pair<int*, int>), vector< pair<int*, int> > *samples) {
	vector< pair<int*, int> > *victim = copySamples(samples); 
	for (vector<pair<int*,int> >::iterator it = victim->begin() ; it != victim->end(); ++it) {
		pair<int *, int> p = *it;
		cout<<"sorting size: "<<p.second<<"\n";
		f(*it);
	}
	deallocSamples(victim);
}

void createRandArray(int *a, int size) {
	for (int i = 0; i < size; i++) {
		a[i] = rand() % 1000000;
	}
}

void createReverseArray(int *a, int size) {
	for (int i = 0; i < size; i++) {
		a[size - i - 1] = i;
	}
}

void createTwentyPercentArray(int *a, int size) {
	int sorted = size/5;

	for (int i = 0; i < size; i++) {
		a[i] = rand() % 1000000; 
	}

	vector<int> used;
	for (int i = 0; i < sorted; i ++) {
		used.push_back(rand() % size);
	}

	sort(used.begin(), used.end());
	int count = 0;
	for (vector<int>::iterator it=used.begin(); it!=used.end(); ++it) {
		a[((int)*it)] = count++;
	}
}

void createFiftyPercentArray(int *a, int size) {
	int sorted = size/2;

	for (int i = 0; i < size; i++) {
		a[i] = rand() % 1000000; 
	}

	vector<int> used;
	for (int i = 0; i < sorted; i ++) {
		used.push_back(rand() % size);
	}

	sort(used.begin(), used.end());
	int count = 0;
	for (vector<int>::iterator it=used.begin(); it!=used.end(); ++it) {
		a[((int)*it)] = count++;
	}
}


vector< pair<int*, int> > * initSamples(vector<int> sizes, vector<SAMPLETYPE> types) {
	vector< pair<int*, int> > * samples = new vector< pair<int*, int> >();
	srand(clock());
	for (vector<int>::iterator i = sizes.begin() ; i != sizes.end(); ++i) {
		int size = *i;
		for (vector<SAMPLETYPE>::iterator j = types.begin() ; j != types.end(); ++j) {
			SAMPLETYPE type = *j;
			int * cur = (int *)malloc(sizeof(int) * size);
			switch(type) {
				case RANDOM:
					createRandArray(cur, size);
					break;
				case REVERSE:
					createReverseArray(cur, size);
					break;
				case TWENTY_PERCENT:
					createTwentyPercentArray(cur, size);
					break;
				case FIFTY_PERCENT:
					createFiftyPercentArray(cur, size);
					break;
				default:
					cout << "WAT\n";
					break;	
			}
			samples->push_back(make_pair(cur, size));
		}
	}
	return samples;
}

vector< pair<int*, int> > * copySamples(vector< pair<int*, int> > * src) {
	vector< pair<int*, int> > *dest = new vector< pair<int*, int> >();
	for (vector<pair<int*,int> >::iterator it = src->begin() ; it != src->end(); ++it) {
		pair<int *, int> p = *it;
		int * ary = p.first;
		int size = p.second;
		int * newAry = (int *)malloc(sizeof(int) * size);
		memcpy(newAry, ary, sizeof(int) * size);
		dest->push_back(make_pair(newAry, size));
	}
	return dest;
}

void deallocSamples(vector< pair<int*, int> > *victim) {
	for (vector<pair<int*,int> >::iterator it = victim->begin() ; it != victim->end(); ++it) {
		pair<int *, int> p = *it;
		int * ary = p.first;
		free(ary);
	}
	delete victim;
}


void printArray(pair<int*, int> p) {
	printArray(p.first, p.second);
}

void printArray(int ary[], int size) {
	for (int i = 0; i < size; i ++) {
		cout << ary[i] << ", ";
	}
	cout << "\n";
}

void printList(list<int> l) {
	for (list<int>::iterator it=l.begin(); it != l.end(); ++it) {
		cout << *it << ", ";
	}
	cout << "\n";
}

void printSamples (vector< pair<int*, int> > * s) {
	for (vector< pair<int*, int> >::iterator it = s->begin() ; it != s->end(); ++it) {
		pair <int*, int> p = *it;
		printArray(p);
	}
}

bool isSorted(int *a, int size) {
	for (int i = 1; i< size; i++){
		if (a[i-1] > a[i]) {
			return false;
		}
	}
	return true;
}

list<int> arrayToList(int * a, int size) {
	list<int> mylist;
	for (int i = 0; i < size; i++) {
		mylist.push_back(a[i]);
	}
	return mylist;
}