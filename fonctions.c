#include "fonctions.h"


void open_file( FILE **f, char *name, char mode, header_type *head )
{
   if ( mode == 'A' || mode == 'a' ) {
	*f = fopen( name, "rb+" );
	if ( *f == NULL ) perror( "ouvrir (probleme dans fopen)" );
	fread( head, sizeof(header_type), 1, *f );
   }
   else { // mode == 'N' || mode == 'n'
	*f = fopen( name, "wb+" );
	if ( *f == NULL ) perror( "ouvrir (probleme dans fopen)" );
	head->last_bloc = 0;
	fwrite( head, sizeof(header_type), 1, *f );
   }
}

void close_file( FILE *f, header_type *head)
{
   fseek(f, 0L, SEEK_SET);
   fwrite( head, sizeof(header_type), 1, f );
   fclose(f);
}
void lireDire( FILE *f, long i, bloc_type *buf )
{
   fseek(f, sizeof(header_type) + (i-1)*sizeof(bloc_type), SEEK_SET);
   fread( buf, sizeof(bloc_type), 1, f );
}

void ecrireDire( FILE *f, long i, bloc_type *buf ,header_type *head )
{
   fseek(f, 0L, SEEK_SET);
   fwrite( head, sizeof(header_type), 1, f );
   fseek(f, sizeof(header_type) + (i-1)*sizeof(bloc_type), SEEK_SET);
   fwrite( buf, sizeof(bloc_type), 1, f );
}

void randomchaine(char *chaineAleatoire, int taille)//elle va genere une chaine randomly pour l'information
{
   int i, longueurChaine = 0;
   char chaine[] = "abcdefghijklmnpqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

   longueurChaine = strlen(chaine);
   srand(time(NULL));
  for(i=0; i != taille; i++)
        {
            chaineAleatoire[i] = chaine[rand()%longueurChaine];
        }
    chaineAleatoire[i] = '\0';
}


void chargement_initiale()
{
   int bloc,nbr_enre,lenght;
   char taille[3];
   int new_bloc = 1;
   int cle_integer = 1000000000; //initialiser la clé en entier du taille de 10 caracteres
   char clee[11] = "";  //utile pour sauvgarder la derniere clé placé dans le tableau.
   int j = 0;   //pour parcourir le tableau.
   int i =1;   //pour les enregistrements.
   bloc = 1;
   ent.last_bloc = 1;   //une initialisation.
   printf("saisir le nombre des enregistrements :   ");
   scanf("%d",&nbr_enre);
   while (i <= nbr_enre) //je vais inserer enregistrement par enregistrement
   {
      char cle[11]="";
      printf("\n\n*******BLOC C : %d        ENREGISTREMENT  : %d   ******\n\n",bloc,i);
      printf("       saisir la taille : ");  //Je demande que la taille de l'information , je la génère randomly.
      scanf("%s",&taille); //lire la taille comme une chaine de caracteres.
      lenght = atoi(&taille); //atoi une fonction prédefinie , transforme une chaine en entier.
      {//un traitement speciale pour ajouter des 000 , pour occuper exactement 3 cases .
          if (lenght<10){taille[2]=taille[0];taille[0]='0';taille[1]='0';}
          else
          {
             if (lenght<100){taille[2]=taille[1];taille[1]=taille[0];taille[0]='0';}
          }

      }
      char information[lenght];
      randomchaine(information,lenght); //une information de taille lenght.
      if (lenght+j+4+10 <= max) //il y a de l'space dans le bloc .
      {
         int l = 0;
         for (l=0; l<=2; l++) //je vais inserer la taille.
         {
            buf.table[j+l] = taille[l];
         }
         j = j + 3;  //assurer toujours que J pointe vers la derniere position libre du tableau.
         buf.table[j] = 'f';  //lors du  chargement initiale, il ne pourra pas etre supprimé.
         j++;
         itoa(cle_integer,cle,10);//la chaine de clé reçoie l'entier cle_integer en base 10. (le contraire de la fonction atoi précedemment utilisée).
         l=0;
         for (l=0; l<=9; l++) //Je vais inserer la clé .
         {
            buf.table[j+l] = cle[l];
         }
         j = j + 10;
         l = 0;
         for (l=0; l<= lenght; l++)    // je vais inserer l'information.
         {
            buf.table[j+l] = information[l];
         }
         j = j + lenght;
         buf.free_pos = j;
         if (new_bloc == 1)//sauvgarder la petite du bloc .
         {
            strcpy(buf.key1,cle);
            new_bloc = 0;
         }
         int m = 0;
         for (m=0; m<=9; m++)
         {
            clee[m] = cle[m]; //sauvegarder la derniere la derniere clé .
            //printf("%c",clee[m]);
         }
         cle_integer++;
         i++;
      }
      else // il n'ya pas de l'éspace dans le bloc courant .
      {
         new_bloc = 1;
         strcpy(buf.key2,clee);  //sauvegarder la grande clé du bloc .
         ecrireDire(f,bloc,&buf,&ent); //ecrire le bloc courant dans le fichier.
         bloc++; //je vais passer au bloc suivant .
         j = 0;   //initialiser le curseur du tableau.
      }
   }
   //ici,je vais inserer mon dernier bloc.
   ent.last_bloc = bloc;   //sauvegarder le numero du dernier bloc.
   strcpy(buf.key2,clee);  //sauvgarder la grande clé de dernier bloc.
   ecrireDire(f,bloc,&buf,&ent);  //ecrire le dernier bloc.
}

int extract(int from, int to, char *chaine, char *sousChaine)
{
	int i=0, j=0;
	//récupérer la longueur de la chaîne
	int length = strlen(chaine);

	if( from > length || from < 0 ){
		printf("L'index 'from' est invalide\n");
		return 1;
	}
	if( to > length ){
		printf("L'index 'to' est invalide\n");
		return 1;
	}
	for( i = from, j = 0; i <= to; i++, j++){
		sousChaine[j] = chaine[i];
	}
	return 0;
}




void search_decho (int *indice, int *bloc, int *trv)
{
    system("CLS");
   printf("\n BIENVENUE dans notre procedure de recherche dechotomique (utilisée aussi dans la suppression.) \n");
   printf("les cles sont generees aleatoirement et par ordre de la maniere suivante : \n");
   printf("A partir de 1000000000   jusqu'a 1000000000+nombre enregistrements-1 \n");
   printf("vous pouvez faire copier/coller pour ne pas tromper dans la clé voulue.\n");
   int key_seach, b_init, b_sup, trouve, stop;
   printf("\n\n Saisir la clé que vous voulez rechercher (Supprimer) : ");
   scanf("%d",&key_seach);
   b_init = 1;
   printf("\n");
   b_sup = ent.last_bloc;
   trouve = 0;    //faux
   stop = 0;   //faux
   int i;
   int int_key1,int_key2;
   while (b_init <= b_sup && stop == 0)   //recuperer le bloc qui peut contenir la clé recherchée .
   {

      i = (b_init + b_sup) /2 ;
      lireDire(f,i,&buf);
      int_key1 = atoi(&buf.key1);
      int_key2 = atoi(&buf.key2);
      if (key_seach >= int_key1 && key_seach <= int_key2)
      {
         stop = 1;
         //printf("rani dert stop");
      }
      else
      {
         if (key_seach < int_key1)
         {
            b_sup = i - 1 ;
         }
         else
         {
            b_init = i + 1 ;
         }
      }
   }
   int j = 0 ;
   char taille[4]="";
   char etat = "" ;
   char chaine_cle[11]="";
   int key;
   if (stop == 1)
   {
      //printf("\n rani dkhalte stop\n");
      while (j<=buf.free_pos && trouve == 0) //je vais rechercher dans le bloc , d'une maniere séquentielle , vu que je ne suis plus dans la mémoire secondaire.
      {
         taille[0] = buf.table[j];
         taille[1] = buf.table[j+1];
         taille[2] = buf.table[j+2];
         int lenght = atoi(&taille);   //récuperer et transformer la taille en entier.
         j = j + 3;
         etat = buf.table[j]; //récupérer l'état de l'enregistrement.
         int h = j+1;
         extract(j+1,j+10,buf.table,chaine_cle);   //recuperer la clé.
         key = atoi(&chaine_cle);   //transformer la clé vers entier.
         j = j + 11;
         if (key == key_seach && etat == 'f')
         {
            int choice;
            *trv = 1;
            trouve = 1;
            *bloc = i;
            *indice = h;
            printf("\n la cle existe bien dans votre fichier \n");
            printf("\n Plus d'information (1/0) ??  :   ");
            scanf("%d",&choice);
            if (choice == 1)
            {
               printf("\n la clé existe dans le bloc :  %d \n",i);
               printf("    A partir de l'indice : %d \n",h);
               printf("la plus petite cle : %s || la plus grande cle : %s  \n",buf.key1,buf.key2);
               printf("le contenu du BLOC est :  \n");
               int m = 0;
               printf("---------------------------------------------------------\n");
               for (m=0; m<=buf.free_pos; m++)
               {
                  printf("%c",buf.table[m]);
               }
               printf("\n---------------------------------------------------------\n");
            }
         }
         else
         {
            if (etat == 'v')
            {
                printf("\n la clé que vous cherchiez est déja supprimée de mon fichier \n");
                break;
            }
            j = j + lenght;
         }
      }
   }
   else
   {
      printf("la clé n'existe pas dans ");
   }
}


void info()
{
   printf("Informations sur le fichier \n");
   printf("\tNombre de blocs utilis�s = %ld\n", ent.last_bloc);
}

void sup ()
{
   int ind,blc;
   int trv = 0;
   search_decho(&ind,&blc,&trv);
   lireDire(f,blc,&buf2);
   if (trv == 1){
      //printf("\n rani raya7 nsuprimiih\n");
      buf2.table[ind-1]='v' ;
      ecrireDire(f,blc,&buf2,&ent);
   }

}

void parcours()
{
    printf("\n le contenu du fichier est  :  \n");
   int i =1;
   while (i <= ent.last_bloc)
   {
      lireDire(f,i,&buf2);
      int m = 0;
      for ( m = 0; m <= buf2.free_pos; m++)
      {
         printf("%c",buf2.table[m]);
      }
      i++;
   }

}

void intro(void)
{
    printf("\n                   *********************************************************");
    printf("\n                   ************** BIENVENUE DANS LE PROGRAMME **************");
    printf("\n                   ------- Recherche déchotomique dans un fichier TOV~C ----");
    printf("\n                   _________________________________________________________\n\n");
    //system("CLS");
}
