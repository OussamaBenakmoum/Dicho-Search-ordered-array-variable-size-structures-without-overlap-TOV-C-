#include <stdio.h>
#include <stdlib.h>
#include "fonctions.c"
int main()
{
    //intro();
    int ind,blc,trouve;
    int choix ;
    char nom[20], mode[20];
    printf("Donnez le nom du fichier : ");
    scanf(" %s", nom);
    printf("Ancien ou Nouveau ? (a/n) : ");
    scanf(" %s", mode);
    if ( mode[0] == 'a' || mode[0] == 'A' )
	    open_file( &f, nom , 'A', &ent );
    else
    {
	    open_file( &f, nom , 'N', &ent );
	    chargement_initiale();	//il va générer des clés ordonnées automatiquement.
    }

    do {
    printf("\n--------- M E N U ---------\n");
	printf("1) Afficher l'entete du fichier\n");
	printf("2) Rechercher un enregistrement dans le fichier\n");
	printf("3) Supprimer un enregistrement dans le fichier\n");
	printf("4) Affichage de bloc(s)\n");
	printf("0) Quitter le programme\n");
	printf("\tchoix : ");
	scanf(" %d", &choix);
	printf("\n---------------------------\n\n");

	switch(choix) {
	   case 1: info(); break;
	   case 2: search_decho(&ind,&blc,&trouve); break;
	   case 3: sup(); break;
	   case 4: parcours(); break;
	}
    } while ( choix != 0);

}
