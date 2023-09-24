#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <vector>
#include <iostream>

#include "Transaction.h"
#include "sha.h"
#include "hex.h"


class MerkleTree
{
private:
	struct Node
	{
		Node* left;
		Node* right;
		std::string node_hash;
		Transaction info;
		bool is_leaf() const;
		Node() = delete;
		Node(std::string node_hash, Transaction t) : node_hash(node_hash), info(t) {
			left = nullptr;
			right = nullptr;
		};
		Node(Node* left, Node* right, std::string node_hash, Transaction t) : left(left), right(right), node_hash(node_hash), info(t) {
			left = nullptr;
			right = nullptr;
		};
		~Node() { delete left, right; };
	};

	Node* root;
	bool exists;

	void traverse(Node*& node, std::vector <Transaction>& ans);
	void build_tree(std::vector <Node*>& transactions);
public:
	MerkleTree();
	MerkleTree(std::vector <Transaction> transactions);

	std::string hash(std::string hash1, std::string hash2);
	std::string hash(Transaction t);
	void change(std::vector <Transaction> transaction);

	std::vector <Transaction> get_transactions_from_tree();

	bool does_tree_exist() { return exists; };
	~MerkleTree() {};
};
