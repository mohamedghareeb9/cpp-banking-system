/**************** PROJECT ON BANKING SYSTEM ***********************/

#include <iostream>
#include <string>
#include <limits>
#include <cctype>
#include <algorithm>
#include <filesystem>
#include <functional>
#include <fstream>
#include <vector>

using namespace std;
namespace fs = std::filesystem;

const string USERS_info = "users/";

string hashPassword(const string& password) {
    std::hash<string> hasher;
    return to_string(hasher(password));
}

class BankingSystem {
private:
    long int account_number{}, balance{}, amount{};
    string name, mob_number, address, email, password; 
    char ch{};
public:
    void open_new_account(vector<BankingSystem>& accounts);
    void account_info();
    void withdraw();
    void deposit();
    void balance_info();
    long int ret();
    void saveAccount();
    bool loadAccount(long int accNumber);
    static bool loginUser(long int account_number, const string& password);
    static bool checkAccountExists(long int account_number, const vector<BankingSystem>& accounts);
};


void BankingSystem::open_new_account(vector<BankingSystem>& accounts) {
    balance = 0;

    cout << "HEY YOU ARE OUR " << (accounts.size() + 1) << " CUSTOMER" << endl << endl;

    cout << "ENTER THE DESIRED ACCOUNT NUMBER" << endl;
    do {
        while (!(cin >> account_number)) {
            cout << "Invalid input! Please enter a number" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        if (checkAccountExists(account_number, accounts)) {
            cout << "ACCOUNT NUMBER ALREADY EXISTS. ENTER UNIQUE ONE." << endl;
        }
        else {
            break;
        }
    } while (true);

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "YOUR NAME PLEASE" << endl;
    getline(cin, name);

    cout << "YOUR ADDRESS" << endl;
    getline(cin, address);

    cout << "YOUR MOBILE NUMBER" << endl;
    cin >> mob_number;
    while (mob_number.length() != 11 || !all_of(mob_number.begin(), mob_number.end(), ::isdigit)) {
        cout << "Mobile Number must be exactly 11 digits (numbers only)" << endl;
        cout << "Re-enter Mobile Number: " << endl;
        cin >> mob_number;
    }

    cout << "ENTER YOUR VALID EMAIL ID" << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, email);

    cout << "SET A PASSWORD FOR YOUR ACCOUNT: " << endl;
    string plainPass;
    cin >> plainPass;
    password = hashPassword(plainPass);

    cout << "DO YOU WANT TO DEPOSIT AMOUNT (Y/N)" << endl;
    cin >> ch;
    saveAccount();
    while (toupper(ch) == 'Y') {
        long int depositAmount;
        cout << "ENTER THE AMOUNT" << endl;

        while (!(cin >> depositAmount) || depositAmount < 0) {
            cout << "Invalid input! Please enter a positive number" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        balance += depositAmount;

        cout << "DO YOU WANT TO ADD MORE DEPOSIT ? (Y/N)" << endl;
        cin >> ch;
    }

    if (toupper(ch) == 'N') {
        cout << "NO WORRIES, YOU CAN ALSO HAVE ZERO BALANCE ACCOUNT" << endl;
    }

    cout << endl;
    cout << "HELLO " << name << ", YOUR ACCOUNT NUMBER "
        << account_number << " HAS BALANCE -> " << balance << endl << endl;
    saveAccount();
}



bool BankingSystem::checkAccountExists(long int accNumber, const vector<BankingSystem>& accounts) {
    for (const auto& acc : accounts) {
        if (acc.account_number == accNumber) return true;
    }
    return false;
}

long int BankingSystem::ret() {
    return account_number;
}

void BankingSystem::account_info() {
    cout << "HELLO " << name << " YOUR ACCOUNT NUMBER "
        << account_number << " HAS BALANCE-> " << balance << endl;
}

void BankingSystem::withdraw() {
    cout << "HELLO " << name << " HAS BALANCE-> " << balance << endl
        << " ENTER THE AMOUNT TO BE WITHDRAWN" << endl;
    do {
        while (!(cin >> amount)) {
            cout << "Invalid input! Please enter a number" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        if (balance < amount)
            cout << "INSUFFICIENT BALANCE" << endl;
        else
            balance -= amount;

        cout << "DO YOU WANT TO CONTINUE WITHDRAWING -Y/N" << endl;
        cin >> ch;
    } while (toupper(ch) == 'Y');
    cout << "NEW BALANCE IS " << balance << endl;
    saveAccount();
}

void BankingSystem::deposit() {
    cout << "HELLO " << name << " HAS BALANCE-> " << balance << endl
        << " ENTER THE AMOUNT TO DEPOSIT" << endl;
    do {
        while (!(cin >> amount)) {
            cout << "Invalid input! Please enter a number" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        balance += amount;
        cout << "DO YOU WANT TO CONTINUE DEPOSITING -Y/N" << endl;
        cin >> ch;
    } while (toupper(ch) == 'Y');
    cout << "NEW BALANCE IS " << balance << endl;
    saveAccount();
}

void BankingSystem::balance_info() {
    cout << "HELLO " << name << " YOU HAVE BALANCE-> " << balance << endl;
}


void BankingSystem::saveAccount() {
    string filename = USERS_info + to_string(account_number) + ".txt";
    ofstream outFile(filename);
    if (outFile.is_open()) {
        outFile << account_number << endl;
        outFile << name << endl;
        outFile << address << endl;
        outFile << mob_number << endl;
        outFile << email << endl;
        outFile << password << endl;  // hashed password
        outFile << balance << endl;
        outFile.close();
    }
}

bool BankingSystem::loadAccount(long int accNumber) {
    string filename = USERS_info + to_string(accNumber) + ".txt";
    if (!fs::exists(filename)) return false;

    ifstream inFile(filename);
    if (!inFile.is_open()) return false;

    string bal, storedAccNo;
    getline(inFile, storedAccNo);
    getline(inFile, name);
    getline(inFile, address);
    getline(inFile, mob_number);
    getline(inFile, email);
    getline(inFile, password);  // hashed
    getline(inFile, bal);
    balance = stol(bal);

    inFile.close();
    account_number = accNumber;
    return true;
}

bool BankingSystem::loginUser(long int account_number, const string& plainPassword) {
    string filename = USERS_info + to_string(account_number) + ".txt";
    if (!fs::exists(filename)) return false;

    ifstream inFile(filename);
    if (!inFile.is_open()) return false;

    string storedAccNo, storedName, storedAddress, storedMob, storedEmail, storedPassword, storedBalance;
    getline(inFile, storedAccNo);
    getline(inFile, storedName);
    getline(inFile, storedAddress);
    getline(inFile, storedMob);
    getline(inFile, storedEmail);
    getline(inFile, storedPassword);
    getline(inFile, storedBalance);
    inFile.close();

    return hashPassword(plainPassword) == storedPassword;
}

// -------------------- MAIN --------------------

int main() {
    fs::create_directory(USERS_info);

    vector<BankingSystem> accounts;

    // Load all existing accounts
    for (const auto& entry : fs::directory_iterator(USERS_info)) {
        if (entry.path().extension() == ".txt") {
            long int accNum = stol(entry.path().stem().string());
            BankingSystem acc;
            if (acc.loadAccount(accNum)) {
                accounts.push_back(acc);
            }
        }
    }

    int wish;
    char demand = 'Y';
    long int tmp;

    do {
        cout << "\t\t\tWELCOME TO SECTION CAIRO BANK\n\n";
        cout << "PRESS 1 TO OPEN NEW ACCOUNT\n";
        cout << "PRESS 2 TO CHECK YOUR ACCOUNT INFO\n";
        cout << "PRESS 3 TO WITHDRAW AMOUNT\n";
        cout << "PRESS 4 TO DEPOSIT AMOUNT\n";
        cout << "PRESS 5 TO CHECK YOUR BALANCE INFO\n";
        cout << "PRESS 6 TO EXIT\n\n";
        cout << "ENTER YOUR WISH: ";
        cin >> wish;

        switch (wish) {
        case 1: {
            BankingSystem newAcc;
            newAcc.open_new_account(accounts);
            accounts.push_back(newAcc);
            break;
        }
        case 2: {
            cout << "ENTER YOUR ACCOUNT NUMBER: ";
            cin >> tmp;
            cout << "ENTER PASSWORD: ";
            string pass;
            cin >> pass;

            if (BankingSystem::loginUser(tmp, pass)) {
                for (auto& acc : accounts) {
                    if (tmp == acc.ret()) {
                        acc.account_info();
                        break;
                    }
                }
            }
            else {
                cout << "Invalid account number or password!\n";
            }
            break;
        }
        case 3: {
            cout << "ENTER YOUR ACCOUNT NUMBER: ";
            cin >> tmp;
            cout << "ENTER PASSWORD: ";
            string pass;
            cin >> pass;

            if (BankingSystem::loginUser(tmp, pass)) {
                for (auto& acc : accounts) {
                    if (tmp == acc.ret()) {
                        acc.withdraw();
                        break;
                    }
                }
            }
            else {
                cout << "Invalid account number or password!\n";
            }
            break;
        }
        case 4: {
            cout << "ENTER YOUR ACCOUNT NUMBER: ";
            cin >> tmp;
            cout << "ENTER PASSWORD: ";
            string pass;
            cin >> pass;

            if (BankingSystem::loginUser(tmp, pass)) {
                for (auto& acc : accounts) {
                    if (tmp == acc.ret()) {
                        acc.deposit();
                        break;
                    }
                }
            }
            else {
                cout << "Invalid account number or password!\n";
            }
            break;
        }
        case 5: {
            cout << "ENTER YOUR ACCOUNT NUMBER: ";
            cin >> tmp;
            cout << "ENTER PASSWORD: ";
            string pass;
            cin >> pass;

            if (BankingSystem::loginUser(tmp, pass)) {
                for (auto& acc : accounts) {
                    if (tmp == acc.ret()) {
                        acc.balance_info();
                        break;
                    }
                }
            }
            else {
                cout << "Invalid account number or password!\n";
            }
            break;
        }
        case 6:
            cout << "THANK YOU\n";
            demand = 'N';
            break;
        default:
            cout << "INVALID CHOICE\n";
            break;
        }

        if (wish != 6) {
            cout << "DO YOU WANT TO CONTINUE BANKING (Y/N): ";
            cin >> demand;
        }

    } while (toupper(demand) == 'Y');
}

