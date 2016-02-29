                                       TP3.h
#ifndef TP3_H_INCLUDED
#define TP3

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


//Creation des structures
typedef struct Produit{
    char marque[50];
    float prix;
    char qualite;
    int quantite_en_stock;
    struct Produit *suivant;
}T_Produit;

typedef struct Rayon{
    char nom_rayon[50];
    int nombre_produits;
    struct Produit *premier;
    struct Rayon *suivant;
}T_Rayon;

typedef struct Liste{
    char nom_rayon[50];
    char nom_produit[50];
    int quantite;
    int dispo;
    struct Liste *suivant;
}T_Liste;


typedef struct Magasin{
    char nom[50];
    struct Rayon *premier;
    struct Liste *listeProd;
}T_Magasin;




//Prototypes des fonctions


T_Produit *creerProduit(char *marque, float prix, char qualite, int quantite);
T_Rayon *creerRayon(char *nom);
T_Magasin *creerMagasin(char *nom);
T_Liste *creerListe(char *nom_rayon , char *nom_produit , int quantite , int dispo);
T_Magasin *creerMagasin(char *nom);
T_Rayon *creerRayon(char *nom);
T_Produit *creerProduit(char *marque, float prix, char qualite, int quantite);
int ajouterProduit(T_Rayon *rayon, T_Produit *produit);
int ajouterRayon(T_Magasin *magasin, T_Rayon *rayon);
int supprimerRayon(T_Magasin *magasin, char *nom_rayon);
int ajouterProduit(T_Rayon *rayon, T_Produit *produit);
int retireProduit(T_Rayon *rayon , char *nom_produit);
void affichRayon(T_Rayon *nR);
void affichMagasin(T_Magasin *nM);

void rechercheProduits(T_Magasin *magasin, float prix_min, float prix_max);
void traiterListeAchat(T_Magasin *magasin);
void supprimeProduitsRayon(T_Rayon *x);
T_Rayon *select_rayon(T_Magasin *magasin , int rayonNum);

#endif // TP3_H_INCLUDED

                                      TP3.c



#include "tp3.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>



T_Produit *creerProduit(char *marque, float prix, char qualite, int quantite){
    T_Produit *newProduit = malloc(sizeof(T_Produit));  //On rªserve l'emplacement mªmoire

    if(newProduit != NULL){  //On vªrifie l'emplacement mªmoire
        newProduit->suivant=NULL;
        strcpy(newProduit->marque, marque);
        newProduit->prix=prix;
        newProduit->qualite=qualite;
        newProduit->quantite_en_stock = quantite;
    }
    return newProduit;
}


T_Rayon *creerRayon(char *nom){
    T_Rayon *newRayon = malloc(sizeof(T_Rayon));

    if(newRayon != NULL){
        newRayon->suivant=NULL;
        strcpy(newRayon->nom_rayon,nom);
        newRayon->premier = NULL;
        newRayon->nombre_produits=0;
    }
    return newRayon;
}

T_Magasin *creerMagasin(char *nom){
    T_Magasin *newMagasin = malloc(sizeof(T_Magasin));

    if(newMagasin != NULL){
        strcpy(newMagasin->nom, nom);
        newMagasin->listeProd = NULL;
        newMagasin->premier = NULL;
    }
    return newMagasin;
}


T_Liste *creerListe(char *nom_rayon , char *nom_produit , int quantite , int dispo){
    T_Liste *newListe = malloc(sizeof(T_Liste));
    if (newListe!=NULL) {
        newListe->suivant=NULL;
        strcpy(newListe->nom_rayon,nom_rayon);
        strcpy(newListe->nom_produit,nom_produit);
        newListe->quantite = quantite;
        newListe->dispo = dispo;
    }
    return newListe;
}


/////////////////////////////// Ajouter Magasin - Rayon - Produits ///////////////////////////////////////

int ajouterProduit(T_Rayon *rayon, T_Produit *produit)
{
    T_Produit *x;
    x=rayon->premier;

    if (x==NULL || strcmp(produit->marque,x->marque)<0) {
        produit->suivant=rayon->premier;
        rayon->premier=produit;
        rayon->nombre_produits=rayon->nombre_produits+produit->quantite_en_stock;
        return 1;
    }

    else{
        while (x->suivant!=NULL && strcmp(produit->marque,x->suivant->marque)>=0) {
            x=x->suivant;
        }
        if(strcmp(produit->marque,x->marque)==0){
            printf("\n Ce produit existe deja \n");
            return 0;
        }
        produit->suivant=x->suivant;
        x->suivant = produit;
        rayon->nombre_produits=rayon->nombre_produits+produit->quantite_en_stock;
        return 1;
    }

}




int retireProduit(T_Rayon *rayon , char *nom_produit)
{
    T_Produit *x , *pred;



    if (rayon->premier==NULL) {
        printf("\n Aucun produit \n");
        return 0;
    }

    x=rayon->premier;


    //Rech address nom

    while ((x->suivant!=NULL)&&(strcmp(x->marque,nom_produit)!=0) ) {
        x=x->suivant;
    }
    if ((x==rayon->premier && strcmp(rayon->premier->marque,nom_produit)!=0)||strcmp(x->marque,nom_produit)!=0) {
        printf("\n Produit Non Trouve \n");
        return 0;
    }

    //Rech pred

    if (x==rayon->premier) {
        pred = NULL;
    }
    else{
        pred = rayon->premier;
        while (pred->suivant!=x) {
            pred=pred->suivant;
        }
    }

    //Suppression

    if (pred==NULL) {
        if (x->suivant==NULL) {
            free(x);
            rayon->premier = NULL;
        }
        else{
            rayon->premier=x->suivant;
            free(x);
        }
    }
    else{
        pred->suivant=x->suivant;
        free(x);
    }
    rayon->nombre_produits=rayon->nombre_produits-x->quantite_en_stock;

    return 1;


}


int ajouterRayon(T_Magasin *magasin, T_Rayon *rayon){
    T_Rayon *x;
    x=magasin->premier;
    if (x == NULL){ //|| strcmp(rayon->nom_rayon,x->nom_rayon)<0) {
        rayon->suivant=magasin->premier;
        magasin->premier=rayon;
        return 1;
    }

    else{

        while (x->suivant!=NULL && strcmp(rayon->nom_rayon,x->suivant->nom_rayon)>=0) {
            x=x->suivant;
        }
        if(strcmp(rayon->nom_rayon,x->nom_rayon)==0){
            printf(" \n Ce Rayon existe deja \n");
            return 0;
        }
        rayon->suivant=x->suivant;
        x->suivant = rayon;
        return 1;
    }



}



int supprimerRayon(T_Magasin *magasin, char *nom_rayon)
{
    T_Rayon *x , *pred;
    x=magasin->premier;


    //Rech address nom

    while ((x->suivant!=NULL)&&(strcmp(x->nom_rayon,nom_rayon)!=0) ) {
        x=x->suivant;
    }
    if (((x==magasin->premier) && (strcmp(x->nom_rayon,nom_rayon)!=0) )|| (strcmp(x->nom_rayon,nom_rayon)!=0)) {
        printf(" \n Rayon Non Trouve \n");
        return 0;
    }

    //Rech pred

    if (x==magasin->premier) {
        pred = NULL;
    }
    else{
        pred = magasin->premier;
        while (pred->suivant!=x) {
            pred=pred->suivant;
        }
    }

    //Suppression

    if (pred==NULL) {
        if (x->suivant==NULL) {
            supprimeProduitsRayon(x);
            free(x);
            magasin->premier = NULL;
        }
        else{
            magasin->premier=x->suivant;
            supprimeProduitsRayon(x);
            free(x);
        }
    }
    else{
        pred->suivant=x->suivant;
        supprimeProduitsRayon(x);
        free(x);
    }

    return 1;

}



/////////////////////////////// Affichages ///////////////////////////////////////

void affichRayon(T_Rayon *nR)
{
    T_Produit *x;
    x=nR->premier;
    printf("-------------------------------------------------------------------------\n");
    printf("Marque               |     Prix               |               Quantite   \n");
    printf("-------------------------------------------------------------------------\n");
    while (x!=NULL) {

        printf("%s                   |     %.1f               |                  %d      \n",x->marque,x->prix,x->quantite_en_stock);

        x=x->suivant;
    }
    printf("-------------------------------------------------------------------------\n\n");
}


void affichMagasin(T_Magasin *nM)
{
    T_Rayon *x;
    int i=1;
    x=nM->premier;
     printf("--------------------------------------------------------\n");
     printf("    Num    |   Nom Rayon       |    Nombre produits     \n");
     printf("--------------------------------------------------------\n");


    while (x!=NULL) {
        printf("     %d     |      %s           |          %d            \n",i , x->nom_rayon,x->nombre_produits);
        x=x->suivant;
        i++;
    }
     printf(" ------------------------------------------------------------------------ \n");


}


void rechercheProduits(T_Magasin *magasin, float prix_min, float prix_max)
{
    T_Rayon *rayon;
    T_Produit *produit;

    rayon = magasin->premier;
    printf("Marque               |     Prix               |               Quantite  | Rayon  \n");
    printf("----------------------------------------------------------------------------------\n");
    while (rayon!=NULL) {
        produit = rayon->premier;

        while (produit!=NULL) {
            if (((produit->prix)>=prix_min)&&((produit->prix)<=prix_max)) {

                printf("%s                   |     %.1f               |      %d                 |    %s  \n",produit->marque,produit->prix,produit->quantite_en_stock,rayon->nom_rayon);

            }
            produit = produit->suivant;
        }
        rayon = rayon->suivant;

    }
    printf("----------------------------------------------------------------------------------");


}

//////////////////FONCTIONS SUPPLEMENTAIRES////////////////////////


void supprimeProduitsRayon(T_Rayon *x){
    T_Produit *y, *temp;

    y = x->premier;
    temp = NULL;

    while(y->suivant!=NULL){
        temp=y->suivant;
        free(y);
        y=temp;
    }
    free(y);
    free(temp);

    }

T_Rayon *select_rayon(T_Magasin *magasin , int rayonNum)
{
    T_Rayon *rayonSelect;
    int i;


    if (magasin->premier==NULL) {
        printf("\nAucun rayons\n");
        rayonSelect=NULL;
        return rayonSelect;
    }

    rayonSelect = magasin->premier;

    for (i=1; i<rayonNum; i++) {

        if (rayonSelect->suivant==NULL) {
            printf("\nLe rayon n'existe pas\n");
            rayonSelect=NULL;
            return rayonSelect;
        }
        rayonSelect = rayonSelect->suivant;
    }
    return rayonSelect;
}


/////////////////////////BONUS////////////////////////////

void traiterListeAchat(T_Magasin *magasin){

    T_Liste *liste;
    T_Rayon *rayon;
    T_Produit *produit;
    int   quant , dispo ,usrChoice = 1;
    char nomRayon[50] , nomProd[50] ;
    float prixTot = 0 ;



    while (usrChoice==1) {

        printf("\n Entrez Nom Rayon \n");
        scanf("%s",nomRayon);


        printf("\nNom Produit  \n");
        scanf("%s",nomProd);

        printf("\nEntrez  quantite \n");
        scanf("%d",&quant);

        rayon = magasin->premier;
        dispo = 0;

        while (rayon!=NULL) {
            produit = rayon->premier;
            while (produit!=NULL) {


                if  ((strcmp(rayon->nom_rayon,nomRayon)==0)&&(strcmp(produit->marque,nomProd)==0)){

                    if (produit->quantite_en_stock>quant || produit->quantite_en_stock==quant) {
                        dispo=1;
                        produit->quantite_en_stock = produit->quantite_en_stock - quant;
                        rayon->nombre_produits  = rayon->nombre_produits - quant ;

                        if (produit->quantite_en_stock==0) {
                            retireProduit(rayon, produit->marque);
                        }


                    }

                    else if(produit->quantite_en_stock<quant){
                        dispo=2;

                        quant = produit->quantite_en_stock;

                        retireProduit(rayon,produit->marque);

                    }
                    prixTot = prixTot + (quant*produit->prix);

                }


                produit = produit->suivant;
            }
            rayon = rayon->suivant;
        }
        liste = creerListe(nomRayon,nomProd,quant, dispo);


        liste->suivant = magasin->listeProd;
        magasin->listeProd = liste;


        printf("\n Continuer ? \n");
        printf("\n 1 - Oui \n 2 - Non \n");
        scanf("%d",&usrChoice);
        printf("\n \n");
    }

    liste = magasin->listeProd;
    printf(" Rayon      |      Nom produit     |  Quantite          |   Informations  ");
    printf(" ------------------------------------------------------------------------\n ");
    printf("     %s     |       %s             |         %d         | ",liste->nom_rayon,liste->nom_produit,liste->quantite);

    while (liste!=NULL) {


        if (liste->dispo==1) {
            printf("   Produit disponile retire   \n");

        }
        else if (liste->dispo==2){
            printf("   Demande superieur au stock - Maximum stock retire \n");
        }

        else if (liste->dispo==0){

            printf("   Produit Non trouve\n");
        }

        else {
            printf("   Produit indisponible\n");
        }
        liste=liste->suivant;
    }
    printf(" ------------------------------------------------------------------------\n ");
    printf(" Total    :    %0.2f  Ä                                                  \n ",prixTot);
    printf(" ------------------------------------------------------------------------\n\n ");



}


                                    main.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "tp3.h"


////////////////////////////////////////////////////////////////


int main()
{
    char prodName;
    float prodCost;
    char qualProd;
    int prodQut , rayonNum;
    char nomProd;
    char magName , rayonName;
    int r , usrChoice ,prix_max , prix_min;




    T_Magasin *magSelect = NULL;

    T_Rayon *rayonSelect;


    while (1)
    {
        printf("1 - Creer un Magasin \n");
        printf("2 - Ajouter un rayon au magasin \n");
        printf("3 - Ajouter un produit dans un rayon \n");
        printf("4 - Afficher les rayons du magasin \n");
        printf("5 - Afficher les produits d'un rayon \n");
        printf("6 - Retirer un produit \n");
        printf("7 - Supprimer un rayon \n");
        printf("8 - Rechercher un produit par prix \n");
        printf("9 - Entrez liste \n");
        printf("10 - Quitter \n");
        scanf("%d",&usrChoice);


        switch (usrChoice) {
            case 1:
            {
                printf("Nom du magasin ? \n");
                scanf("%s",&magName);
                magSelect = creerMagasin(&magName);
                break;
            }
            case 2:
            {
                if (magSelect==NULL){
                    printf("Aucun magasin - Creer Magasin\n");
                    break;
                }

                printf("Nom du rayon ? \n");
                scanf("%s",&rayonName);

                r = ajouterRayon(magSelect, creerRayon(&rayonName));

                break;
            }
            case 3:
            {

                if (magSelect!=NULL && magSelect->premier!=NULL) {
                    printf("Ajouter dans quel rayon? Rentrez le numero du rayon\n");
                    affichMagasin(magSelect);
                    scanf("%d",&rayonNum);


                    rayonSelect=select_rayon(magSelect, rayonNum);
                    if (rayonSelect==NULL) break;


                    printf("Nom du produit ?\n");
                    scanf("%s",&prodName);
                    printf("Prix du produit ?\n");
                    scanf("%f",&prodCost);
                    printf("Qualite du produit ( A B C )?\n");
                    scanf("%s",&qualProd);
                    printf("Quantite ?\n");
                    scanf("%d",&prodQut);

                    r = ajouterProduit(rayonSelect, creerProduit(&prodName,prodCost,qualProd,prodQut));
                }
                else{
                    printf("\nAucun rayon\n");
                }
                break;
            }


            case 4:

            {
                if (magSelect==NULL){

                    printf("Aucun magasin - Creer Magasin\n");
                    break;

                }

                affichMagasin(magSelect);
                break;
            }
            case 5:
            {
                if (magSelect!=NULL && magSelect->premier!=NULL) {
                    printf("Voir produits de quel rayon?\n");
                    affichMagasin(magSelect);
                    scanf("%d",&rayonNum);

                    rayonSelect=select_rayon(magSelect, rayonNum);
                    if (rayonSelect==NULL) break;


                    affichRayon(rayonSelect);
                }

                else{
                    printf("\nAucun rayon\n");
                }
                break;
            }


            case 6:
            {
                if (magSelect!=NULL && magSelect->premier!=NULL) {


                    printf("Supprimer produit de quel rayon?\n");
                    affichMagasin(magSelect);
                    scanf("%d",&rayonNum);

                    rayonSelect=select_rayon(magSelect, rayonNum);

                    if (rayonSelect->premier==NULL){
                        printf("Aucun produits\n");
                        break;}

                    affichRayon(rayonSelect);

                    printf("Supprimer quel produit ?\n");
                    scanf("%s",&nomProd);
                    retireProduit(rayonSelect,&nomProd);
                }
                else{
                    printf("\nAucun rayon\n");
                }

                break;
            }

            case 7:
            {
                if (magSelect!=NULL && magSelect->premier!=NULL) {

                    printf("Supprimer rayon?\n");
                    affichMagasin(magSelect);
                    scanf("%d",&rayonNum);

                    rayonSelect=select_rayon(magSelect, rayonNum);
                    if (rayonSelect==NULL) break;

                    supprimerRayon(magSelect,rayonSelect->nom_rayon);
                }
                else{
                    printf("\nAucun rayon\n");
                }

                break;
            }


            case 8:
            {
                if (magSelect!=NULL && magSelect->premier!=NULL) {

                    printf("Prix Min ?\n");
                    scanf("%d",&prix_min);
                    printf("Prix Max ?\n");
                    scanf("%d",&prix_max);
                    rechercheProduits(magSelect,prix_min,prix_max);
                }
                else{
                    printf("\nAucun rayon\n");
                }
                break;
            }

            case 9:
                traiterListeAchat(magSelect);

                break;

            case 10:
                return 1;

            case 11:

                r = ajouterRayon(magSelect, creerRayon("Jeux"));
                r = ajouterRayon(magSelect, creerRayon("Tv"));

                rayonSelect=select_rayon(magSelect, 1);
                r = ajouterProduit(rayonSelect, creerProduit("Aee",3,'A',4));
                r = ajouterProduit(rayonSelect, creerProduit("Lsj",3,'A',1));
                r = ajouterProduit(rayonSelect, creerProduit("Adez",3,'A',1));
                r = ajouterProduit(rayonSelect, creerProduit("Ncdsj",3,'A',2));

                rayonSelect=select_rayon(magSelect, 2);
                r = ajouterProduit(rayonSelect, creerProduit("ecxwlc",3,'A',4));
                r = ajouterProduit(rayonSelect, creerProduit("sdf",3,'A',1));
                r = ajouterProduit(rayonSelect, creerProduit("dsf",3,'A',5));
                r = ajouterProduit(rayonSelect, creerProduit("sqfsqf",3,'A',2));

                break;

            default:
                return 1;
        }


    }
}





