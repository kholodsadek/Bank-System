#include "STD_TYPES.h"
#include "Bank_Account.h"

#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAXACCOUNT 100
static BankAccount accounts[MAXACCOUNT];
static u32 numAccount =0;

u32 generateBankAccountID() {
    static u32 accountCounter = 10000; // Starting account ID
    return accountCounter++;
}
void generateRandomPassword(char *password, int length) {
    srand(time(NULL)); // Seed the random number generator
    const char charset[] = "abcdefghijklmnopqrstuvwxyz0123456789";
    for (int i = 0; i < length; i++) {
        int index = rand() % (sizeof(charset) - 1);
        password[i] = charset[index];
    }
    password[length] = '\0'; // Null-terminate the password
}

void createNewAccount(){
    if (numAccount >= MAXACCOUNT) {
        printf("Maximum number of accounts reached.\n");
        return;
    }

    printf("FullName: ");
    fflush(stdin);fflush(stdout);
    scanf("%s", accounts[numAccount].name);
    printf("FullAddress: ");
    fflush(stdin);fflush(stdout);
    scanf("%s", accounts[numAccount].address);
    printf("Age: ");
    fflush(stdin);fflush(stdout);
    scanf("%d", &accounts[numAccount].age);
    printf("National ID: ");
    fflush(stdin);fflush(stdout);
    scanf("%d", &accounts[numAccount].national_ID);

    if(accounts[numAccount].age < 21){
        accounts[numAccount].hasGuardian = true;
        printf("Guardian National ID: ");
        fflush(stdin);fflush(stdout);
        scanf("%d",&accounts[numAccount].guardianNational_ID);
    }
    else {
        accounts[numAccount].hasGuardian = false;
    }
    accounts[numAccount].bankAccount_ID = generateBankAccountID();
    generateRandomPassword(accounts[numAccount].password, 5);
    accounts[numAccount].accountStatus = ACCOUNT_ACTIVE;
    accounts[numAccount].balance = 0.0;

    printf("Your Bank Account ID: %d\n",accounts[numAccount].bankAccount_ID);
    printf("Your Password : %s\n",accounts[numAccount].password);
    if(accounts[numAccount].accountStatus == 0)
        printf("Account Status: ACTIVE\n");
    else if(accounts[numAccount].accountStatus == 1)
        printf("Account Status: RESTRICTED\n");
    else if(accounts[numAccount].accountStatus == 2)
        printf("Account Status: CLOSED\n");

    numAccount++;
}

u32 checkID(clientID){
    //find the client's account
    u32 clientIndex = -1;
    for(u32 i=0;i<numAccount;i++){
        if (accounts[i].accountStatus == ACCOUNT_ACTIVE && accounts[i].bankAccount_ID == clientID){
            clientIndex = i;
            break;
        }
    }
    if (clientIndex == -1){
        printf("Sender's account not found or not active.\n");
        return;
    }

    return clientIndex;
}

void makeTransaction(u32 clientID){
    if (numAccount == 0) {
        printf("No accounts available for transaction.\n");
        return;
    }

    u32 receiverID;
    f64 amount;

    u32 clientIndex = checkID(clientID);
    if (clientIndex == -1){
        return;
    }

    //get receiver's Bank Account ID
    printf("Enter the recipient's Bank Account ID: ");
    fflush(stdin);fflush(stdout);
    if (scanf("%d", &receiverID) != 1) {
        printf("Invalid input for recipient's Bank Account ID.\n");
        return;
    }

    //find the receiver's account
    u32 receiverIndex = -1;
    for(u32 i=0;i<numAccount;i++){
        if (accounts[i].accountStatus == ACCOUNT_ACTIVE && accounts[i].bankAccount_ID == receiverID){
            receiverIndex = i;
            break;
        }
    }
    if (receiverIndex == -1){
        printf("Receiver's account not found or not active.\n");
        return;
    }

    //get the amount to transfer
    printf("Enter the amount to transfer: ");
    fflush(stdin);fflush(stdout);
    if (scanf("%lf", &amount) != 1) {
        printf("Invalid input for amount.\n");
        return;
    }

    //check if the sender has sufficient balance
    if (accounts[clientIndex].balance >= amount){
        //perform the transfer
        accounts[clientIndex].balance -= amount;
        accounts[receiverIndex].balance += amount;
        printf("Transaction completed. $%.2f transferred to account %d.\n", amount , receiverID);
        printf("Account %d have balance now $%.2f\n",clientID,accounts[clientIndex].balance);
    }else {
        printf("Insufficient balance to complete the transaction.\n");
    }
}

void changeAccountStatus(clientID){
    u32 choice;

    u32 clientIndex = checkID(clientID);
    if (clientIndex == -1){
        return;
    }

    printf(" 1- Set Account to Active State \n 2- Set Account to Restricted State \n 3- Set Account to Closed \n");
    printf("Enter the Bank Account Status: ");
    fflush(stdin);fflush(stdout);
    scanf("%d",&choice);
    switch(choice){
    case 1:
        accounts[clientIndex].accountStatus = ACCOUNT_ACTIVE;
        break;
    case 2:
        accounts[clientIndex].accountStatus = ACCOUNT_RESTRICTED;
        break;
    case 3:
        accounts[clientIndex].accountStatus = ACCOUNT_CLOSED;
        break;
    }
}

void getCash(u32 clientID){
    u32 clientIndex = checkID(clientID);
    if (clientIndex == -1){
        return;
    }
    f64 amount;
    printf("Enter the amount you want from this account: ");
    fflush(stdin);fflush(stdout);
    scanf("%lf",&amount);
    if (accounts[clientIndex].balance >= amount){
        accounts[clientIndex].balance -= amount;
        printf("Get your cash $%.2f\n",amount);
        printf("Your balance is have now $%.2f\n",accounts[clientIndex].balance);
    }else{
        printf("Sorry but your balance is not enough\n");
        return;
    }
}

void depositInAccount(u32 clientID){
    u32 clientIndex = checkID(clientID);
    if (clientIndex == -1){
        return;
    }
    f64 amount;
    printf("Enter the amount you want to add to this account: ");
    fflush(stdin);fflush(stdout);
    scanf("%lf",&amount);
    accounts[clientIndex].balance += amount;
    printf("Your money is added Successfully");
}

u32 AccessToAccount(u32 clientID, u8 *pass){
    u32 clientIndex = checkID(clientID);
    if (clientIndex == -1){
        return 0;
    }
    if (clientID == accounts[clientIndex].bankAccount_ID && !strcmp(pass , accounts[clientIndex].password))
        return 1;
    return 0;
}

void changeAccountPassword(u32 clientID){
    u32 clientIndex = checkID(clientID);
    if (clientIndex == -1){
        return 0;
    }
    u8 pass[21];
    printf("Enter your current password: ");
    scanf("%s",&pass);
    if(!strcmp(pass , accounts[clientIndex].password))
    {
        printf("Enter your new password: ");
        scanf("%s",&accounts[clientIndex].password);
    }else{
        printf("Your Password is Wrong.\n");
        return;
    }
}


