#include "includes.h"
#include "my_list.h"

int main() {
	struct Node* head = NULL;
	struct Node* tail = NULL;
	head = initList(14);
	tail = addElemBack(head, 12);
	struct Node * sos = addElemBack(head, 11);
	addElemBack(head, 14);
	addElemBack(head, 88);
	std::cout << std::endl <<  index(head, sos) << std::endl;
	printInOrder(head);
	head = reRoot(head);
	printInOrder(head);
	struct Node* temp = findByValue(head, 12);
	system("PAUSE");
	return 0;
}