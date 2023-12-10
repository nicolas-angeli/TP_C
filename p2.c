#include<stdio.h>
#include<stdlib.h>

typedef struct Element Element;

struct Element{
	int colonne; //servira pour afficher M(ligne,colonne)
	int nombre;
	Element *suivant;
};

typedef struct Liste Liste;

struct Liste {
        Element *premier;
};

Liste *initialisation(){
        Liste *liste = malloc(sizeof(*liste));
        if(liste == NULL ) exit(EXIT_FAILURE);
        liste->premier = NULL; 
        return liste;
}//crée une liste dont le premier élément est nul

/*On crée un élément correspondant au nouveau nombre, on décale vers al droite le premier élément de la liste puis on met le nouvel élément en tête de liste. Ceci fonctionne car chaque élément possède un pointeur vers le suivant et donc en décalant l’ancien premier élément on décale aussi tout les éléments qui le suivait*/ 
void insertion(Liste *liste, int nb){
        Element *nouveau = malloc(sizeof(Element));
        if(liste == NULL || nouveau == NULL) exit(EXIT_FAILURE);
        nouveau->nombre = nb;
        nouveau->suivant = liste->premier;
        liste->premier = nouveau;
}

void suppression(Liste *liste){
        if(liste == NULL) exit(EXIT_FAILURE);
        if(liste->premier != NULL){
                Element *aSupprimer = liste->premier;
                liste->premier = liste->premier->suivant;
                free(aSupprimer);    
        }
}

/*L’élément actuel correspond initialement au premier élément de la liste puis tant que l’élément actuel est non nul on l’affiche et le remplace par l’élément qui suit*/
void afficherListe(Liste *liste){
        if(liste == NULL) exit(EXIT_FAILURE);
        Element *actuel = liste->premier;
        while(actuel != NULL){
                printf("%d, %d -> ", actuel->nombre, actuel->colonne);
                actuel = actuel->suivant;        
        }
        printf("NULL\n");
}

/*La fonction prendra en paramètre le tableau 2d correspondant à la matrice ainsi que son nombre de lignes et de colonnes.
*/
Liste** matCreuse(int *Matrice, int n, int m){
        int i, j;
          
        Liste **Tableau = malloc(n * sizeof(Liste*));     
        
        for(i = 0; i < n; i++){
                Liste *L = initialisation();//On crée la liste
                for (j = m-1; j >= 0; j--){
//On instancie la liste à l’envers car l’insertion rajoute les 
//éléments en début de liste. Les indices j serviront à pour 
//afficher les M(ligne,colonne)
                       if (*((Matrice + i*m) + j) != 0) {
//Matrice est l’adresse du premier élément du tableau +i*m pour 
//pointer vers le i-ème élément du tableau +j pour la j-ième colonne
//En effet le 3ème élément (colonne) du deuxième tableau (ligne) 
//représenterai le (2m+3)-ième élément du tableau 2d
                       	insertion(L, *((Matrice + i*m) + j));
                       	L->premier->colonne = j;
                       }
                }
                Tableau[i] = L;
                printf("\n");
                afficherListe(Tableau[i]);
                printf("\n");
        }
        return Tableau;
}

/*Prend comme paramètres la matrice et les coordonnées de l’élément à afficher
*/
void afficheMij(Liste *T[], int k, int l) {
	if (T == NULL) {
        	printf("0\n");
		exit(EXIT_FAILURE);
	}

	Liste *liste = T[k];
//On cherchera l’élément dans la k-ième liste 
	Element *actuel = liste->premier;

	while (actuel != NULL && actuel->colonne != l) actuel = actuel->suivant;
//On trouve le l-ième élément de la k-ième liste        
	if (actuel == NULL) printf("M(%d,%d)=0\n", k, l);
//S’il est NULL on affiche 0
	else printf("M(%d,%d)=%d\n", k, l, actuel->nombre);
}

int main(){
	int Matrice[4][6] = {
	      	{0, 7, 0, 5, 0, 0},
	     	{6, 0, 0, 0, 0, 5},
	     	{0, 0, 1, 0, 0, 0},
	     	{0, 0, 0, 0, 0, 0}
    	};
	
        Liste **T = matCreuse(Matrice, 4, 6);
        afficheMij(T, 1, 2);
        afficheMij(T, 0, 1);
        return 0;
}

