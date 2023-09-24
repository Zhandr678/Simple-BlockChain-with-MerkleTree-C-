#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <vector>
#include <chrono>
#include <ctime>
#include <exception>
#include <iostream>

#include "Transaction.h"
#include "TransactionPool.h"
#include "MerkleTree.h"
#include "sha.h"
#include "hex.h"
#include "timeParser.h"

class Block
{
private:
	std::string block_hash, previous_hash, root_hash;
	MerkleTree tree;
	std::time_t timestamp;
	std::string hash();
public:
	Block() = default;
	Block(std::string hash);
	Block(std::string previous_hash, std::vector <Transaction> transaction);

	std::time_t time_stamp() const;

	//void add_transaction(Transaction transaction);
	void view_transactions();

	std::string get_block_hash();
	std::string get_previous_block_hash();
	void print_info();

	~Block() {};
};

