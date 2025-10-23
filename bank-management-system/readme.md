# Project Description.

A Bank Account System is essential for managing personal finances, allowing users to securely store money, check balances, and transfer funds. Using C language, we can create an application that can manage the data of the Bank, we use basic knowledge of C like string, array, structures, etc.

The functionality of the Bank Management System Project is mentioned below:

- Transfer Money to the Account
- Creation of Account
- Check Amount
- Login Functionality.

# Data organisation. 
A database would be Ideal but lest use a file to store this information between instances.

We load the file, this will contain user detail. Name, address, password, account_amount, Account Number.

Database will be in a struct.

# Functions

- Create an account.
- Check Money in Account.
- Transfer Money from your account to anouther address.

# CLI

./bank create-account
- starts inputs for account.
returns with account number and current deposit amount.

./bank check-amount -account-number <account number> -password <password>
- returns invalud account, incorrect password. or current balance.

./bank transfer-money -account-number <senders-account-number> -password <password> -destination-account <destination-account> -amount <amount>
- returns invalid send account, invalid destination account, incorrect password, insufficient funds or sucessful transfer. 


