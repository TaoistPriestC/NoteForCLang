#include <stdio.h>
#include <stdlib.h>

typedef struct _Node{
    void *data;
    struct _Node *prev;
    struct _Node *next;
} Node;

typedef struct _LinkList{
    Node *head;
    Node *tail;
    Node *curr;
    size_t size;
} LinkList;

typedef Node *NodePtr;
typedef LinkList *LinkListPtr;

LinkListPtr initLinkList(LinkListPtr list, NodePtr val){
    if (list == NULL)
        exit(EXIT_FAILURE);
    list->head = val;
    list->tail = val;
    list->curr = NULL;
    list->size = 0;
    return list;
}

int isEmpty(LinkListPtr list){
    return list->head == NULL && list->tail == NULL;
}

size_t listLength(LinkListPtr list){
    return list->size;
}

NodePtr newNode(void *data){
    NodePtr node = (NodePtr)malloc(sizeof(Node));
    if(node == NULL)
        exit(EXIT_FAILURE);
    node->data = data;
    node->prev = NULL;
    node->next = NULL;
    return node;
}

void addHead(LinkListPtr list, void *data){
    NodePtr node = newNode(data);
    if(isEmpty(list)){
        initLinkList(list, node);
    }else{
        node->next = list->head;
        list->head->prev = node;
        list->head = node;
    }
    list->size++;
}

void addTail(LinkListPtr list, void *data){
    NodePtr node = newNode(data);
    if(isEmpty(list)){
        initLinkList(list, node);
    }else{
        node->prev = list->tail;
        list->tail->next = node;
        list->tail = node;
    }
    list->size++;
}

void subHead(LinkListPtr list){
    if(isEmpty(list)){
        exit(EXIT_FAILURE);
    }else{
        NodePtr node = list->head;
        list->head = node->next;
        free(node);
        if (list->head == NULL){
            list->tail = NULL;
        }else{
            list->head->prev = NULL;
        }
    }
    list->size--;
}

void subTail(LinkListPtr list){
    if(isEmpty(list)){
        exit(EXIT_FAILURE);
    }else{
        NodePtr node = list->tail;
        list->tail = node->prev;
        free(node);
        if (list->tail == NULL){
            list->head = NULL;
        }else{
            list->tail->next = NULL;
        }
    }
    list->size--;
}


// 此处使用下划线代表辅助函数, 但是其实这种命名风格并不好
void _modify(NodePtr node, size_t i ,size_t idx, void *data){
    if (i == idx){
        node->data = data;
        return;
    }
    _modify(node->next, i + 1, idx, data);
}

void modify(LinkListPtr list, size_t idx, void *data){
    if (list != NULL && idx >= 0 && idx < list->size){
        _modify(list->head, 0, idx, data);
    }
}

// 此处使用下划线代表辅助函数, 但是其实这种命名风格并不好
NodePtr _search(NodePtr node, void *data){
    if (node == NULL || node->data == data){
        return node;
    }
    _search(node->next, data);
}

NodePtr search(LinkListPtr list, void *data){
    if (list != NULL){
        return _search(list->head, data);
    }
}

//测试链接功能的函数声明
void printNodeData(void *data);
void printList(NodePtr head);
void printDetail(LinkListPtr list);

void addTest(LinkListPtr list, void (*func)(LinkListPtr list, void *data));
void subTest(LinkListPtr list, void (*func)(LinkListPtr list));




// 下面这种写法其实不太符合面向过程的风格
int main(){
    LinkList *list = initLinkList((LinkList *)malloc(sizeof(LinkList)), NULL);
    
    /**
     * @brief Construct a new Test object
        // UnitTesting1
        addTest(list, addHead);
        subTest(list, subTail);
        printDetail(list);

        // UnitTesting2
        addTest(list, addTail);
        subTest(list, subHead);
        printDetail(list);    

        // UnitTesting3
        addTest(list, addHead);
        subTest(list, subHead);
        printDetail(list);

        // UnitTesting4
        addTest(list, addTail);
        subTest(list, subTail);
        printDetail(list);
    */
    return 0;
}



// 下面都是用来测试链表功能的函数
void printNodeData(void *data){
    printf("->%s", (char *)data);
}


void printList(Node *head){
    if (head == NULL)
        return;
    printNodeData(head->data);
    if (head->next == NULL)
        printf("->NULL[tail]\n");
    printList(head->next);
}


void printDetail(LinkListPtr list){
    printf("Head: %s\n", list->head ? (char *)list->head->data : "NULL");
    printf("Curr: %s\n", list->curr ? (char *)list->curr->data : "NULL");
    printf("Tail: %s\n", list->tail ? (char *)list->tail->data : "NULL");
    printf("Length:%ld\n", listLength(list));
}

void addTest(LinkList *list, void (*func)(LinkList *list, void *data)){
    func(list, "personA");
    printList(list->head);
    func(list, "personB");
    printList(list->head);
    func(list, "personC");
    printList(list->head);
}


void subTest(LinkListPtr list, void (*func)(LinkListPtr list)){
    func(list);
    printList(list->head);
    func(list);
    printList(list->head);
    func(list);
    printList(list->head);
}
