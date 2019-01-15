// Maze.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Author: Tim James
// Course: CST-201
// Date: 1/14/19
// Professor: Bass
// Description: Maze program - Displays a maze to the console based on input from user. Writes a maze to a file based on user input.
// Program was designed by Tim James and inspired by professor Brandon Bass' code.

#include "pch.h"
#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
#include <sstream>
#include <list>
#include "Maze.h"

using namespace std;

// Declare variables for maze
// Start row and start column
int startRow;
int startCol;

// Row size and column size
int rowSize;
int colSize;

// Wall Row and column
int wallRow;
int wallCol;

// End row and column
int endRow;
int endCol;

// Checks for input error from file for start, end, and size input
int CheckStartData() {
	if (startRow < 0 || startRow > rowSize || colSize < 0 ||
		rowSize < 0 || startCol < 0 || startCol > colSize ||
		endCol < 0 || endCol > colSize || endRow < 0 || endRow > rowSize) {
		cout << "Error!" << " File contents invalid." << endl
			<< "*** Check start, end, and size input data. ***" << endl;

		return 1;
	}
}

// Checks for input error from file for wall input
int CheckFileIn() {
	if (wallCol < 0 || wallCol > colSize || wallRow < 0 || wallRow > rowSize) {
		cout << "Error!" << " File contents invalid." << endl
			<< endl << "*** Check wall input data. ***" << endl;

		return 1;
	}
}

class Group {

	// Declaring variables to be used
	protected: char contArray[3][3]; // used for default constructor to be loaded

	protected: int x_Location; // x location
	protected: int y_Location; // y location
	
	// Start, end, and blocked booleans 
	protected: bool start;
	protected: bool end;
	protected: bool blocked;

	// Creates constructor of blank 3x3 group
	public: Group() {

		// Fills the contArray with the default start character '.'
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				
				contArray[i][j] = '.';
			}
		}

		start = false;
		end = false;
		blocked = false;
				
		x_Location = 0;
		y_Location = 0;
	}

	// overloaded constructor that accepts a char to add to Group (index 1,1)
	public:	Group(char brand) {

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				// Checks to see if a wall exists and assigns 'X'
				if (brand == 'X' || brand == 'x') { // Converts to all Caps

					// Fills the contArray with the wall char
					contArray[i][j] = 'X'; 

					// Setting blocked to true
					blocked = true; 
				}
				// if no wall assign '.'
				else { 

					// Fills contArray with default char if not a wall
					contArray[i][j] = '.'; 
				}
			}
		}
		
		// Start position assignment
		if (brand == 'S' || brand == 's') { // Converts to all Caps

			// Sets Start position for contArray coordinates
			contArray[1][1] = 'S'; 

			start = true; 
		}
		// End possition assignment
		else if (brand == 'E' || brand == 'e') { // Converts to all Caps

			// Sets End position for contArray coordinates
			contArray[1][1] = 'E'; 

			end = true; 
		}

		x_Location = 0;
		y_Location = 0;
	}

	// Returns values
	char ReturnBrand(int row, int col) {

		return contArray[row][col];
	}

	// Sets the Brand 
	public:	void SetBrand(char brand) {

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				// Checks to see if a wall exists and assigns 'X'
				if (brand == 'X' || brand == 'x') { // Converts to all Caps

					// Fills the contArray with the wall char
					contArray[i][j] = 'X';

					// Setting blocked to true
					blocked = true;
				}
				// if no wall assign '.'
				else { 

					// Fills contArray with default char if not a wall
					contArray[i][j] = '.';
				}
			}
		}
		// Start position assignment
		if (brand == 'S' || brand == 's') { // Converts to all Caps

			// Sets Start position for contArray coordinates
			contArray[1][1] = 'S';

			start = true;
		}
		// End possition assignment
		else if (brand == 'E' || brand == 'e') { // Converts to all Caps

			// Sets End position for contArray coordinates
			contArray[1][1] = 'E';

			end = true;
		}

		x_Location = 0;
		y_Location = 0;
	}
};

// Writes the maze to a file
void WriteMaze(list<list<Group>> mazeBucket, int rowSize, int colSize) {

	// Declaring iterators
	list<list<Group>>::iterator it_R = mazeBucket.begin();
	list<Group>::iterator it_C = it_R->begin();

	// Declares new ofstream variable
	ofstream fileOut;

	// Opens a file to be written to 
	fileOut.open("C:\\Users\\mrtim\\Documents\\GCU\\CST-201\\WEEK 1\\Maze project 1\\fileOut.txt");

	// Used for Header Columns
	char header[] = { 'A', 'B', 'C', 'D', 'E', 'F', 
		'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 
		'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 
		'Y', 'Z' };

	cout << "   "; // used for spacing between headers

	// Header Letter spacing
	for (int i = 0; i < colSize; i++) {

			fileOut << "     " << header[i] << "";
	}

	// Formating
	fileOut << endl;

	// Row headers and loads the array with the maze data
	for (int i = 0; i < rowSize; i++) {
		for (int m = 0; m < 3; m++) {

			// Row number added to left header column
			if (m == 1) {
				if (i < 10) { 

					fileOut << i << "  "; // spacing for formating
				}
				else { 

					fileOut << i << " ";  // alternate spacing for formating
				}
			}
			else { 
				
				fileOut << "   "; 
			}

			for (int j = 0; j < colSize; j++) { // determines the amount of columns
				for (int n = 0; n < 3; n++) { // used for the loading of a Group object
					it_R = mazeBucket.begin(); // the iterator to select the row list
					for (int o = 0; o < i; o++) it_R++; // cycles through the row lists
					it_C = it_R->begin(); // sets the column iterator to the begining of the row list 
					for (int p = 0; p < j; p++) it_C++; // cycles through the column list 
					fileOut << it_C->ReturnBrand(m, n) << " "; // loads the group object at it_C location with appropriate brand and prints to file
				}
			}
			fileOut << endl; // adds a new line for next set of data
		}
	}
	fileOut.close(); // closes output file stream
}

// Prints the maze graphically to the console
void showMaze(list<list<Group>> mazeBucket, int rowSize, int colSize) {

	// Declaring iterators
	list<list<Group>>::iterator it_R = mazeBucket.begin();
	list<Group>::iterator it_C = it_R->begin();

	// Used for Header Columns
	char header[] = { 'A', 'B', 'C', 'D', 'E', 'F',
		'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
		'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
		'Y', 'Z' };

	// Formatting
	cout << endl;

	// Header Letter spacing
	for (int i = 0; i < colSize; i++) {

		cout << "     " << header[i];
	}

	cout << endl;

	// Row headers and loads the array with the maze data
	for (int i = 0; i < rowSize; i++) {
		for (int m = 0; m < 3; m++) {
			// Row number added to left header column
			if (m == 1) {
				if (i < 10) {

					cout << i << "  "; // spacing for formating
				}
				else {

					cout << i << " ";  // alternate spacing for formating
				}
			}
			else {

				cout << "   ";
			}
			
			// prints the maze
			for (int j = 0; j < colSize; j++) {	// determines the amount of columns
				for (int n = 0; n < 3; n++) { // used for the loading of a Group object
					it_R = mazeBucket.begin(); // the iterator to select the row list
					for (int o = 0; o < i; o++) it_R++; // cycles through the row lists
					it_C = it_R->begin(); // sets the column iterator to the begining of the row list 
					for (int p = 0; p < j; p++) it_C++; // cycles through the column list 
					cout << it_C->ReturnBrand(m, n) << " "; // loads the group object at it_C location with appropriate brand and prints to console
				}
			}
			cout << endl; // adds a new line for next set of data
		}	
	}
}

int main() {

	// Variable for new input file stream
	ifstream fileIn;

	// open new file and read data
	fileIn.open("C:\\Users\\mrtim\\Documents\\GCU\\CST-201\\WEEK 1\\Maze project 1\\test.txt");

	//Check if file open is a success
	if (!fileIn) {
		cerr << "*** Unable to open file." << " Check file path. ***" << endl;
		exit(1); // system stop
	}

	// read input
	fileIn >> colSize >> rowSize;
	fileIn >> startCol >> startRow >> endCol >> endRow;

	// Calling the error function to action for start, end, and size input
	CheckStartData();

	// mazeBucket is a list of lists holding Group objects
	list<list<Group>> mazeBucket;

	// Creates the list of lists holding Group objects
	for (int i = 0; i < rowSize; i++) {
		list<Group> newRow; 
		mazeBucket.push_back(newRow); // creates new row list in the mazeBucket
		for (int j = 0; j < colSize; j++) {
			Group newCell('.'); // default start character
			mazeBucket.back().push_back(newCell); // adds a Group object to the row list in the mazeBucket
		}
	}

	// instantiating iterators for col and row lists
	list<list<Group>>::iterator it_R = mazeBucket.begin();
	list<Group>::iterator it_C = it_R->begin();

	// brand as walls from input file data
	for (int h = 0; h < 79; h++) {
		fileIn >> wallCol >> wallRow;

		// iterates through the list row and col and loads a group object with the correct
		// brand based on input file coordinates
		it_R = mazeBucket.begin();
		for (int i = 0; i < wallRow; i++) it_R++;
		it_C = it_R->begin();
		for (int j = 0; j < wallCol; j++) it_C++;

		// Checks for errors with wall input
		CheckFileIn();

		// Loads wall brand
		it_C->SetBrand('X');
	}

	// iterates through the list row and col and loads a group object with the correct
	// brand based on input file coordinates
	it_R = mazeBucket.begin();
	for (int i = 0; i < startRow; i++) it_R++;
	it_C = it_R->begin();
	for (int j = 0; j < startCol; j++) it_C++;

	// Loads Start brand
	it_C->SetBrand('S');

	// This does what maze[startCol][startRow].SetBrand('S'); does 
	// iterates through the list row and col and loads a group object with the correct
	// brand based on input file coordinates
	it_R = mazeBucket.begin();
	for (int i = 0; i < endCol; i++) it_R++;
	it_C = it_R->begin();
	for (int j = 0; j < endRow; j++) it_C++;

	// loads End brand
	it_C->SetBrand('E');

	// Close File
	fileIn.close();

	// Writes the maze to a file
	WriteMaze(mazeBucket, rowSize, colSize);

	// Prints the maze to the console
	showMaze(mazeBucket, rowSize, colSize);

	return 0;
}
