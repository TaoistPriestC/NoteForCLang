#pragma once
#include <stdio.h>
#include <string.h>

typedef struct {
    size_t id;
    char name[30];
    enum{
        STAFF,
        MANAGER,
        CEO
    } job;
    char dstr[50];
} Worker;

#define MAXN 1000

typedef struct {
    Worker workerList[MAXN];
    size_t size;
    size_t isChange;
    size_t allocedMaxID;
} WorkerBook;


void initWorkBook();
void exitWorkBook();


// 删改与查看
void deleteWorkers();
void deleteOneWorker();
void findWorker();
void updateWorker();
void clearWorkers();

// 排序
void sortWorkers();
int sortCmp_asc(Worker *w1, Worker *w2);
int sortCmp_dsc(Worker *w1, Worker *w2);