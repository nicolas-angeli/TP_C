#include <stdio.h>
#include <stdlib.h>

typedef struct Element Element;
struct Element{
	int nombre;
	Element *suivant;
};


typedef struct Liste Liste;
struct Liste{
	Element *premier;
};

Liste *initialisation(){
	Liste* liste = malloc(sizeof(*liste));
	Element *element = malloc(sizeof(*element));
	if (liste == NULL || element == NULL)
		exit(EXIT_FAILURE);
	element->nombre = 0;
	element->suivant = NULL;
	liste->premier = element;
	
	return liste;
}
   
/*i commence à 1 et la boucle for au premier élément de la liste puis tant que l’élément suivant n’est pas nul, on passe à l’élément suivant et on incrémente i*/
int taille(Liste *liste){
	int i=1;
	Element* e;
	for (e=liste->premier ; e->suivant != NULL ; e = e->suivant){
		i++;
	}
	return i;
}

/*Si la position est inférieure ou égale à zéro on crée l’élément correspondant au nombre fourni en paramètre puis on le met en tête de liste
Si la position est supérieure à la taille on la réajuste à 
taille pour mettre l’élément en fin de liste
On parcourt la liste jusqu’à arriver à l’élément précédant la position indiquée (où on veut insérer notre nombre).
Puis on copie le pointeur vers l’élément suivant (qui suivra ensuite l’élément inséré) dans le nouvel élément que nous positionnons à la suite de l’élément situé en pos-1.*/
void insertion(Liste *liste, int nb, int pos){
	Element *element = malloc(sizeof(Element));
	element->nombre = nb;
	int t = taille(liste);
	
	if (liste == NULL || element == NULL)
		exit(EXIT_FAILURE);
		
	if(pos<=0){
		Element *nouveau = malloc(sizeof(Element));
		if(liste == NULL || nouveau == NULL) exit(EXIT_FAILURE);
		nouveau->nombre = nb;
		nouveau->suivant = liste->premier;
		liste->premier = nouveau;
		
		return;
	}
	
	if(pos>=t){
		pos=t;		
	}
	
	int i=0;

	Element *e = liste->premier;
	while (i < pos - 1) {
		e = e->suivant;
		i++;
	}
	element->suivant=e->suivant;
	e->suivant=element;	
}

int occurrences(Liste *liste, int nb){
	int i=0;
	Element* e;
	for (e=liste->premier ; e->suivant != NULL ; e = e->suivant){
		if(e->nombre == nb)	i++;
	}
	if(e->nombre == nb)	i++;
//pour le cas où le dernier élément serait une occurrence
	return i;
}

/*On crée une fonction qui supprime le premier élément dont le nombre correspond à celui passé en paramètre*/
void del(Liste *liste, int nb){
	if(liste == NULL)
		exit(EXIT_FAILURE);
	else{
		Element* e; // élément qui parcourt
		e=liste->premier; 
		while (e->suivant->nombre != nb){
			e = e->suivant;
		}
		
		Element *aSupprimer = e->suivant;
		
		e->suivant = aSupprimer->suivant;
		free(aSupprimer);
	}
}

void suppression(Liste *liste, int nb){
	int occ = occurrences(liste, nb);
	for(int i = 0; i<occ; i++)	del(liste,nb);
}

/*On procède par échange en stockant 3 éléments dans des variables.
Avant que l’élément suivant ne devienne l’actuel l’élément qui le précédait lui est affecté et l’élément qui le précédait a été assigné à l’élément actuel.*/
void inversion(Liste *liste){
	if(liste == NULL)
		exit(EXIT_FAILURE);
	
	Element *precedent, *actuel, *suivant;
	
	precedent = NULL;
	actuel = liste->premier;
	while (actuel != NULL){
		suivant = actuel->suivant;
		actuel->suivant = precedent;
		precedent = actuel;
		actuel = suivant;
	}
	liste->premier = precedent;
	
}

void afficherListe(Liste *liste){
	if(liste == NULL)
		exit(EXIT_FAILURE);
	Element *actuel = liste->premier;

	while (actuel != NULL){
		printf("%d -> ",actuel->nombre);
		actuel = actuel->suivant;
	}
	printf("NULL\n");
}
int main(){
	Liste* L = initialisation();
	afficherListe(L);
	
	insertion(L,4, 0);
	afficherListe(L);
	insertion(L,8, 0);
	afficherListe(L);
	insertion(L,15, 1);
	afficherListe(L);
	insertion(L,15, 1);
	afficherListe(L);
	insertion(L,15, 1);
	afficherListe(L);
	printf("taille : %d\n", taille(L));
	printf("occurrences de 15 : %d\n", occurrences(L,15));
	insertion(L,15, 10);
	afficherListe(L);
	printf("taille : %d\n", taille(L));
	printf("occurrences de 15 : %d\n", occurrences(L,15));
	
	suppression(L,15);
	afficherListe(L);
	printf("taille : %d\n", taille(L));
	inversion(L);
	afficherListe(L);
	
	return 0;
}
