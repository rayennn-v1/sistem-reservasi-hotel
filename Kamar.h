#ifndef KAMAR_H
#define KAMAR_H

#include <iostream>
#include <string>
using namespace std;

// ADT KAMAR (LIST CHILD - SINGLY LINKED LIST)

// Tipe pointer untuk menunjuk ke elemen Kamar
typedef struct elmKamar *adrKamar;

// Struktur node/elemen Kamar
struct elmKamar {
    int nomorKamar;     // Menyimpan nomor kamar (contoh: 101, 203)
    string tipeKamar;   // Menyimpan tipe kamar (Standard, Deluxe, Suite)
    double harga;       // Menyimpan harga sewa kamar per malam
    adrKamar next;      // Pointer ke elemen kamar berikutnya (Singly Linked List)
};

// Struktur List Kamar (Child)
struct ListKamar {
    adrKamar firstChild; // Pointer ke elemen pertama di List Kamar
};

// Prototipe fungsi dasar Kamar untuk Progress 1
void createListKamar(ListKamar &L);
adrKamar alokasiKamar(int nomor, string tipe, double harga);
void insertKamar(ListKamar &L, adrKamar P); // Menggunakan metode Insert Last
adrKamar cariKamar(ListKamar L, int nomor);
void tampilKamar(ListKamar L);

#endif