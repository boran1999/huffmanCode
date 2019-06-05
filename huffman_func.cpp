#include<iostream>
#include<fstream>
#include<map>
#include<vector>
#include<list>
#include"Node.h"
#include"mySort.h"

using namespace std;
map<char, vector<bool>>tab;
vector<bool>code;

void add_data_into_tree(map<char, int>&gur, list<Node*> &heapNode) {
	for (map<char, int>::iterator it = gur.begin(); it != gur.end(); it++) {
		Node* p = new Node;
		p->w = it->second;
		p->c = it->first;
		heapNode.push_back(p);
	}
	while (heapNode.size() != 1) {
		heapNode.sort(mySort());
		Node* sonl = heapNode.front();
		heapNode.pop_front();
		Node* sonr = heapNode.front();
		heapNode.pop_front();
		Node* parent = new Node(sonl, sonr);
		heapNode.push_back(parent);
	}
}

int symbol_count(const char* filename) {
	ifstream in(filename, ios::binary);
	int count = 0;
	int check_count = 0;
	char sym;
	int res;
	while (!in.eof()) {
		sym = in.get();
		if (sym == '\n') {
			count++;
		}
	}
	in.clear();
	in.seekg(0);
	while (!in.eof()) {
		sym = in.get();
		if (sym == '\n') {
			check_count++;
		}
		if (check_count == count) {
			in >> res;
		}
	}
	in.close();
	return res;
}

void BuildCodeTable(Node* root) {
	if (root->left != NULL) {
		code.push_back(0);
		BuildCodeTable(root->left);
	}
	if (root->right != NULL) {
		code.push_back(1);
		BuildCodeTable(root->right);
	}
	if (root->left == NULL && root->right == NULL) {
		tab[root->c] = code;
	}
	if (code.size() != 0) {
		code.pop_back();
	}
}

void coder(const char* file, const char* file2) {
	ifstream in(file, ios::binary);
	ofstream out(file2, ios::out | ios::binary);
	int count = 0;
	int symcount = 0;
	char buf = 0;
	while (!in.eof()) {
		symcount++;
		char sym = in.get();
		vector<bool> v = tab[sym];
		for (int i = 0; i < v.size(); i++) {
			buf = buf | v[i] << (7 - count);
			count++;
			if (count == 8) {
				count = 0;
				out << buf;
				buf = 0;
			}
		}
	}
	if (count != 0) {
		out << buf;
	}
	out << '\n' << (symcount - 1);
}
void decoder(const char* file, const char* file2, Node*root) {
	int res = symbol_count(file);
	ifstream in(file, ios::binary);
	ofstream out(file2, ios::out | ios::binary);
	int count = 0;
	bool buf = 0;
	char byte;
	int teksym = 0;
	Node* nod = root;
	byte = in.get();
	while (!in.eof()) {
		buf = byte & (1 << (7 - count));
		if (buf == 1) {
			nod = nod->right;
			count++;
		}
		else {
			nod = nod->left;
			count++;
		}
		if (nod->left == NULL && nod->right == NULL) {
			teksym++;
			if (teksym > res) {
				break;
			}
			out << nod->c;
			nod = root;
		}
		if (count == 8) {
			count = 0;
			byte = in.get();
		}
	}
}
