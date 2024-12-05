#include <vector>
#include <iostream>
#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED
void rotate_fliphor(std::vector<std::vector<char>>& v);
void rotate_fliphor(std::vector<std::vector<int>>& v);

void rotate_vec90(std::vector<std::vector<char>>& v);
void rotate_vec90(std::vector<std::vector<int>>& v);

void subvector(std::vector<std::vector<char>>& v1,
			   std::vector<std::vector<char>>& v2,
			   int row, int col, int size);
void subvector(std::vector<std::vector<int>>& v1,
			   std::vector<std::vector<int>>& v2,
			   int row, int col, int size);

void print_2Dvector(std::vector<std::vector<char>>& v);
void print_2Dvector(std::vector<std::vector<int>>& v);
void print_2Dvector(std::vector<std::vector<double>>& v);
#endif
