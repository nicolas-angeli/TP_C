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

void  pendu(){
	char name[]="mots.txt", mot[30], te[30], restant[30], d[30];
	int n=countWord(name), len, a=0, g=0;
	searchWord(name, randomN(n), mot);
	len=strlen(mot);
		
	strcpy(restant,mot);
	for(int i=0;i<len;i++)	d[i]='.';
	d[len]='\0';

	char *image[]={"/-----\n|  \n|  \n| \n|  \n| \n|_______\n\n","/-----\n|  |\n|  \n| \n|  \n| \n|_______\n\n","/-----\n|  |\n|  Q\n| \n|  \n| \n|_______\n\n","/-----\n|  |\n|  Q\n|  |\n|  \n| \n|_______\n\n","/-----\n|  |\n|  Q\n| \\|\n|  \n| \n|_______\n\n","/-----\n|  |\n|  Q\n| \\|/\n|  \n| \n|_______\n\n","/-----\n|  |\n|  Q\n| \\|/\n|  |\n| \n|_______\n\n","/-----\n|  |\n|  Q\n| \\|/\n|  |\n| / \n|_______\n\n","/-----\n|  |\n|  Q\n| \\|/\n|  |\n| / \\\n|_______\n\n"};
	printf("Jouons au pendu:\n");
	for(int i=0;i<8;){
		printf("\n%s\nEntrez un mot\n\n%s\n", d, image[i]);
		scanf("%s", te);
		a=0;
		for(int j=0;j<len;j++){
			if(strchr(restant, te[j])!=NULL){
				for(int k=0;k<len;k++){
					if(te[j]==restant[k]){
						char rk=restant[k];
						for(int l=k;l<len;l++){
							if(restant[l]==rk){
								restant[l]=' ';
								d[l]=rk;
							}
						}
						a=1;
					}
				}
			}
		}
		if(a==0) i++;
		g=0;
		for(int j=0;j<len;j++)	if(restant[j]!=' '){g=1;break;}
		if(g==0){printf("Le mot etait : %s\nFelicitations, vous remportez la partie !\n", mot);return;}
	}
	printf("%sPerdu !\nLe mot etait : %s\n", image[8], mot);			
}

int main(){
	srand(time(NULL));
	pendu();

	return 0;
}


/*
Depart:
/-----
| 
| 
| 
| 
| 
|_______	

1:
/-----
|  |
| 
| 
|  
| 
|_______

Second essai :
/-----
|  |
|  Q
| 
| 
| 
|_______

Troisième essai :
/-----
|  |
|  Q
|  |
|  
| 
|_______

Quatrième essai :

/-----
|  |
|  Q
| \|
|  
| 
|_______

Cinquième essai :

/-----
|  |
|  Q
| \|/
|  
| 
|_______

Sixième essai :

/-----
|  |
|  Q
| \|/
|  |
| 
|_______

Septième essai :

/-----
|  |
|  Q
| \|/
|  |
| / 
|_______

Huitième essai :

/-----
|  |
|  Q
| \|/
|  |
| / \
|_______
*/




