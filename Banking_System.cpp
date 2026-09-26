
#include<iostream> 
#include<fstream> 
#include<cstdlib> 
#include<vector> 
#include<map> 
#include <stdexcept> 

using namespace std; 

#define MIN_BALANCE 500 

// Custom exceptions
class InsufficientFunds{}; 
class AccountNotFound{}; 
class InvalidInitialBalance {}; 
class InvalidAmount {}; 


class Account 
{ 
private: 
    long accountNumber; 
    string firstName; 
    string lastName; 
    float balance; 
    static long NextAccountNumber; // Shared account number counter

public: 
    Account(){} 
    Account(string fname,string lname,float balance); 

    // Getter functions
    long getAccNo(){return accountNumber;} 
    string getFirstName(){return firstName;} 
    string getLastName(){return lastName;} 
    float getBalance(){return balance;} 
     
    void Deposit(float amount); 
    void Withdraw(float amount); 

    // Manage account number counter
    static void setLastAccountNumber(long accountNumber); 
    static long getLastAccountNumber(); 

    // Operator overloading for file and console operations
    friend ofstream & operator<<(ofstream &ofs,Account &acc); 
    friend ifstream & operator>>(ifstream &ifs,Account &acc); 
    friend ostream & operator<<(ostream &os,Account &acc); 
}; 

long Account::NextAccountNumber=0; 


class Bank 
{ 
private: 
    map<long,Account> accounts; // Account number -> Account

public: 
    Bank(); 

    // Bank operations
    Account OpenAccount(string fname,string lname,float balance); 
    Account BalanceEnquiry(long accountNumber); 
    Account Deposit(long accountNumber,float amount); 
    Account Withdraw(long accountNumber,float amount); 
    void CloseAccount(long accountNumber); 
    void ShowAllAccounts(); 

    ~Bank(); 
}; 


int main() 
{ 
    Bank b; 
    Account acc; 
     
    int choice; 
    string fname,lname; 
    long accountNumber; 
    float balance; 
    float amount; 

    cout<<"***Banking System***"<<endl; 

    do 
    { 
        cout<<"\n\tSelect one option below "; 
        cout<<"\n\t1 Open an Account"; 
        cout<<"\n\t2 Balance Enquiry"; 
        cout<<"\n\t3 Deposit"; 
        cout<<"\n\t4 Withdrawal"; 
        cout<<"\n\t5 Close an Account"; 
        cout<<"\n\t6 Show All Accounts"; 
        cout<<"\n\t7 Quit"; 

        cout<<"\nEnter your choice: "; 
        cin>>choice; 

        switch(choice) 
        { 
            // Open account
            case 1: 
                cout<<"Enter First Name: "; 
                cin>>fname; 

                cout<<"Enter Last Name: "; 
                cin>>lname; 

                cout<<"Enter initil Balance: "; 
                cin>>balance; 

                try { 
                     acc=b.OpenAccount(fname,lname,balance); 
 
                     cout<<endl<<"Congradulation Account is Created"<<endl; 
                     cout<<acc; 
                  } 
                  catch(InvalidInitialBalance) { 
                     cout<<"Initial balance must be at least " 
                           <<MIN_BALANCE <<endl; 
                  } 
                  catch(const runtime_error& e) { 
                     cout<<"File error: "<<e.what()<<endl; 
                  } 

                break; 


            // Balance enquiry
            case 2: 
                cout<<"Enter Account Number:"; 
                cin>>accountNumber; 

                try{ 
                  acc=b.BalanceEnquiry(accountNumber); 
                  cout<<endl<<"Your Account Details"<<endl; 
                  cout<<acc; 
                } 
                catch(AccountNotFound){ 
                  cout<<"Account does not exist."<<endl; 
                } 

                break; 


            // Deposit money
            case 3: 
                cout<<"Enter Account Number:"; 
                cin>>accountNumber; 

                cout<<"Enter Balance:"; 
                cin>>amount; 

                try { 
                     acc = b.Deposit(accountNumber, amount); 
 
                     cout<<endl<<"Amount is Deposited"<<endl; 
                     cout<<acc; 
                  } 
                  catch(AccountNotFound) { 
                     cout<<"Account does not exist."<<endl; 
                  } 
                  catch(InvalidAmount) { 
                     cout<<"Amount must be greater than zero."<<endl; 
                  } 
                 
                break; 


            // Withdraw money
            case 4: 
                cout<<"Enter Account Number:"; 
                cin>>accountNumber; 

                cout<<"Enter Balance:"; 
                cin>>amount; 

                try { 
                     acc = b.Withdraw(accountNumber, amount); 
 
                     cout<<endl<<"Amount Withdrawn"<<endl; 
                     cout<<acc; 
                  } 
                  catch(AccountNotFound) { 
                     cout<<"Account does not exist."<<endl; 
                  } 
                  catch(InsufficientFunds) { 
                     cout<<"Insufficient funds."<<endl; 
                  } 
                  catch(InvalidAmount) { 
                     cout<<"Amount must be greater than zero."<<endl; 
                  } 

                break; 


            // Close account
            case 5: 
                cout<<"Enter Account Number:"; 
                cin>>accountNumber; 

                try { 
                  b.CloseAccount(accountNumber); 
                  cout << "Account is Closed" << endl; 
               } 
               catch(AccountNotFound) { 
                  cout << "Account does not exist." << endl; 
               } 
 
               break; 


            // Display all accounts
            case 6: 
                b.ShowAllAccounts(); 
                break; 


            // Exit
            case 7: 
                break; 


            default: 
                cout<<"\nEnter corret choice"; 
                exit(0); 
        } 

    }while(choice!=7); 
     
    return 0; 
} 


// Create account and validate initial balance
Account::Account(string fname,string lname,float balance) 
{ 
   if(balance<MIN_BALANCE) 
      throw InvalidInitialBalance(); 

   NextAccountNumber++; 
   accountNumber=NextAccountNumber; 
   firstName=fname; 
   lastName=lname; 
   this->balance=balance; 
} 


// Deposit money after validating amount
void Account::Deposit(float amount) 
{ 
   if(amount <= 0) { 
        throw InvalidAmount(); 
    } 

    balance+=amount; 
} 


// Withdraw money after validation and minimum balance check
void Account::Withdraw(float amount) 
{ 
   if(amount <= 0) { 
        throw InvalidAmount(); 
    } 
 
   if(balance-amount<MIN_BALANCE) 
        throw InsufficientFunds(); 

   balance-=amount; 
} 


// Update last account number
void Account::setLastAccountNumber(long accountNumber) 
{ 
    NextAccountNumber=accountNumber; 
} 


// Return last account number
long Account::getLastAccountNumber() 
{ 
    return NextAccountNumber; 
} 


// Save Account data to file
ofstream & operator<<(ofstream &ofs,Account &acc) 
{ 
    ofs<<acc.accountNumber<<endl; 
    ofs<<acc.firstName<<endl; 
    ofs<<acc.lastName<<endl; 
    ofs<<acc.balance<<endl; 

    return ofs; 
} 


// Read Account data from file
ifstream & operator>>(ifstream &ifs,Account &acc) 
{ 
    ifs>>acc.accountNumber; 
    ifs>>acc.firstName; 
    ifs>>acc.lastName; 
    ifs>>acc.balance; 

    return ifs; 
     
} 


// Display Account data on console
ostream & operator<<(ostream &os,Account &acc) 
{ 
    os<<"First Name:"<<acc.getFirstName()<<endl; 
    os<<"Last Name:"<<acc.getLastName()<<endl; 
    os<<"Account Number:"<<acc.getAccNo()<<endl; 
    os<<"Balance:"<<acc.getBalance()<<endl; 

    return os; 
} 


// Load accounts from Bank.data
Bank::Bank() { 
    Account account; 
    ifstream infile; 
 
    infile.open("Bank.data"); 
 
    if(!infile) 
        return; 
 
    // Read accounts until reading fails
    while(infile >> account) { 
        accounts.insert(pair<long,Account>(account.getAccNo(), account)); 
    } 
 
    // Set counter to the largest existing account number
    if(!accounts.empty()) { 
        Account::setLastAccountNumber(accounts.rbegin()->first); 
    } 
 
    infile.close(); 
} 


// Create account and save updated accounts to file
Account Bank::OpenAccount(string fname,string lname,float balance) 
{ 
    ofstream outfile; 
    Account account(fname,lname,balance); 

    accounts.insert(pair<long,Account>(account.getAccNo(),account)); 
     
    outfile.open("Bank.data", ios::trunc); 
 
    // Check whether file opened successfully
    if(!outfile) { 
      throw runtime_error("Unable to open Bank.data for writing"); 
    } 
 
    map<long,Account>::iterator itr; 
 
    for(itr=accounts.begin();itr!=accounts.end();itr++) { 
      outfile<<itr->second; 
    } 
 
    outfile.close(); 

    return account; 
} 


// Find and return account details
Account Bank::BalanceEnquiry(long accountNumber) 
{ 
    map<long,Account>::iterator itr=accounts.find(accountNumber); 

    // end() means account was not found
    if(itr==accounts.end()) 
      throw AccountNotFound(); 

    return itr->second; 
} 


// Find account and deposit money
Account Bank::Deposit(long accountNumber,float amount) 
{ 
    map<long,Account>::iterator itr=accounts.find(accountNumber); 

    // Check whether account exists
    if (itr == accounts.end()) { 
        throw AccountNotFound(); 
    } 

    itr->second.Deposit(amount); 

    return itr->second; 
} 


// Find account and withdraw money
Account Bank::Withdraw(long accountNumber,float amount) 
{ 
    map<long,Account>::iterator itr=accounts.find(accountNumber); 

    // Check whether account exists
    if(itr==accounts.end()) 
      throw AccountNotFound(); 

    itr->second.Withdraw(amount); 

    return itr->second; 
} 


// Find and remove an account
void Bank::CloseAccount(long accountNumber) 
{ 
    map<long,Account>::iterator itr=accounts.find(accountNumber); 

    // Check whether account exists
    if (itr == accounts.end()) { 
        throw AccountNotFound(); 
    } 

    cout << "Account Deleted" << endl; 
    cout << itr->second; 

    accounts.erase(accountNumber); // Can also use accounts.erase(itr)
} 


// Display all accounts
void Bank::ShowAllAccounts() 
{ 
    map<long,Account>::iterator itr; 

    for(itr=accounts.begin();itr!=accounts.end();itr++) 
    { 
        cout<<"Account "<<itr->first<<endl<<itr->second<<endl; 
    } 
} 


// Save all remaining accounts when Bank object is destroyed
Bank::~Bank() { 
    ofstream outfile; 
    outfile.open("Bank.data", ios::trunc); 
 
    // Destructor reports file error instead of throwing exception
    if(!outfile) { 
        cerr << "Error: Unable to save account data." << endl; 
        return; 
    } 
 
    map<long,Account>::iterator itr; 
 
    for(itr=accounts.begin();itr!=accounts.end();itr++) { 
        outfile<<itr->second; 
    } 

    outfile.close(); 
}

