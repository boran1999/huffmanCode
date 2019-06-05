#pragma once
#include"mySort.h"

void add_data_into_tree(map<char, int>&gur, list<Node*> &heapNode);

int symbol_count(const char* filename);

void BuildCodeTable(Node* root);

void coder(const char* file, const char* file2);

void decoder(const char* file, const char* file2, Node*root);

