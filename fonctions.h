#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define max 30

typedef struct bloc
{
    char table[max];
    int free_pos;
    char key1[11];
    char key2[11];
} bloc_type;


typedef struct header
{
    int last_bloc;
} header_type;

FILE *f = NULL;
header_type ent;
bloc_type buf,buf2;

void open_file( FILE **f, char *name, char mode, header_type *head );

// fermer le fichier en sauvegardant l'entête ent dans le 1er bloc (num 0) du fichier.
void close_file( FILE *f, header_type *head);

// lecture du bloc de données num i dans la variable buf.
void lireDire( FILE *f, long i, bloc_type *buf );

// ecriture du contenu de la variable buf dans le bloc de données num i.
void ecrireDire( FILE *f, long i, bloc_type *buf,header_type *head );

// Le chargement initiale de votre fichier (les clés seront automatiquements générées par ordre).
void chargement_initiale();

// elle extrait une sous chaine 'souschaine' de la grande chaine 'chaine' selon les indices 'from' 'to'.
int extract(int from, int to, char *chaine, char *sousChaine);

// elle génère randomly une chaine de caracteres de taille 'taille'.
void randomchaine(char *chaineAleatoire, int taille);

// la plus importante procédure qui faisse la recherche dechotomique en retournant son indice dans le tableau du bloc numero 'bloc'
void search_decho (int *indice, int *bloc, int *trv);

// le parcours pour afficher tout le contenu de fichier .
void parcours();

// la fonction qui fasse la suppression .
void sup();

void intro(void);

void info();