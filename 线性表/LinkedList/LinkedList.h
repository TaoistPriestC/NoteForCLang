#pragma once
#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;   // 数据类型有可能是原子类型也有可能是聚合类型
typedef int ElemKey;    // 聚合类型包含的作为主键的一条关键字信息

typedef struct _LNode{
    void *data;
    struct _LNode *next;
}LNode;


LNode* new_node(void *data);


void init_List(LNode* head);
void destroy_List(LNode* head);
void clear_List(LNode* head);
int list_Empty(LNode* head);
int list_Length(LNode* head);

// 判断一个元素在不在链表之中
int locate_Elem(LNode* head, ElemKey key);

// 获取第i个元素
ElemType get_Elem(LNode* head, int i);
ElemType prev_Elem(LNode* head, ElemKey key); // 获取关键字节点的前驱
ElemType next_Elem(LNode* head, ElemKey key); // 获取关键字节点的后继

// 关键字比较函数
int compare_Key(ElemKey key, ElemKey other);

// 遍历整个链表
void list_traverse(LNode* head);

// 增删改查函数
void insert_Elem(LNode* head, void *data);
void delete_Elem(LNode* head, ElemKey key);
void update_Elem(LNode* head, ElemKey key, void *data);
void retrieve_Elem(LNode* head, ElemKey key);