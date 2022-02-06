#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "infoio.h"
#include "config.h"
#include "contact.h"


AddressBook adbs;


ssize_t findContact(){
    char pat[30];
    printf("目标联系人姓名:");
    scanf("%s", pat);
    for (int i = 0; i < adbs.size; i++){
        if (strcmp(adbs.contactList[i].name, pat) == 0){
            return i;
        }
    }
    return -1;
}

void initContact(){
    File fp = openFile("database", "r+");
    fscanf(fp, "%ld\n", &adbs.size);
    for (int i = 0; i < adbs.size; i++){
        fscanf(fp, "%s %s %s %hhd %hhd\n",
            &adbs.contactList[i].name[0],
            &adbs.contactList[i].tel[0],
            &adbs.contactList[i].addr[0],
            &adbs.contactList[i].sex,
            &adbs.contactList[i].age);
    }
    adbs.isChange = 0;
    closeFile(fp);
}

void exitContact(){
    printf(WELCOME_NEXT_TIME);
    if(adbs.isChange){
        File fp = openFile("database", "w+");
        fprintf(fp, "%ld\n", adbs.size);
        for (int i = 0; i < adbs.size; i++){
            fprintf(fp, "%s %s %s %hhd %hhd\n",
                adbs.contactList[i].name,
                adbs.contactList[i].tel,
                adbs.contactList[i].addr,
                adbs.contactList[i].sex,
                adbs.contactList[i].age);
        }
        closeFile(fp);
    }
    cls();
    exit(EXIT_SUCCESS);
}


void addContact(){
    if(adbs.size == MAXN){
        printf(AD_BOOK_FULL);
    }else{
        inputContact(&adbs.contactList[adbs.size]);
        adbs.size++;
        adbs.isChange = 1;
    }
    cls();
}


void subContact(){
    ssize_t idx = findContact();
    if (idx < 0){
        printf(PERSON_NO_FOUND);
    }else{
        for (int i = idx; i < adbs.size - 1; i++){
            adbs.contactList[i] = adbs.contactList[i + 1];
        }
        adbs.size--;
        adbs.isChange = 1;
    }
    cls();
}

void modifyContact(){
    ssize_t idx = findContact();
    if (idx < 0){
        printf(PERSON_NO_FOUND);
    }else{
        inputContact(&adbs.contactList[idx]);
        adbs.isChange = 1;
    }
    cls();
}


void retrieveContact(){
    ssize_t idx = findContact();
    if (idx < 0){
        printf(PERSON_NO_FOUND);
    }else{
        header();
        outputContact(&adbs.contactList[idx]);
    }
    cls();
}

void showContact(){
    if (adbs.size == 0){
        printf(AD_BOOK_EMPTY);
    }else{
        header();
        for (int i = 0; i < adbs.size; i++){
            outputContact(&adbs.contactList[i]);
        }
    }
    cls();
}

void clearContact(){
    printf(AD_BOOK_CLEARED);
    adbs.size = 0;
    adbs.isChange = 1;
    cls();
}
