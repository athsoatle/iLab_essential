#ifndef HASH_H
#define HASH_H
#include "inc.h"

class Hash {
private:

	static const int tableSize = 40;

	struct Item {
		std::string name;
		std::string drink;
		Item * next;
	};

	Item * HashTable[tableSize];

public:

	Hash();

	int hash(std::string key, std::string drink);

	void addItem(std::string name, std::string drink);

	int numberOfItemsInIndex(int index);

	void printTable();

	void printIntemInIndex(int index);

};
#endif