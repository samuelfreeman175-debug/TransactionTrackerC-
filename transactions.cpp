#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

class Transaction {
    public:

        std::string getCategory() const {
            return category;
        }

        double getAmount() const {
            return amount;
        }

        Transaction(std::string transactionCategory, double transactionAmount) 
        : category(transactionCategory), amount(transactionAmount) 
        
        {
            std::cout << "Category: " << category << "\n";
            std::cout << "Amount: " << amount << "\n";
        }

    private:
        
        std::string category{};
        double amount{};
};

class Ledger {

    public:

        std::vector<Transaction> getVector() const {
            return transactions;
        }

        void addTransaction(const std::string& category, const double& amount) {
            Transaction transactionobj(category, amount);
            transactions.push_back(transactionobj);

        }

        void printAll() const {
            for (const Transaction& trans : transactions) {
                std::cout << trans.getCategory() << "\n";
                std::cout << trans.getAmount() << "\n";
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
                    std::cout << trans.getCategory() << "\n";
                    std::cout << trans.getAmount() << "\n";
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
        std::cout << "Menu" << "\n" << "1.  Add.  2.  View All Transactions.  3.  Total Balance.  4.  Print Categories  5.  Quit" << "\n";
        std::cin >> option;

        if (option == 1) {
            std::cout << "Enter a category: " << "\n";
            std::getline(std::cin >> std::ws, category);

            std::cout << "Enter an amount: " << "\n";
            std::cin >> amount;

            myLedger.addTransaction(category, amount);
        }

        else if (option == 2) {
            myLedger.printAll();
        }

        else if (option == 3) {
             
            std::cout << myLedger.getTotalBalance() << "\n";
        }

        else if (option == 4) {
            std::string selectedCategory{};

            std::cout << "Enter a category: " << "\n";
            std::getline(std::cin >> std::ws, selectedCategory);
            myLedger.printByCategory(selectedCategory);
        }

        else if (option == 5) {
            myLedger.saveFile("ledger.csv");
            return false;
        }
    }

}

int main() {
    
    transaction_menu();
    return 0;
}