
#pragma once
#define MAXN 1000

#include<stdio.h>
#include<string.h>

typedef struct _Person{
    char name[30];
    char tel[30];
    char addr[30];
    unsigned char sex;
    unsigned char age;
} Person;

typedef struct _AddressBook{
    Person contactList[MAXN];
    size_t size;
} AddressBook;

typedef FILE *File;


ssize_t findContact();

void initContact();
void exitContact();

void addContact();
void subContact();
void modifyContact();
void retrieveContact();

void showContact();
void clearContact();





