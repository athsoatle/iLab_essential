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


void readFile(vector<string> * textArray) {/*reading file*/
	string curStr;
	while (getline(fin, curStr)) {
		textArray->push_back(curStr);
	}
}

string stringConverter(string str) {
	string strRet = "";
	for (unsigned int i = 0; i < str.length(); i++) {
		if (isupper(str[i]))	strRet.push_back(tolower(str[i]));
		else if (ispunct(str[i]) || str[i] == ' ')	pass;
		else	strRet.push_back(str[i]);
	}
	return strRet;
}

void printFile(unsigned int arraySize, vector<pair <string, string> > * ans) {
	for (unsigned int i = 0; i < arraySize; i++) {
		fout << (*ans)[i].second << "**---**" << (*ans)[i].first << endl;
	}
	fout << endl;
}

int main(int argc, char**argv) {
	setlocale(LC_ALL, "Russian");
	vector <string> textArray;
	vector <string> convertedText;
	vector <pair <string, string> > ans;
	readFile(&textArray);
	unsigned arraySize = textArray.size();
	for (unsigned i = 0; i < arraySize; i++) {
		convertedText.push_back(stringConverter(textArray[i]));
	}
	for (unsigned i = 0; i < arraySize; i++) {
		ans.push_back(make_pair(convertedText[i], textArray[i]));
	}
	sort(ans.begin(), ans.end());
	printFile(arraySize, &ans);
	for (unsigned i = 0; i < arraySize; i++) {
		reverse(ans[i].first.begin(), ans[i].first.end());
	}
	sort(ans.begin(), ans.end());
	printFile(arraySize, &ans);
	system("PAUSE");
	return 0;
}
