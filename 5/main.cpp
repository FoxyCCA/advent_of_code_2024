#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>

#include "../lib/F_Vectors.h"

using namespace std;

int sum1 = 0;
int sum2 = 0;

ifstream read_file(string file_name){
	ifstream file(file_name);

	if(!file.is_open()){
		cerr << "There was an issue opening this file\n";
		exit(1);
	}
	return file;
}

vector<int> split_str(string line, char delimiter){
	vector<int> v;
	if(line.length() == 0) return v;

	for (int pos; (pos = line.find(delimiter)) < line.length();){
		v.push_back(stoi(line.substr(0, pos)));

		line.erase(line.begin(), line.begin()+pos+1);
	}
	v.push_back(stoi(line));
	return v;
}

void sort_by_rule(vector<int>& p, vector<vector<int>>& rules){
	bool wrong = false;
	for(int i = p.size()-1; i > 0; i--){
		auto rule = rules[p[i]];
		for(auto rule_num = rule.begin(); rule_num<rule.end(); rule_num++){

			for(int idn = 0; idn < i; idn++){
				if(p[idn] == *rule_num){
					wrong = true;
					swap(p[idn], p[i]);
				}
			}
		}
		if(i == 1 && wrong){
			i = p.size();
			wrong = false;
		}
		if(i==1 && !wrong) break;
	}
}

void solution(){
	auto file = read_file("input.txt");
	vector<vector<int>> rules(100);
	string line;
	bool switch_to_pages = false;
	int row = 0;

	while (getline(file, line)) {

		if(line.length() == 0) { 
			switch_to_pages = true;
			row = 0;
			continue;
		}
		
		if(switch_to_pages){
			vector<int> p = split_str(line, ',');
			vector<int> p_copy = p;

			sort_by_rule(p_copy, rules);

			if(p!=p_copy){
				sum2+= p_copy[p_copy.size()/2];
			}
			if(p==p_copy){
				sum1+= p[p.size()/2];
			}

		} else {
			vector<int> r = split_str(line, '|');
			rules[r[0]].push_back(r[1]);
		}
		row++;
	}
}

int main(int argc, char* argv[]){
	solution();

	cout << sum1 << endl;
	cout << sum2 << endl;

	exit(0);
}
