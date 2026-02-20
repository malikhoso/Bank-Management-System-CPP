#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>
using namespace std;

struct account {
    string accountNumber;
    string name;
    string accountType;
    double balance;
    double loanAmount; 
    double loanInterestRate; 
    bool hasLoan = false; 
};

// Function prototypes
void createAccount(account accounts[], int &numAccounts, int &nextAccountNumber);
void depositMoney(account accounts[], int numAccounts);
void withdrawMoney(account accounts[], int numAccounts);
void checkBalance(const account accounts[], int numAccounts);
void transferFunds(account accounts[], int numAccounts);
void takeLoan(account accounts[], int numAccounts);
void displayLoanInfo(const account& acc);
void payLoanBack(account accounts[], int numAccounts);
void deleteAccount(account accounts[], int &numAccounts);
void displayAllDataFromFile(const string &filename);
void displayAllAccounts(const account accounts[], int numAccounts);
void displayAccountByNumber(const account accounts[], int numAccounts);
void saveAccountsToFile(const account accounts[], int numAccounts, int nextAccountNumber, const string &filename);
void loadAccountsFromFile(account accounts[], int &numAccounts, int &nextAccountNumber, const string &filename);

const int MAX_ACCOUNTS = 100;

// Main function
int main() {
    account accounts[MAX_ACCOUNTS];
    int numAccounts = 0;
    int nextAccountNumber = 1001; // Initialize the next account number
    string filename = "accounts.txt";
    loadAccountsFromFile(accounts, numAccounts, nextAccountNumber, filename);

    int choice;
    do {
        cout << "\n===== BANK MANAGEMENT SYSTEM =====\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Check Balance\n";
        cout << "5. Transfer Funds Within Acoounts\n";
        cout << "6. Take a Loan\n";
        cout << "7. Display Loan Information\n";
        cout << "8. Pay Loan Back\n"; // New option for loan repayment
        cout << "9. Delete Account\n";
        cout << "10. Display All Bank Data\n";
        cout << "11. Display All Accounts\n";
        cout << "12. Display Account by Number\n";
        cout << "13. Save & Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                createAccount(accounts, numAccounts, nextAccountNumber);
                break;
            case 2: 
                depositMoney(accounts, numAccounts);
                break;
            case 3: 
                withdrawMoney(accounts, numAccounts);
                break;
            case 4: 
                checkBalance(accounts, numAccounts);
                break;
            case 5:
                transferFunds(accounts, numAccounts); // Call the transferFunds function
                break;
            case 6:
                takeLoan(accounts, numAccounts);
                break;   
            case 7: {
                string accountNumber;
                cout << "Enter account number: ";
                cin >> accountNumber;
                for (int i = 0; i < numAccounts; ++i) {
                    if (accounts[i].accountNumber == accountNumber) {
                        displayLoanInfo(accounts[i]);
                        break;
                    }
                }
                break;
            }
            case 8:
                payLoanBack(accounts, numAccounts); // Call the payLoanBack function
                break;
            case 9:
                deleteAccount(accounts, numAccounts);
                break;
            case 10: {
                int password = 4507;
                int userPassword;
                cout << "Please Enter the code to open the bank data: ";
                cin >> userPassword;
                if(userPassword == password){
                    displayAllDataFromFile(filename);
                } else {
                    cout << "Incorrect Code entered" << endl;
                }
                break;
            }
            case 11: { 
                int password = 4507;
                int userPassword;
                cout << "Please Enter the code to open the bank data: ";
                cin >> userPassword;
                if(userPassword == password){
                    displayAllAccounts(accounts, numAccounts);
                } else {
                    cout << "Incorrect Code entered" << endl;
                }
                break;
            }
            case 12:
                displayAccountByNumber(accounts, numAccounts);
                break;
            case 13:
                cout << "Record Saved!\nExiting...\n";
                saveAccountsToFile(accounts, numAccounts, nextAccountNumber, filename);
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 13);

    return 0;
}

// Function to create a new account
void createAccount(account accounts[], int &numAccounts, int &nextAccountNumber) {
    if (numAccounts >= MAX_ACCOUNTS) {
        cout << "Cannot create more accounts, limit reached.\n";
        return;
    }
    
    account* newAccount = new account;
    newAccount->accountNumber = to_string(nextAccountNumber++);
    cout << "Enter name: ";
    cin.ignore();   
    getline(cin, newAccount->name);
    cout << "Enter account type (Savings/Current): ";
    cin >> newAccount->accountType;
    newAccount->balance = 0.0;
    accounts[numAccounts++] = *newAccount;
    cout << "Account created successfully with account number: " << newAccount->accountNumber << "\n";
    delete newAccount;
    newAccount = nullptr;
        
}

// Function to deposit money
void depositMoney(account accounts[], int numAccounts) {
    string accNum;
    double amount;
    cout << "Enter account number: ";
    cin >> accNum;
    cout << "Enter amount to deposit: ";
    cin >> amount;

    for (int i = 0; i < numAccounts; ++i) {
        if (accounts[i].accountNumber == accNum) {
            accounts[i].balance += amount;
            cout << "Amount deposited successfully!\n";
            return;
        }
    }
    cout << "Account not found.\n";
}

// Function to withdraw money
void withdrawMoney(account accounts[], int numAccounts) {
    string accNum;
    double amount;
    cout << "Enter account number: ";
    cin >> accNum;
    cout << "Enter amount to withdraw: ";
    cin >> amount;

    for (int i = 0; i < numAccounts; ++i) {
        if (accounts[i].accountNumber == accNum) {
            if (accounts[i].balance >= amount) {
                accounts[i].balance -= amount;
                cout << "Amount withdrawn successfully!\n";
            } else {
                cout << "Insufficient balance.\n";
            }
            return;
        }
    }
    cout << "Account not found.\n";
}

// Function to check balance
void checkBalance(const account accounts[], int numAccounts) {
    string accNum;
    cout << "Enter account number: ";
    cin >> accNum;

    for (int i = 0; i < numAccounts; ++i) {
        if (accounts[i].accountNumber == accNum) {
            cout << "Current balance: " << accounts[i].balance << endl;
            return;
        }
    }
    cout << "Account not found.\n";
}

//Function to Transfer Money within Accounts
void transferFunds(account accounts[], int numAccounts) {
    string fromAccountNumber, toAccountNumber;
    double amount;

    cout << "Enter the account number to transfer from: ";
    cin >> fromAccountNumber;
    cout << "Enter the account number to transfer to: ";
    cin >> toAccountNumber;
    cout << "Enter the amount to transfer: ";
    cin >> amount;

    int fromIndex = -1, toIndex = -1;

    for (int i = 0; i < numAccounts; ++i) {
        if (accounts[i].accountNumber == fromAccountNumber) {
            fromIndex = i;
        }
        if (accounts[i].accountNumber == toAccountNumber) {
            toIndex = i;
        }
    }
    if (fromIndex == -1) {
        cout << "Source account not found." << endl;
        return;
    }
    if (toIndex == -1) {
        cout << "Destination account not found." << endl;
        return;
    }
    if (accounts[fromIndex].balance < amount) {
        cout << "Insufficient balance in the source account." << endl;
        return;
    }
    accounts[fromIndex].balance -= amount;
    accounts[toIndex].balance += amount;
    cout << "Transfer successful." << endl;
    cout << "New balance for " << accounts[fromIndex].name  << ": $" << accounts[fromIndex].balance << endl;
    cout << "New balance for " << accounts[toIndex].name << ": $" << accounts[toIndex].balance << endl;
}

// Function to take a loan (with installment details)
void takeLoan(account accounts[], int numAccounts) {
    string accNum;
    double loanAmount;
    int installments;
    cout << "Enter account number: ";
    cin >> accNum;

    // Find the account
    for (int i = 0; i < numAccounts; ++i) {
        if (accounts[i].accountNumber == accNum) {
            if (accounts[i].hasLoan) {
                cout << "Loan already taken. Existing loan amount: $" << accounts[i].loanAmount << " at " << accounts[i].loanInterestRate * 100 << "% interest rate." << endl;
                return;
            }

            cout << "Enter loan amount: ";
            cin >> loanAmount;

            cout << "Enter number of installments (12, 24, 36): ";
            cin >> installments;
            if (installments != 12 && installments != 24 && installments != 36) {
                cout << "Invalid number of installments. Please choose 12, 24, or 36.\n";
                return;
            }

            // Calculate total amount with 10% interest
            double totalAmount = loanAmount * 1.10;
            double monthlyInstallment = totalAmount / installments;

            accounts[i].balance += loanAmount; // Adding loan amount to the balance
            accounts[i].loanAmount = totalAmount; // Store total amount with interest
            accounts[i].loanInterestRate = 0.10;
            accounts[i].hasLoan = true;

            cout << "Loan granted successfully!\n";
            cout << "Total amount to be paid (with interest): $" << totalAmount << "\n";
            cout << "Monthly installment amount: $" << monthlyInstallment << "\n";
            cout << "New balance: $" << accounts[i].balance << "\n";
            return;
        }
    }
    cout << "Account not found.\n";
}

//Function to Display the taken Loan Information
void displayLoanInfo(const account& acc) {
    if (acc.hasLoan) {
        cout << "Loan Information for " << acc.name << ":" << endl;
        cout << "Loan Amount: $" << acc.loanAmount << endl;
        cout << "Interest Rate: " << acc.loanInterestRate * 100 << "%" << endl;
    } else {
        cout << "No loan information for " << acc.name << "." << endl;
    }
}

//Function to pay the taken Loan
void payLoanBack(account accounts[], int numAccounts) {
    string accountNumber;
    double paymentAmount;

    cout << "Enter account number: ";
    cin >> accountNumber;

    for (int i = 0; i < numAccounts; ++i) {
        if (accounts[i].accountNumber == accountNumber) {
            if (!accounts[i].hasLoan) {
                cout << "No outstanding loan for this account." << endl;
                return;
            }

            cout << "Current loan amount: $" << accounts[i].loanAmount << endl;
            cout << "Enter payment amount: ";
            cin >> paymentAmount;

            if (paymentAmount > accounts[i].balance) {
                cout << "Insufficient balance to make the payment." << endl;
                return;
            }

            accounts[i].balance -= paymentAmount;
            accounts[i].loanAmount -= paymentAmount;

            if (accounts[i].loanAmount <= 0) {
                accounts[i].hasLoan = false;
                accounts[i].loanAmount = 0;
                cout << "Loan fully repaid. Thank you!" << endl;
            } else {
                cout << "Partial payment successful. Remaining loan amount: $" << accounts[i].loanAmount << endl;
            }

            cout << "New balance: $" << accounts[i].balance << endl;
            return;
        }
    }

    cout << "Account not found." << endl;
}


// Function to delete an account
void deleteAccount(account accounts[], int &numAccounts) {
    string accNum;
    cout << "Enter account number: ";
    cin >> accNum;

    for (int i = 0; i < numAccounts; ++i) {
        if (accounts[i].accountNumber == accNum) {
            for (int j = i; j < numAccounts - 1; ++j) {
                accounts[j] = accounts[j + 1];
            }
            numAccounts--;
            cout << "Account deleted successfully!\n";
            return;
        }
    }
    cout << "Account not found.\n";
}

// Function to display all data from the file
void displayAllDataFromFile(const string &filename) {
    ifstream inFile(filename);
    if (inFile.is_open()) {
        string line;
        while (getline(inFile, line)) {
            cout << line << endl;
        }
        inFile.close();
    } else {
        cout << "Unable to open file for reading.\n";
    }
}

// Function to display all accounts
void displayAllAccounts(const account accounts[], int numAccounts) {
    for (int i = 0; i < numAccounts; ++i) {
        cout << "Account Number: " << accounts[i].accountNumber 
             << ", Name: " << accounts[i].name 
             << ", Type: " << accounts[i].accountType 
             << ", Balance: " << accounts[i].balance << endl;
    }
}

// Function to display an account by number
void displayAccountByNumber(const account accounts[], int numAccounts) {
    string accNum;
    cout << "Enter account number: ";
    cin >> accNum;

    for (int i = 0; i < numAccounts; ++i) {
        if (accounts[i].accountNumber == accNum) {
            cout << "Account Number: " << accounts[i].accountNumber 
                 << ", Name: " << accounts[i].name 
                 << ", Type: " << accounts[i].accountType 
                 << ", Balance: " << accounts[i].balance << endl;
            return;
        }
    }
    cout << "Account not found.\n";
}

//Function to Save Accounts to File at the end of the execution
void saveAccountsToFile(const account accounts[], int numAccounts, int nextAccountNumber, const string &filename) {
    ofstream outFile(filename); // Open file in write mode to overwrite
    if (outFile.is_open()) {
        outFile << "AccountNumber\tName\t\t\tAccountType\tBalance\t\tLoanAmount\tInterestRate\tLoanStatus\n";  // Headings
        for (int i = 0; i < numAccounts; ++i) {
            outFile << accounts[i].accountNumber << "\t\t"
                    << accounts[i].name << "\t\t"
                    << accounts[i].accountType << "\t\t"
                    << accounts[i].balance << "\t\t"
                    << accounts[i].loanAmount << "\t\t"
                    << accounts[i].loanInterestRate << "\t\t"
                    << accounts[i].hasLoan << "\n";
        }
        outFile.close();
    } else {
        cout << "Unable to open file for writing.\n";
    }

    // Save the next account number to a separate file
    ofstream numFile("nextAccountNumber.txt"); // Open file in write mode
    if (numFile.is_open()) {
        numFile << nextAccountNumber;
        numFile.close();
    } else {
        cout << "Unable to open nextAccountNumber file for writing.\n";
    }
}

//Function to load Accounts from File at the beginning of the execution
void loadAccountsFromFile(account accounts[], int &numAccounts, int &nextAccountNumber, const string &filename) {
    ifstream inFile(filename);
    if (inFile.is_open()) {
        string line;
        getline(inFile, line);  // Skip the headings line
        account* acc = new account;
        numAccounts = 0;
        while (getline(inFile, line)) {
            istringstream iss(line);
            iss >> acc->accountNumber >> ws;
            getline(iss, acc->name, '\t');
            iss >> acc->accountType >> acc->balance >> acc->loanAmount >> acc->loanInterestRate >> acc->hasLoan;
            accounts[numAccounts++] = *acc;
        }
        delete acc;
        acc = nullptr;
        inFile.close();
    } else {
        cout << "Unable to open file for reading.\n";
    }

    // Load the next account number from a separate file
    ifstream numFile("nextAccountNumber.txt");
    if (numFile.is_open()) {
        numFile >> nextAccountNumber;
        numFile.close();
    } else {
        cout << "Unable to open nextAccountNumber file for reading. Initializing to 1001.\n";
        nextAccountNumber = 1001;  // Initialize if the file doesn't exist
    }
}
