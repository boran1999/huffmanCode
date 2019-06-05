#include<iostream>
#include<fstream>
#include<string>
#include<map>
#include<vector>
#include<list>
#include"Node.h"
#include"mySort.h"
#include"huffman_func.h"

using namespace std;

int main(void) {
	setlocale(LC_ALL, "Russian");
	ifstream in("text.dat", ios::binary);
	if (!in.is_open()) {
		cout << "ФАЙЛА НЕ СУЩЕСТВУЕТ(ИН)" << endl;
		return -1;
	}
	map<char, int>gur;
	list<Node*> heapNode;
	while (!in.eof()) {
		char c = in.get();
		gur[c]++;
	}
	add_data_into_tree(gur, heapNode);
	Node* root = heapNode.front();
	BuildCodeTable(root);
	in.clear();
	in.seekg(0);
	string str;
	cout << "Введите encode(кодирование) или decode(декоддирование)" << endl;
	cin >> str;
	if (str == "encode") {
		coder("text.dat", "zip.dat");
	}
	else if (str == "decode") {
		decoder("zip.dat", "texts.dat", root);
	}
	else {
		cout << "команда не распознана"<<endl;
	}
	system("pause");
	return 0;
}
