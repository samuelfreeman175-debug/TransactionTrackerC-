#pragma once
#include "transactions.h"

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <atomic>
#include <functional>
#include <fstream>





class Ledger {

    public:

        std::vector<Transaction> getVector()  {
            return transactions;
        }

        void addTransaction(const std::string& category, const double& amount) {
            Transaction transactionobj(category, amount);
            transactions.push_back(transactionobj);
        }

        void removeTransaction(uint64_t ID) {
            std::erase_if(transactions, [ID](const Transaction& t) {
                return t.getID() == ID;
            });
        }

        void sortTransactions() {
            sort(transactions.begin(), transactions.end(),
            [](const Transaction& a, const Transaction& b) {
                return a.getAmount() < b.getAmount();
            });
        
        }

        void printAll() const {
            for (const Transaction& trans : transactions) {
                std::cout << "ID: " << trans.getID() << "\n";
                std::cout << "Category: " << trans.getCategory() << "\n";
                std::cout << "Amount: " << trans.getAmount() << "\n";
            }
        }

        double getTotalBalance() const {
            double totalAmount{};
            for (const Transaction& trans : transactions) {
                
                totalAmount += trans.getAmount();
            }
            return totalAmount;

        }

        void printByCategory(std::string searchCategory) const {
            bool found{false};

            for (const Transaction& trans : transactions) {
                if (trans.getCategory() == searchCategory) {
                    found = true;
                std::cout << "ID: " << trans.getID() << "\n";
                std::cout << "Category: " << trans.getCategory() << "\n";
                std::cout << "Amount: " << trans.getAmount() << "\n";
                }
            }
                if (!found) {
                    std::cout << "No transactions found for: " << searchCategory << "\n";
                }
        }

        void saveFile(const std::string& filename) const {
            std::ofstream outFile(filename);
            
            for (const Transaction& trans : transactions) {
                outFile << trans.getCategory() << "," << trans.getAmount() << "\n";
            }
        }
       void loadFile(const std::string& filename)  {
            std::ifstream inFile(filename);

            std::string categoryString{};
            std::string amountString{};

            while (std::getline(inFile, categoryString, ',') && std::getline(inFile, amountString, '\n')) {
                double amount = std::stod(amountString);
                addTransaction(categoryString, amount);
            }
       }

    private:
        std::vector<Transaction> transactions{};
};