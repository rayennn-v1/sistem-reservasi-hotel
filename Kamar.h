#ifndef KAMAR_H
#define KAMAR_H

#include <iostream>
#include <string>
using namespace std;

struct infotypeKamar {
    int nomorKamar;
    string tipeKamar;
    double harga;
};

typedef struct elmKamar *adrKamar;

struct elmKamar {
    infotypeKamar info;
    adrKamar next;
};

struct ListKamar {
    adrKamar firstChild;
};


void createListKamar(ListKamar &L);
adrKamar alokasiKamar(int nomor, string tipe, double harga);
void insertKamar(ListKamar &L, adrKamar P); // Insert Last
void tampilKamar(ListKamar L);

#endif