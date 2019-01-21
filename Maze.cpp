/*
Tyson M. Cruz
CST201 - Algorithms and Data Structures
01/20/2018
Professor Brandon Bass

This is my own work.

This application will read data from a file and create a 2-dimensional maze map consisting of 3x3 squares.
The user will select directions throughout the maze generating a historical path throughout the maze that is
stored in a stack. The path taken will be marked as the user traverses throughout the maze until the user
finds the finish. Once the finish is achieved, the path history will be displayed from the stack by
its coordinates. 
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
#include <stack>
using namespace std;


////////////////////////////////////////////FUNCTION PROTOTYPES//////////////////////////////////////////////
vector<vector<vector<string> > > createMaze(void);
void printSquare(vector<vector<vector<string> > > &newSquare);
vector<string> getStartSquare();
vector<string> getFinishSquare();
vector<string> getBlockSquare();
vector<string> getOpenSquare();
vector<string> getPathMarker();
vector<string> getUserMarker();


//////////////////////////////////////////GLOBAL VARIABLES//////////////////////////////////////////////////
ifstream fileIn;
int xAxis, yAxis, startX, startY, finishX, finishY, blockX, blockY;
vector<string> startTile = getStartSquare();
vector<string> finishTile = getFinishSquare();
vector<string> blockTile = getBlockSquare();
vector<string> openTile = getOpenSquare();
vector<vector<vector<string> > > mazeGrid;
stack<int> userPath;


////////////////////////////////////////////MAIN FUNCTION////////////////////////////////////////////////////
int main()
{
	vector<vector<vector<string> > > row = createMaze();
	printSquare(row);
}

//////////////////////////////////////////FUNCTION DEFINITIONS///////////////////////////////////////////////
//createMaze function creates a maze grid and populates the grid with tiles specified from the text file
vector<vector<vector<string> > > createMaze(void) {

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

//printSquare function displays the maze grid in the proper format and updates the maze with each user move.
void printSquare(vector<vector<vector<string> > > &mazeGrid){
	
	//Function variables that will be used
	vector<string> userTile = getUserMarker();
	vector<string> markedPath = getPathMarker();
	int userMove;
	int userX;
	int userY;

	//Initialize variables
	userX = startX;
	userY = startY;
	mazeGrid[userY][userX] = userTile;


	//This loop refreshes the maze map with each user move.
	do{
		//Initial map display
		for (int i = 0; i < mazeGrid.size(); i++) {
			for (int j = 0; j < mazeGrid[i].size(); j++) {
				cout << mazeGrid[i][j][0];
			}
			cout << endl;
			for (int j = 0; j < mazeGrid[i].size(); j++) {
				cout << mazeGrid[i][j][1];
			}
			cout << endl;
			for (int j = 0; j < mazeGrid[i].size(); j++) {
				cout << mazeGrid[i][j][2];
			}
			cout << endl;
		}

		//Menu/Key Legend
		cout << "Select your next move:" << endl;
		cout << "8: Up" << endl;
		cout << "4: Left" << endl;
		cout << "6: Right" << endl;
		cout << "2: Down" << endl;

		//Variable captures the key entered by the user
		cin >> userMove;

		//"If" statement verifies that the coordinates don't go beyond the grid size
		if (userMove == 8) {////////////////////If user chooses to go up.....
			mazeGrid[userY][userX] = markedPath;
			userY--;
			if (userX >= xAxis || userY >= yAxis || userX < 0 || userY < 0) {
				cout << "Out of Bounds Error: Stay within the maze map!" << endl;
				userY++;
				mazeGrid[userY][userX] = userTile;
			}
			else if (mazeGrid[userY][userX][0] == "XXX") {
				cout << "You ran into a wall! Try a different direction..." << endl;
				userY++;
				mazeGrid[userY][userX] = userTile;
			}
			else {
				userPath.push(userY);
				userPath.push(userX);
				mazeGrid[userY][userX] = userTile;
			}
		}
		else if (userMove == 4) {//////////////If user chooses to go left.....
			mazeGrid[userY][userX] = markedPath;
			userX--;
			if (userX >= xAxis || userY >= yAxis || userX < 0 || userY < 0) {
				cout << "Out of Bounds Error: Stay within the maze map!" << endl;
				userX++;
				mazeGrid[userY][userX] = userTile;
			}
			else if (mazeGrid[userY][userX][0] == "XXX") {
				cout << "You ran into a wall! Try a different direction..." << endl;
				userX++;
				mazeGrid[userY][userX] = userTile;
			}
			else {
				userPath.push(userY);
				userPath.push(userX);
				mazeGrid[userY][userX] = userTile;
			}
		}
		else if (userMove == 6) {///////////////If user chooses to go right.....
			mazeGrid[userY][userX] = markedPath;
			userX++;
			if (userX >= xAxis || userY >= yAxis || userX < 0 || userY < 0) {
				cout << "Out of Bounds Error: Stay within the maze map!" << endl;
				userX--;
				mazeGrid[userY][userX] = userTile;
			}
			else if (mazeGrid[userY][userX][0] == "XXX") {
				cout << "You ran into a wall! Try a different direction..." << endl;
				userX--;
				mazeGrid[userY][userX] = userTile;
			}
			else {
				userPath.push(userY);
				userPath.push(userX);
				mazeGrid[userY][userX] = userTile;
			}
		}
		else if (userMove == 2) {/////////////If user chooses to go down.....
			mazeGrid[userY][userX] = markedPath;
			userY++;
			if (userX >= xAxis || userY >= yAxis || userX < 0 || userY < 0) {
				cout << "Out of Bounds Error: Stay within the maze map!" << endl;
				userY--;
				mazeGrid[userY][userX] = userTile;
			}
			else if (mazeGrid[userY][userX][0] == "XXX") {
				cout << "You ran into a wall! Try a different direction..." << endl;
				userY--;
				mazeGrid[userY][userX] = userTile;
			}
			else {
				userPath.push(userY);
				userPath.push(userX);
				mazeGrid[userY][userX] = userTile;
			}
		}
		else///////////////If user enters a value that doesn't match up/down/left/right.....
			cout << "Invalid Entry. Please enter a valid direction." << endl;
		
		//When the user finds the finish....
		if (userX == finishY && userY == finishX) {
			cout << "Congratulations, you win!" << endl;
			cout << "User path taken was: " << endl;
			do{//This do-while loop displays all moves from the stack
				cout << "(" << userPath.top();
				userPath.pop();
				cout << ", ";
				cout << userPath.top() << ")" << endl;;
				userPath.pop();
			} while (!userPath.empty());
			break;
		}
	} while (!(userY == finishY && userX == finishX));

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

//Creates tiles to mark the path as user traverses through the maze
vector<string> getPathMarker() {

	vector<string> newSquare =
	{ "!!!",
	  "!!!",
	  "!!!" };

	return newSquare;
}

//Creates tiles to mark the path as user traverses through the maze
vector<string> getUserMarker() {

	vector<string> newSquare =
	{ "!!!",
	  "ME!",
	  "!!!" };

	return newSquare;
}