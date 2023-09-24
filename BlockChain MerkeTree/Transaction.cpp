#include "Transaction.h"

Transaction::Transaction(std::string sender, std::string receiver, double amount)
{
    timestamp = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    sender_addr = sender;
    receiver_addr = receiver;
    this->amount = amount;
}

std::string Transaction::to_string() const
{
    return sender_addr + " " + receiver_addr + " " + std::to_string(amount);
}

std::string Transaction::get_sender_address() const
{
    return this->sender_addr;
}

std::string Transaction::get_receiver_address() const
{
    return this->receiver_addr;
}

double Transaction::get_amount() const
{
    return this->amount;
}

std::time_t Transaction::time_stamp() const
{
    return timestamp;
}

void Transaction::print_info() const
{
    std::cout << "------------------------------\n";
    std::cout << "Time: " << parse_timestamp(this->timestamp) << "\n";
    std::cout << "Sent From: " << this->sender_addr << "\n";
    std::cout << "Received By: " << this->receiver_addr << "\n";
    std::cout << "Amount: " << this->amount << "\n";
    std::cout << "------------------------------\n";
}
