#include "BlockChain.h"

void BlockChain::create_genesis()
{
	Block genesis("#");
	chain.push_back(genesis);
}

BlockChain::BlockChain()
{
	create_genesis();
}

BlockChain::BlockChain(std::vector<Block> chain)
{
	this->chain = chain;
}

Block BlockChain::get_by_index(size_t index)
{
	return chain.at(index);
}

Block BlockChain::get_last()
{
	return chain.at(chain.size() - 1);
}

Block BlockChain::get_genesis()
{
	return chain.at(0);
}

size_t BlockChain::size()
{
	return chain.size();
}

bool BlockChain::is_valid()
{
	for (size_t i = 1; i < chain.size(); i++)
	{
		if (chain.at(i - 1).get_block_hash() != chain.at(i).get_previous_block_hash())
		{
			return false;
		}
	}
	return true;
}

void BlockChain::generate_block(std::string previous_hash, std::vector<Transaction> transactions)
{
	Block block(previous_hash, transactions);
	chain.push_back(block);
}

void BlockChain::print_info()
{
	for (Block& b : chain)
	{
		b.print_info();
	}
}
