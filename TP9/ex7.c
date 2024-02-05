#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int countWord(char name[]){
	FILE *f;
	f=fopen("ex3.txt","r");
	
	//if(f==NULL)	{printf("le fichier n'a pas pu être ouvert");return 0;}
	char mot[30];
	int i=0;
	while(fscanf(f, "%s", mot) != EOF){
		i++;
	}
	fclose(f);
	return i;
}

int searchWord(char fichier[], int n, char mot[]){
	FILE *f;
	f=fopen(fichier,"r");
	
	if(f==NULL)	{return -1;}
	
	int i=0;
	while(i<n && (fscanf(f, "%s", mot) != EOF)){
		i++;
	}
	
	fclose(f);
	if(i!=n) return -1;
	return n;
}

int randomN(int n){
	return rand()%(n+1);
}

void  testex6(){
	char name[]="texte.txt";
	int n=countWord(name);
	char mot[30];
	searchWord(name, randomN(n), mot);
	printf(mot);		
}

int main(){
	srand(time(NULL));
	testex6();

	return 0;
}

	


