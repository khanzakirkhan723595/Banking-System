# 🏦 Bank Management System (C++)

A simple **Bank Management System** built using **C++** that simulates basic banking operations like creating accounts, depositing money, withdrawing money, checking balance, and closing accounts.  
This project demonstrates **OOP principles, file handling, STL containers, and exception handling** in C++.

---

## Features
- Open a new bank account  
- Balance enquiry for any account  
- Deposit money into an account  
- Withdraw money with **minimum balance check** (`500`)  
- Close an account  
- Display all existing accounts  
- Persistent data storage using **file handling** (`Bank.data`)  

---

## Tech Stack
- **Language**: C++  
- **Concepts Used**:  
  - Object-Oriented Programming (OOP)  
  - File Handling (`fstream`)  
  - Exception Handling  
  - STL containers (`map`)  

---

## 📂 Project Structure
    .
    ├── Bank.data # File storing account records
    ├── main.cpp # Source code
    └── README.md # Project documentation

---
    
## ⚡ How to Run
1. Clone this repository:
   ```bash
   git clone https://github.com/khanzakirkhan723595/Banking-System.git
   cd bank-management-system

2. Compile the code:
   ```bash
   g++ main.cpp -o bank

3. Run the program:
   ```bash
   ./bank

---

## Sample Output
***Banking System***

    Select one option below 
    1 Open an Account
    2 Balance Enquiry
    3 Deposit
    4 Withdrawal
    5 Close an Account
    6 Show All Accounts
    7 Quit
Enter your choice: 1
Enter First Name: Zakir
Enter Last Name: Khan
Enter Initial Balance: 2000

Congratulation Account is Created
First Name: Zakir
Last Name: Khan
Account Number: 1
Balance: 2000


   
