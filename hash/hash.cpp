#include "inc.hpp"
#include "hash.hpp"

Hash::Hash() {
	for (int i = 0; i < kTable_size_; i++) {
		hash_table[i] = new Item;
		hash_table[i]->name = "empty";
		hash_table[i]->surename = "empty";
		hash_table[i]->next = NULL;
	}
}

int Hash::hash(std::string key) {
	int hash = 0;
	int index = 0;
	for (unsigned int i = 0; i < key.length(); i++) {
		hash = (hash + (int)key[i]) * 2;
	}
	index = hash % kTable_size_;
	return index;
}

void Hash::addItem(std::string name, std::string drink) {
	int index = hash(name);
	if (hash_table[index]->name == "empty") {
		hash_table[index]->name = name;
		hash_table[index]->surename = drink;
	}
	else {
		Item * ptr = hash_table[index];
		Item * n = new Item;
		n->name = name;
		n->surename = drink;
		n->next = NULL;
		while (ptr->next != NULL) {
			ptr = ptr->next;
		}
		ptr->next = n;
	}
}

int Hash::numberOfItemsInIndex(int index) {
	int count = 0;
	if (hash_table[index]->name == "empty") {
		return count;
	}
	else {
		count++;
		Item * ptr = hash_table[index];
		while (ptr->next != NULL) {
			count++;
			ptr = ptr->next;
		}
	}
	return count;
}

void Hash::printTable() {
	int number = 0;
	for (int i = 0; i < kTable_size_; i++) {
		number = numberOfItemsInIndex(i);
		std::cout << "----------\n" << i << std::endl;
		std::cout << hash_table[i]->name << std::endl;
		std::cout << hash_table[i]->surename << std::endl;
		std::cout << number << std::endl;
		std::cout << "----------\n";
	}
}

void Hash::printItemInIndex(int index) {
	Item * ptr = hash_table[index];
	if (ptr->name == "empty") {
		std::cout << index << "EMPTY\n";
	}
	else {
		std::cout << index << std::endl;
		std::cout << "content: ";
		while (ptr != NULL) {
			std::cout << "----____----\n";
			std::cout << ptr->name << std::endl;
			std::cout << ptr->surename << std::endl;
			std::cout << "----____----\n";
			ptr = ptr->next;
		}
	}
}

void Hash::findSurename(std::string name) {
	int index = hash(name);
	bool found_name = false;
	std::string drink;
	Item * ptr = hash_table[index];
	while (ptr != NULL) {
		if (ptr->name == name) {
			found_name = true;
			drink = ptr->surename;
		}
		ptr = ptr->next;
	}
	if (found_name)	std::cout << "Surename:" << drink << std::endl;
	else std::cout << name << "'s Surename was not found!\n";
}

void Hash::removeItem(std::string name) {
	int index = hash(name);
	Item * del_ptr;
	Item * p1;
	Item * p2;
	if (hash_table[index]->name == "empty" && hash_table[index]->surename == "empty") {
		std::cout << name << " was not found in hash table\n";
	}
	else if (hash_table[index]->name == name && hash_table[index]->next == NULL) {
		hash_table[index]->name = "empty";
		hash_table[index]->surename = "empty";
	}
	else if (hash_table[index]->name == name) {
		del_ptr = hash_table[index];
		hash_table[index] = hash_table[index]->next;
		delete del_ptr;
		std::cout << name << " was removed\n";
	}
	else {
		p1 = hash_table[index];
		p2 = hash_table[index]->next;
		while (p1 != NULL && p1->name != name) {
			p2 = p1;
			p1 = p1->next;
		}
		if (p1 == NULL)	std::cout << name << " was not found in hash table\n";
		else {
			del_ptr = p1;
			p1 = p1->next;
			p2->next = p1;
			delete del_ptr;
			std::cout << name << " was removed\n";
		}
	}
}
