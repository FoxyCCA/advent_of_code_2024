#include <cstdlib>
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

ifstream read_file(string file_name){
	ifstream file(file_name);

	if(!file.is_open()){
		cerr << "There was an issue opening this file\n";
		exit(1);
	}

	return file;
}

int num_of_spaces(string text){
	int spaces = 0;
	for (int i = 0; i < text.size(); i++) {
		if(text[i] == ' ') ++spaces;
	}

	return spaces;
}

void vec_printer(vector<int>& v){
	for (auto numbers : v) {
		cout << numbers << " ";
	}
	cout << endl;

}

void solution_one(){

	auto file = read_file("input.txt");

	string line;
	string number;
	bool increasing = true;
	bool correct = true;

	int difference = 0;
	
	int sum = 0;


	while(getline(file,line)){
		stringstream ss(line);
		vector<int> report;

		while(ss >> number)
			report.push_back(stoi(number));
		
		if(report[0] > report[report.size()-1]) increasing = false;
		else increasing = true;

		int prev_number = report[0];
		correct = true;

		for(int i = 1; i < report.size(); i++){
			difference = report[i] - prev_number;

			if(difference == 0 ||
				(increasing  && ( difference > 3  || difference <= -1 )) ||
				(!increasing && ( difference < -3 || difference >=1 )))
				correct = false;

			if(i == report.size() - 1 && correct) sum++;
			
			prev_number = report[i];
		}
	}
	cout << sum << endl;

	file.close();
}

bool checker(bool increasing, int difference){
	if(difference == 0 ||
		(increasing  && ( difference > 3  || difference <= -1 )) ||
		(!increasing && ( difference < -3 || difference >=1 ))){
		return true;
	}
	return false;
}

void solution_two(){

	auto file = read_file("input.txt");

	string line;
	string number;
	bool increasing = true;
	bool correct = true;

	int difference = 0;
	int hl_difference = 0;

	int sum = 0;
	int error_val = 0;

	while(getline(file,line)){
		stringstream ss(line);
		vector<int> report;

		while(ss >> number)
			report.push_back(stoi(number));

		int len = report.size();

		if(report[0] > report[len-1]) increasing = false;
		else increasing = true;

		int prev_number = report[0];
		correct = true;

		
		error_val = 0;

		vector<int> filtered;
		filtered.push_back(report[0]);
		vec_printer(report);
		for(int i = 1; i < len; i++){
			difference = report[i] - prev_number;

			if(checker(increasing, difference)){
				error_val++;
				cout << "found error";
			}

			prev_number = report[i];

			if(error_val == 1){
				error_val++;
				filtered.pop_back();
			}
			filtered.push_back(report[i]);
		}
		vec_printer(filtered);

		prev_number = filtered[0];
		for(int i = 1; i < filtered.size(); i++){
			difference = filtered[i] - prev_number;

			if(difference == 0 ||
				(increasing  && ( difference > 3  || difference <= -1 )) ||
				(!increasing && ( difference < -3 || difference >=1 )))
				correct = false;

			if(i == report.size() - 1 && correct) { sum++; cout << "^ correct " << endl; }
			prev_number = filtered[i];
		}
	}
	cout << sum << endl;

	file.close();
}

int main(){

	/*solution_one();*/
	solution_two();

	exit(0);
}
