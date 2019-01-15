/*
Tyson M. Cruz
CST201 - Algorithms and Data Structures
01/13/2019
Professor Brandon Bass

This is my own work.

This application will read data from a file and create a 2-dimensional maze map consisting of 3x3 squares built by using a list.
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
#include <list>
using namespace std;


///////////////////////////////////////////////Node Definition///////////////////////////////////////////////
struct newSquare {
	int xCoordinate;
	int yCoordinate;
	vector<string> square;
};


////////////////////////////////////////////FUNCTION PROTOTYPES//////////////////////////////////////////////
void createMaze(list<newSquare>&);
vector<string> getStartSquare();
vector<string> getFinishSquare();
vector<string> getBlockSquare();
void printSquare(list<newSquare>&);

//Global variables
int xAxis;
int yAxis;

////////////////////////////////////////////MAIN FUNCTION////////////////////////////////////////////////////
int main()
{
	list<newSquare> maze;
	createMaze(maze);
	printSquare(maze);
}

//////////////////////////////////////////FUNCTION DEFINITIONS///////////////////////////////////////////////
//createMaze function creates a maze grid and populates the grid with tiles specified from the text file
void createMaze(list<newSquare>& mazeGrid){

	ifstream fileIn;
	int startX, startY, finishX, finishY, blockX, blockY;

	//Open text file. If file doesn't open, throw error message
	fileIn.open("file.in.txt");
	if (!fileIn) {
		cerr << "Unable to start file.in.txt";
		exit(1);
	}

	//Define grid size and Start/Finish squares with starting values from the file
	fileIn >> yAxis >> xAxis;
	fileIn >> startY >> startX;
	newSquare startSquare;
	startSquare.xCoordinate = startX;
	startSquare.yCoordinate = startY;
	startSquare.square = getStartSquare();
	mazeGrid.push_front(startSquare);

	fileIn >> finishY >> finishX;
	newSquare finishSquare;
	finishSquare.xCoordinate = finishX;
	finishSquare.yCoordinate = finishY;
	finishSquare.square = getFinishSquare();
	mazeGrid.push_front(finishSquare);

	//Stub used to declare the size of the maze grid and coordinates for start/finish
	cout << "Grid size: (" << xAxis << ", " << yAxis << ")." << endl;
	cout << "start: " << startX << ", " << startY << endl;
	cout << "finish: " << finishX << ", " << finishY << endl;

	//"If" statement verifies that the coordinates don't go beyond the grid size
	if (startX > xAxis || finishX > xAxis || startY > yAxis || finishY > yAxis || 
			xAxis < 0 || yAxis < 0 || 
			startX < 0 || startY < 0 || finishX < 0 || finishY < 0){

		cout << "Out of Bounds Error: Check that the start and ";
		cout << "finish coordinates are not beyond of the size of the maze." << endl;
	}

	//Loop to define the blocked squares
	while (!fileIn.eof()) {
		fileIn >> blockY >> blockX;
		newSquare blockSquare;
		blockSquare.xCoordinate = blockX;
		blockSquare.yCoordinate = blockY;
		blockSquare.square = getBlockSquare();
		mazeGrid.push_front(blockSquare);
	}
}

//printSquare function displays the maze grid in the proper format
void printSquare(list<newSquare>& mazeGrid) {

	//Outer loop traverses the y-axis
	for (int y = 0; y <= yAxis; y++) {
		//Inner loop traverses the x-axis. Prints the top line of the 3x3 tiles
		for (int x = 0; x <= xAxis; x++) {
			string printSquare = "...";
			for (list<newSquare>::iterator it = mazeGrid.begin(); it != mazeGrid.end(); it++) {
				if (it->yCoordinate == y && it->xCoordinate == x) {
					printSquare = it->square[0];
				}
			}
			cout << printSquare;
		}
		cout << endl;
		//Inner loop traverses the x-axis. Prints the middle line of the 3x3 tiles
		for (int x = 0; x <= xAxis; x++) {
			string printSquare = "...";
			for (list<newSquare>::iterator it = mazeGrid.begin(); it != mazeGrid.end(); ++it) {
				if (it->yCoordinate == y && it->xCoordinate == x) {
					printSquare = it->square[1];
				}
			}
			cout << printSquare;
		}
		cout << endl;
		//Inner loop traverses the x-axis. Prints the bottom line of the 3x3 tiles
		for (int x = 0; x <= xAxis; x++) {
			string printSquare = "...";
			for (list<newSquare>::iterator it = mazeGrid.begin(); it != mazeGrid.end(); ++it) {
				if (it->yCoordinate == y && it->xCoordinate == x) {
					printSquare = it->square[2];
				}
			}
			cout << printSquare;
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