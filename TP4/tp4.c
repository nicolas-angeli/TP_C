#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

long* diviseurs(long n) {
    int ii = 2;
    int xx = 0;
    long* tab = malloc(sizeof(long));

    if (n < 2) {
        printf("Mauvaise valeur de n\n");
        return tab;
    }

    while (ii <= sqrtl(n)) {
        if (n % ii == 0) {
            tab = realloc(tab, (xx + 1) * sizeof(long));
            tab[xx] = ii;
            xx++;
        }
        ii++;
    }

    if (xx > 0) {
        tab = realloc(tab, (xx + 1) * sizeof(long));
        tab[xx] = n / tab[0];  // Ajoute le dernier diviseur
    } else {
        tab[xx] = n;  // Si n est un nombre premier
    }

    return tab;
}


int* nombresPremiers(int n){
    int* P=(int*) malloc(sizeof(int));
    P[0]=2;
    int dimP = 1;
    for(int i=3;i<n;i=i+2){
        int estPremier = 1;
        for(int k=0;k<dimP;k++) {
            int p = P[k];
            if (p * p > i) break;
            if (i % p == 0){
                estPremier = 0;
                break;
            }
        }
        if (estPremier){
            P=(int*) realloc(P,(dimP+1) * sizeof(int));
            P[dimP]=i;
            dimP++;
        }
    }
    P=(int*)realloc(P,(dimP+1)*sizeof(int));
    P[dimP]=-1;
    return P;
}

int* numeration(int n, int base){
    int* B= (int*)malloc(sizeof(int));
    int k=0;
    while (n!=0){
        B[k] = n % base;
        n = n / base;
        k++;
        B = (int*) realloc(B,(k+1)*sizeof(int));
    }
    B[k]=-1;
    return B;
}

long puissance(long x, int n){
    int* d=numeration(n,2);
    
    long p = 1;
    long z = x;
    int i=0;
    
    while(d[i]!=-1){
        int k=d[i];
        if(k==1) p=p*z;
        z=z*z;
        i++;
    }
    
    return p;
}

long puissanceModulo(long x, int n, int m){
    int* d=numeration(n,2);
    long p = 1;
    long z = x % m;
    int i=0;
    
    while(d[i]!=-1){
        int k=d[i];
        if(k==1) p=(p*z) % m;
        z=(z*z) % m;
        i++;
    }
    
    return p;
}

char int2char (int n){

	char alphabet[] = " abcdefghijklmnopqrstuvwxyz";
	return alphabet[n];
    
}

int char2int (char n){
    
	char alphabet[] = " abcdefghijklmnopqrstuvwxyz";
    
	int ii = -1;
	while (alphabet[++ii] != '\0'){
  	  if (alphabet[ii] == n)
  		  return ii;
	}
    
	return -1;
}

long text2int (char* texte){
    long n = 0;
    int i = 0;
    
    while (texte[i] != '\0'){
   	    n += (long)(char2int(texte[i])) * puissance(27, i);
   	    i++;
    }
    
    return n;
}

int taille(int* tab){
    int i=0;
    while(tab[i+1] != -1){
        i++;
    }
    
    return i+1;
}

char* int2text(long n){
    int *num = numeration(n, 27);
    
    int i = 0, t = taille(num);
    
    char* texte = (char*)malloc(sizeof(char));
    
    while (i<t){
        char c = int2char(num[i]);
   	    texte[i] = c;
   	    i++;
   	    texte = (char*) realloc(texte, (i+1)*sizeof(char));
    }

    return texte;
}

void print(int* tab){
    int i=0;
    printf("[");
    while(tab[i+1] != -1){
        printf("%d, ", tab[i]);
        i++;
    }
    printf("%d]\n\n", tab[i]);
}

/*
int main() {
    long n=24;
    print(numeration(n, 2));
    printf("taille: %d\n", taille(numeration(n, 2)));
    
    return 0;
}
*/

/*
int main() {
	char text[] = "salut";
	long res = text2int(text);
	
	printf("salut => %ld\n", res);
	//print_text_from_int(res);
	printf("%ld => %s\n", res, int2text(res));
	
	
	printf("%ld\n", puissanceModulo(11050957, , 21));
	return 0;
}
*/

long ithPrime(int n){
        int i = 3;
        int j = 2;
        int estPremier = 1;
        int count = 1;
        while (count != n) {
                estPremier = 1;
                for (j = 2; j < i/2; j++)
                        if (!(i % j)) {
                                estPremier = 0;
                                break;
                        }
                count += estPremier; // <=> si estPremier == 1 alors count ++
                i += 2;
        }
        return (long)(i-2);
}

char** split(char* s){
    if(s==NULL) return NULL;
    int n = strlen(s);
    int N=n/5+2;
    char** t = (char**) malloc(N*sizeof(char*));
    for(int i=0;i<N-1;i++){
        t[i] = (char*) malloc(6*sizeof(char));
        for(int j=0;j<5;j++)    t[i][j]=s[5*i+j];
        t[i][6]='\n';
    }
    
    t[N-1] = (char*) malloc(4*sizeof(char));
    strcpy(t[N-1],"FIN");
    return t;
}

/*
int main() {
    long n=24;
    long* t = diviseurs(n);
    printf("Diviseurs de %d:\n",n);
    int k=0;
    while(t[k]!=-1){
        printf("%d, %d\n",t[k],n/t[k]);
        k++;
    }
    free(t);
    return 0;
}

int main() {
    int n=5;
    printf("%d ième nombre premier:\n",n);
    int k = ithPrime(n);
    printf("%d\n",k);
    return 0;
}

int main() {
    char text[] = "salut";
    int n = text2int(text);
    char* s = int2text(n);
    printf("%s => %d\n",text,n);
    printf("%d => %s\n",n,s);
    free(s);
    return 0;
}
*/

/*
    char* texte = (char*)malloc(sizeof(char));
    
    while (i<t){
        char c = int2char(num[i]);
   	    texte[i] = c;
   	    i++;
   	    texte = (char*) realloc(texte, (i+1)*sizeof(char));
*/

int size(long* tab){
    int i=0;
    while(tab[i+1] != -1){
        i++;
    }
    
    return i+1;
}

char* decryptage(long* L){
    if(L == NULL)   return "";
    
    long t = size(L);
    printf("taille:%ld\n", t);

    long p = ithPrime(4000);
    long q = ithPrime(5000);
    long N = p*q;
    
    long K = 3*(p-1)*(q-1)+1;
    long* D = diviseurs(K);
    long e = D[0];
    long d = K/D[0];
    
    char* res = (char*) malloc(sizeof(char));
    
    //long* l;
    int i;
    
    for(i=0; i<t;i++){
        long l = L[i];
        int size = strlen(res);
        
        long Md = puissanceModulo(l,d,N);
        char* dec = int2text(Md);
        
        res = (char*) realloc(res, size+strlen(dec));
        strcat(res, dec);
    }
    
    return res;
}

/*
int main() {
        
        long p = ithPrime(4000);
        long q = ithPrime(5000);
        long N = p*q;
        printf("%ld\n",N);
        long K = 3*(p-1)*(q-1)+1;
        long* D = diviseurs(K);
        long e = D[0];
        long d = K/D[0];
        char* message = "salut";
        printf("e: %ld\nN: %ld\np: %ld\nq: %ld\n", e, N, p, q);
        
        long M = text2int("salut");
        
        long adec[4] = {1589246440,1589246440,1589246440, -1};
        
        printf("décryptage: %s\n", decryptage(adec));
        /*
        printf("Message numérisé: ( %s => %d )\n", message, M);
        long Mc = puissanceModulo(M,e,N);
        printf("Message numérique crypté: ( %d => %ld )\n", M, Mc);
        printf("Message alphabétique crypté: ( %ld = %s )\n", Mc, int2text(Mc) );
        long Md = puissanceModulo(Mc,d,N);
        printf("Message numérique décrypté: ( %ld => %ld = %s )\n", Mc, Md, int2text(Md));
        free(D);*//*
        return 0;
}
*/

/*
int main() {
    long N, e;
    N = 1838127743;
    e = 13;
    
    int taille = 0;
    long* diviseurs_avec_taille(long n){
        int ii = 2;
        int xx = 0;
        long* tab = malloc(sizeof(long));
        
        if (n<2){
            printf("Mauvaise valeur de n\n");
            return tab;
        }

        while (ii <= sqrt(n)){
            if (n % ii == 0){
                tab[xx] = ii;
                xx++;
                tab = realloc(tab,(xx+1)* sizeof(long));
                taille++;
            }
            ii++;
        }
       	 
        tab[xx] = -1;
        
        return tab;
    }
    
    long* tab = diviseurs_avec_taille(N);  
    print(tab);
    long p, q, d, k;
    
    int i;    
    for(i=0; i<taille; i++){
        long ptemp, qtemp, Ktemp, dtemp;
        ptemp = tab[i];
        qtemp = N/ptemp;
        Ktemp = 3*(ptemp-1)*(qtemp-1)+1;
        //printf("Ktemp: %ld\n", ptemp, qtemp, div[0], dtemp);
        
        long* div = diviseurs(Ktemp);
        print(div);
        dtemp = (long)(Ktemp/div[0]);
        printf("ptemp: %ld\nqtemp: %ld\nKtemp: %ld\ndiv[0]: %ld\ndtemp: %ld\n", ptemp, qtemp, Ktemp, div[0], dtemp);
        if(div[0]==e){
            p = ptemp;
            q = qtemp;
            k = Ktemp;
            d = dtemp;
            break;
        }
    }
    
    printf("e: %ld\nN: %ld\np: %ld\nq: %ld\nk: %ld\nd: %ld\n", e, N, p, q, k, d);
    
    return 0;
}
*/

int main() {
    long p = 37813;
    long q = 48611;
    long N=p*q;
    printf("%d\n",N);
    long K=3*(p-1)*(q-1)+1;
    long* D=diviseurs(K);
    long e = D[0];
    long d = K/D[0];
    char* message = "salut";
    int M=text2int(message);
    printf("Message numérisé: ( %s => %d )\n",message,M);
    int Mc = puissanceModulo(M,e,N);
    printf("Message numérique crypté: ( %d => %d )\n",M, Mc);
    printf("Message alphabétique crypté: ( %d = %s )\n",Mc,int2text(Mc) );
    int Md = puissanceModulo(Mc,d,N);
    printf("Message numérique décrypté: ( %d => %d = %s )\n",Mc, Md,int2text(Md));
    free(D);
    return 0;
}
