#include <stdio.h>

int gcd(int x, int y);

int main() {
    int a, b;
    int MCD=0;

    printf("Inserisci due numeri <a> <b>: ");
    scanf("%d %d", &a, &b);

    if (a>b)
        MCD=gcd(a, b);
    else
        MCD=gcd(b, a);

    if (MCD==-1)
        printf("ERRORE: a PARI, b DISPARI ----> NON PRESENTE TRA LE SCELTE");
    else
        printf("\nMassimo comun divisore: %d", MCD);

    return 0;
}

int gcd(int x, int y) {
    if (x<y){
        int tmp=y;
        y=x;
        x=tmp;
    }

    if (x==y)
        return x;
    else
        if (x%2==0 && y%2==0)
            return 2*gcd(x/2, y/2);
        else if (x%2!=0 && y%2!=0)
            return gcd((x-y)/2, y);
        else if (x%2!=0 && y%2==0)
            return gcd(x, y/2);
        else if (x%2==0 && y%2!=0)
            return gcd(x/2, y);
}