// ********************************************************************
// Projekt:         Implementace pøekladaèe jazyka IFJ21.
// Varianta:        19, I
// Soubor:          symtable.c
// Datum:           30.11.2021
// Autoøi:
//                  Kamil Hlavinka            xhlavi20
//                  Vít Hrbáèek               xhrbac10
//                  Tomáš Král                xkralt06
//                  Pater Babic               xbabic13
// ********************************************************************

#include <stdio.h>
#include <stdbool.h>
#include <stlib.h>

//Inicializace prázdného stromu
void initStrom(uzelStromu* uzel){
    uzel=NULL;
}

//Vložení nového uzlu
void vlozUzel (uzelStromu *uzel,char klic,char* hodnota){
    if(uzel == NULL){
        uzelStromu *novyUzel;
        if ((novyUzel=malloc(sizeof(uzelStromu)))==NULL)
        {
            return;
        }
        novyUzel->klic=klic;
        novyUzel->hodnota=hodnota;
        novyUzel->levy=NULL;
        novyUzel->pravy=NULL;
        *uzel=novyUzel;
    }
    else if(klic<(*uzel)->klic)
    {
        vlozUzel(&(uzel->levy),klic,&hodnota);
    }
    else if(klic >(*uzel)->klic)
    {
        vlozUzel(&(uzel->pravy),klic,hodnota);
    }
    else
    {
        *uzel->hodnota=hodnota;
    }
}






