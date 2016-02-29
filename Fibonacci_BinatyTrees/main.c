#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <ctype.h>
#include "tp4.h"

#define MAX 50




int main()
{

    Node *root=NULL ;
    Node *root_inv=NULL ;
    ListNode **tab_list=NULL;
    ListNode **tab_list1=NULL;

    int  i , usrChoice, usrChoice1, nb=0 ,nb_levels=0, maxi=50;


    while (1)
    {
        printf("1 - Initialiser un arbre \n");
        printf("2 - Generer un arbre de niveau n \n");
        printf("3 - Ajouter un niveau \n");
        printf("4 - Supprimer le dernier niveau\n");
        printf("5 - Afficher la liste des feuilles de l'arbre \n");
        printf("6 - Afficher l'arbre \n");
        printf("7 - Calculer le Fibo d'un nombre n \n");
        printf("8 - Detruire l'arbre \n");
        printf("9 - Inverser\n");
        printf("10 - Quitter\n");
        scanf("%d",&usrChoice);


        switch (usrChoice) {
            case 1:
            {
                // Init tree

                nb_levels=1;
                root = createNode('A');

                tab_list = malloc(sizeof(ListNode)*maxi);
                tab_list[0] = createList() ;
                tab_list[0]->start = root;
                tab_list[0]->end = root;
                tab_list[0]->number = 0 ;

                break;


            }
            case 2:
            {

                if (root!=NULL) {
                    printf("Combien de niveaux ?\n");
                    scanf("%d",&usrChoice);

                    for (i=1; i<=usrChoice; i++) {
                        tab_list[i] = generateList(tab_list[i-1]);
                        nb_levels++;
                    }
                }

                else{
                    printf("Aucun arbre initialise \n");
                }

                break;

            }
            case 3:
            {
                if (root!=NULL) {
                    tab_list[nb_levels] = generateList(tab_list[nb_levels-1]);
                    nb_levels++;
                }
                else{
                    printf("Aucun arbre initialise \n");
                }

                break;
            }


            case 4:

            {
                if (root!=NULL) {
                    if(nb_levels>1){
                        removeList(tab_list[nb_levels-1]);
                        nb_levels--;
                    }
                    else{
                        removeList(tab_list[nb_levels-1]);
                        root=NULL;
                        free(tab_list);
                        printf("Racine sup\n");
                    }

                }
                else{
                    printf("Aucun arbre initialise \n");
                }

                break;
            }
            case 5:
            {
                if (root!=NULL) {
                    displayList(tab_list[nb_levels-1]);
                }
                else{
                    printf("Aucun arbre initialise \n");
                }
                break;
            }


            case 6:
            {
                if (root!=NULL) {
                    displayTree(root);
                }
                else{
                    printf("Aucun arbre initialise \n");
                }
                printf("\n");
                break;
            }

            case 7:
            {
                if (root!=NULL) {
                    printf("Calculer fibo de ?\n");
                    scanf("%d",&usrChoice);
                    if(usrChoice<nb_levels){
                        nb=calculateSizeList(tab_list[usrChoice-1]);
                        printf(" fibo = %d \n ",nb);
                    }
                    else{
                        printf("Ce nombre n'a pas encore ete calcule. Generation des niveaux manquants \n");

                        for (i=nb_levels; i<=usrChoice; i++) {
                            tab_list[i] = generateList(tab_list[i-1]);
                            nb_levels++;
                        }
                        nb=calculateSizeList(tab_list[usrChoice-1]);
                        printf(" fibo = %d \n ",nb);
                    }
                }
                else{
                    printf("Aucun arbre initialise \n");
                }
                break;
            }


            case 8:
            {
                if (root!=NULL) {

                    freeTree(root);
                    root=NULL;
                    free(tab_list);
                }
                else{
                    printf("Aucun arbre initialise \n");
                }

                break;
            }

            case 9:
            {

                root_inv = createNode('A');
                tab_list1 = malloc(sizeof(ListNode)*maxi);
                tab_list1[0] = createList() ;
                tab_list1[0]->start = root_inv;
                tab_list1[0]->end = root_inv;
                tab_list1[0]->number = 0 ;

                if (root_inv!=NULL) {
                    for (i=1; i<=nb_levels-1; i++) {
                        tab_list1[i] = generateList(tab_list1[i-1]);
                    }
                }

                else{
                    printf("Aucun arbre initialise \n");
                }

                printf("Arbre initial \n");
                displayTree(root);
                printf("\n");
                Inverse(root_inv);
                if (root_inv!=NULL) {
                    printf("Arbre inverse \n");
                    displayTreeInv(root_inv);
                }
                else{
                    printf("Aucun arbre initialise \n");
                }
                printf("\n");

                break;


            }

            case 10:
            {

                return 1;


            }

        }
    }
}



