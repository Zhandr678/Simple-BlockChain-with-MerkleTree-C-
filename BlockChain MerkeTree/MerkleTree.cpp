#include "MerkleTree.h"

#define STEP_SIZE 2

bool MerkleTree::Node::is_leaf() const
{
	return !left and !right ? true : false;
}

void MerkleTree::build_tree(std::vector<MerkleTree::Node*>& transactions)
{
	if (transactions.empty())
	{
		root = nullptr;
		return;
	}
	if (transactions.size() == 1)
	{
		root = transactions[0];
		transactions[0] = nullptr;
		return;
	}
	if (transactions.size() == STEP_SIZE)
	{ 
		std::string hash = this->hash(transactions[0]->node_hash, transactions[1]->node_hash);
		root = new Node(transactions[0], transactions[1], hash, Transaction());
		transactions[0] = nullptr;
		transactions[1] = nullptr;
		return;
	}
	std::vector <MerkleTree::Node*> next;

	for (size_t i = 0; i < transactions.size(); i += STEP_SIZE)
	{
		if (i == transactions.size() - 1)
		{
			std::string hash = this->hash(transactions[i]->node_hash, transactions[i]->node_hash);
			next.push_back(new MerkleTree::Node(transactions[i], nullptr, hash, Transaction()));
			transactions[i] = nullptr;
		}
		else 
		{
			std::string hash = this->hash(transactions[i]->node_hash, transactions[i + 1]->node_hash);
			next.push_back(new MerkleTree::Node(transactions[i], transactions[i + 1], hash, Transaction()));
			transactions[i] = nullptr;
			transactions[i + 1] = nullptr;
		}
	}
	return build_tree(next);
}

MerkleTree::MerkleTree()
{
	root = nullptr;
	exists = false;
}

MerkleTree::MerkleTree(std::vector<Transaction> transactions)
{
	exists = true;
	std::vector <MerkleTree::Node*> ptrs;
	for (const Transaction& transaction : transactions)
	{
		ptrs.push_back(new MerkleTree::Node(this->hash(transaction), transaction));
	}
	build_tree(ptrs);
}

std::string MerkleTree::hash(std::string hash1, std::string hash2)
{
	std::string data = hash1 + hash2;

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

std::string MerkleTree::hash(Transaction t)
{
	std::string data;
	data = t.get_sender_address() + t.get_receiver_address() + std::to_string(t.get_amount());
	data += std::to_string(t.time_stamp());

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

void MerkleTree::change(std::vector<Transaction> transaction)
{

}

void MerkleTree::traverse(Node*& node, std::vector<Transaction>& ans)
{
	if (node == nullptr) { return; }
	if (node->is_leaf()) { ans.push_back(node->info); return; }

	traverse(node->left, ans);
	traverse(node->right, ans);
}


std::vector<Transaction> MerkleTree::get_transactions_from_tree()
{
	std::vector <Transaction> ans;
	traverse(root, ans);
	return ans;
}
