#ifndef HASH_H
#define HASH_H
#include "inc.hpp"

class Hash {
private:

	static const int kTable_size_ = 40;

	struct Item {
		std::string name;
		std::string surename;
		Item * next;
	};

	Item * hash_table[kTable_size_];

public:

	Hash();

	int hash(std::string key);

	void addItem(std::string name, std::string drink);

	int numberOfItemsInIndex(int index);

	void printTable();

	void printItemInIndex(int index);

	void findSurename(std::string name);

	void removeItem(std::string name);
};
#endif