// Finding the nth element.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

using namespace std;


// Creating the doubly linked list node
struct Node {
	int value;
	struct Node *prev;
	struct Node *next;
	struct Node *random;
	struct Node(int x) {
		value = x;
		next = random = NULL;
	}
};

// creates the head node
struct Node* head = NULL;
struct Node* otherList = NULL;


// creates the insert function allowing numbers to be inserted into the doubly linked list
void insert(int newValue) {

	// allocates the node for use
	struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));

	// put in the value 
	newNode->value = newValue;

	// prev is NULL because we will be inserting at the begining of the list
	newNode->prev = NULL;

	// old list is linked to new node
	newNode->next = head;

	// prev of head is changed to new node
	if (head != NULL) {
		head->prev = newNode;
	}

	// point the head to the new node
	head = newNode;
}

// creates the delNode function which deletes items in the list
void delNode(struct Node** head, struct Node* del) {
	
	if (*head == NULL || del == NULL) {
		return;
	}
	// delete head node
	if (*head == del) {
		*head = del->next;
	}
	// next is changed only when last node is not deleted
	if (del->next != NULL) {
		del->next->prev = del->prev;
	}
	// prev is changed only when first node is not deleted
	if (del->prev != NULL) {
		del->prev->next = del->next;
	}

	// Frees the memory space where del resided
	free(del);
}

// creates the delNodePOS function which allows deletion at the nth position within the list
void delNodePOS(struct Node** head, int n) {

	// gives position when list is NULL
	if (*head == NULL || n <= 0) {
		return;
	}

	struct Node* current = *head;

	// iterate to the nth node from beginning
	for (int i = 1; current != NULL && i < n; i++) {
		current = current->next;
	}

	// checks to see if n is greater than the number of items within the list
	if (current == NULL) {
		return;
	}

	// delete the node
	delNode(head, current);
}

// creates the function to insert at nth location
void InsertNth(struct Node** head, int newValue, int position) {
	struct Node* current = *head;
	Node* prev = NULL;

	// iterates to the position
	int i = 1;
	while (i < position) {
		prev = current;
		current = current->next;
		i++;
	}

	// allocates the node for use
	struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));

	// put in the value 
	newNode->value = newValue;
	newNode->next = current;
	newNode->prev = prev;
	current->prev = newNode;

	if (prev != NULL) {
		prev->next = newNode;
	}

	if (i == 1) {
		*head = newNode;
	}
}

// creates function that reverses list
void reverseList(struct Node **head)
{
	struct Node *temp = NULL;
	struct Node *current = *head;

	// swaps next and prev
	while (current != NULL)
	{
		temp = current->prev;
		current->prev = current->next;
		current->next = temp;
		current = current->prev;
	}

	// checks for an empty list or a list with only one node
	if (temp != NULL)
		*head = temp->prev;
}

// I couldn't figure out how to get the copy to work. I tried a constructor with template T and then
// tried this code below I found on a website but could not figure out how to implement it into my code
// I think no I would start this project as a class and use constructors rather than functions.

// creates function that clones the list
//void clone(struct Node **head)
//{
//	struct Node* current = *head, *temp;
//
//	// insert additional node after 
//	// every node of original list 
//	while (current)
//	{
//		temp = current->next;
//
//		// Inserting node 
//		current->next = new Node(current->value);
//		current->next->next = temp;
//		current = temp;
//	}
//
//	current = *head;
//
//	// adjust the random pointers of the 
//	// newly added nodes 
//	while (current)
//	{
//		if (current->next)
//			current->next->random = current->random ? current->random->next : current->random;
//
//		// move to the next newly added node by 
//		// skipping an original node 
//		current = current->next ? current->next->next : current->next;
//	}
//
//	struct Node* original = (*head), *copy = (*head)->next;
//
//	// save the start of copied linked list 
//	temp = copy;
//
//	// now separate the original list and copied list 
//	while (original && copy)
//	{
//		original->next =
//			original->next ? original->next->next : original->next;
//
//		copy->next = copy->next ? copy->next->next : copy->next;
//		original = original->next;
//		copy = copy->next;
//	}
//
//	//return temp;
//}

// creates the show function that prints the values within the list to console
void show() {
	struct Node* ptr;

	ptr = head;

	while (ptr != NULL) {
		cout << ptr->value << " ";
		ptr = ptr->next;
	}
}

int main()
{
	// calling the insert method to load the list
	insert(24);
	insert(25);
	insert(25);
	insert(27);
	insert(28);

	// List before deleted node
	cout << "List before deleted node: ";
	show();
	cout << endl;

	// create the variable for the nth position to be deleted
	int nPOS = 3;

	// deletes the node at the nth postion
	delNodePOS(&head, nPOS);

	// List after deleted node
	cout << "List after deleted node: ";
	show();
	cout << endl;

	// create variable to be inserted
	int nInsert = 26;

	// insert at the nth position
	InsertNth(&head, nInsert, nPOS);

	// list after inserted data
	cout << "List after inserted data: ";
	show();
	cout << endl;

	// reverse the list
	reverseList(&head);

	// list after reversal
	cout << "List after reversal: ";
	show();
	cout << endl;

	// copy list
	/*clone(&head);
	cout << "Cloned list: ";
	show();
	cout << endl;*/



}


