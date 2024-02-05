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

int main(){
	srand(time(NULL));
	char mot[30];
	for(int i=0;i<10;i++){
		searchWord("ex3.txt",randomN(11), mot);
		printf("Le mot retourne est %s\n", mot);
	}
	return 0;
}

	


