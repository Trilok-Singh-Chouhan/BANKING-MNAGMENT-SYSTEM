#include <iostream>
#include <fstream>
#include <string>
using namespace std;

bool loginUser() {
    string user, pass, line;

    cout << "Username: ";
    cin >> user;
    cout << "Password: ";
    cin >> pass;

    ifstream in("users.txt");
    while (getline(in, line)) {
        int p = line.find("|");
        string fileUser = line.substr(0, p);
        string filePass = line.substr(p + 1);

        if (user == fileUser && pass == filePass) {
            in.close();
            return true;
        }
    }
    in.close();
    return false;
}

void createUser() {
    string user, pass;
    ofstream out("users.txt", ios::app);

    cin.ignore();  
    cout << "Create Username: ";
    getline(cin, user);   

    cout << "Create Password: ";
    cin >> pass;          

    out << user << "|" << pass << endl;
    out.close();

    cout << "User Created Successfully!\n";
}



class Bank {
private:
    int accNo;
    string name;
    float balance;
    int pin;

public:
    void setData(int a, string n, float b, int p) {
        accNo = a;
        name = n;
        balance = b;
        pin = p;
    }

    int getAccNo() { return accNo; }
    int getPin() { return pin; }
    float getBalance() { return balance; }
    string getName() { return name; }

    void deposit(float amt) { balance += amt; }
    void withdraw(float amt) { balance -= amt; }

    void write(ofstream &out) {
        out << accNo << "|" << name << "|" << balance << "|" << pin << endl;
    }

    bool read(ifstream &in) {
        string line;
        if (!getline(in, line)) return false;

        int p1 = line.find("|");
        int p2 = line.find("|", p1 + 1);
        int p3 = line.find("|", p2 + 1);

        accNo = stoi(line.substr(0, p1));
        name = line.substr(p1 + 1, p2 - p1 - 1);
        balance = stof(line.substr(p2 + 1, p3 - p2 - 1));
        pin = stoi(line.substr(p3 + 1));
        return true;
    }
};


int getNextAccountNo() {
    ifstream in("bank.txt");
    Bank b;
    int last = 1000;
    while (b.read(in)) last = b.getAccNo();
    in.close();
    return last + 1;
}


bool checkPin(int acc, int p) {
    Bank b;
    ifstream in("bank.txt");
    while (b.read(in)) {
        if (b.getAccNo() == acc && b.getPin() == p) {
            in.close();
            return true;
        }
    }
    in.close();
    return false;
}


void createAccount() {
    Bank b;
    ofstream out("bank.txt", ios::app);

    int acc = getNextAccountNo();
    string name;
    float bal;
    int pin;

    cout << "\nYour Account Number: " << acc << endl;
    cin.ignore();
    cout << "Enter Full Name: ";
    getline(cin, name);
    cout << "Enter Initial Balance: ";
    cin >> bal;
    cout << "Create PIN: ";
    cin >> pin;

    b.setData(acc, name, bal, pin);
    b.write(out);
    out.close();

    cout << "Account Created Successfully!\n";
}


void viewBalance() {
    Bank b;
    int acc, pin;
    bool found = false;

    cout << "Account No: ";
    cin >> acc;
    cout << "PIN: ";
    cin >> pin;

    if (!checkPin(acc, pin)) {
        cout << "Wrong PIN\n";
        return;
    }

    ifstream in("bank.txt");

    cout << "\n-----------------------------------------------\n";
    cout << "Acc No\t\tName\t\t\tBalance\n";
    cout << "-----------------------------------------------\n";

    while (b.read(in)) {
        if (b.getAccNo() == acc) {
            cout << b.getAccNo() << "\t\t"
                 << b.getName() << "\t\t"
                 << b.getBalance() << endl;
            found = true;
            break;
        }
    }

    cout << "-----------------------------------------------\n";
    in.close();

    if (!found)
        cout << "Account Not Found\n";
}


void depositMoney() {
    Bank b;
    int acc, pin;
    float amt;

    cout << "Account No: ";
    cin >> acc;
    cout << "PIN: ";
    cin >> pin;

    if (!checkPin(acc, pin)) {
        cout << "Wrong PIN\n";
        return;
    }

    cout << "Amount to Deposit: ";
    cin >> amt;

    ifstream in("bank.txt");
    ofstream out("temp.txt");

    while (b.read(in)) {
        if (b.getAccNo() == acc)
            b.deposit(amt);
        b.write(out);
    }

    in.close(); out.close();
    remove("bank.txt");
    rename("temp.txt", "bank.txt");

    cout << "Deposit Successful\n";
}


void withdrawMoney() {
    Bank b;
    int acc, pin;
    float amt;

    cout << "Account No: ";
    cin >> acc;
    cout << "PIN: ";
    cin >> pin;

    if (!checkPin(acc, pin)) {
        cout << "Wrong PIN\n";
        return;
    }

    cout << "Amount to Withdraw: ";
    cin >> amt;

    ifstream in("bank.txt");
    ofstream out("temp.txt");

    while (b.read(in)) {
        if (b.getAccNo() == acc && amt <= b.getBalance())
            b.withdraw(amt);
        b.write(out);
    }

    in.close(); out.close();
    remove("bank.txt");
    rename("temp.txt", "bank.txt");

    cout << "Withdrawal Done\n";
}


void deleteAccount() {
    Bank b;
    int acc, pin;

    cout << "Account No: ";
    cin >> acc;
    cout << "PIN: ";
    cin >> pin;

    ifstream in("bank.txt");
    ofstream out("temp.txt");

    while (b.read(in)) {
        if (!(b.getAccNo() == acc && b.getPin() == pin))
            b.write(out);
    }

    in.close(); out.close();
    remove("bank.txt");
    rename("temp.txt", "bank.txt");

    cout << "Account Deleted\n";
}


int main() {
    int choice;
    bool loggedIn = false;

   
    do {
        cout << "\n===== BANK ADMINS LOGIN LOGIN =====";
        COUT <<"\n\t\tLOGIN WITH YOUR ID ";
        cout << "\n1. Login";
        cout << "\n2. Create User";
        cout << "\n3. Exit";
        cout << "\nChoice: ";
        cin >> choice;

        if (choice == 1) {
            if (loginUser()) {
                cout << "\nLogin Successful!\n";
                loggedIn = true;
            } else {
                cout << "\nInvalid Credentials!\n";
            }
        }
        else if (choice == 2) {
            createUser();
        }

    } while (!loggedIn && choice != 3);

    if (!loggedIn) return 0;

    
    int ch;
    do {
        cout << "\n===== BANK MANAGEMENT SYSTEM =====";
        cout << "\n1. Create Account";
        cout << "\n2. View Balance";
        cout << "\n3. Deposit";
        cout << "\n4. Withdraw";
        cout << "\n5. Delete Account";
        cout << "\n6. Exit";
        cout << "\nEnter Choice: ";
        cin >> ch;

        if (ch == 1) createAccount();
        else if (ch == 2) viewBalance();
        else if (ch == 3) depositMoney();
        else if (ch == 4) withdrawMoney();
        else if (ch == 5) deleteAccount();

    } while (ch != 6);

    return 0;
}
