//Mateusz Maciejewski
//Program zadanie 3 "Fiskus" (nazwa własna)
//2016-10-10

#include <stdio.h>

/* wypisz zestawienie stanu konta, jesli kwote 10 tys. zl.
   wlozylismy na lokate 10 letnia oprocentowana 5% rocznie
   i procenty sa dopisywane co kwartal. */

int main(void) // wersja zmiennoprzecinkowa
{
    int lata, okresow_w_roku;
    float procent;
    float podatek = 0.19f;
    int kwota_pocz, kwota;
    int rok, okres;

    printf("podaj kwote poczatkowa (w zl):\n");
    scanf("%d", &kwota_pocz);
    kwota_pocz*=100;

    printf("podaj oprocentowanie:\n");
    scanf("%f", &procent);

    printf("podaj liczbe lat:\n");
    scanf("%d", &lata);

    printf("podaj liczbe okresow w roku:\n");
    scanf("%d", &okresow_w_roku);


    // kwota_pocz=10000*100;     /* kwota lokaty */
    // lata=10;              /* liczba lat lokaty */
    // okresow_w_roku=4;     /* liczba okresow w roku */
    // procent=0.05;         /* oprocentowanie roczne */

    kwota=kwota_pocz; rok=1;

    printf("rok\tkwota\n");
    while (rok <= lata) {
        okres=1;
        while (okres <= okresow_w_roku) {
            kwota=kwota*(1.0+(procent/okresow_w_roku)*(1.0 - podatek) );
            okres=okres+1;
        }
        printf("%d\t%d.%02d\n",rok,kwota/100, kwota%100);
        rok=rok+1;
    }
    return 0;
}
