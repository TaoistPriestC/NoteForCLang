#include<stdio.h>
typedef struct _Student{
    char name[32];
    unsigned char sex;
    unsigned char age;
    unsigned short rank;
    float score;
} Student;

Student sts[5] = {
    {"某陈", 1, 22, 1, 572.00f},
    {"某蔡", 0, 20, 1, 585.00f},
    {"某曾", 1, 21, 1, 595.00f},
    {"某梁", 1, 20, 1, 582.08f},
    {"某郭", 0, 22, 1, 572.50f}
};

int main(){
    FILE *fp = fopen("dataset", "wb");
    if (fp != NULL){
        fwrite((void *)(&sts[0]), sizeof(Student), 5, fp);
        printf("写入成功!\n");
    }
    for (int i = 0; i < 5; i++){
        printf("%s %hhd %hhd %d %f\n",
                sts[i].name,
                sts[i].sex,
                sts[i].age,
                sts[i].rank,
                sts[i].score);
    }
    return 0;
}