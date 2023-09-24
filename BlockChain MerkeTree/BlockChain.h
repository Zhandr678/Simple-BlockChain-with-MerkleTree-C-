#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <iostream>

#include "MerkleTree.h"
#include "Block.h"
#include "timeParser.h"

class BlockChain
{
private:
	std::vector <Block> chain;
	void create_genesis();
public:
	BlockChain();
	BlockChain(std::vector <Block> chain);

	Block get_by_index(size_t index);
	Block get_last();
	Block get_genesis();
	size_t size();

	bool is_valid();

	void generate_block(std::string previous_hash, std::vector <Transaction> transactions);
	void print_info();

	~BlockChain() {};
};

