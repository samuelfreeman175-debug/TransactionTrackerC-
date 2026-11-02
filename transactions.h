#pragma once

#include <vector>
#include <string>
#include <iostream>



class Transaction {
    public:

        std::string getCategory() const {
            return category;
        }

        double getAmount() const {
            return amount;
        }

        uint64_t getID() const {
            return ID;
        }

        Transaction(std::string transactionCategory, double transactionAmount) 
        : ID(++next_id), category(transactionCategory), amount(transactionAmount) 
        
        {
            std::cout << "ID: " << ID << "\n";
            std::cout << "Category: " << category << "\n";
            std::cout << "Amount: " << amount << "\n";
        }

    private:
        
        std::string category{};
        double amount{};
        static inline std::atomic<uint64_t> next_id{0};
        uint64_t ID;
};