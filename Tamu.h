#ifndef TAMU_H
#define TAMU_H

#include <iostream>
#include <string>
using namespace std;

// ADT TAMU (LIST PARENT - SINGLY LINKED LIST)

// Tipe pointer untuk menunjuk ke elemen Tamu
typedef struct elmTamu *adrTamu;

// Struktur node/elemen Tamu
struct elmTamu {
    string idTamu;      // Menyimpan ID unik tamu (contoh: T01)
    string nama;        // Menyimpan nama tamu
    string noTelepon;   // Menyimpan nomor telepon tamu
    adrTamu next;       // Pointer ke elemen tamu berikutnya (Singly Linked List)
};

// Struktur List Tamu (Parent)
struct ListTamu {
    adrTamu firstParent; // Pointer ke elemen pertama di List Tamu
};

// fungsi dasar Tamu
void createListTamu(ListTamu &L);
adrTamu alokasiTamu(string id, string nama, string noTelp);
void insertTamu(ListTamu &L, adrTamu P); // Menggunakan metode Insert First
adrTamu cariTamu(ListTamu L, string id);
void tampilTamu(ListTamu L);

#endif