#include <stdio.h>
#include <stdlib.h>

#include "STD_TYPES.h"
#include "Bank_Account.h"


int main(){
    while(1){
            u8 choice_window,choice_from_window,choice_from_existing_account;
            printf("\n");
            printf(" 1- Admin Window. \n 2- Client Window. \n");
            printf("Enter your choice: ");
            scanf("%d",&choice_window);
            if (choice_window == 1){ //admin window
                printf("******Admin Window******\n");
                printf(" 1- Create New Account. \n 2- Open Existing Account. \n 3- Exit System\n");
                printf("Enter your choice: ");
                scanf("%d",&choice_from_window);
                u32 clientID;
                switch (choice_from_window){
                case 1:
                    //create new account
                    printf("******Create New Account******\n");
                    createNewAccount();
                    break;
                case 2:
                    printf("Enter client Bank Account ID: ");
                    if (scanf("%d", &clientID) != 1) {
                        printf("Invalid input for Bank Account ID.\n");
                        return;
                    }
                    //open existing account
                    printf("******Open Existing Account******\n");
                    printf(" 1- Make Transaction. \n 2- Change Account Status. \n 3- Get Cash. \n 4- Deposit in Account. \n 5- Return to main Menu.\n");
                    printf("Enter your choice: ");
                    scanf("%d",&choice_from_existing_account);
                    switch (choice_from_existing_account){
                    case 1:
                        //make transaction
                        makeTransaction(clientID);
                        break;
                    case 2:
                        //change account status
                        changeAccountStatus(clientID);
                        break;
                    case 3:
                        //get cash
                        getCash(clientID);
                        break;
                    case 4:
                        //deposit in account
                        depositInAccount(clientID);
                        break;
                    case 5:
                        //return to main menu
                        break;
                    }
                    break;
                case 3:
                    //Exit System
                    printf("Thanks for use our System");
                    return 0;
                    break;

                }
            }else if (choice_window == 2){ // client window
                u32 clientID;
                u8 pass[21];
                printf("Bank Account ID: ");
                if (scanf("%d", &clientID) != 1) {
                    printf("Invalid input for Bank Account ID.\n");
                    break;
                }
                printf("Pass: ");
                scanf("%s",&pass);

                if (AccessToAccount(clientID,pass)){
                    printf("******Client Window******\n");
                    printf(" 1- Make Transaction. \n 2- Change Account Password. \n 3- Get Cash. \n 4- Deposit in Account. \n 5- Return to main Menu.\n");
                    printf("Enter your choice: ");
                    scanf("%d",&choice_from_window);
                    switch(choice_from_window){
                    case 1:
                        //make transaction
                        makeTransaction(clientID);
                        break;
                    case 2:
                        //change account password
                        changeAccountPassword(clientID);
                        break;
                    case 3:
                        //get cash
                        getCash(clientID);
                        break;
                    case 4:
                        //deposit in account
                        depositInAccount(clientID);
                        break;
                    case 5:
                        //return to main menu
                        break;
                    }
                }
                else{
                    printf("Bank Account ID is wrong or Password is wrong.\n");
                    break;
                }
            }else
                return 0;
    }
}

