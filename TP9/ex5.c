#include <stdio.h>
#include <string.h>

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

int main(){
	char mot[30];
	if(searchWord("ex3.txt", 3, mot)!=-1)
		printf("Le 3ieme mot de ex3.txt est %s", mot); 
	else printf("Le fichier contient moins de 3 mots");
	return 0;
}

	


