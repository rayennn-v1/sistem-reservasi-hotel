#include "Kamar.h"

void createListKamar(ListKamar &L) {
    L.firstChild = nullptr;
}

adrKamar alokasiKamar(int nomor, string tipe, double harga) {
    adrKamar P = new elmKamar;
    P->info.nomorKamar = nomor;
    P->info.tipeKamar = tipe;
    P->info.harga = harga;
    P->next = nullptr;
    return P;
}

void insertKamar(ListKamar &L, adrKamar P) {
    if (L.firstChild == nullptr) {
        L.firstChild = P;
    } else {
        adrKamar Q = L.firstChild;
        while (Q->next != nullptr) {
            Q = Q->next;
        }
        Q->next = P;
    }
}

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
        cout << P->info.nomorKamar << "       | " << P->info.tipeKamar << "\t    | Rp " << (long)P->info.harga << "\n";
        P = P->next;
    }
    cout << "---------------------------------------------------\n";
}