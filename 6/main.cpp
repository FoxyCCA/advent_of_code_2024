#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include <windows.h>
#include <vector>
using namespace std;

int sum = 0;

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

/* https://www.geeksforgeeks.org/find-number-of-rectangles-that-can-be-formed-from-a-given-set-of-coordinates/ */
int countRectangles(vector<pair<int, int>>& ob) {
    set<pair<int, int>> points;


    for (int i = 0; i < ob.size(); ++i) {
        points.insert(ob[i]);
    }

    int ans = 0;
    for (int i = 0; i < ob.size(); ++i) {
        for (int j = i + 1; j < ob.size(); ++j) {
            if (ob[i].first != ob[j].first && ob[i].second != ob[j].second) {
                if (points.count({ob[i].first, ob[j].second}) && points.count({ob[j].first, ob[i].second})) {
                    ++ans;
                }
            }
        }
    }
    return ans / 2;
}

void ClearScreen()
{	
  COORD cursorPosition;	    cursorPosition.X = 0;	cursorPosition.Y = 0;
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}

void solution_one(){
	auto file = read_file("input.txt");

	vector<string> map;

	int x = 0;


	string line;

	int xPos = 0, yPos = 0;

	while(getline(file, line)){
		x++;
		map.push_back(line);

		if(line.find('^') != string::npos){
			yPos = line.find('^');
			xPos = x-1;
		}

	}

	char current = '^';


	bool complete = false;
	while(!complete){

		current = map[xPos][yPos];

		switch (current) {
			case '^':
				if (xPos - 1 >= 0){
					if(map[xPos-1][yPos] == '#'){
						map[xPos][yPos] = '>';
						break;
					} else {
						/*if(map[xPos-1][yPos] != 'X'){*/
						/*	sum++;*/
						/*}*/
						map[xPos-1][yPos] = current;
						map[xPos][yPos] = 'X';
						xPos-=1;
					}
				}
				else complete = true;
				break;

			case '>':
				if (yPos + 1 < x){
					if(map[xPos][yPos+1] == '#'){
						map[xPos][yPos] = 'V';
						break;
					} else {
						/*if(map[xPos][yPos+1] != 'X'){*/
						/*	sum++;*/
						/*}*/
						map[xPos][yPos+1] = current;
						map[xPos][yPos] = 'X';
						yPos+=1;
					}
				}
				else complete = true;
				break;

			case 'V':
				if (xPos + 1 < x){
					if(map[xPos+1][yPos] == '#'){
						map[xPos][yPos] = '<';
						break;
					} else {
						/*if(map[xPos+1][yPos] != 'X'){*/
						/*	sum++;*/
						/*}*/
						map[xPos+1][yPos] = current;
						map[xPos][yPos] = 'X';
						xPos+=1;
					}
				}
				else complete = true;
				break;

			case '<':
				if (yPos - 1 >= 0){
					if(map[xPos][yPos-1] == '#'){
						map[xPos][yPos] = '^';
						break;
					} else {
						/*if(map[xPos][yPos-1] != 'X'){*/
						/*	sum++;*/
						/*}*/
						map[xPos][yPos-1] = current;
						map[xPos][yPos] = 'X';
						yPos-=1;
					}
				}
				else complete = true;
				break;
		}


		/*for(auto& col: map){*/
		/*	cout << col << endl;*/
		/*}*/
		/*cout << sum << endl;*/
		/*cout << endl;*/

	}

	for(auto& row: map){
		for(auto& col: row){
			if(col == 'X'){
				sum++;
			}
		}
	}
	/*for(auto& col: map){*/
	/*	cout << col << endl;*/
	/*}*/
	/*cout << map[xPos][yPos] << endl;*/

}

void solution_two(){
	auto file = read_file("input.txt");

	vector<string> map;

	int x = 0;


	string line;

	int xPos = 0, yPos = 0;

	while(getline(file, line)){
		x++;
		map.push_back(line);

		if(line.find('^') != string::npos){
			yPos = line.find('^');
			xPos = x-1;
		}

	}

	char current = '^';

	bool complete = false;
	while(!complete){

		current = map[xPos][yPos];

		switch (current) {
			case '^':
				if (xPos - 1 >= 0){
					if(map[xPos-1][yPos] == '#'){
						map[xPos][yPos+1] = '>';
						map[xPos][yPos] = '+';
						yPos+=1;
						break;
					} else {

						if(( map[xPos-1][yPos] == '|' || map[xPos-1][yPos] == '-' ) && map[xPos-2][yPos] != '#'){
							map[xPos-2][yPos] = current;
							map[xPos-1][yPos] = '+';
							map[xPos][yPos] = '|';
							xPos-=2;
						} else{
							map[xPos-1][yPos] = current;
							map[xPos][yPos] = '|';
							xPos-=1;
						}

					}
				}
				else {
					map[xPos+1][yPos] = '+';
					complete = true;
				}
				break;

			case '>':
				if (yPos + 1 < x){
					if(map[xPos][yPos+1] == '#'){
						map[xPos+1][yPos] = 'V';
						map[xPos][yPos] = '+';
						xPos+=1;
						break;
					} else {

						if(( map[xPos][yPos+1] == '|' || map[xPos][yPos+1] == '-' ) && map[xPos][yPos+2] != '#'){
							map[xPos][yPos+2] = current;
							map[xPos][yPos+1] = '+';
							map[xPos][yPos] = '-';
							yPos+=2;
						} else{
							map[xPos][yPos+1] = current;
							map[xPos][yPos] = '-';
							yPos+=1;
						}
					}
				}
				else {
					map[xPos][yPos-1] = '+';
					complete = true;
				}
				break;

			case 'V':
				if (xPos + 1 < x){
					if(map[xPos+1][yPos] == '#'){
						map[xPos][yPos-1] = '<';
						map[xPos][yPos] = '+';
						yPos-=1;
						break;
					} else {
						/*if(map[xPos+1][yPos] != 'X'){*/
						/*	sum++;*/
						/*}*/

						if(( map[xPos+1][yPos] == '|' || map[xPos+1][yPos] == '-' ) && map[xPos+2][yPos] != '#'){
							map[xPos+2][yPos] = current;
							map[xPos+1][yPos] = '+';
							map[xPos][yPos] = '|';
							xPos+=2;
						} else{
							map[xPos+1][yPos] = current;
							map[xPos][yPos] = '|';
							xPos+=1;
						}
						
					}
				}
				else {
					map[xPos-1][yPos] = '+';
					complete = true;
				}
				break;

			case '<':
				if (yPos - 1 >= 0){
					if(map[xPos][yPos-1] == '#'){
						map[xPos-1][yPos] = '^';
						map[xPos][yPos] = '+';
						xPos-=1;
						break;
					} else {
						/*if(map[xPos][yPos-1] != 'X'){*/
						/*	sum++;*/
						/*}*/

						if(( map[xPos][yPos-1] == '|' || map[xPos][yPos-1] == '-' ) && map[xPos][yPos-2] != '#'){
							map[xPos][yPos-2] = current;
							map[xPos][yPos-1] = '+';
							map[xPos][yPos] = '-';
							yPos-=2;
						} else{
							map[xPos][yPos-1] = current;
							map[xPos][yPos] = '-';
							yPos-=1;
						}
						
					}
				}
				else {
					map[xPos][yPos+1] = '+';
					complete = true;
				}
				break;
		}


		for(auto& col: map){
			cout << col << endl;
		}
		ClearScreen();
	}

	/*cout << points.size() << endl;*/

	vector<pair<int, int>> points;
	for(int i = 0; i< x; i++ ){
		for(int j = 0; j < x; j++){
			if(map[i][j] == '+'){
				points.push_back({i, j});
			}
		}
	}
	cout << countRectangles(points)-1 << endl;
	/*for(auto& col: map){*/
	/*	cout << col << endl;*/
	/*}*/
	/*cout << map[xPos][yPos] << endl;*/

}

void test(){
	auto file = read_file("input.txt");

	vector<string> map;

	int x = 0;
	string line;
	int xPos = 0, yPos = 0;

	while(getline(file, line)){
		x++;
		map.push_back(line);

		if(line.find('^') != string::npos){
			yPos = line.find('^');
			xPos = x-1;
		}

	}

}

int main(int argc, char* argv[]){
	if('1' == *argv[argc-1]) solution_one();
	else					 solution_two();

	cout << sum+1;

	exit(0);
}
