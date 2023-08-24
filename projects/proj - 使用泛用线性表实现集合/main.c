#include <stdio.h>
#include <stdlib.h>

#include "LinkedList.h"

// 用于生成数据
int* val;
int* new_int(int x) {
    val = (int*)malloc(sizeof(int)), *val = x;
    return val;
}


// 使用数组构造链表用于测试
LNode* new_list_test(int A[], int nsize){
    LNode* head = new_node(NULL);
    for (int i = 0; i < nsize; i++){
        insert_Elem(head, new_int(A[i]));
    }
    return head;
}

// 并集
LNode* union_list(LNode *headA, LNode *headB){
    LNode* headC = new_node(NULL);
    for (LNode* curr = headA->next; curr != NULL; curr = curr->next){
        ElemType* block = (ElemType*)curr->data;
        ElemKey key = *block;
        if (!locate_Elem(headC, key)){
            insert_Elem(headC, new_int(key));
        }
    }
    for (LNode* curr = headB->next; curr != NULL; curr = curr->next){
        ElemType* block = (ElemType*)curr->data;
        ElemKey key = *block;
        if (!locate_Elem(headC, key)){
            insert_Elem(headC, new_int(key));
        }
    }
    return headC;
}

// 交集
LNode* intersect_list(LNode* headA, LNode *headB){
    LNode* headC = new_node(NULL);
    for (LNode* curr = headA->next; curr != NULL; curr = curr->next){
        ElemType* block = (ElemType*)curr->data;
        ElemKey key = *block;
        if (locate_Elem(headB, key)){
            insert_Elem(headC, new_int(key));
        }
    }
    return headC;
}

// 差集
LNode* differ_list(LNode* headA, LNode *headB){
    LNode* headC = new_node(NULL);
    for (LNode* curr = headA->next; curr != NULL; curr = curr->next){
        ElemType* block = (ElemType*)curr->data;
        ElemKey key = *block;
        if (!locate_Elem(headB, key)){
            insert_Elem(headC, new_int(key));
        }
    }
    return headC;
}



// 使用链表维护交集与并集测试其它函数接口的准确性
int main(){
    int A[] = {1, 3, 5, 7, 9, 11};
    int B[] = {2, 3, 5, 8, 9, 12};
    LNode* headA = new_list_test(A, sizeof(A) / sizeof(int));
    list_traverse(headA);
    LNode* headB = new_list_test(B, sizeof(B) / sizeof(int));
    list_traverse(headB);

    LNode* headC;

    // 测试两个链表的并集
    headC = union_list(headA, headB);
    list_traverse(headC);
    destroy_List(headC);
    

    // 测试两个链表的交集
    headC = intersect_list(headA, headB);
    list_traverse(headC);
    destroy_List(headC);

    // 测试两个链表的差集
    headC = differ_list(headA, headB);
    list_traverse(headC);
    destroy_List(headC);

    /**
     *  需要注意链表的插入如果使用 insert_Elem(headC, curr->data) 则为浅拷贝，
     * 虽然节点不同，但是使用的都是同一个 data 指针，如果释放 headC，将会牵连
     * 另外两条链表 headA 和 headB，它们的数据域将被破坏！
     */
    destroy_List(headB);
    destroy_List(headA);
    return 0;
}