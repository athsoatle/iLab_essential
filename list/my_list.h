#pragma once

struct Node;

struct Node * initList(int data);

Node* nodeFindNext(Node* begin_search, int value_to_find);

struct Node * addElemBack(struct Node * list, int data);

struct Node * deleteElem(struct Node * list);

struct Node * reRoot(struct Node * root);

void printInOrder(struct Node * list);

struct Node * findByValue(struct Node * list, int data);

int index(struct Node * root, struct Node * list);