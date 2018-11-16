#define _CRT_SECURE_NO_WARNINGS
#define _CRT_DISABLE_PERFCRIT_LOCKS
#define pass (void)0

#include <iostream>
#include <stack>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <utility>
#include <string>
#include <cmath>
#include <set>
#include <map>
#include <fstream>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

ifstream fin("input.in");/*file opening*/
ofstream fout("output.out");

vector <string> textArray;
vector <string> sortedArray;
vector <string> convertedText;
vector <pair <string, string> > ans;


void readFile() {/*reading file*/
	string curStr;
	while (getline(fin, curStr)) {
		textArray.push_back(curStr);
	}
}

string stringConverter(string str) {
	string strRet = "";
	for (unsigned int i = 0; i < str.length(); i++) {
		if (isupper(str[i]))	strRet.push_back(tolower(str[i]));
		else if (ispunct(str[i]))	pass;
		else	strRet.push_back(str[i]);
	}
	return strRet;
}

void sortByBegin(){
	sort(ans.begin(), ans.end());
}

void sortByEnds(){
	for(unsigned i = 0; i < textArray.size(); i++){
        reverse(ans[i].first.begin(), ans[i].first.end());
    }
    sort(ans.begin(), ans.end());
}

void printFile() {
	for (unsigned int i = 0; i < textArray.size(); i++) {
		fout << ans[i].second << endl;
	}
	fout << endl;
}

int main(int argc, char**argv) {
	setlocale(LC_ALL, "Russian");
	readFile();
	for(unsigned i = 0; i < textArray.size(); i++){
        convertedText.push_back(stringConverter(textArray[i]));
	}
	for(unsigned i = 0; i < textArray.size(); i++){
        ans.push_back(make_pair(convertedText[i], textArray[i]));
	}
	sortByBegin();
    printFile();
    sortByEnds();
    printFile();
	system("PAUSE");
	return 0;
}
