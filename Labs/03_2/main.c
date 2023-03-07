#include <stdio.h>

int checkEndian();
void stampasizeof();
void stampaCodifica (void *p, int size, int bigEndian);

int main() {
    int bigEndian=checkEndian();
    float af;
    double ad;
    long double ald;

    stampasizeof();
    printf("Inserisci numero:");
    scanf("%f", &af);
    ad = (double) af;
    ald = (long double) ad;

    printf("Float: %f\n", af);
    printf("Double: %lf\n", ad);
    //printf("Long Double: %Lf\n", ald);        PROBLEMA CON MINGW

    stampaCodifica((void *)&af, sizeof(af), bigEndian);
    stampaCodifica((void *)&ad, sizeof(ad), bigEndian);
    stampaCodifica((void *)&ald, sizeof(ald), bigEndian);

    return 0;
}

int checkEndian() {
    int n=1;
    if ((char*) &n == 0) {
        printf("Big Endian\n");
        return 1;
    }
    printf("Little Endian\n");
    return 0;
}

void stampasizeof(){
    printf("Dimensione in byte: \t float %d\t double %d\t long double %d\n", sizeof(float), sizeof(double), sizeof(long double));
    printf("Dimensione in bit:  \t float %d\t double %d\t long double %d\n", 8*sizeof(float), 8*sizeof(double), 8*sizeof(long double));
}

void stampaCodifica (void *p, int size, int bigEndian) {
    unsigned char *pointer = (unsigned char *) p;
    int v[8*size];
    int count=0;

    for (int i = 0; i < size; i++, pointer++) {
        for (int j = 0; j < 8; j++, count++) {
            v[count]=((*pointer)&1?1:0);
            *pointer = *pointer >> 1;
        }
    }

    if (!bigEndian) {
        switch (size) {
            case 4:
                printf("Segno: %d\t", v[31]);
                printf("Esponente: ");
                for (int i=30; i>22; i--)
                    printf("%d", v[i]);
                printf("\t");
                printf("Mantissa: ");
                for (int i=22; i>=0; i--)
                    printf("%d", v[i]);
                printf("\n");
                break;
            case 8:
                printf("Segno: %d\t", v[63]);
                printf("Esponente: ");
                for (int i = 62; i > 51; i--)
                    printf("%d", v[i]);
                printf("\t");
                printf("Mantissa: ");
                for(int i = 51; i >= 0; i--)
                    printf("%d", v[i]);
                printf("\n");
                break;
            default:
                printf("Segno: %d\t", v[size*8-1-16]);
                printf("Esponente: ");
                for (int i = size*8-2-16; i > size*8-17-16; i--)
                    printf("%d", v[i]);
                printf("\t");
                printf("Mantissa: ");
                for(int i = size*8-17-16; i >= 0; i--)
                    printf("%d", v[i]);
                printf("\n");
                break;

        }
    }
    else {
        switch (size) {
            case 4:
                printf("Segno: %d\t", v[0]);
                printf("Esponente: ");
                for (int i=1; i>9; i--)
                    printf("%d", v[i]);
                printf("\t");
                printf("Mantissa: ");
                for (int i=9; i>=31; i--)
                    printf("%d", v[i]);
                printf("\n");
                break;
            case 8:
                printf("Segno: %d\t", v[0]);
                printf("Esponente: ");
                for (int i = 1; i > 13; i--)
                    printf("%d", v[i]);
                printf("\t");
                printf("Mantissa: ");
                for(int i = 13; i >= 63; i--)
                    printf("%d", v[i]);
                printf("\n");
                break;
            default:
                printf("Segno: %d\t", v[0+16]);
                printf("Esponente: ");
                for (int i = 1+16; i > 17+16; i--)
                    printf("%d", v[i]);
                printf("\t");
                printf("Mantissa: ");
                for(int i = 17+16; i >= size-1; i--)
                    printf("%d", v[i]);
                printf("\n");
                break;

        }
    }

}