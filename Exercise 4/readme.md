# Multi-threaded Bank Account Program

This repository contains two versions of a multi-threaded banking program written in C. The programs simulate bank transactions and demonstrate the impact of race conditions and the efficacy of mutexes in concurrent environments.

## Program Description

The programs model a bank account with operations for depositing and withdrawing money using multiple threads.

### Version 1: Without Mutex (`race.c`)

- **File:** `race.c`
- This version does not use mutexes and may exhibit race conditions when multiple threads perform concurrent deposits and withdrawals, potentially leading to inconsistent and incorrect account balances.
- It serves as a demonstration of the potential issues in a multi-threaded environment lacking proper synchronization.

### Version 2: With Mutex (`norace.c`)

- **File:** `norace.c`
- This version implements mutex locks to prevent race conditions, ensuring that the account balance remains consistent and correct, regardless of the number of concurrent operations.
- This version illustrates the importance of synchronization mechanisms in multi-threaded applications to maintain data integrity.

## Setup and Execution

### Requirements

- GCC compiler
- POSIX Threads Library (pthread)

### Compilation

Compile the programs using the following commands:

```bash
gcc -o race race.c -pthread
gcc -o norace norace.c -pthread



Run the Program using the following command
./race
./norace
