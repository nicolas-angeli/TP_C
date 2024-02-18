#include <stdio.h>
#include <string.h>

int main(int argc, char *argu[]){
	FILE *f, *fc;
	if(argc>1){
		f=fopen(argu[0],"r");
		fc=fopen(argu[1],"w+");
	
		int car=0;
		while(!feof(f)){
			car=fgetc(f);
			if(0<car && car<236)
				fputc((char)(car), fc);
		}	
		fclose(f);

		return 0;
	}
	else
		printf("Vous n'avez pas mentionné le nom des 2 fichiers");
}