#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

//using chatgpt

typedef struct {
    int balance;
} BankAccount;

BankAccount account = {1000};

void* deposit(void* amount) {
    int deposit_amount = *(int*)amount;
    int old_balance = account.balance;
    usleep(100);
    account.balance = old_balance + deposit_amount;
    printf("Deposited %d, New Balance: %d\n", deposit_amount, account.balance);
    return NULL;
}

void* withdraw(void* amount) {
    int withdraw_amount = *(int*)amount;
    int old_balance = account.balance;
    usleep(100);
    account.balance = old_balance - withdraw_amount;
    printf("Withdrew %d, New Balance: %d\n", withdraw_amount, account.balance);
    return NULL;
}

int main() {
    pthread_t tid1, tid2;

    int deposit_amount = 500;
    int withdraw_amount = 200;

    pthread_create(&tid1, NULL, deposit, &deposit_amount);
    pthread_create(&tid2, NULL, withdraw, &withdraw_amount);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    printf("Final Balance: %d\n", account.balance);
    return 0;
}