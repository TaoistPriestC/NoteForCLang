#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAXN (256)
#define NUL ('\0')
#define StringPtr struct string *

// 按照上下文语义来确定
typedef char *bytePtr;
typedef char *charPtr;

typedef struct string{
    // 成员变量
    int size;
    int capacity;
    char *buf;
    
    // 成员方法-增删改查
    StringPtr (*push_phrase)(struct string *this, const char *txt);
    StringPtr (*push_char)(struct string *this, char ch);
    StringPtr (*delete_Interval)(struct string *str, int a, int b);
    StringPtr (*delete_Index)(struct string *str, int idx);

    StringPtr (*modify)(struct string *str, int idx, char newChar);
    StringPtr (*modifySegment)(struct string *str, int a, int b, char newChar);

    charPtr (*slice)(struct string *str, int a, int b);
    charPtr (*sliceToEnd)(struct string *str, int from);

    int (*searchByTXT)(struct string *str, const char *txt);
    int (*searchByString)(struct string *str, struct string *pat);
} string;






StringPtr _push_phrase(struct string *this, const char *txt){
    int extraLen = strlen(txt);
    if(this->size + extraLen >= this->capacity){
        this->capacity = 2 * this->capacity + 1;
        this->buf = (char *)realloc(this->buf, this->capacity);
        if(this->buf==NULL){
            exit(EXIT_FAILURE);
        }
    }
    this->size += extraLen;
    strcat(this->buf, txt);
    return this;
}

StringPtr _push_char(struct string *this, char ch){
    if(this->size + 1 >= this->capacity){
        this->capacity = 2 * this->capacity + 1;
        this->buf = (char *)realloc(this->buf, this->capacity);
        if (this->buf == NULL){
            exit(EXIT_FAILURE);
        }
    }
    this->buf[this->size] = ch;
    this->size += 1;
    this->buf[this->size] = NUL;
    return this;
}


StringPtr _delete_Interval(struct string *this, int a, int b){
    while (b < this->size){
        this->buf[a++] = this->buf[b++];
    }
    this->size -= (b - a + 1);
    if(4 * this->size <= this->capacity){
        this->capacity = this->capacity / 2;
        this->buf = (char *)realloc(this->buf, this->capacity);
    }
    return this;
}

StringPtr _delete_Index(struct string *this, int idx){
    _delete_Interval(this, idx, idx);
    return this;
}

StringPtr _modifySegment(struct string *this, int a, int b, char newChar){
    if(a >= 0 && b < this->size && a <= b){
        for (int i = a; i < b; i++){
            this->buf[i] = newChar;
        }
    }
    return this;
}
StringPtr _modify(struct string *this, int idx, char newChar){
    _modifySegment(this, idx, idx + 1, newChar);
    return this;
}


charPtr _slice(struct string *this,int a, int b){
    char *buf = (char *)calloc(b - a + 1, sizeof(char));
    for (int i = a; i < b; i++){
        buf[i] = this->buf[i];
    }
    return buf;
}

charPtr _sliceToEnd(struct string *this, int from){
    return _slice(this, from, this->size);
}

int _searchByTXT(struct string * this, const char *txt){
    int txtLen = strlen(txt);
    if(!this || !txt || txtLen > this->size || this->size == 0)
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
    for (i = 0, j = 0; this->buf[i] && j < txtLen; i++){
        if(txt[j]==this->buf[i]){
            ++j;
        }else if(j){
            while (prefix[j - 1] > 0 && txt[prefix[j - 1]] != this->buf[i]){
                j = prefix[j - 1];
            }
            if(prefix[j - 1] > 0){
                j = prefix[j - 1] + 1;
            }
        }else{
            j = (txt[0] == this->buf[i]);
        }
    }

    free(prefix);
    return j < txtLen ? -1 : i - txtLen;
}

int _searchByString(struct string * this, string *pat){
    const char * txt = pat->buf;
    return _searchByTXT(this, txt);
}


// 构造函数
StringPtr  newString(){
    string *ret = (string *)malloc(sizeof(string));

    ret->size = 0;
    ret->capacity = MAXN;
    ret->buf = (char *)calloc(MAXN, sizeof(char));
    
    //增
    ret->push_phrase = _push_phrase;
    ret->push_char = _push_char;

    //删
    ret->delete_Interval = _delete_Interval;
    ret->delete_Index = _delete_Index;

    // 改
    ret->modify = _modify;
    ret->modifySegment = _modifySegment;

    // 查
    ret->slice = _slice;
    ret->sliceToEnd = _sliceToEnd;
    ret->searchByTXT = _searchByTXT;
    ret->searchByString = _searchByString;
    return ret;
}


StringPtr  newStringByTxT(const char *txt){
    string* ret = newString();
    return  ret->push_phrase(ret, txt);
}


int main(){
    /**
     * 此处可以写入一些简单测试用例,
     * 用于测试接口
     */
    return 0;
}











