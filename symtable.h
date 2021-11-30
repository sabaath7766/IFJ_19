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


#endif // S
YMTABLE_H_INCLUDED
