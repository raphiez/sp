#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void print_george() {
    while (1) {
        printf("George\n");
        sleep(1);
    }
}

void print_mary() {
    while (1) {
        printf("Mary\n");
        sleep(2);
    }
}

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        print_george();
    } else {
        pid_t pid2 = fork();
        if (pid2 == 0) {
            print_mary();
        } else {
            while (1) {
                printf("----------------\n");
                sleep(1);
            }
        }
    }
    return 0;
}