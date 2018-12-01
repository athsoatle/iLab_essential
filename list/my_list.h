#pragma once
#include "includes.h"

/*class List
{
private:
	node *head, *tail;
public:
	node *head, *tail;
	List()
	{
		head = NULL;
		tail = NULL;
	}
};*/

struct Node {
	Node() {
		prev = next = NULL;
	}
	int data;
	struct Node * next;
	struct Node * prev;
};

struct Node * initList(int data) {//list initialization
	struct Node * list;
	list = new struct Node;
	list->data = data;
	list->next = NULL;
	list->prev = NULL;
	return(list);
}

Node* nodeFindNext(Node* begin_search, int value_to_find) {
	Node* cur_ptr = begin_search;
	while (cur_ptr != NULL) {
		if (cur_ptr->data == value_to_find) return cur_ptr;
		cur_ptr = cur_ptr->next;
	}
	return NULL;
}

struct Node * addElemBack(struct Node * list, int data) {//add element back to current
	struct Node * temp, * tmp;
	temp = new struct Node;
	tmp = list->next;
	list->next = temp;
	temp->data = data;
	temp->next = tmp;
	temp->prev = list;
	if (tmp != NULL) tmp->prev = temp;
	return temp;
}

struct Node * deleteElem(struct Node * list) {//deletes an element and return prev
	struct Node *next, *prev;
	next = list->next;
	prev = list->prev;
	if (prev != NULL)
		prev->next = list->next;
	if (next != NULL)
		next->prev = list->prev;
	std::cout << list->data;
	delete list;
	return(prev);
}

struct Node * reRoot(struct Node * root) {//creates new root instead of root
	struct Node * newRoot = root->next;
	newRoot->prev = NULL;
	delete root;
	return(newRoot);
}

void printInOrder(struct Node * list) {//prints all elements in order
	struct Node * temp = list;
	while (temp != NULL) {
		std::cout << temp->data << std::endl;
		temp = temp->next;
	}
}

struct Node * findByValue(struct Node * list, int data) {
	struct Node * temp = list;
	while (temp != NULL) {
		if (temp->data == data) return(temp);
		temp = temp->next;
	}
	if (temp == NULL) {
		std::cout << "Not found\n";
		system("PAUSE");
		exit(0);
	}
}

int index(struct Node * root, struct Node * list) {
	struct Node * temp = root;
	if (temp == list) {
		return 0;
	}
	else
	{
		return(index(temp->next, list) + 1);
	}
}