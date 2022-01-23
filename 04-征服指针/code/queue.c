#include<stdio.h>
#include<stdlib.h>


typedef struct _Node{
    void *data;
    struct _Node *next;
} Node;
typedef Node *NodePtr;


typedef struct _Queue{
    //成员变量
    NodePtr head;
    NodePtr tail;
    size_t size;

    //不带有返回值的成员方法
    void (*push_queue)(struct _Queue *this, void *data);
    void (*pop_queue)(struct _Queue *this);

    //带有返回值的成员变量
    NodePtr (*first_queue)(struct _Queue *this);
    NodePtr (*last_queue)(struct _Queue *this);
} Queue;
typedef Queue *QueuePtr;


NodePtr newNode(void *data){
    NodePtr node = (NodePtr)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    return node;
}

void _push_queue(struct _Queue *this, void *data){
    NodePtr node = newNode(data);
    if (this->size == 0){
        this->head = node;
        this->tail = node;
    }else{
        this->tail->next = node;
        this->tail = node;
    }
    this->size++;
}

void _pop_queue(struct _Queue *this){
    NodePtr node = this->head;
    this->head = node->next;
    this->size--;
    free(node);
}

NodePtr _first_queue(struct _Queue *this){
    return this->head;
}

NodePtr _last_queue(struct _Queue *this){
    return this->tail;
}

QueuePtr newQueue(){
    QueuePtr this = (QueuePtr)malloc(sizeof(Queue));
    this->head = NULL;
    this->tail = NULL;
    this->size = 0;
    this->push_queue = _push_queue;
    this->pop_queue = _pop_queue;
    this->first_queue = _first_queue;
    this->last_queue = _last_queue;
    return this;
}

void printData(NodePtr node){
    printf("Now the fisrt Data: %s\n", (char *)node->data);
}

void dumpQueue(QueuePtr que){
    NodePtr curr = que->head;
    while (curr != NULL){
        printData(curr);
        que->pop_queue(que);
        curr = que->head;
    }
}

int main(){
    QueuePtr que = newQueue();

    que->push_queue(que, "PersonA");
    que->push_queue(que, "PersonB");
    que->push_queue(que, "PersonC");

    dumpQueue(que);
    
    return 0;
}