#pragma once
#include<iostream>

using namespace std;

class Node {
public:
	Node* left;
	Node* right;
	int w;
	char c;
	Node() {
		left = right = NULL;
		w = 0;
		c = 0;
	}
	Node(Node* l, Node* r) {
		left = l;
		right = r;
		w = l->w + r->w;
		c = 0;
	}
};
