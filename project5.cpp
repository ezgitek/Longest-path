/*
Student Name: Ezgi Tekdemir
Student Number: 2014400090
Project Number: 5
Operating System: Virtual Machine
Compile Status: Compiling
Program Status: Working
Notes: 
*/
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int NUM_OF_CITIES;
int NUM_OF_ROADS;
int START; int TARGET;

int* memoization;
pair < vector<int>, vector<int>>* edges;

void importData (char* inputFile){
	ifstream in(inputFile);

	in >> NUM_OF_CITIES >> NUM_OF_ROADS >> START >> TARGET; 

	memoization = new int[NUM_OF_CITIES+1];

	for(int i=0; i<=NUM_OF_CITIES; i++){
		memoization[i] = -1;
	}

	edges = new pair<vector<int>, vector<int>> [NUM_OF_CITIES+1];

	for (int i=0; i<NUM_OF_ROADS; i++){
		int vertex = 0; int dest = 0; int weight = 0;
		in >> dest >> vertex >> weight;
		edges[vertex].first.push_back(dest);
		edges[vertex].second.push_back(weight);
	}
}

int longest_path (int s){
	if (s == START){
		return 0;
	}

	if (memoization[s] != -1) {
		return memoization[s]; 
	}
		
	long max = 0; long current = -1;

	for(unsigned int j=0; j<edges[s].first.size(); j++){

		current = edges[s].second[j] + longest_path(edges[s].first[j]);//weight + recursive 

		if(current > max) {
			max = current; 
		} 

	}

	if(max==0) 
		max = -1e9;

	memoization[s] = max;

	return max;
}

void runAlgorithm(char* outputFile){ 
	long longest = longest_path(TARGET);
	if(longest==-1e9) 
		longest = -1;
	ofstream out (outputFile);
	out << longest;
}

int main(int argc, char *argv[]) {

	importData(argv[1]);
	runAlgorithm(argv[2]);

	return 0;
}
