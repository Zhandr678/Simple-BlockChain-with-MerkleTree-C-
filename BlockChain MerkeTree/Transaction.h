#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <time.h>
#include <chrono>

#include "timeParser.h"

class Transaction
{
private:
	std::string key;
	std::string sender_addr, receiver_addr;
	std::time_t timestamp;
	double amount;
public:
	Transaction() = default;
	Transaction(std::string sender, std::string receiver, double amount);
	std::string to_string() const;

	std::string get_sender_address() const;
	std::string get_receiver_address() const;
	double get_amount() const;
	std::time_t time_stamp() const;

	void print_info() const;

	~Transaction() {};
};

