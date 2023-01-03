#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LinkedList.h"


LNode* new_node(void *data){
    LNode* node = (LNode*)malloc(sizeof(LNode));
    node->data = data; 
    node->next = NULL;
    return node;
}

void init_List(LNode* head){
    /**
     *   如果传入的 head 节点是一个局部变量，那么 head 是不可以通过 destroy_List 释放的，
     * 能够释放的部分是哪些分配出来的，放在堆区的节点，然而问题在于不存在一种跨平台的方案来
     * 实现对变量的在堆区或是栈区的判断，判断不了这点，也就无法自动化的分析 head 要不要释放了，
     * 因此释放内存的重要需要程序员自己完成...
     */ 
    *head = *new_node(NULL);
}

void destroy_List(LNode* head){
    if(head == NULL)
        return;
    destroy_List(head->next);
    
    // 释放之后记得需要置空，由于浅拷贝的特点要对节点本身及其数据域单独判定
    if(head != NULL){
        if (head->data != NULL){
            free(head->data), head->data = NULL;
        }
        free(head), head = NULL;
    }
}

void clear_List(LNode* head){
    destroy_List(head);
    if(head != NULL){
        *head = *new_node(NULL);
    }
}

int list_Empty(LNode* head){
    /**
     * 以下两种情况会被认为是空链表，
     *      1. 传入空指针，
     *      2. 传入没有数据的哑节点且哑节点没有挂接任何有意义节点
     */ 
    return head == NULL || (head->next == NULL && head->data == NULL);
}

int list_Length(LNode* head){
    int cnt = 0;
    for (LNode* curr = head->next; curr != NULL; curr = curr->next){
        cnt++;
    }
    return cnt;
}

// 关键字比较函数，这个函数可以根据具体的需求重写
int compare_Key(ElemKey key, ElemKey other){
    if(key == other){
        return 0;
    }else if(key > other){
        return 1;
    }else{ // key < other
        return -1;
    }
}

ElemType get_Elem(LNode* head, int i){
    int cnt = 0;
    void* ret = NULL;
    for (LNode* curr = head->next; curr != NULL; curr = curr->next) {
        if(++cnt == i){
            ret = curr->data;
            break;
        }
    }
    return *((ElemType*)ret);
}

int locate_Elem(LNode* head, ElemKey key){
    for (LNode* curr = head->next; curr != NULL; curr = curr->next) {
        if(!compare_Key(key, *((ElemKey*)curr->data))){
            return 1;
        }
    }
    return 0;
}

ElemType prev_Elem(LNode* head, ElemKey key){
    LNode* prev_node = NULL;
    LNode* curr = head;
    while (curr->next != NULL) {
        if (curr->next->data) {
            ElemType* curr_elem = (ElemType*)curr->next->data;
            ElemKey curr_key = *(curr_elem);
            if (compare_Key(curr_key, key) == 0) {
                prev_node = curr;
                break;
            }
        }
        curr = curr->next;
    }
    if (prev_node == NULL) // 查找不到的时候具体返回什么需要重写
        return 0xFFFFFFFF; 
    return *((ElemType*)(prev_node->data));
}

ElemType next_Elem(LNode* head, ElemKey key){
    LNode* next_node = NULL;
    LNode* curr = head;
    while (curr != NULL) {
        if (curr->data) {
            ElemType* curr_elem = (ElemType*)curr->data;
            ElemKey curr_key = *(curr_elem);
            if (compare_Key(curr_key, key) == 0) {
                next_node = curr->next;
                break;
            }
        }
        curr = curr->next;
    }
    if (next_node == NULL) // 查找不到的时候具体返回什么需要重写
        return 0xFFFFFFFF; 
    return *((ElemType*)(next_node->data));
}

void list_traverse(LNode* head){
    int i = 0;
    for (LNode* curr = head->next; curr != NULL; curr = curr->next, i++) {
        ElemType* t = (ElemType*)curr->data;

        // +===================================+
        // | 下面这段代码需要根据具体的需求来重写 |
        // +===================================+
        if(i){
            printf(" --> ");
        }
        printf("%d", *t);
    }
    printf("\n");
}

// 增删改查函数
void insert_Elem(LNode* head, void *data){
    LNode* node = new_node(data);
    LNode* curr = head;
    while (curr->next != NULL){
        if(curr->next->data){
            // 首先转为 ElemType 类型，然后再从 ElemType 类型的聚合数据里面去除主键,
            ElemType* inserted_elem = (ElemType*)data;
            ElemKey inserted_key = *(inserted_elem);    // 这句话需要根据具体情况改动

            // 与上面同理，这个步骤的转化主要是为了可扩展性
            ElemType* curr_elem = (ElemType*)curr->next->data;
            ElemKey curr_key = *(curr_elem);            // 这句话需要根据具体情况改动

            // 找出第一个较其更大的元素，然后跳出，再将当前 data 构建的节点插在其前一个位置, 如果需要去重，当其等于零，直接结束函数即可
            if(compare_Key(curr_key, inserted_key) >= 0){
                break;
            }
        }
        curr = curr->next;
    }
    node->next = curr->next;
    curr->next = node;
}

void delete_Elem(LNode* head, ElemKey key){
    LNode* curr = head;
    LNode* delete_node = NULL;
    while(curr->next != NULL){
        if(curr->next->data){
            ElemType* curr_elem = (ElemType*)curr->next->data;
            ElemKey curr_key = *(curr_elem);
            if(!compare_Key(curr_key, key)){
                delete_node = curr->next;
                break;
            }
        }
        curr = curr->next;
    }

    // 如果关键字能够找到对应的节点，那么删除并释放
    if (curr->next != NULL && delete_node != NULL) {
        curr->next = curr->next->next;
        free(delete_node->data);
        free(delete_node);
    }
}

// 直接使用 update 是会破坏链表保序性，因而使用这个函数的时候需要慎重
void update_Elem(LNode* head, ElemKey key, void *data){
    LNode* curr = head;
    LNode* update_node = NULL;
    while(curr->next != NULL){
        if(curr->next->data){
            ElemType* curr_elem = (ElemType*)curr->next->data;
            ElemKey curr_key = *(curr_elem);
            if(!compare_Key(curr_key, key)){
                update_node = curr->next;
                break;
            }
        }
        curr = curr->next;
    }
    if(update_node && update_node->data)
        free(update_node->data);
    update_node->data = data;
}

// 枚举所有的节点，查找匹配的关键字
void retrieve_Elem(LNode* head, ElemKey key){
    LNode* curr = head;
    while(curr != NULL){
        if(curr->data){
            ElemType* curr_elem = (ElemType*)curr->data;
            ElemKey curr_key = *(curr_elem);
            if(!compare_Key(curr_key, key)){
                // 此处的操作函数需要根据具体情况重写
                printf("Find it! Value(%d) in List!\n", curr_key);
                break;
            }
        }
        curr = curr->next;
    }
}
