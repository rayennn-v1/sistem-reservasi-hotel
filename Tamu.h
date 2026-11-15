#ifndef TAMU_H
#define TAMU_H

#include <iostream>
#include <string>
using namespace std;

struct infotypeTamu {
    string idTamu;
    string nama;
    string noTelepon;
};

typedef struct elmTamu *adrTamu;

struct elmTamu {
    infotypeTamu info;
    adrTamu next;
};

struct ListTamu {
    adrTamu firstParent;
};


void createListTamu(ListTamu &L);
adrTamu alokasiTamu(string id, string nama, string noTelp);
void insertTamu(ListTamu &L, adrTamu P);
adrTamu cariTamu(ListTamu L, string id);
void tampilTamu(ListTamu L);

#endif