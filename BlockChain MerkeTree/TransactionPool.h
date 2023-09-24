#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <queue>
#include <vector>
#include <iostream>

#include "Transaction.h"
#include "timeParser.h"

class TransactionPool
{
private:
	std::queue <Transaction> recent;
public:
	TransactionPool() = default;
	TransactionPool(const TransactionPool& another) = delete;

	void process_transaction(Transaction transaction);

	std::vector <Transaction> retrieve_pack_if_size(size_t size);
	std::vector <Transaction> retrieve_pack_anyway(size_t size);

	std::queue <Transaction> get_queue() { return recent; }

	void print_info();

	size_t size();
};

