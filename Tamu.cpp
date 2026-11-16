#include "Tamu.h"

// Menginisialisasi List Tamu menjadi kosong (nullptr)
void createListTamu(ListTamu &L) {
    L.firstParent = nullptr;
}

// Membuat elemen/node Tamu baru di memori
adrTamu alokasiTamu(string id, string nama, string noTelp) {
    adrTamu P = new elmTamu;
    P->idTamu = id;
    P->nama = nama;
    P->noTelepon = noTelp;
    P->next = nullptr;
    return P;
}

// Menambahkan Tamu baru di AWAL list (Insert First sesuai spesifikasi proposal)
void insertTamu(ListTamu &L, adrTamu P) {
    if (L.firstParent == nullptr) {
        L.firstParent = P; // Jika list kosong, P menjadi elemen pertama
    } else {
        P->next = L.firstParent; // Sambungkan P ke elemen pertama saat ini
        L.firstParent = P;       // Jadikan P sebagai elemen pertama yang baru
    }
}

// Mencari Tamu berdasarkan ID Tamu (digunakan untuk validasi & buat reservasi)
adrTamu cariTamu(ListTamu L, string id) {
    adrTamu P = L.firstParent;
    while (P != nullptr) {
        if (P->idTamu == id) {
            return P; // Mengembalikan alamat memori tamu jika ketemu
        }
        P = P->next;
    }
    return nullptr; // Mengembalikan nullptr jika tidak ditemukan
}

// Menampilkan seluruh daftar Tamu yang ada di List Parent
void tampilTamu(ListTamu L) {
    if (L.firstParent == nullptr) {
        cout << "  [!] Data tamu masih kosong.\n";
        return;
    }
    adrTamu P = L.firstParent;
    int no = 1;
    cout << "---------------------------------------------------\n";
    cout << "No | ID Tamu | Nama Tamu          | No. Telepon\n";
    cout << "---------------------------------------------------\n";
    while (P != nullptr) {
        cout << no++ << "  | " << P->idTamu << "    | " << P->nama << "\t  | " << P->noTelepon << "\n";
        P = P->next;
    }
    cout << "---------------------------------------------------\n";
}