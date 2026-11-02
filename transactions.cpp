#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <atomic>
#include <functional>

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

int main() {
    
    transaction_menu();
    return 0;
}