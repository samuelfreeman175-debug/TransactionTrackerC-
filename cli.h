#pragma once
#include "ledger.h"

#include <string>
#include <iostream>

bool transaction_menu() {
    int option{};
    double amount{};
    std::string category{};

    Ledger myLedger;

    myLedger.loadFile("ledger.csv");

    while (true) {
        std::cout << "Menu" << "\n" << "1.  Add.  2.  View All Transactions.  3.  Total Balance.  4.  Print Categories.  5.  Remove.  6.  Quit" << "\n";
        std::cin >> option;

        if (option == 1) {
            std::cout << "Enter a category: " << "\n";
            std::getline(std::cin >> std::ws, category);

            std::cout << "Enter an amount: " << "\n";
            std::cin >> amount;

            myLedger.addTransaction(category, amount);
        }

        else if (option == 2) {
            int sort{};
            myLedger.printAll();
            std::cout << "Sort by Amount = 1" << "\n";
            std::cin >> sort;

            if (sort == 1) {
                myLedger.sortTransactions();
            }
        }

        else if (option == 3) {
             
            std::cout << myLedger.getTotalBalance() << "\n";
        }

        else if (option == 4) {
            int sort{};
            std::string selectedCategory{};

            std::cout << "Enter a category: " << "\n";
            std::getline(std::cin >> std::ws, selectedCategory);
            myLedger.printByCategory(selectedCategory);

            std::cout << "Sort by Amount = 1" << "\n";
            std::cin >> sort;
            if (sort == 1) {
                myLedger.sortTransactions();
            }
        }

        else if (option == 5) {
            uint64_t ID_;
            
            std::cout << "Enter a Transaction ID: " << "\n";
            std::cin >> ID_;
            myLedger.removeTransaction(ID_);
        }

        else if (option == 6) {
            myLedger.saveFile("ledger.csv");
            return false;
        }
    }

}