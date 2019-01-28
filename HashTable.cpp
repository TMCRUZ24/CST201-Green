/*
Green Group (Katon Bingham/Tim James/Tyson Cruz)
CST201 - Algorithms and Data Structures
01/23/2019
Professor Brandon Bass
*/

#include "pch.h"
#include <iostream>
#include <string>
using namespace std;

//Nodes that will be used to populate that hash table (for username and usernumbers)
class Node {
public:
	int userKey;
	int userNumber;
	string userName;

	Node() {
		this->userKey = -1;
		this->userName = "nullName";
		this->userNumber = -1;
	}

	Node(int userNumber, string userName) {
		this->userKey = userNumber;
		this->userName = userName;
		this->userNumber = userNumber;
	}
};


//This is that actual hash table that will store nodes of user information
class HashMap {
	Node *numArray[9];
	int arrayCapacity = 9;
	int arraySize = 0;
	Node *dummy;

public:
	//This hash function populates the hash table (node array) with "null" nodes
	void HashFunction() {

		dummy = new Node(-1, "nullName");

		for (int i = 0; i < arrayCapacity; i++) {
			numArray[i] = dummy;
		}

	}

	//This hash number function creates an index to store a node in the hash table based on user numbers
	int hashNumber(int hashKey) {
		return hashKey % arrayCapacity;
	}

	//This function is used to insert a new node into the hash table
	void insertNode(int userNumber, string userName) {
		Node *temp = new Node(userNumber, userName);

		int index = hashNumber(userNumber);

		while (numArray[index]->userKey != userNumber && numArray[index]->userKey != -1) {
			index++;
			index %= arrayCapacity;
		}

		if (numArray[index] == NULL || numArray[index]->userKey == -1) {
			arraySize++;
		}

		numArray[index] = temp;
	}

	//This function returns a specific node based on entering the user phone number
	void getNode(int userKey) {

		int index = hashNumber(userKey);
		while (numArray[index]->userKey != userKey && numArray[index]->userKey != -1) {
			index++;
			index %= arrayCapacity;
		}
		cout << numArray[index]->userName;
		cout << "\t";
		cout << numArray[index]->userNumber;
	}

	//This function displays all the nodes in the hash table
	void displayNodes()
	{
		for (int i = 0; i < arrayCapacity; i++){

			if (numArray[i] != NULL && numArray[i]->userKey != -1) {
				cout << "Search key (Phone number): " << numArray[i]->userKey << "  Name: " << numArray[i]->userName << endl;
			}
		}
	}
};

//Main driver function
int main(){

	HashMap *myHashTable = new HashMap;
	myHashTable->HashFunction(); //creates hash table object
	myHashTable->insertNode(1234567, "Adam");//Enter value
	myHashTable->insertNode(3455352, "Branda");//Enter value
	myHashTable->insertNode(9837373, "Brendon");//Enter value
	myHashTable->insertNode(7894563, "Jeremiah");//Enter value
	myHashTable->insertNode(8231573, "Katherine");//Enter value
	myHashTable->insertNode(7574532, "Patrick");//Enter value
	myHashTable->insertNode(5909383, "Raymond");//Enter value
	myHashTable->insertNode(9296632, "Thorsten");//Enter value
	myHashTable->displayNodes();//Display all nodes in the hash table
	myHashTable->getNode(1234567);//Display node search for by user number (finds index through hash function)

	return 0;
}
