/*
Tyson M. Cruz
CST201 - Algorithms and Data Structures
12/27/2018
Professor Brandon Bass

This is my own work.

This application will read data from a file and create a 2-dimensional maze map consisting of 3x3 squares.
*/


/////////////////////////////////////Header files and class libraries////////////////////////////////////////
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

//createMaze function creates a maze grid and populates the grid with tiles specified from the text file
vector<vector<vector<string> > > createMaze(void) {

	ifstream fileIn;
	int xAxis, yAxis, startX, startY, finishX, finishY, blockX, blockY;
	vector<string> startTile = getStartSquare();
	vector<string> finishTile = getFinishSquare();
	vector<string> blockTile = getBlockSquare();
	vector<string> openTile = getOpenSquare();
	vector<vector<vector<string> > > mazeGrid;

	//Open text file. If file doesn't open, throw error message
	fileIn.open("file.in.txt");
	if (!fileIn) {
		cerr << "Unable to start file.in.txt";
		exit(1);
	}

	//Initialize variables with starting values from the file
	fileIn >> xAxis >> yAxis;
	fileIn >> startX >> startY;
	fileIn >> finishX >> finishY;

	//Stub used to declare the size of the maze grid
	cout << "Grid size: (" << xAxis << ", " << yAxis << ")." << endl;

	//"If" statement verifies that the coordinates don't go beyond the grid size
	if (startX > xAxis || finishX > xAxis || startY > yAxis || finishY > yAxis || 
			xAxis < 0 || yAxis < 0 || 
			startX < 0 || startY < 0 || finishX < 0 || finishY < 0){

		cout << "Out of Bounds Error: Check that the start and ";
		cout << "finish coordinates are not beyond of the size of the maze." << endl;
	}

	//Resize the grid using the variables initialized from the file
	mazeGrid.resize(yAxis);
	for (int i = 0; i < yAxis; i++) {
		mazeGrid[i].resize(xAxis);
	}

	//Initialize the grid with all "open space" tiles
	for (int i = 0; i < mazeGrid.size(); i++){
		for (int j = 0; j < mazeGrid[i].size(); j++) {
			mazeGrid[i][j] = openTile;
		}
	}

	//Set the coordinates to place the "Start" and "Finish" tiles
	mazeGrid[startX][startY] = startTile;
	mazeGrid[finishX][finishY] = finishTile;

	//Use the rest of the text file as coordinates to place "Blocked" tiles
	while (!fileIn.eof()){
	fileIn >> blockX >> blockY;

		if (blockX < 0 || blockY < 0 || blockX > xAxis || blockY > yAxis) {
			cout << "Out of Bounds Error: coordinates are outside the scope of the grid" << endl;
		}
		mazeGrid[blockY][blockX] = blockTile;
	}

	//End of "createMaze" function, returns the maze to the "main" method
	return mazeGrid;
}

//printSquare function displays the maze grid in the proper format
void printSquare(vector<vector<vector<string> > > &row){

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
}

//creates the tile for the "Start" position
vector<string> getStartSquare(){

	vector<string> newSquare =
		{ "...",
		  ".S.",
		  "..." };

	return newSquare;
}

//creates the tile for the "Finish" position
vector<string> getFinishSquare() {

	vector<string> newSquare =
		{ "...",
		  ".F.",
		  "..." };

	return newSquare;
}

//creates the tile for the "Blocked" positions
vector<string> getBlockSquare() {

	vector<string> newSquare =
		{ "XXX",
		  "XXX",
		  "XXX" };

	return newSquare;
}

//creates the tile for the "Open" positions
vector<string> getOpenSquare() {

	vector<string> newSquare =
		{ "...",
		  "...",
		  "..." };

	return newSquare;
}