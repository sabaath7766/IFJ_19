#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
// Vít Hrbácek & Kamil Hlavinka

// Deklarace konstant pro funkci zda je to klicove slovo
#define POCET_KLICOVYCH_SLOV 15
#define NEJVETSI_DELKA_SLOV 9

// Uvozovka nejde dat do uvozovek, tak jsem definoval její ascii hodnotu
#define UVOZOVKA_ASCII 34

typedef enum stavy {idle, identifikator, klicove_slovo, uvozovka1,
uvozovka2, uvozovka_vyjimka_pro_lomitko, cislo, desetinne_cislo, desetinne_cislo2,
desetinne_cislo_final, zacatek_komentare_1,zacatek_komentare_2,zacatek_komentare_3,
radkovy_komentar, blokovy_komentar, konec_blokoveho_komentare, komentar, dvojbodka,

// Stavy pro operátory
jedno_rovna_se, jen_tilda, tecka
} TStavy;

typedef struct list{
  char *prvniZnak;
  int pocetZnaku;
}TString; // Ukazatel na dynamicky alokovane znaky

void InicializaceTString(TString* retezec){
  retezec->prvniZnak = NULL;
  retezec->pocetZnaku = 0;
}

//identefikator bude jako jednosmerne vazany seznam (nevime jak bude dlouhy)
typedef struct idZnak{
    char znak;
    TIDptr dalsiZnak;
    TIDptr predchoziZnak;
} *TIDptr;
//id
typedef struct idList{
    TIDptr prvniZnak;
    TIDptr posledniZnak;
    TIDptr aktivniZnak;
    int pocetZnaku;
}TID

void idInit(TID* list){
    list->prvniZnak=NULL;
    list->posledniZnak=NULL;
    list->aktivniZnak=NULL;
    list->pocetZnaku=0;
}
//vlozeni znaku do "pole" id
void idInsert(TID* list, char znak){
    //deklarace noveho prvku
    TIDptr IDznak = malloc(sizeof(*IDznak));
    //kontrola mallocu
    if(IDznak != NULL){
         IDznak->znak; //vlozim data
    IDznak->dalsiZnak = NULL; //posledni ukazuje zase na prvniho
    IDznak->predchoziZnak = list->posledniZnak;

    /*pokud neni seznam prazdny, tak je potreba nastavit,
     aby predchozi prvek mel za naslednika novy prvek*/
    if(list->posledniZnak != NULL){
        list->posledniZnak->dalsiZnak = IDznak;
    }else{
     //novy prvek je zaroven i prvnim prvkem v seznamu
    list->prvniZnak = IDznak;
    }
    list->posledniZnak = IDznak;
    }
    list->pocetZnaku = list->pocetZnaku+;
}

//nastaveni aktivity
void firstID(TID* list){
    list->aktivniZnak = list->prvniZnak;
}
//posouvani aktivity
void nextID( TID *list ) {
    //pokud je seznam aktivni
    if (list->aktivniZnak != NULL){
        if (list->aktivniZnak == list->posledniZnak){ //pokud jsme na poslednim prvku
            list->aktivniZnak = NULL;
        }else{
            list->aktivniZnak = list->aktivniZnak->dalsiZnak; //predam aktivitu nasledujicimu
        }
    }
}

//ukonceni seznamu id
void disposeID(TID* list) {

    while(list->prvniZnak != NULL){
        TIDptr *vymaz; //ukazatel na prvek
    if(list->prvniZnak != NULL){ //pokud neni seznam prazdny
        vymaz = list->prvniZnak; //ukazuju na prvni prvek
        if(list->aktivniZnak == list->prvniZnak){ //pokud je ten prvek aktivni, rusim aktivitu
            list->aktivniZnak = NULL;
        }
        if(list->prvniZnak == list->posledniZnak){ //posledni prvek
            list->prvniZnak = NULL;
            list->prvniZnak = NULL;
        }
        else{
            list->prvniZnak = list->prvniZnak->dalsiZnak; //nastaveni noveho prvniho prvku
            list->prvniZnak->predchoziZnak = NULL; //novy prvni prvek ukazuje na NULL
        }
        free(elemPtr);
    }
    }

    list->aktivniZnak = NULL;
    list->prvniZnak = NULL;
    list->posledniZnak = NULL;
}

void pridatZnakTString(int znak, TString* retezec){
  // Zvetsi naalokovane misto pro retezec ci pro pro novy string ho naalokuje
  if(retezec->prvniZnak == NULL && retezec->pocetZnaku == 0){
    char* ukazatel = (char*) malloc(sizeof(char)*2);
    // 2 protoze prvni je znak a potom konec retezce
    if(ukazatel != NULL){
      ukazatel[0] = znak;
      ukazatel[1] = '\0';
      retezec->prvniZnak = ukazatel;
      retezec->pocetZnaku = 1;
    }
  }else{
    char* ukazatel = (char*) realloc(retezec->prvniZnak, sizeof(char)*(retezec->pocetZnaku + 2));
    // + 2 protoze koncovy znak retezce a novy znak
    if(ukazatel != NULL){
      ukazatel[retezec->pocetZnaku] = znak;
      ukazatel[retezec->pocetZnaku + 1] = '\0';
      retezec->prvniZnak = ukazatel;
      retezec->pocetZnaku++;
    }
  }
}

typedef struct TokenStruktura{
  char* typ; // Typ tokenu - Identifiktor, cislo, operator +, operator *,...

  // Atribut
  char *AtributRetezec;
  bool jeToRetezec;

  double hodnotaDouble;
  bool jeToDouble;

  int hodnotaInt;
  bool jeToInt;
} TToken;

void inicializaceTokenu(TToken* token){
  token->typ = NULL;
  token->AtributRetezec = NULL;
  token->hodnotaDouble = 0.0;
  token->hodnotaInt = 0;

  token->jeToDouble = false;
  token->jeToInt = false;
  token->jeToRetezec = false;
}

void vratZnak(int znak){
  ungetc((char) znak, stdin); // Vrati nacteny znak na stdin

  // Hodi se, kdyz potřebujeme zjistit, zda odeslat token na = nebo ==
  // nacteme znak po = a podle něho se rozhodneme a pak vratime zpátky
  // pokud to neni ==, aby ho lexikální analyza znala pro pristí analyzu
}

// Funkce odzkousena/testovana
bool jeToPismeno(int znak){
  return ((znak >= 'a' && znak <= 'z')||(znak >= 'A' && znak <= 'Z'));
}

// Funkce odzkousena/testovana
bool jeRetezecKlicoveSlovo(char* Retezec){
  char PoleKlicovychSlov[POCET_KLICOVYCH_SLOV][NEJVETSI_DELKA_SLOV] = {{"do"}, {"else"}, {"end"}, {"function"},
  {"global"}, {"if"}, {"integer"}, {"local"}, {"nil"},
  {"number"}, {"require"}, {"return"}, {"string"}, {"then"}, {"while"}};

  // Odstranil jsem puvodni zarazku v poli a zacal jsem pouzivat pocetKlicovychSlov
  int i = 0;
  bool vystup = false;

  // Jestli retezec je klicove slovo, tak vystup zmenim na true
  while(i < POCET_KLICOVYCH_SLOV){
    if(0 == strcmp(Retezec, PoleKlicovychSlov[i])){
      vystup = true;
      break; // pro zrychlení programu
    }
    i++;
  }
  return vystup;
}

// TODO: Funkce na ignorovani bilych znaku a její vlozeni do kodu na potrebna mista


TToken dejToken()
{
  TToken token;               // Vytvorim token
  inicializaceTokenu(&token); // a zmenim nahodne hodnoty na nuly.
  bool mamToken = false;      // Zaznamenani zda mam platna data v tokenu
  TStavy stav = idle;
  TString pametHodnoty;
  InicializaceTString(&pametHodnoty);
  int znak;
  TID id;
  idInit(&id);

  /*TODO: Dat volání funkce vratZnak, kam patri - dvojbodka atd.*/
  /*TODO: Funkce na preskakovani bilych znaku*/
  /*TODO: Vyresit EOF aby s nim pocitaly presuny v jednotlivých stavech*/

  while(!mamToken){
    znak = getchar();
    pridatZnakTString(znak, &pametHodnoty);
    switch(stav){
      case idle:
        if(znak == '_' || jeToPismeno(znak)){
          stav = identifikator;
          idInsert(&id,znak); //vloz do seznamu
        }else if(znak == '-'){
          stav = zacatek_komentare_1;
        }else if(znak >= '0' && znak <= '9'){
          stav = cislo;
        }else if(znak == UVOZOVKA_ASCII){
          stav = uvozovka1;
        }else if(znak == ':'){
          // Vytvorim token
          token.typ = (char*) malloc(sizeof(char)*(strlen(":") + 1));
          // Dynamicky alokuji string
          if(token.typ != NULL){
            strcpy(token.typ, ":");
          }
          free(pametHodnoty.prvniZnak); // Uvolním pamět znaků ze vstupu
          mamToken = true;

        }else if(znak == '='){
          stav = jedno_rovna_se;
        }else if(znak == '~'){
          stav = jen_tilda;
        }else if(znak == '#' || znak == '*' || znak == '+'){
          token.typ = (char*) malloc(sizeof(char)*(2)); // 2 protoze znak a konec retezce
          // Dynamicky alokuji string
          if(token.typ != NULL){
            token.typ[0] = znak;
            token.typ[1] = '\0';
            free(pametHodnoty.prvniZnak); // Uvolním pamět znaků ze vstupu
          }
          mamToken = true;
        }else if(znak == '.'){
          stav = tecka;
        }else if(znak == EOF){
          // Vytvorim token
          token.typ = (char*) malloc(sizeof(char)*(strlen("EOF") + 1));
          // Dynamicky alokuji string

          if(token.typ != NULL){
            strcpy(token.typ, "EOF");
          }
          free(pametHodnoty.prvniZnak); // Uvolním pamět znaků ze vstupu
          mamToken = true;
        }else{
          /* TODO: Chyba predana lexikalni analyzou*/
          exit(1);
        }

      case identifikator:
        if(jeToPismeno(znak) || znak == '_' || znak >= '0' && znak <= '9'){
          stav = identifikator;
          idInsert(&id, znak); //vloz do seznamu
        }else{
            int delka = id->pocetZnaku; //delka id
            token.typ = (char*) malloc(sizeof(char)*(3)); // 3 protoze 'i' 'd' a konec retezce
            token.AtributRetezec (char*) malloc(sizeof(char)*((delka)+1); //delka id + konec retezce
            firstID(&id); //prvni znak seznamu
            for(int i=0;i<delka+1;id++){ //projdu cely seznam a ulozim znaky do pole AtributRetezec
                token.AtributRetezec[i] = id->aktivniZnak->znak; //na pozici ulozim znak
                nextID(&id); //dalsi znak
            }
            token.AtributRetezec[delka+1] = '\0'; //posledni znak
            disposeID(&id); //uvolni seznam
            free(pametHodnoty.prvniZnak); // Uvolním pamět znaků ze vstupu

            vratZnak(znak);
            //klicova slova
            if(jeRetezecKlicoveSlovo(&token.AtributRetezec)){
                token.typ = (char*) malloc(sizeof(char)*(delka+1));
                strcpy(token.typ, token.AtributRetezec);
            }else{
                token.jeToRetezec = true;
                token.typ = (char*) malloc(sizeof(char)*(strlen("Identifikator") + 1));
                if(token.typ != NULL){
                    strcpy(token.typ, "Identifikator");
                }
            }

            mamToken = true;
        }

      case cislo:
        if(znak >= '0' && znak <= '9'){
          stav = cislo;
        }else if(znak == '.' || znak == 'e' || znak == 'E'){
          stav = desetinne_cislo;
        }else{
          vratZnak(znak); // jiny znak vratim
          // Vytvorim token
          token.hodnotaInt = atoi(pametHodnoty.prvniZnak);
          free(pametHodnoty.prvniZnak); // Uvolním pamět znaků ze vstupu
          token.jeToInt = true;
          token.typ = (char*) malloc(sizeof(char)*(strlen("Cislo") + 1));
          // Dynamicky alokuji string

          if(token.typ != NULL){
            strcpy(token.typ, "Cislo");
          }
          mamToken = true;
        }

      case desetinne_cislo:
        if(znak >= '0' && znak <= '9'){
          stav = desetinne_cislo_final;
        }else if(znak == '+' || znak == '-'){
            stav = desetinne_cislo2;
        }else{
          exit(1);
        }

      case desetinne_cislo2:
        if(znak >= '0' && znak <= '9'){
          stav = desetinne_cislo_final;
        }else{
          exit(1);
        }

      case desetinne_cislo_final:
        //TODO

      case uvozovka1:
        /* TODO: Zakomponovat EOF do jednotlivych stavù */
        if(znak == UVOZOVKA_ASCII){
          stav = uvozovka2;
        }else if(znak == '/'){
          stav = uvozovka_vyjimka_pro_lomitko;
        }else{
          stav = uvozovka1; //TODO: Nacitej jen znak do retezce mezipameti
        }

      case uvozovka2:
          // Vytvorim token
          token.AtributRetezec = pametHodnoty.prvniZnak;
          token.jeToRetezec = true;
          token.typ = (char*) malloc(sizeof(char)*(strlen("Retezec") + 1));
          // Dynamicky alokuji string

          if(token.typ != NULL){
            strcpy(token.typ, "Retezec");
          }
          mamToken = true;

      // Stavy operatorù
      case jedno_rovna_se:
        if(znak == '='){
          /* Vytvorim token protoze vim, ze je to == */
          token.typ = (char*) malloc(sizeof(char)*(strlen("==") + 1));
          // Dynamicky alokuji string
          if(token.typ != NULL){
            strcpy(token.typ, "==");
          }
          mamToken = true;
          free(pametHodnoty.prvniZnak); // Uvolním pamět znaků ze vstupu
        }else{
          vratZnak(znak); // jiny znak vratim pro pristi cteni

          // vytvorim token =
          token.typ = (char*) malloc(sizeof(char)*(strlen("=") + 1));
          // Dynamicky alokuji string
          if(token.typ != NULL){
            strcpy(token.typ, "=");
          }
          free(pametHodnoty.prvniZnak);
          mamToken = true;

        }

      case jen_tilda:
        if(znak == '='){
          // vytvorim token =
          token.typ = (char*) malloc(sizeof(char)*(strlen("~=") + 1));
          // Dynamicky alokuji string
          if(token.typ != NULL){
            strcpy(token.typ, "~=");
          }
          mamToken = true;
          free(pametHodnoty.prvniZnak); // Uvolním pamět znaků ze vstupu
        }else{
            exit(1);
        }

      case tecka:
        if(znak == '.'){
          // Vratim token dve_tecky;
          token.typ = (char*) malloc(sizeof(char)*(strlen("..") + 1));
          // Dynamicky alokuji string

          if(token.typ != NULL){
            strcpy(token.typ, "..");
          }
          mamToken = true;
        }else{
            exit(1);
        }

      case zacatek_komentare_1:
        if(znak == '-'){
            stav = zacatek_komentare_2;
        }else{
            token.typ = (char*) malloc(sizeof(char)*(2)); // 2 protoze znak a konec retezce
          // Dynamicky alokuji string
          if(token.typ != NULL){
            token.typ[0] = znak;
            token.typ[1] = '\0';
            free(pametHodnoty.prvniZnak); // Uvolním pamět znaků ze vstupu
          }
          mamToken = true;
        }

      case zacatek_komentare_2:
        if(znak == '['){
            stav = zacatek_komentare_3;
        }else{
            stav = radkovy_komentar;
        }

      case zacatek_komentare_3:
        if(znak == '['){
            stav = blokovy_komentar;
        }else{
            exit(1);
        }

      case radkovy_komentar:
        if(znak == '/0'){
            stav = komentar;
        }else{
            stav = radkovy_komentar;
        }

      case blokovy_komentar:
        if(znak == ']'){
            stav = konec_blokoveho_komentare;
        }else{
            stav = blokovy_komentar;
        }

      case konec_blokoveho_komentare:
        if(znak == ']'){
            stav = komentar;
        }else{
            stav = blokovy_komentar;
        }

      case komentar:
        //TODO

      default: stav == idle; /* TODO: Asi bych mel poslat chybu*/

      // Zadání:
      // Jestliže došlo k nejaké chybe, vrací se návratová hodnota následovnì:
      // • 1 - chyba v programu v rámci lexikální analýzy (chybná struktura aktuálního lexému).
    }

    if(mamToken){
        return token;
    }
  }
}
