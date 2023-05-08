#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

#define MAX_WORD_LENGTH 50
#define MAX_WORDS 5000000

#define MIN(x,y)  ((x<y)?(x):(y))
#define MAX(x,y)  ((x>y)?(x):(y))
char filename[MAX_WORD_LENGTH];         // store the file name
char word[MAX_WORD_LENGTH];             // store a single word
char words[MAX_WORDS][MAX_WORD_LENGTH]; // store all words
int counts[MAX_WORDS] = {0};            // store the frequency of each word
int tmp[MAX_WORDS] = {0};               // used to sort and get the top 100 high-frequency words
int num_words = 0, total = 0;

// Trie node
typedef struct TrieNode {
    int count; // record the number of times the word corresponding to this node appears
    int children[256]; // store all child nodes of this node
} TrieNode;

TrieNode trie[MAX_WORDS]; // store the trie of all words
int trie_size = 0; // the size of the trie

// insert a word into the trie
void insert(char* word) {
    int node = 0; // start from the root node
    for (int i = 0; word[i] != '\0'; i++) {
        int c = word[i];
        if (trie[node].children[c] == 0) {
            trie[node].children[c] = ++trie_size; // if the node does not have a corresponding child node, create a new child node
        }
        node = trie[node].children[c]; // continue to traverse the next character
    }
    trie[node].count++; // the word is inserted, increase the counter of this node by one
}

// depth-first search the trie, get the top 100 high-frequency words, and store the tree nodes in tmp, and the word formed by the root node to the tree node in words array
void dfs(int node, int depth) {
    if (trie[node].count > 0) {
        tmp[num_words++] = node;
    }

    if (num_words >= 100) {
        return;
    }
    for (int i = 0; i < 256; i++) {
        if (trie[node].children[i] > 0) {
            tmp[depth] = i;
            dfs(trie[node].children[i], depth + 1);
        }
    }
}



// 比较函数，用于排序
int cmp(const void* a, const void* b) {
    return trie[*(int*)b].count - trie[*(int*)a].count;
}

int main() {
    printf("tell which file your wanna to read...\n"); // prompt the user to input the file name
    scanf("%s", filename); // read the file name from the user
    FILE *fp = fopen(filename, "r"); // open the file
    if (fp == NULL) { // check if the file is opened successfully
        printf("Error opening file\n"); // print an error message if the file cannot be opened
        return 1;
    }

    clock_t start, stop; // define two variables to store the time before and after the program runs
    start = clock(); // record the time before the program runs
    while (fscanf(fp, "%s", word) == 1) { // read each word from the file
        int word_len = strlen(word), j = 0;

        // convert the word to lowercase
        for (int i = 0; i < word_len; i++) {
            word[i] = tolower(word[i]);
        }

        // remove punctuation marks from the word
        for (int i = 0; i < word_len; i++) {
            if (isalpha(word[i])) {
                word[j++] = word[i];
            }
        }
        word[j] = '\0';

        // update the word count
        if(strlen(word) > 0){
            insert(word);
            total++; // only count the word if it contains at least one letter
        }
    }
    fclose(fp); // close the file
    dfs(0, 0); // depth-first search the trie to get the top 100 high-frequency words

    qsort(tmp, num_words, sizeof(int), cmp); // sort the top 100 high-frequency words

    stop = clock(); // record the time after the program runs
    double duration = (double)(stop - start) / CLOCKS_PER_SEC; // convert the time to seconds

    // 打印统计信息
    printf("How many wrods: %d\n", total); // print the total number of words
    printf("How many different words: %d\n", trie_size); // print the number of different words
    printf("How many the time spent for processing the input file: %f\n",duration); // print the time spent processing the input file

    // 打印top-100 高频单词
    printf("Top 100 words's frequency:\n");
    for (int i = 0; i < MIN(num_words, 100); i++) {
        int node = tmp[i];
        printf("%d\n", trie[node].count);
    }

    return 0;
}




