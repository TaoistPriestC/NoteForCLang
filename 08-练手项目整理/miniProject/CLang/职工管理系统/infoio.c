#include "worker.h"
#include "infoio.h"

#include <stdio.h>
#include <stdlib.h>

// 本次项目感觉掌握了extern结构体
extern WorkerBook wbook;

void inputWorkers(){
    Worker w;
    int batch = 0;
    printf("输入员工个数:");
    scanf("%d", &batch);
    wbook.isChange = (batch > 0 ? 1 : 0);
    for (int i = 0; i < batch; i++){
        scanfOneWorker(&w);
        w.id = wbook.allocedMaxID++;
        wbook.workerList[wbook.size++] = w;
    }
    cls();
}


void outputWorkers(){
    int count = wbook.size;
    if(count){
        for (int i = 0; i < count; i++){
            printOneWorker(&wbook.workerList[i]);
        }
    }else{
        printf("职工信息为空!\n");
    }
    cls();
}



void scanfOneWorker(Worker *w){
    int opts = 0;
    printf("输入员工姓名:");
    scanf("%s", w->name);

    printf("输入员工岗位 (0:员工,1:经理,2:总裁):");
    scanf("%d", &opts);

    while(1){
        int ok = 1;
        switch (opts){
            case 0:
                w->job = STAFF;
                break;
            case 1:
                w->job = MANAGER;
                break;
            case 2:
                w->job = CEO;
                break;
            default:
                ok = 0;
                break;
        }
        if(ok)break;
    }
    
    printf("输入员工职责:");
    scanf("%s", w->dstr);
}



void printOneWorker(Worker *w){
    const char *tmp = NULL;
    switch (w->job){
        case STAFF:
            tmp = "员工";
            break;
        case MANAGER:
            tmp = "经理";
            break;
        case CEO:
            tmp = "总裁";
            break;
        default:
            exit(EXIT_FAILURE);
            break;
    }
    printf("\t员工ID:%05ld\t 姓名:%5s\t 岗位:%5s\t 职责:%-12s\t\n", w->id, w->name, tmp, w->dstr);
}

void cls(){
    system("read -p '按任意键继续...' var");
    system("clear");
}