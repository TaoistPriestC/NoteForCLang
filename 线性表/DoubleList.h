#include <stdio.h>
#include <stdlib.h>

typedef struct _DNode{
    void *data;
    struct _DNode *prev;
    struct _DNode *next;
}DNode;