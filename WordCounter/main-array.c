#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

#define MAX_WORD_LENGTH 50
#define MAX_WORDS 100000

#define MIN(x,y)  ((x<y)?(x):(y))
#define MAX(x,y)  ((x>y)?(x):(y))

char filename[MAX_WORD_LENGTH];         // 存储文件名
char word[MAX_WORD_LENGTH];             // 存储单个单词
char words[MAX_WORDS][MAX_WORD_LENGTH]; // 存储所有单词
int counts[MAX_WORDS] = {0};            // 存储词频
int tmp[MAX_WORDS] = {0};               // 用来排序获取前一百名的高频词
int num_words = 0, total = 0;


int cmp(const void *a, const void *b){
    int ax = *(int*)a, bx = *(int*)b;
    return counts[bx] - counts[ax];
}

int main() {
    printf("tell which file your wanna to read...\n");
    scanf("%s", filename);
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    clock_t start, stop; // 定义两个变量用于存储程序运行前后的时间
    start = clock(); // 记录程序运行前的时间
    while (fscanf(fp, "%s", word) == 1) {
        int word_len = strlen(word), j = 0;

        // 转换为小写
        for (int i = 0; i < word_len; i++) {
            word[i] = tolower(word[i]);
        }

        // 去除单词中的标点符号
        for (int i = 0; i < word_len; i++) {
            if (isalpha(word[i])) {
                word[j++] = word[i];
            }
        }
        word[j] = '\0';

        // 更新单词计数
        if(strlen(word) > 0){
            int found = 0;
            for (int i = 0; i < num_words && !found; i++) {
                if (strcmp(word, words[i]) == 0) {
                    counts[i]++, found = 1;
                }
            }
            if (!found) {
                strncpy(words[num_words], word, sizeof(word));
                counts[num_words++]++;
            }
            total++; // 只有当前的单词包含至少一个字母都会计入总单词数
        }
    }
    fclose(fp);
    for (int i = 0; i < num_words; i++){
        tmp[i] = i;
    }
    qsort(tmp, num_words, sizeof(int), cmp);

    stop = clock(); // 记录程序运行后的时间
    double duration = (double)(stop - start) / CLOCKS_PER_SEC; // 换算转为秒数

    // 打印对所有单词的统计
    printf("How many wrods: %d\n", total);
    printf("How many different words: %d\n", num_words);
    printf("How many the time spent for processing the input file: %f\n",duration);
    printf("The 100 most frequent words in descending order:\n");
    for (int i = 0; i < MIN(100, num_words); i++) {
        printf("Word: %-15s  Freq: %6d\n", words[tmp[i]], counts[tmp[i]]);
    }
    return 0;
}