#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _TreeNode{
    void *data;
    struct _TreeNode *lt;
    struct _TreeNode *rt;
} TreeNode;

typedef TreeNode *TreeNodePtr;
typedef int(Compare)(void *a, void *b);
typedef void(Display)(void *x);

TreeNodePtr newTreeNode(void *data){
    TreeNodePtr node = (TreeNodePtr)malloc(sizeof(TreeNode));
    node->data = data;
    node->lt = NULL;
    node->rt = NULL;
    return node;
}

void DisplayNode(void *x){
    printf("%s\t", (char *)x);
}

int CompareNode(void *a, void *b){
    char *sa = (char *)a;
    char *sb = (char *)b;
    return strcmp(sa, sb);
}

void insertNode(TreeNode **root, Compare cmp, void *data){
    TreeNodePtr node = newTreeNode(data);
    if (*root == NULL){
        *root = node;
        return;
    }
    TreeNode *rootback = *root;
    while(1){
        if (cmp((*root)->data, data) > 0){
            if ((*root)->lt != NULL){
                *root = (*root)->lt;
            }else{
                (*root)->lt = node;
                break;
            }
        }else{
            if ((*root)->rt != NULL){
                *root = (*root)->rt;
            }else{
                (*root)->rt = node;
                break;
            }
        }
    }
    *root = rootback;
}

void preOrder(TreeNode *root, Display display){
    if (root != NULL){
        display(root->data);
        preOrder(root->lt, display);
        preOrder(root->rt, display);
    }
}

void inOrder(TreeNode *root, Display display){
    if (root != NULL){
        inOrder(root->lt, display);
        display(root->data);
        inOrder(root->rt, display);
    }
}

void postOrder(TreeNode *root, Display display){
    if (root != NULL){
        postOrder(root->lt, display);
        postOrder(root->rt, display);
        display(root->data);
    }
}

int main(){
    TreeNode *tree = NULL;
    
    // 插入测试数据
    insertNode(&tree, CompareNode, "PersonB");
    insertNode(&tree, CompareNode, "PersonA");
    insertNode(&tree, CompareNode, "PersonC");
    
    // 树结构三种遍历
    preOrder(tree, DisplayNode);
    printf("\n");
    inOrder(tree, DisplayNode);
    printf("\n");
    postOrder(tree, DisplayNode);
    printf("\n");
    return 0;
}