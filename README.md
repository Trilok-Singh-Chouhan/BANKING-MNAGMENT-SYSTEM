# BANKING-MNAGMENT-SYSTEM
# Banking Management System in C++

A **console-based Banking Management System** developed using **C++**, following **Object-Oriented Programming (OOP)** principles and **File Handling** concepts.  
The project includes a **system-level login module** to protect customer data and a **menu-driven banking system** for managing accounts.

---

## Project Overview

This project simulates basic banking operations such as account creation, balance inquiry, deposits, withdrawals, and account deletion.  
Before accessing banking data, the user must **log in or create a system user**, ensuring data security.

---

## Features

### System Login Module
- Login using **username & password**
- Create new system users
- Supports **usernames with spaces**
- Credentials stored securely in a text file

### Banking System
- Create bank account (auto-generated account number)
- View account balance (table format)
- Deposit money
- Withdraw money
- Delete bank account
- PIN-based account security
- Supports long customer names with surname

---

## Concepts Used

- Object-Oriented Programming (OOP)
- Classes and Objects
- Encapsulation (private data members)
- File Handling using text files
- Menu-driven program
- String handling (`string`, `getline`)
- Temporary file method (for update & delete)

---

##  File Structure
Banking-Management-System
│
├── BANKING_MANAGMENT_SYSTEM.cpp
├── users.txt
├── bank.txt
└── README.md
## Sample Output Flow
===== BANK ADMINS LOGIN LOGIN =====
1. Login
2. Create User
3. Exit

(Login Successful)

===== BANK MANAGEMENT SYSTEM =====
1. Create Account
2. View Balance
3. Deposit
4. Withdraw
5. Delete Account
6. Exit


