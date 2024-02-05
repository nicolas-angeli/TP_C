#include <stdio.h>
#include <string.h>

int main(){
	FILE *f, *fc;
	f=fopen("texte.txt","r");
	fc=fopen("copie.txt","w+");
	
	//if(f==NULL)	{printf("le fichier n'a pas pu être ouvert");return 0;}
	int car=0;

	while(!feof(f)){
		car=fgetc(f);
		if(32<car && car<236){
			fputc((char)(~car), fc);
		}
	}	
	fclose(f);

	return 0;
}