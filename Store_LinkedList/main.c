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
