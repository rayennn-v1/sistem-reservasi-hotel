#include "Kamar.h"

// Menginisialisasi List Kamar menjadi kosong
void createListKamar(ListKamar &L) {
    L.firstChild = nullptr;
}

// Membuat elemen/node Kamar baru di memori
adrKamar alokasiKamar(int nomor, string tipe, double harga) {
    adrKamar P = new elmKamar;
    P->nomorKamar = nomor;
    P->tipeKamar = tipe;
    P->harga = harga;
    P->next = nullptr;
    return P;
}

// Menambahkan Kamar baru di AKHIR list (Insert Last sesuai spesifikasi proposal)
void insertKamar(ListKamar &L, adrKamar P) {
    if (L.firstChild == nullptr) {
        L.firstChild = P; // Jika list kosong, P menjadi elemen pertama
    } else {
        // Telusuri list sampai menemukan elemen paling akhir
        adrKamar Q = L.firstChild;
        while (Q->next != nullptr) {
            Q = Q->next;
        }
        Q->next = P; // Sambungkan elemen terakhir dengan P
    }
}

// Mencari Kamar berdasarkan Nomor Kamar
adrKamar cariKamar(ListKamar L, int nomor) {
    adrKamar P = L.firstChild;
    while (P != nullptr) {
        if (P->nomorKamar == nomor) {
            return P; // Mengembalikan alamat kamar jika ketemu
        }
        P = P->next;
    }
    return nullptr; // Mengembalikan nullptr jika tidak ditemukan
}

// Menampilkan seluruh daftar Kamar di List Child
void tampilKamar(ListKamar L) {
    if (L.firstChild == nullptr) {
        cout << "  [!] Data kamar masih kosong.\n";
        return;
    }
    adrKamar P = L.firstChild;
    cout << "---------------------------------------------------\n";
    cout << "No. Kamar | Tipe Kamar      | Harga per Malam\n";
    cout << "---------------------------------------------------\n";
    while (P != nullptr) {
        cout << P->nomorKamar << "       | " << P->tipeKamar << "\t    | Rp " << (long)P->harga << "\n";
        P = P->next;
    }
    cout << "---------------------------------------------------\n";
}