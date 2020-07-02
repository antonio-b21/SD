#include <iostream>
#include <fstream>
#include <queue>
#include <map>
#include <functional>

struct tree {
	char character = char();
	int freq = 0;
	tree* left = nullptr;
	tree* right = nullptr;
};

void inorder(tree* current, std::streamsize level = 0) {
	if (current != nullptr) {
		inorder(current->left, level + 1);
		std::cout.width(level * 5);
		std::cout << "";
		std::cout << current->freq << ":" << current->character << "\n";
		inorder(current->right, level + 1);
	}
}

void preorder(tree* current, std::streamsize level = 0) {
	if (current != nullptr) {
		std::cout.width(level * 5);
		std::cout << "";
		std::cout << current->freq << ":" << current->character << "\n";
		preorder(current->left, level + 1);
		preorder(current->right, level + 1);
	}
}

void code(tree* node, std::map<char, std::string>& codes, std::string currCode = "") {
	if (node->left and node->right) {
		code(node->left, codes, currCode + "0");
		code(node->right, codes, currCode + "1");
	}
	else {
		codes.insert({ node->character, currCode });
	}
	delete node;
}

bool compare(tree* a, tree* b) { return a->freq > b->freq; }

int main() {
	std::ifstream fin("text.in");
	std::map<char, int> freq;
	while (!fin.eof()) {
		char x;
		fin >> x;
		if (fin.eof()) break;

		std::map<char, int>::iterator search = freq.find(x);
		if (search != freq.end()) {
			search->second++;
		}
		else {
			freq.insert({ x, 1 });
		}
	}
	fin.close();

	std::priority_queue<tree*, std::vector<tree*>, std::function<bool(tree*, tree*)>> pqueue(compare);
	for (std::map<char, int>::iterator it = freq.begin(); it != freq.end(); it++) {
		tree* newTree = new tree;
		newTree->character = it->first;
		newTree->freq = it->second;
		pqueue.push(newTree);
	}
	freq.clear();

	while (pqueue.size() > 1) {
		tree* newTree = new tree;
		newTree->left = pqueue.top(); pqueue.pop();
		newTree->right = pqueue.top(); pqueue.pop();
		newTree->freq = newTree->left->freq + newTree->right->freq;
		pqueue.push(newTree);
	}

	tree* root = pqueue.top();
	pqueue.pop();
	inorder(root); std::cout << "\n\n"; //for checking
	preorder(root); std::cout << "\n\n"; //for checking

	std::map<char, std::string> codes;
	code(root, codes);

	for (std::map<char, std::string>::iterator it = codes.begin(); it != codes.end(); it++) { //for checking
		std::cout << it->first << " " << it->second << "\n";
	}

	fin.open("text.in");
	std::ofstream fout("text.binary", std::ios_base::binary);
	while (!fin.eof()) {
		char x;
		fin >> x;
		if (fin.eof()) break;

		std::map<char, std::string>::iterator search = codes.find(x);
		fout << search->second;
		fout << " "; // for legibility
	}
	fin.close();
	fout.close();


	return 0;
}
