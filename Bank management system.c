#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char name[20];
int dep_amt, amt = 10000, acc_no;
int trans_amt;
int count = 0;
int with_amt;

void menu();
void deposit_money();
void withdraw_money();
void transfer_money();
void account_detail();
void transaction_detail();
void last_details();

void divider() {
    for (int i = 0; i < 50; i++) {
        printf("-");
    }
    printf("\n");
}

int main() {
    int choice;

    printf("Enter your name: ");
    fgets(name, sizeof(name), stdin);

    printf("Enter your account no: ");
    scanf("%d", &acc_no);

    while (1) {
        menu();

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                system("cls"); // Use "clear" instead of "cls" on Linux/macOS
                deposit_money();
                break;
            case 2:
                system("cls");
                withdraw_money();
                break;
            case 3:
                system("cls");
                transfer_money();
                break;
            case 4:
                system("cls");
                account_detail();
                break;
            case 5:
                system("cls");
                transaction_detail();
                break;
            case 6:
                system("cls");
                last_details();
                exit(0);
            default:
                printf("Invalid Choice!\n");
                break;
        }
    }

    return 0;
}

void menu() {
    system("cls");
    printf("MAIN MENU\n");
    divider();
    printf("1. Deposit Money\n");
    printf("2. Withdraw Money\n");
    printf("3. Transfer Money\n");
    printf("4. Account details\n");
    printf("5. Transaction details\n");
    printf("6. Exit\n");
    divider();
}

void deposit_money() {
    time_t tm;
    time(&tm);
    FILE *ptr = fopen("Account.txt", "a");

    if (ptr == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("Depositing Money\n");
    divider();
    printf("Enter the amount: ");
    scanf("%d", &dep_amt);

    amt += dep_amt;
    printf("Money Deposited\n");
    printf("Current balance: %d\n", amt);

    fprintf(ptr, "Tk%d had been deposited to your account\n", dep_amt);
    fprintf(ptr, "Date / time of transaction: %s\n", ctime(&tm));
    count++;

    fclose(ptr);

    printf("Press Enter to continue...");
    while (getchar() != '\n'); getchar();
}

void withdraw_money() {
    FILE *fp = fopen("Account.txt", "a");
    time_t tm;
    time(&tm);

    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("WITHDRAW MONEY\n");
    divider();
    printf("Enter the amount: ");
    scanf("%d", &with_amt);

    if (amt < with_amt) {
        printf("Insufficient balance\n");
    } else {
        amt -= with_amt;
        printf("MONEY WITHDRAWN\n");
        printf("Current balance: %d\n", amt);
        fprintf(fp, "\nTk%d has been withdrawn from your account\n", with_amt);
        fprintf(fp, "Date/Time of transaction: %s\n", ctime(&tm));
        count++;
    }

    fclose(fp);

    printf("Press Enter to continue...");
    while (getchar() != '\n'); getchar();
}

void transfer_money() {
    int ac;
    FILE *ptr = fopen("Account.txt", "a");
    time_t tm;
    time(&tm);

    if (ptr == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("TRANSFERRING MONEY\n");
    divider();
    printf("Enter the amount: ");
    scanf("%d", &trans_amt);
    printf("Enter the account no in which you want to transfer the money: ");
    scanf("%d", &ac);

    if (amt < trans_amt) {
        printf("You don't have sufficient balance\n");
    } else {
        amt -= trans_amt;
        printf("Money transferred\n");
        printf("Current balance: %d\n", amt);
        fprintf(ptr, "Tk%d has been transferred to account no %d\n", trans_amt, ac);
        fprintf(ptr, "Date/Time of transaction: %s\n", ctime(&tm));
        count++;
    }

    fclose(ptr);

    printf("Press Enter to continue...");
    while (getchar() != '\n'); getchar();
}

void account_detail() {
    printf("ACCOUNT DETAILS\n");
    divider();
    printf("Name: %s", name);
    printf("Account No: %d\n", acc_no);
    printf("Total Balance: %d\n", amt);
    printf("No of transactions made through your account: %d\n", count);

    printf("Press Enter to continue...");
    while (getchar() != '\n'); getchar();
}

void transaction_detail() {
    FILE *ptr = fopen("Account.txt", "r");

    if (ptr == NULL) {
        printf("No transactions found.\n");
    } else {
        printf("Transaction Details\n");
        divider();
        char c = fgetc(ptr);
        if (c == EOF) {
            printf("No recent transactions\n");
        } else {
            while (c != EOF) {
                printf("%c", c);
                c = fgetc(ptr);
            }
        }
        fclose(ptr);
    }

    printf("Press Enter to continue...");
    while (getchar() != '\n'); getchar();
}

void last_details() {
    printf("Account Summary\n");
    divider();
    printf("Name: %s", name);
    printf("Account No: %d\n", acc_no);
    printf("Current Balance: %d\n", amt);

    printf("Press Enter to exit...");
    while (getchar() != '\n'); getchar();
}
