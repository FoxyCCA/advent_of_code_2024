#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <sstream>

using namespace std;

bool scan_word(int i, string word, string text){
	if((i + word.length()) >= text.length()) return false;
	
	for (auto w = word.begin(); w < word.end(); w++) {
		if( *w != text[i]) return false;
		i++;
	}

	return true;
}

ifstream read_file(string file_name){
	ifstream file(file_name);

	if(!file.is_open()){
		cerr << "There was an issue opening this file\n";
		exit(1);
	}

	return file;
}

void solution_one_regex(){
	auto file = read_file("input.txt");

	string line;
	string number;
	int sum = 0;

	regex const re{R"(\bmul\((\d+(?:,\s*\d+)*)\))"};

	while(getline(file,line)){
		smatch match;
		auto words_begin = std::sregex_iterator(line.begin(), line.end(), re);
		auto words_end = std::sregex_iterator();

		for (std::sregex_iterator i = words_begin; i != words_end; ++i)
		{
			std::smatch match = *i;
			std::string match_str = match[1].str();
			stringstream ss(match_str);
			vector<int> v;
			while (getline(ss, number, ',')) { 
				v.push_back(stoi(number));
			}
			sum+= v[0] * v[1];
		}
	}

	cout << sum << endl;
	// solution 173785482
}

void solution_one(){
	auto file = read_file("input.txt");

	string line;
	string numbers;
	int first_num = 0;
	int second_num = 0;
	int sum = 0;

	bool once = true;

	while(getline(file,line)){

		int len = line.length();

		for (int i = 0; i < len; i ++) {
			if(scan_word(i, "mul(", line)) {

				for(int j = i+4; j < len; j ++){
					if(isdigit(line[j]) || line[j] == ','){
						if(line[j] == ',' && once){
							first_num = stoi(numbers);
							numbers.clear();
							once = false;

						} else numbers.push_back(line[j]);
						
						if(!once){
							once = true;
							continue;
						}

					} else if (line[j] == ')') {
						second_num = stoi(numbers);
						sum += (first_num * second_num);
						numbers.clear();
						break;

					} else break;
				}
				numbers.clear();
				once = true;
			}
		}
	}
	cout << sum << endl;
}


void solution_two(){
	auto file = read_file("input.txt");

	string line;
	string numbers;
	int first_num = 0;
	int second_num = 0;
	int sum = 0;

	bool once = true;
	bool enabled = true;

	while(getline(file,line)){

		int len = line.length();

		for (int i = 0; i < len; i ++) {

			if(scan_word(i, "do()", line)) enabled = true;
			if(scan_word(i, "don't()", line)) enabled = false;


			if(scan_word(i, "mul(", line) && enabled){
				for(int j = i+4; j < len; j ++){
					if(isdigit(line[j]) || line[j] == ','){
						if(line[j] == ',' && once){
							first_num = stoi(numbers);
							numbers.clear();
							once = false;
						} else numbers.push_back(line[j]);
						
						if(!once){
							once = true;
							continue;
						}

					} else if (line[j] == ')') {
						second_num = stoi(numbers);
						sum += (first_num * second_num);
						numbers.clear();
						break;
					} else break;
				}
				numbers.clear();
				once = true;
			}
		}
	}
	cout << sum << endl;
}

int main(){
	/*solution_one();*/
	solution_two();
	exit(0);
}
