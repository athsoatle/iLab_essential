#include "inc.h"
#include "hash.h"

Hash::Hash() {
	for (int i = 0; i < tableSize; i++) {
		HashTable[i] = new Item;
		HashTable[i]->name = "empty";
		HashTable[i]->drink = "empty";
		HashTable[i]->next = NULL;
	}
}

int Hash::hash(std::string key, std::string drink) {
	int hash = 0;
	int index = 0;
	for (unsigned int i = 0; i < key.length(); i++) {
		hash = (hash + (int)key[i]) * 2;
	}
	index = hash % tableSize;
	return index;
}

void Hash::addItem(std::string name, std::string drink){
	int index = hash(name, drink);
	if (HashTable[index]->name == "empty") {
		HashTable[index]->name = name;
		HashTable[index]->drink = drink;
	}
	else {
		Item * ptr = HashTable[index];
		Item * n = new Item;
		n->name = name;
		n->drink = drink;
		n->next = NULL;
		while (ptr->next != NULL) {
			ptr = ptr->next;
		}
		ptr->next = n;
	}
}

int Hash::numberOfItemsInIndex(int index)
{
	int count = 0;
	if (HashTable[index]->name == "empty") {
		return count;
	}
	else {
		count++;
		Item * ptr = HashTable[index];
		while (ptr->next != NULL) {
			count++;
			ptr = ptr->next;
		}
	}
	return count;
}

void Hash::printTable(){
	int number = 0;
	for (int i = 0; i < tableSize; i++) {
		number = numberOfItemsInIndex(i);
		std::cout << "----------\n" << i << std::endl;
		std::cout << HashTable[i]->name << std::endl;
		std::cout << HashTable[i]->drink << std::endl;
		std::cout << number << std::endl;
		std::cout << "----------\n";
	}
}

void Hash::printIntemInIndex(int index){
	Item * ptr = HashTable[index];
	if (ptr->name == "empty") {
		std::cout << index << "EMPTY\n";
	}
	else {
		std::cout << index << std::endl;
		std::cout << "content: ";
		while (ptr != NULL) {
			std::cout << "----____----\n";
			std::cout << ptr->name << std::endl;
			std::cout << ptr->drink << std::endl;
			std::cout << "----____----\n";
			ptr = ptr->next;
		}
	}
}
