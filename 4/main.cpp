#include <cstdlib>
#include <fstream>
#include <string>

#include "../F_Vectors.h"

using namespace std;

int sum = 0;

int scan_vector(vector<vector<char>>& v, string word, int vec_size ){

	bool top_boundry;
	bool top_right_boundry;
	bool right_boundry;
	bool bottom_right_boundry;
	bool bottom_boundry;

	for(int row = 0; row < vec_size; row++){
		for (int col = 0; col < vec_size; col++) {

			int row_diff = ( word.length()-row )-1;

			top_boundry = row_diff <= 0;
			right_boundry = (col + ( word.length()-1 ) < vec_size);
			bottom_boundry = (row + ( word.length()-1 ) < vec_size);
			top_right_boundry = (top_boundry && right_boundry);
			bottom_right_boundry = (bottom_boundry && right_boundry);

			if(top_right_boundry)
				if(
					v[row][col]     == word[0] &&
					v[row-1][col+1] == word[1] &&
					v[row-2][col+2] == word[2] &&
					v[row-3][col+3] == word[3]
				)
				{
					sum++;
				}

			if(right_boundry)
				if(
					v[row][col]   == word[0] &&
					v[row][col+1] == word[1] &&
					v[row][col+2] == word[2] &&
					v[row][col+3] == word[3]
				)
				{
					sum++;
				}

			if(bottom_right_boundry)
				if(
					v[row][col]     == word[0] &&
					v[row+1][col+1] == word[1] &&
					v[row+2][col+2] == word[2] &&
					v[row+3][col+3] == word[3]
				)
				{
					sum++;
				}

			if(bottom_boundry)
				if(
					v[row][col]   == word[0] &&
					v[row+1][col] == word[1] &&
					v[row+2][col] == word[2] &&
					v[row+3][col] == word[3]
				)
				{
					sum++;
				}
		}
	}

	return sum;
}

ifstream read_file(string file_name){
	ifstream file(file_name);

	if(!file.is_open()){
		cerr << "There was an issue opening this file\n";
		exit(1);
	}
	return file;
}

void get_line_numbers(ifstream& file, int& x, int& y){
	string line;

	while(getline(file, line)){
		y++;
		for(static bool first = true;first;first=false){
			for (auto letter = line.begin(); letter < line.end(); letter++){
				x++;
				if(*letter == '\n') break;
			}
		}
	}

	file.clear();
	file.seekg(0);
}

// M.S
// .A.
// M.S

void find_mas(vector<vector<char>>& v, int vec_size){
	vector<vector<char>> r(3, vector<char>(3));
	for(int row = 0; row < vec_size; row++){
		for (int col = 0; col < vec_size; col++) {
			int row_diff = row - 1;
			int col_diff = col - 1;

			if(
				v[row][col] == 'A' &&
				row_diff >= 0 && col_diff >= 0 &&
				row + 1 < vec_size && col + 1 < vec_size ){

				subvector(v, r, row, col, 3);

				for(int i = 0; i < 4; i++){
					if(
						r[0][0] == 'M' &&
						r[2][0] == 'M' &&
						r[0][2] == 'S' &&
						r[2][2] == 'S') {
						sum++;
						break;
					}
					rotate_vec90(r);
				}
			}
		}
	}
}

void solution_one(){
	auto file = read_file("input.txt");

	string line;

	int j = 0;
	int x = 0;
	int y = 0;

	get_line_numbers(file, x, y);

	vector<vector<char>> v(x, vector<char>(y));

	while(getline(file, line)){
		for (int i = 0; i < line.length(); i++)
			v[j][i] = line[i];
		j++;
	}

	scan_vector(v, "XMAS", x);
	scan_vector(v, "SAMX", x);
}

void solution_two(){
	auto file = read_file("input.txt");
	string line;

	int j = 0;
	int x = 0;
	int y = 0;

	get_line_numbers(file, x, y);

	vector<vector<char>> v(x, vector<char>(y));

	while(getline(file, line)){
		for (int i = 0; i < line.length(); i++)
			v[j][i] = line[i];
		j++;
	}

	find_mas(v, x);
}

int main(int argc, char* argv[]){
	if('1' == *argv[argc-1]) solution_one();
	else					 solution_two();

	cout << sum;

	exit(0);
}
