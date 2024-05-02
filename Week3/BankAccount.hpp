#ifndef BANKACCOUNT_HPP
#define BANKACCOUNT_HPP
class BankAccount
{
    public:
        BankAccount();
        BankAccount(const char *iban, const char *name, const double balance);
        BankAccount(const BankAccount &other);
        BankAccount& operator=(const BankAccount &other);
        ~BankAccount();
        
        void depositMoney(double sum);
        void withdrawMoney(double sum);

        double getBalance() const;
        void printInfo() const;
    private:
        void copy(const BankAccount& other);
        void deallocate();
    private:
        char* iban;
        char* name;
        float balance;
};
#endif