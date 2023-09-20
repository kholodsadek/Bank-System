#ifndef BANK_ACCOUNT_H_INCLUDED
#define BANK_ACCOUNT_H_INCLUDED

#include <stdbool.h>

typedef enum {
    ACCOUNT_ACTIVE = 0,
    ACCOUNT_RESTRICTED,
    ACCOUNT_CLOSED
} AccountStatus;

typedef struct {
    u8 name[100];
    u8 address[200];
    u32 national_ID;
    u32 age;
    u32 bankAccount_ID;
    bool hasGuardian; // Boolean flag indicating whether a guardian is present
    u32 guardianNational_ID;
    AccountStatus accountStatus; // Enumerated account status
    f64 balance; // Consider using double for balance to handle decimal values
    u8 password[21];
}BankAccount;


u32 generateBankAccountID();
void generateRandomPassword(char *password, int length);
void createNewAccount();
u32 checkID(clientID);
void makeTransaction(u32 clientID);
void changeAccountStatus(clientID);
void getCash(u32 clientID);
void depositInAccount(u32 clientID);

u32 AccessToAccount(u32 clientID, u8 *pass);
void changeAccountPassword(u32 clientID);






#endif // BANK_ACCOUNT_H_INCLUDED
