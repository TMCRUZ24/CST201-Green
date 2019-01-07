/*
Tyson M. Cruz
CST201 - Algorithms and Data Structures
12/27/2018
Professor Brandon Bass

This is my own work.

This application will read data from a file and create a 2-dimensional maze map consisting of 3x3 squares.
*/

#include "pch.h"
#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <algorithm>
#include <functional>
#include <string>
#include <iterator>
using namespace std;

////////////////////////////////////////////FUNCTION PROTOTYPES//////////////////////////////////////////////
vector<vector<vector<string> > > createMaze(void);
void printSquare(vector<vector<vector<string> > > &newSquare);
vector<string> getStartSquare();
vector<string> getFinishSquare();
vector<string> getBlockSquare();
vector<string> getOpenSquare();

////////////////////////////////////////////MAIN FUNCTION////////////////////////////////////////////////////
int main()
{
	vector<vector<vector<string> > > row = createMaze();
	printSquare(row);
}

//////////////////////////////////////////FUNCTION DEFINITIONS///////////////////////////////////////////////

vector<vector<vector<string> > > createMaze(void) {

	ifstream fileIn;
	int xAxis, yAxis, startX, startY, finishX, finishY, blockX, blockY;
	vector<string> startTile = getStartSquare();
	vector<string> finishTile = getFinishSquare();
	vector<string> blockTile = getBlockSquare();
	vector<string> openTile = getOpenSquare();
	vector<vector<vector<string> > > mazeGrid;

	//numOfColumns = 200;
	//numOfRows = 200;

	fileIn.open("file.in.txt");
	if (!fileIn) {
		cerr << "Unable to start file.in.txt";
		exit(1);
	}

	fileIn >> xAxis >> yAxis;
	fileIn >> startX >> startY;
	fileIn >> finishX >> finishY;

	cout << "Grid size: (" << xAxis << ", " << yAxis << ")." << endl;

	if (startX > xAxis || finishX > xAxis || startY > yAxis || finishY > yAxis || 
			xAxis < 0 || yAxis < 0 || 
			startX < 0 || startY < 0 || finishX < 0 || finishY < 0){
		cout << "Number of columns: " << xAxis << endl;
		cout << "Number of rows: " << yAxis << endl;
		cout << "Start X/T :" << startX << "  " << startY << endl;
		cout << "Finish X/Y :" << finishX << "  " << finishY << "  " << endl;

		cout << "Out of Bounds Error: Check that the start and ";
		cout << "finish coordinates are not beyond of the size of the maze." << endl;
	}

	mazeGrid.resize(yAxis);
	cout << "Number of rows set: " << yAxis << endl;

	for (int i = 0; i < yAxis; i++) {
		mazeGrid[i].resize(xAxis);
	}
	cout << "Number of columns set: " << xAxis << endl;

	for (int i = 0; i < mazeGrid.size(); i++){
		for (int j = 0; j < mazeGrid[i].size(); j++) {
			mazeGrid[i][j] = openTile;
		}
	}
	cout << "Open tiles initialized." << endl;

	mazeGrid[startX][startY] = startTile;
	cout << "Start tile set: (" << startX << ", " << startY << ")." << endl;
	mazeGrid[finishX][finishY] = finishTile;
	cout << "Finish tile set: (" << finishX << ", " << finishY << ")." << endl;

	cout << endl;
	cout << "Grid size: (" << xAxis << ", " << yAxis << ")." << endl;

	do{
	fileIn >> blockX >> blockY;

		cout << "Block (" << blockX << " , " << blockY << ") set." << endl;

		if (blockX < 0 || blockY < 0 || blockX > xAxis || blockY > yAxis) {
			cout << "Out of Bounds Error: coordinates are outside the scope of the grid" << endl;
		}
		mazeGrid[blockY][blockX] = blockTile;
		
	} while (!fileIn.eof());


	cout << "Blocked tiles initialized." << endl;

	return mazeGrid;
}


void printSquare(vector<vector<vector<string> > > &row){

			//cout << row.size() << endl;
			//cout << row[0].size() << endl;
			//cout << row[0][0][0] << row[0][1][0] << row[0][2][0] << row[0][3][0] << endl; until the end of xAxis
			//cout << row[1][0][1] << row[1][1][1] << row[1][2][1] << row[1][3][1] << endl;
			//cout << row[2][0][2] << row[2][1][2] << row[2][2][2] << row[2][3][2] << endl;
			//keep going down until the end of yAxis

			for (int i = 0; i < row.size(); i++) {
				for (int j = 0; j < row[i].size(); j++) {
					cout << row[i][j][0];
				}
				cout << endl;
				for (int j = 0; j < row[i].size(); j++) {
					cout << row[i][j][1];
				}
				cout << endl;
				for (int j = 0; j < row[i].size(); j++) {
					cout << row[i][j][2];
				}
				cout << endl;
			}
			/*cout << endl;
			for (int i = 0; i < row.size(); i++) {
				for (int j = 0; j < row[i].size(); j++) {
					cout << row[i][j][1];
				}
				cout << endl;
			}					
			cout << endl;
			for (int i = 0; i < row.size(); i++) {
				for (int j = 0; j < row[i].size(); j++) {
					cout << row[i][j][2];
				}
				cout << endl;
			}
			cout << endl;
			*/	
}

vector<string> getStartSquare(){

	vector<string> newSquare =
		{ "...",
		  ".S.",
		  "..." };

	return newSquare;
}

vector<string> getFinishSquare() {

	vector<string> newSquare =
		{ "...",
		  ".F.",
		  "..." };

	return newSquare;
}

vector<string> getBlockSquare() {

	vector<string> newSquare =
		{ "XXX",
		  "XXX",
		  "XXX" };

	return newSquare;
}

vector<string> getOpenSquare() {

	vector<string> newSquare =
		{ "...",
		  "...",
		  "..." };

	return newSquare;
}