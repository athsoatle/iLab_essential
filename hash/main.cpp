#include "inc.hpp"
#include "hash.hpp"

int main(int argc, char ** argv) {
	Hash hashy;
	std::string name = "";
	hashy.addItem("sos", "sas");
	hashy.addItem("asss", "asddd");
	hashy.addItem("vfv", "dasfg");
	hashy.addItem("asd", "q");
	hashy.addItem("qwe", "asd");
	hashy.printItemInIndex(6);
	while (name != "exit") {
		std::cin >> name;
		hashy.findSurename(name);
	}
	system("PAUSE");
	return 0;
}