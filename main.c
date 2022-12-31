#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {char kod[101]; int cena;}POLOZKA;

POLOZKA search(POLOZKA polozka, POLOZKA * seznam, int counter){
    for(int i = 0; i < counter; i++){
        if(!strcmp(polozka.kod, seznam[i].kod)){
            return seznam[i];
        }
    }
    polozka.cena = -1;
    return polozka;
}

 int nactikod(char * kod){
     char x;
     for (int i = 0; i < 101; i++) {
        x = fgetc(stdin);
        if(i == 0 && x == '\n'){
            return -1;
        }
        //printf("x = %c\n", x);
        if(x == ' '){
            //printf("mezera\n");
            if(i < 5){
                printf("Nespravny vstup, moc kratky kod.\n");
                return 0;
            }else{
                kod[i] = '\0';
                return 1;
            }
        } else if (x < '0' || x > '9'){
            printf("Nespravny vstup, znak neni cislo.\n");
            return 0;
        } else if (kod[100] != ' ' && i == 100){
            printf("Nespravny vstup, moc dlouhy kod.\n");
            return 0;
        }

        kod[i] = x;
    }

}

void porovnaniCen(POLOZKA * cenik1, POLOZKA * cenik2){

}

int main() {
    int counter1 = 0, counter2 = 0, check, cislo;
    char a, b, c, enter;
    POLOZKA * cenik1 = (POLOZKA*) malloc (sizeof(POLOZKA));
    POLOZKA * cenik2 = (POLOZKA*) malloc (sizeof(POLOZKA));

    printf("Zadej prvni cenik:\n");

    while (1) {
        //printf("novy\n");
        check = nactikod(cenik1[counter1].kod);
        if (check == -1) {
            break;
        } else if (check == 0) {
            for (int i = 0; i < counter1; i++) {
                free(cenik1[i].kod);
            }
            free(cenik1);
            return 0;
        }

        check = scanf("%c%c%c%d%c", &a, &b, &c, &cislo, &enter);
        if(a != '=' || b != '>' || c != ' ' || check != 5 || cislo < 0 || enter != '\n'){
            printf("Nespravny vstup.\n");
            for (int i = 0; i < counter1; i++) {
                free(cenik1[i].kod);
            }
            free(cenik1);
            return 0;
        }
        cenik1[counter1].cena = cislo;

        counter1++;

    }

    /*
    printf("kontrola ceniku 1\n");
    for (int i = 0; i < counter1; i++) {
        printf("%s %d\n", cenik1[i].kod, cenik1[i].cena);
    }
    */
    printf("Zadej druhy cenik:\n");

    while (1) {
        //printf("novy\n");
        check = nactikod(cenik2[counter2].kod);
        if (check == -1) {
            break;
        } else if (check == 0) {
            for (int i = 0; i < counter1; i++) {
                free(cenik1[i].kod);
            }
            free(cenik1);
            for (int i = 0; i < counter2; i++) {
                free(cenik2[i].kod);
            }
            free(cenik2);
            return 0;
        }

        check = scanf("%c%c%c%d%c", &a, &b, &c, &cislo, &enter);
        if(a != '=' || b != '>' || c != ' ' || check != 5 || cislo < 0 || enter != '\n'){
            printf("Nespravny vstup.\n");
            for (int i = 0; i < counter1; i++) {
                free(cenik1[i].kod);
            }
            free(cenik1);
            for (int i = 0; i < counter2; i++) {
                free(cenik2[i].kod);
            }
            free(cenik2);
            return 0;
        }
        cenik2[counter2].cena = cislo;

        counter2++;

    }

    while(1) {
        printf("Zvolte cinnost:\n(1) Vyhledat stejne polozky a porovnat ceny (1)\n(2) Vypsat vsechny polozky a seradit je podle ceny (2)\n(3) Spocitat cenu uctenky (3)\n(0) Ukoncit (0)\n");
        int moznost;
        scanf("%d", &moznost);

        if(!moznost){
            for (int i = 0; i < counter1; i++) {
                free(cenik1[i].kod);
            }
            free(cenik1);
            for (int i = 0; i < counter2; i++) {
                free(cenik2[i].kod);
            }
            free(cenik2);
            return 0;
        } else if (moznost == 1){
            printf("Stejne polozky a jejich ceny:\n");
            POLOZKA pomocne;
            int checkinos = 1;
            printf("\n");
            //POLOZKA vysledek[counter1];
            for(int i = 0; i < counter1; i++){
                if((pomocne = search(cenik1[i],cenik2,counter2)).cena != -1){
                    if(cenik1[i].cena > pomocne.cena){
                        printf("Polozka: %s je o %d levnejsi v druhem ceniku.\n", cenik1[i].kod, cenik1[i].cena - pomocne.cena);
                        checkinos = 0;
                    }else {
                        printf("Polozka: %s je o %d levnejsi v prvnim ceniku.\n", cenik1[i].kod, pomocne.cena - cenik1[i].cena);
                        checkinos = 0;
                    }
                }
            }
            if(checkinos){
                printf("Ceniky neobsahuji 2 stejne polozky.\n");
            }
            printf("\n");
        }else if (moznost == 2){
            int counterVysledek = 0;
            POLOZKA pomocne;
            printf("Polozky a jejich ceny:\n");
            POLOZKA vysledek[counter1 + counter2];
            for(int i = 0; i < counter1; i++){
                if((pomocne = search(cenik1[i], cenik2, counter2)).cena == -1){
                    vysledek[counterVysledek] = cenik1[i];
                    counterVysledek++;
                }else {
                    strcpy(vysledek[counterVysledek].kod, cenik1[i].kod);
                    if(pomocne.cena > cenik1[i].cena){
                        vysledek[counterVysledek].cena = cenik1[i].cena;
                    }else{
                        vysledek[counterVysledek].cena = pomocne.cena;
                    }
                    counterVysledek++;
                }
            }
            int i;
            for(i = 0; i < counter2; i++){
                if(search(cenik1[i], cenik2, counter2).cena == -1){
                    vysledek[i + counterVysledek] = cenik2[i];
                }
            }
            counterVysledek = counterVysledek + i;

            for(int i = 0; i < counterVysledek; i++){
                printf("Polozka: %s Cena: %d\n", vysledek[i].kod, vysledek[i].cena);
            }
            for(int i = 0; i < counterVysledek; i++){
                free(vysledek[i].kod);
            }
            free(vysledek);
        }else if (moznost == 3){

        }

    }

}
