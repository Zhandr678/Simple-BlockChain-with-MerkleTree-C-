#include "TransactionPool.h"

void TransactionPool::process_transaction(Transaction transaction)
{
	// TODO: Error handling
	recent.push(transaction);
}

std::vector<Transaction> TransactionPool::retrieve_pack_if_size(size_t size)
{
	if (recent.size() < size) { throw std::exception("Size is out of bound"); }
	std::vector <Transaction> sub;
	for (size_t i = 0; i < size; i++)
	{
		sub.push_back(recent.front());
		recent.pop();
	}
	return sub;
}

std::vector<Transaction> TransactionPool::retrieve_pack_anyway(size_t size)
{
	std::vector <Transaction> sub;
	for (size_t i = 0; i < std::min(recent.size(), size); i++)
	{
		sub.push_back(recent.front());
		recent.pop();
	}
	return sub;
}

void TransactionPool::print_info()
{
	std::queue <Transaction> q = this->get_queue();
	while (!q.empty())
	{
		std::cout << "------------------------------\n";
		std::cout << "Time: " << parse_timestamp(q.front().time_stamp()) << "\n";
		std::cout << "Sent From: " << q.front().get_sender_address() << "\n";
		std::cout << "Received By: " << q.front().get_receiver_address() << "\n";
		std::cout << "Amount: " << q.front().get_amount() << "\n";
		std::cout << "------------------------------\n";
		q.pop();
	}
}

size_t TransactionPool::size()
{
	return recent.size();
}
