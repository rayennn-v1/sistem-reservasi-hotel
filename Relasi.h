#ifndef RELASI_H
#define RELASI_H

#include "Tamu.h"
#include "Kamar.h"

// ADT RELASI / RESERVASI (MLL-02 - DOUBLY LINKED LIST)
// Berfungsi menyimpan transaksi Reservasi yang menghubungkan
// pointer Tamu (Parent) dan pointer Kamar (Child)

typedef struct elmRelasi *adrRelasi;

// Struktur elemen Relasi (Transaksi Reservasi)
struct elmRelasi {
    string tanggalCheckIn; // Tanggal masuk menginap
    int durasi;            // Lama menginap (dalam malam)
    adrTamu parent;        // Pointer yang menunjuk ke Tamu yang memesan
    adrKamar child;        // Pointer yang menunjuk ke Kamar yang dipesan
    adrRelasi next;        // Pointer ke reservasi berikutnya
    adrRelasi prev;        // Pointer ke reservasi sebelumnya (Doubly Linked List)
};

// Struktur List Relasi
struct ListRelasi {
    adrRelasi first;
    adrRelasi last;
};

// fungsi Reservasi
void createListRelasi(ListRelasi &L);
adrRelasi alokasiRelasi(adrTamu P, adrKamar C, string tanggal, int durasi);
void insertAfterRelasi(ListRelasi &L, adrRelasi Prec, adrRelasi R); // Metode Insert After
void buatReservasi(ListRelasi &L, adrTamu P, adrKamar C, string tanggal, int durasi);
adrRelasi cariRelasi(ListRelasi L, adrTamu P, adrKamar C);
void tampilSemuaReservasi(ListTamu LT, ListRelasi LR);

#endif