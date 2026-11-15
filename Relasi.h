#ifndef RELASI_H
#define RELASI_H

#include "Tamu.h"
#include "Kamar.h"

typedef struct elmRelasi *adrRelasi;

struct elmRelasi {
    string tanggalCheckIn;
    int durasi;
    adrTamu parent; // Pointer ke Tamu
    adrKamar child; // Pointer ke Kamar
    adrRelasi next;
    adrRelasi prev;
};

struct ListRelasi {
    adrRelasi first;
    adrRelasi last;
};

void createListRelasi(ListRelasi &L);

#endif