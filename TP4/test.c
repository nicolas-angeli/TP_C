#include <stdio.h>
#include <math.h>
#include <stdlib.h>

long* diviseurs (long n){
    if (n<2){
   	 printf("Mauvaise valeur de n\n");
   	 return;
    }
    
    long* tab[] = malloc(sizeof(long));
    
    int ii = 0;
    int xx = 0;
    while (ii < sqrt(n){
   	 if (n % ii == 0){
   		 tab[xx] = ii;
   		 xx++;
   		 tab = realloc(tab,(xx+1)* sizeof(long));
   	 }
    }
    ii++
    
    tab[xx] = -1;
    
    return tab;
}


int main() {
    long n = 24;
    long* t[] = diviseurs(n);
    printf("Diviseurs de %ld : \n",n);
    int k=0;
    while(t[k] != -1){
   	 printf("%ld, %ld\n",t[k],n/t[k]);
   	 k++;
    }
    free(t);
    return 0;
}

