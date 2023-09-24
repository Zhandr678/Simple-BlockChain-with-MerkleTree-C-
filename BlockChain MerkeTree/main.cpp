#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include <limits>
#include <future>
#include <ctime>

#include "BlockChain.h"
#include "TransactionPool.h"

#define EMPTY_TRANSACTION_LIST std::vector <Transaction>({})

int main()
{
	BlockChain chain;
	TransactionPool pool;

	std::cout << "-------------Welcome to custom blockchain-------------\n\n\n";

	while (true)
	{
		std::cout << "Operations: \n";
		std::cout << "1. Make transaction\n";
		std::cout << "2. Generate block\n";
		std::cout << "3. View BlockChain\n";
		std::cout << "4. View transactions history\n";
		std::cout << "5. View pending transactions\n";
		std::cout << "------------------------------------\n";

		bool select = false;

		while (!select) 
		{
			if (GetAsyncKeyState('1') & 0x8000)
			{
				select = true;
				std::string addr, rec;
				double amount;
				std::cout << "\nYour Address: ";
				std::cin >> addr;
				std::cout << "\nFinal Address: ";
				std::cin >> rec;
				std::cout << "\nAmount: ";
				std::cin >> amount;

				try {
					Transaction transaction(addr, rec, amount);
					pool.process_transaction(transaction);
					std::cout << "Transaction confirmed: " << transaction.to_string();
					std::cout << "\n\n\n";
				}
				catch (const std::exception& e)
				{
					std::cout << "Transaction Failed: ";
					std::cout << e.what() << "\nTry Again!\n";
					std::cout << "\n\n";
				}
			}
			if (GetAsyncKeyState('2') & 0x8000)
			{
				select = true;
				int num;
				std::cout << "Specify the number of transactions in a block: ";
				std::cin >> num;
				try {
					std::vector <Transaction> trans = pool.retrieve_pack_if_size(num);
					chain.generate_block(chain.get_last().get_block_hash(), trans);
					std::cout << "Block generated successfully with hash: " << chain.get_last().get_block_hash();
					std::cout << "\n\n\n";
				}
				catch (const std::exception& e)
				{
					std::cout << "Block generation failed: " << e.what() << "\nTry Again!";
					std::cout << "\n\n\n";
				}
			}
			if (GetAsyncKeyState('3') & 0x8000)
			{
				select = true;
				if (!chain.is_valid()) 
				{
					std::cout << "BlockChain seems to be invalid!\nEnd the Program? (y/n)";
					bool select2 = false;
					while (!select2)
					{
						if (GetAsyncKeyState('y') & 0x8000)
						{
							select2 = true;
							std::cout << "Program is finished!\n";
							return 0;
						}
						if (GetAsyncKeyState('n') & 0x8000)
						{
							select2 = true;
							std::cout << "Restarting BlockChain!\n";
							chain = BlockChain();
						}
					}
					std::cout << "\n\n";
				}
				else {
					chain.print_info();
					std::cout << "\n\n";
				}
			}
			if (GetAsyncKeyState('4') & 0x8000)
			{
				select = true;
				std::cout << "---------Transaction History---------\n";
				chain.print_info();
				std::cout << "---------Transaction History---------\n";
				std::cout << "\n\n";
			}
			if (GetAsyncKeyState('5') & 0x8000)
			{
				select = true;
				std::cout << "--------Pending transactions---------\n";
				pool.print_info();
				std::cout << "--------Pending transactions---------\n\n\n";
			}
		}
	}
}