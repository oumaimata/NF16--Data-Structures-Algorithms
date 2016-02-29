#ifndef __TP4_f__tp4__
#define __TP4_f__tp4__

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>

typedef struct Node{
    char letter;
    struct Node *parent;
    struct Node *left;
    struct Node *right;
    struct Node *next;
}Node;

typedef struct ListNode{
    struct Node *start;
    int number;
    struct Node *end;
}ListNode;



Node *createNode(char letter);
void generateChilds(Node *node);
void freeTree(Node *root);
void displayTree(Node *root);
ListNode *createList();
void addEndList(ListNode * list, Node *node);
ListNode *generateList(ListNode *list);
void Inverse(Node *node);
void inverse_inter(Node *nN);
int calculateSizeList(ListNode * list);
void displayList(ListNode *list);
void removeList(ListNode *list);
void displayTreeInv(Node *root);

#endif

