#include "F_Vectors.h"

void rotate_fliphor(std::vector<std::vector<char>>& v){
	int row = 0;
	int col = 0;

	auto copy = v;

	for(int i = 0; i < v.size(); i++){
		col = 0;
		for(int j = v.size()-1; j >= 0; j--){
			copy[i][j] = v[row][col];
			col++;
		}
		row++;
	}
	v = copy;
}

void rotate_vec90(std::vector<std::vector<char>>& v){
	int row = 0;
	int col = 0;

	auto copy = v;

	for(int i = 0; i < v.size(); i++){
		col = 0;
		for(int j = v.size()-1; j >= 0; j--){
			copy[j][i] = v[row][col];
			col++;
		}
		row++;
	}
	v = copy;
}

void subvector(std::vector<std::vector<char>>& v1, std::vector<std::vector<char>>& v2, int row, int col, int size){
	int row_diff = row - 1;
	int col_diff = col - 1;

	for(int i = 0; i < size; i++){
		col_diff = col - 1;
		for(int j = 0; j < size; j++){
			v2[i][j] = v1[row_diff][col_diff];
			col_diff++;
		}
		row_diff++;
	}
}

void print_2Dvector(std::vector<std::vector<char>>& v){
	for(auto& row: v){
		for(auto& col:row){
			std::cout << col;
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
void print_2Dvector(std::vector<std::vector<int>>& v){
	for(auto& row: v){
		for(auto& col:row){
			std::cout << col;
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
void print_2Dvector(std::vector<std::vector<double>>& v){
	for(auto& row: v){
		for(auto& col:row){
			std::cout << col;
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
