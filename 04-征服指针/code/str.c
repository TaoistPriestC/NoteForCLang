#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 256
typedef struct string{
    int size;
    int capacity;
    char *buf;
} string;

void init(string * str){
    str->size = 0;
    str->capacity = MAXN;
    str->buf = (char *)calloc(MAXN, sizeof(char));
}

void initByTxT(string *str, const char *txt){
    init(str);
    strcpy(str->buf, txt);
}

void pushback(string *str, const char *txt){
    int extraLen = strlen(txt);
    if(str->size + extraLen >= str->capacity){
        str->capacity = 2 * str->capacity + 1;
        str->buf = (char *)realloc(str->buf, str->capacity);
        if (str->buf == NULL){
            exit(EXIT_FAILURE);
        }
    }
    str->size += extraLen;
    strcat(str->buf, txt);
}

void deleteInterval(string *str, int a, int b){
    while (b < str->size){
        str->buf[a++] = str->buf[b++];
    }
    str->size -= (b - a + 1);
    if(4 * str->size <= str->capacity){
        str->capacity = str->capacity / 2;
        str->buf = (char *)realloc(str->buf, str->capacity);
    }
}

void deleteIndex(string *str, int idx){
    deleteInterval(str, idx, idx);
}


void modifySegment(string *str, int a, int b, char newChar){
     if(a >= 0 && b < this->size && a <= b){
        for (int i = a; i < b; i++){
            str->buf[i] = newChar;
        }
    }
}

void modify(string *str, int idx, char newChar){
    if (idx >= 0 && idx < str->size){
        str->buf[idx] = newChar;
    }
}

char* slice(string *str,int a, int b){
    char *buf = (char *)calloc(b - a + 1, sizeof(char));
    for (int i = a; i < b; i++){
        buf[i] = str->buf[i];
    }
    // 返回动态分配的指针意味着程序员要自己记得释放
    return buf;
}


char* sliceToEnd(string *str,int from){
    return slice(str, from, str->size);
}

int searchByTXT(string * str, const char *txt){
    int txtLen = strlen(txt);
    if(!str || !txt || txtLen > str->size || str->size == 0)
        return -1;
    if(!*txt)
        return 0;

    // 初始化KMP所需的前缀表
    int *prefix = (int *)calloc(txtLen, sizeof(int));

    for (int i = 1; i < txtLen; i++){
        if (txt[i] == txt[prefix[i - 1]]){
            prefix[i] = prefix[i - 1] + 1;
        }else{
            int j = i - 1;
            while (prefix[j] > 0 && txt[prefix[j]] != txt[i]){
                j = prefix[j] - 1;
            }
            if(prefix[j] > 0){
                prefix[i] = prefix[j] + 1;
            }else{
                prefix[i] = (txt[i] == txt[0]);
            }
        }
    }

    int i, j;
    for (i = 0, j = 0; str->buf[i] && j < txtLen; i++){
        if(txt[j]==str->buf[i]){
            ++j;
        }else if(j){
            while (prefix[j - 1] > 0 && txt[prefix[j - 1]] != str->buf[i]){
                j = prefix[j - 1];
            }
            if(prefix[j - 1] > 0){
                j = prefix[j - 1] + 1;
            }
        }else{
            j = (txt[0] == str->buf[i]);
        }
    }

    free(prefix);
    return j < txtLen ? -1 : i - txtLen;
}

int searchByString(string * str, string *pat){
    const char * txt = pat->buf;
    return searchByTXT(str, txt);
}


int main(){
    string t;
    init(&t);
    pushback(&t, "Hello World!~");

    string s;
    init(&s);
    pushback(&s, "ld!");

    /**
     * 此时可以写入一些测试用例,
     * 用于测试函数接口!
     */
    return 0;
}