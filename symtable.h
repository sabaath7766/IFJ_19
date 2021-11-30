// ********************************************************************
// Projekt:         Implementace překladače jazyka IFJ21.
// Varianta:        19, I
// Soubor:          symtable.h
// Datum:           30.11.2021
// Autoři:
//                  Kamil Hlavinka            xhlavi20
//                  Vít Hrbáček               xhrbac10
//                  Tomáš Král                xkralt06
//                  Pater Babic               xbabic13
// ********************************************************************

#ifndef SYMTABLE_H_INCLUDED
#define SYMTABLE_H_INCLUDED

#include <stdbool.h>

//TODO - upravit strukturu
typedef struct uzelStromu {
char klic;
char* hodnota;
struct uzelStromu *levy;
struct uzelStromu *pravy;
}uzelStromu;

void initStrom (uzelStromuUk *uzel);
void vlozUzel (uzelStromu *uzel,char klic,char* hodnota);
bool hledejUzel(uzelStromu *uzel, char klic, char* hodnota);
void smazUzel(uzelStromu * uzel, char klic);
void zrusStrom (uzelStromu *uzel);
//pomocna fce
void nahradNejvicPravym(uzelStromu cil, uzelStromu *uzel);


#endif // SYMTABLE_H_INCLUDED
