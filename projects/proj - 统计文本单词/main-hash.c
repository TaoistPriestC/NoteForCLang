#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define HASH_SIZE 10000009
#define TOP_SIZE  100

// 使用拉链法构建哈希表，链表
typedef struct ListNode {
	struct ListNode* next;
	char* word;
	int cnt;
} ListNode;

ListNode* hashTable[HASH_SIZE]; // 用于存储词频的哈希表 

int hash(const char* str) {
	int hash_code = 0;
	int len = strlen(str);
	for (int i = 0;i < len; i++) {
		hash_code = (hash_code * 131) % HASH_SIZE;
		if (str[i] == '\''){
			hash_code += 1331;
		} else {
			hash_code += str[i] - 'A' + 1;
		}
		hash_code %= HASH_SIZE;
	}
	return hash_code;
}

ListNode* new_node(char *str, ListNode* next){
	ListNode* node = malloc(sizeof(ListNode));
	node->word = str;
	node->cnt = 1;
	node->next = next;
	return node;
}

void insert_hashtable(char* str) {
	int hash_code = hash(str);
	if (hashTable[hash_code] != NULL) {
		ListNode* ptr = hashTable[hash_code];
		while (ptr != NULL) {
			if (strcmp(ptr->word, str) == 0) {
				ptr->cnt++;
				free(str);
				return;
			}
			ptr = ptr->next;
		}
	}
	hashTable[hash_code] = new_node(str, hashTable[hash_code]);
}

char* read_token(FILE* fp) {
	int c;
	while ((c = fgetc(fp)) != EOF && (!isalpha(c) && c != '\''));
	if (c == EOF){
		return NULL;
	}
	char* result = malloc(sizeof(char) * 2);
	int n = 1;
	result[0] = tolower(c);
	result[1] = 0;
	while ((c = fgetc(fp)) != EOF && (isalpha(c) || c == '\'')) {
		result = realloc(result, sizeof(char) * (n + 2));
		result[n] = tolower(c);
		result[n + 1] = 0;
		n++;
	}
	return result;
}

void statistics(FILE* fout) {
	int tot = 0, diff = 0;
	ListNode* result[TOP_SIZE];
	memset(result, 0, sizeof(result));
	for (int i = 0;i < HASH_SIZE; i++) {
		for (ListNode* curr = hashTable[i]; curr != NULL; curr = curr->next){
			tot += curr->cnt, diff++;
			for (int j = 0; j < TOP_SIZE; j++) {
				if (!result[j] || result[j]->cnt < curr->cnt) {
					for (int k = TOP_SIZE - 1; k >= j; k--) {
						result[k + 1] = result[k];
					}
					result[j] = curr;
					break;
				}
			}
		}
	}
	// 打印结果
	fprintf(fout, "Total number of words = %d\n", tot);
	fprintf(fout, "Number of different words = %d\n", diff);
	// 打印单词与对应词频
	fprintf(fout, "The %d most common words:\n", tot >= 100 ? 100 : tot);
	fprintf(fout, "Word:\t\tFred\n");
	for (int i = 0;i < TOP_SIZE; i++) {
		if (!result[i]){
			break;
		}
		fprintf(fout, "%-17s%d\n", result[i]->word, result[i]->cnt);
	}
}

void free_list(ListNode *head){
	if(head == NULL)
		return;
	free_list(head->next);
	free(head->word);
	free(head);
}

void free_hashTable() {
	for (int i=0;i < HASH_SIZE;i++) {
		free_list(hashTable[i]);
	}
}

int main() {
	memset(hashTable, 0, sizeof(hashTable)); // 初始化哈希表
	char filename[512];						 // 足够大的空间用于存储文件名
	printf("Enter filename: ");
	scanf("%[^\n]", filename); 		 		 // 文件名可能包含空格
	FILE* fp = fopen(filename, "r");
	if (fp == NULL) {
		fprintf(stderr, "Cannot open %s for read\n", filename);
		return EXIT_FAILURE;
	}

	// 使用哈希表统计词频，并且使用计时器设置时间
	char* word;
	double startTime = clock();
	while ((word = read_token(fp)) != NULL){
		insert_hashtable(word);
	}
	double endTime = clock();

	fprintf(stderr, "Time Cost: %.6lf Sec\n", (endTime - startTime) / CLOCKS_PER_SEC);
	statistics(stdout);

	fclose(fp);
	free_hashTable();
	return EXIT_SUCCESS;
}