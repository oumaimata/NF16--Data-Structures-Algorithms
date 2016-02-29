#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>

#include "tp4.h"

Node *createNode(char letter){
    Node *nN = (Node*)malloc(sizeof(Node));

    if(nN == NULL){
        printf("Erreur\n");
    }

    nN->letter=letter;
    nN->parent=NULL;
    nN->left=NULL;
    nN->next=NULL;
    nN->right=NULL;

    return nN;
}


void generateChilds(Node *node){

    if (!node) {
        return;
    }

    if(node->letter == 'A'){
        Node *nNl = createNode('B');
        nNl->parent=node;

        node->left=nNl;
        node->right=NULL;
    }
    else if(node->letter == 'B'){
        Node *nNl = createNode('A');
        Node *nNr = createNode('B');

        nNl->parent=node;
        node->left=nNl;

        nNr->parent=node;
        node->right=nNr;
    }
}



void freeTree(Node *root){


    if(root == NULL){
        return;
    }

    freeTree(root->left);
    freeTree(root->right);
    root->left=NULL;
    root->right=NULL;

    free(root);

}



void displayTree(Node *root){
    if(root == NULL ){
        printf("-");
        return;
    }
    if (root->letter == 'A') {
            if(root->left!=NULL){
                printf("{");
                displayTree(root->left);
                printf(",");
                printf("A,");
                printf("-");
                printf("}");
            }
            else{
                printf("A,");
            }
    }

    if (root->letter=='B'){
            if(root->left!=NULL && root->right !=NULL){
                printf("{");
                displayTree(root->left);
                printf("B,");
                displayTree(root->right);
                printf("}");
            }
            else{
                printf("B");
            }
    }
}

void displayTreeInv(Node *root){
    if(root == NULL ){
        printf("-");
        return;
    }
    if (root->letter == 'B') {
            if(root->left!=NULL){
                printf("{");
                displayTreeInv(root->left);
                printf(",");
                printf("B,");
                printf("-");
                printf("}");
            }
            else{
                printf("B,");
            }
    }

    if (root->letter=='A'){
            if(root->left!=NULL && root->right !=NULL){
                printf("{");
                displayTreeInv(root->left);
                printf("A,");
                displayTreeInv(root->right);
                printf("}");
            }
            else{
                printf("A");
            }
    }
}





ListNode *createList(){
    ListNode *nL = (ListNode*)malloc(sizeof(ListNode));

    if(nL == NULL){
        printf("Erreur\n");
        return NULL;
    }

    nL->number = 0;
    nL->start = NULL;
    nL->end= NULL;

    return nL;
}

void addEndList(ListNode *list, Node *node){
    if (list == NULL || node == NULL) {
        return;
    }

    if(list->start == NULL){
        list->start = node;
    }
    else{
        list->end->next=node;
    }
    list->end=node;
    list->number=list->number + 1;
}

ListNode *generateList(ListNode *list){
    Node *temp;
    ListNode *lit = (ListNode*)malloc(sizeof(ListNode));

    if(list == NULL)
        return NULL;

    temp=list->start;
    generateChilds(temp);
    lit->start = temp->left;
    lit->end = temp->left;
    lit->number = 1;


    if(temp->right != NULL){                
        addEndList(lit, temp->right);
    }
    temp=temp->next;
    while(temp != NULL){
        generateChilds(temp);
        addEndList(lit, temp->left);
        if(temp->right != NULL){
            addEndList(lit, temp->right);
        }

        temp=temp->next;
    }
    return lit;
}


void removeList(ListNode *list){
    if (list == NULL) {
        return;
    }
    Node *x, *y;
    x=list->start;
    y=x;

    while(y!=NULL) {
        y=x->next;
        free(x);
        x=y;
    }
    list->start=NULL;
    list->end=NULL;
    list->number=0;
}



void displayList(ListNode *list){
    if (list == NULL) {
        return;
    }
    Node *x;
    x=list->start;
    while(x!=NULL){
        printf("%c ", x->letter);
        x=x->next;
    }
    printf("\n");
}

int calculateSizeList(ListNode * list){
    Node *x;
    int i=0;
    x=list->start;
    while(x!=NULL){
        i++;
        x=x->next;
    }
    return i;
}

// Bonus //

void Inverse(Node *nN){

    if(nN == NULL){
        return;
    }

    if(nN->letter == 'A'){
        nN->letter = 'B';
    }
    else{
        nN->letter = 'A';
    }

    Inverse(nN->left);
    Inverse(nN->right);
}




////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////




