#define _CRT_SECURE_NO_WARNINGS
#include "Block.h"

Block::Block(std::string hash)
{
	this->block_hash = previous_hash;
	this->previous_hash = "NULL";
	timestamp = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	tree = MerkleTree();
}

Block::Block(std::string previous_hash, std::vector<Transaction> transaction)
{
	this->previous_hash = previous_hash;
	timestamp = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	tree = MerkleTree(transaction);
	block_hash = hash();
}

std::time_t Block::time_stamp() const
{
	return this->timestamp;
}

std::string Block::hash()
{
	std::string data = previous_hash + std::to_string(timestamp);
	std::vector <Transaction> trans = tree.get_transactions_from_tree();
	for (const Transaction& transaction : trans)
	{
		data += transaction.to_string();
	}

	CryptoPP::SHA256 hash;
	CryptoPP::byte digest[CryptoPP::SHA256::DIGESTSIZE];
	hash.CalculateDigest(digest, reinterpret_cast <const CryptoPP::byte*>(data.data()), data.size());
	CryptoPP::HexEncoder encoder;
	std::string result;

	encoder.Attach(new CryptoPP::StringSink(result));
	encoder.Put(digest, sizeof(digest));
	encoder.MessageEnd();
	return result;
}

void Block::view_transactions()
{
	std::vector <Transaction> trans = tree.get_transactions_from_tree();
	for (const Transaction& t : trans)
	{
		std::cout << "------------------------------\n";
		std::cout << "Transaction:\n" << "Send From: " << t.get_sender_address() << "\nReceived By: " << t.get_receiver_address() << "\nAmount: " << t.get_amount() << "\n";
	}
	std::cout << "------------------------------\n";
}

std::string Block::get_block_hash()
{
	return this->block_hash;
}

std::string Block::get_previous_block_hash()
{
	return previous_hash;
}

void Block::print_info()
{
	std::cout << "------------------------------\n";
	std::cout << "Block Hash: " << this->block_hash << "\n";
	std::cout << "Previous Block Hash: " << this->previous_hash << "\n";
	std::cout << "Time Generated: " << parse_timestamp(this->timestamp) << "\n";
	std::cout << "----------Transactions---------\n";
	std::vector <Transaction> trans = tree.get_transactions_from_tree();
	for (const Transaction& t : trans)
	{
		t.print_info();
	}
}
