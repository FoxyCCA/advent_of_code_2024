#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "../Quick_Sort.h"

using namespace std;

void solution_one(vector<int> left, vector<int> right, int line_number){
	quick_sort(left, 0, line_number-1);
	quick_sort(right, 0, line_number-1);

	int sum= 0;
	for (int i = 0; i < line_number; i++) {
		cout << left[i] << " - " << right[i] << " = " << abs(left[i] - right[i]) << endl; 
		sum+= abs(left[i] - right[i]);
	}

	cout << sum;
}

void solution_two(vector<int> left, vector<int> right, int line_number){

	int sum = 0;

	for (int i = 0; i < line_number; i++) {
		int count = 0;

		for (auto right_number : right) 
			if(left[i] == right_number)
				count++;

		sum += left[i] * count;
	}

	cout << sum;
}

int get_line_number(ifstream& file){
	string line;
	int line_number = 0;

	while(getline(file, line)){
		++line_number;
	}

	file.clear();
	file.seekg(0);
	return line_number;
}

ifstream read_file(string file_name){
	ifstream file(file_name);

	if(!file.is_open()){
		cerr << "There was an issue opening this file\n";
		exit(1);
	}

	return file;
}

int main(){
	ifstream file = read_file("input.txt");

	string line;
	int line_number = get_line_number(file);

	vector<int> left(line_number);
	vector<int> right(line_number);

	stringstream ss(line);
	string word;
	int index = 0;

	while(getline(file, line)){
		stringstream ss(line);

		ss >> word;
		left[index] = stoi(word);

		ss >> word;
		right[index] = stoi(word);

		++index;
	}

	/*solution_one(left, right, line_number);*/
	solution_two(left, right, line_number);

	file.close();
	exit(0);
}
