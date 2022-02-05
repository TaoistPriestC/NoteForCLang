#include "worker.h"
#include "infoio.h"

#include <stdio.h>
#include <stdlib.h>

WorkerBook wbook;

void initWorkBook(){
    FILE *fp = fopen("database", "rb");
    if (fp != NULL){
        fread(&wbook, sizeof(wbook), 1, fp);
        return;
    }
    exit(EXIT_FAILURE);
}

void exitWorkBook(){
    if(wbook.isChange){
        FILE *fp = fopen("database", "wb");
        if (fp != NULL){
            fwrite(&wbook, sizeof(wbook), 1, fp);
        }
    }
    cls();
    exit(EXIT_SUCCESS);
}


void deleteWorkers(){
    int batch = 0;
    printf("输入待删职工的个数:");
    scanf("%d", &batch);
    wbook.isChange = (batch > 0 ? 1 : 0);
    for (int i = 0; i < batch; i++){
        deleteOneWorker();
    }
}

void deleteOneWorker(){
    size_t id, found = 0;
    printf("输入待删职工的工号:");
    scanf("%ld", &id);
    for (int i = 0; i < wbook.size; i++){
        if (wbook.workerList[i].id == id){
            found = 1;
            for (int j = i; j < wbook.size - 1; j++){
                wbook.workerList[j] = wbook.workerList[j + 1];
            }
            wbook.size--;
            break;
        }
    }
    printf("%s\n", found ? "删除成功" : "删除失败");
    cls();
}

void findWorker(){
    size_t id, found = 0;
    printf("输入待查职工的工号:");
    scanf("%ld", &id);
    for (int i = 0; i < wbook.size; i++){
        if (wbook.workerList[i].id == id){
            found = 1;
            printOneWorker(&wbook.workerList[i]);
            break;
        }
    }
    //显然借助有序性能把这段查找改为二分查找
    printf("%s\n", found ? "查找成功" : "查无此人");
    cls();
}

void updateWorker(){
    size_t id, found = 0;
    printf("输入待改职工的工号:");
    scanf("%ld", &id);
    for (int i = 0; i < wbook.size; i++){
        if (wbook.workerList[i].id == id){
            found = 1;
            scanfOneWorker(&wbook.workerList[i]);
            wbook.isChange = 1;
            break;
        }
    }
    printf("%s\n", found ? "修改成功" : "修改失败");
    cls();
}

void clearWorkers(){
    wbook.size = 0;
    wbook.allocedMaxID = 0;
    cls();
}

void sortWorkers(){
    int op;
    int (*sortCmp)(Worker * w1, Worker * w2);

    printf("选择升序或降序(0升序,1降序):\n");
    scanf("%d", &op);
    sortCmp = op ? sortCmp_dsc : sortCmp_asc;
    for (int i = 0; i < wbook.size; i++){
        int idx = i;
        for (int j = i + 1; j < wbook.size - i; j++){
            if(sortCmp(&wbook.workerList[i],&wbook.workerList[j]) > 0){
                idx = j;
            }
        }
        Worker temp = wbook.workerList[i];
        wbook.workerList[i] = wbook.workerList[idx];
        wbook.workerList[idx] = temp;
    }
    printf("排序成功!\n");
    cls();
}

int sortCmp_asc(Worker *w1, Worker *w2){
    if(w1->id == w2->id){
        return 0;
    }
    return w1->id < w2->id ? -1 : 1;
}

int sortCmp_dsc(Worker *w1, Worker *w2){
    if(w1->id == w2->id){
        return 0;
    }
    return w1->id > w2->id ? -1 : 1;
}