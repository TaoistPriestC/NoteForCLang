#include <stdio.h>
#include <stdlib.h>

typedef struct _Node{
    void *data;
    struct _Node *next;
} Node;
typedef Node *NodePtr;

typedef struct _Stack{
    // 成员变量
    NodePtr top;
    size_t size;

    // 不带返回值的成员方法
    void (*push_stack)(struct _Stack *this, void *data);
    void (*pop_stack)(struct _Stack *this);

    // 带有返回值的成员方法
    NodePtr (*top_stack)(struct _Stack *this);
} Stack;
typedef Stack *StackPtr;


NodePtr newNode(void* data){
    NodePtr node = (NodePtr)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    return node;
}

void _push_stack(struct _Stack *this, void *data){
    NodePtr node = newNode(data);
    node->next = this->top;
    this->top = node;
    this->size++;
}

void _pop_stack(struct _Stack *this){
    NodePtr node = this->top;
    this->top = node->next;
    this->size--;
    free(node);
}

NodePtr _top_stack(struct _Stack *this){
    return this->top;
}

StackPtr newStack(){
    StackPtr this = (StackPtr)malloc(sizeof(Stack));
    this->top = NULL;
    this->size = 0;
    this->push_stack = _push_stack;
    this->pop_stack = _pop_stack;
    this->top_stack = _top_stack;
    return this;
}

void printData(NodePtr node){
    printf("Now the Top Data: %s\n", (char *)node->data);
}

void dumpStack(StackPtr stk){
    NodePtr top = stk->top;
    while (top != NULL){
        printData(stk->top_stack(stk));
        stk->pop_stack(stk);
        top = stk->top;
    }
}

int main(){
    StackPtr stk = newStack();

    stk->push_stack(stk, "PersonA");
    stk->push_stack(stk, "PersonB");
    stk->push_stack(stk, "PersonC");

    dumpStack(stk);

    return 0;
}


