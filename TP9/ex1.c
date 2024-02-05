#include <stdio.h>
#include <string.h>

int main(int argc, char *argu[]){
	FILE *f;
	if(argc>0){
		f=fopen(argu[0],"r");
	
		int car;
		while(!feof(f)){
			car=fgetc(f);
			if(31<car && car<236)
				printf("%d={%c}\n", car, car);
		}
		fclose(f);

		return 0;
	}
	else
		printf("Vous n'avez pas mentionné le nom du fichier");
}

	


