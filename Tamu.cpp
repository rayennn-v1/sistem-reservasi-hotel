#include "Tamu.h"

void createListTamu(ListTamu &L) {
    L.firstParent = nullptr;
}

adrTamu alokasiTamu(string id, string nama, string noTelp) {
    adrTamu P = new elmTamu;
    P->info.idTamu = id;
    P->info.nama = nama;
    P->info.noTelepon = noTelp;
    P->next = nullptr;
    return P;
}

void insertTamu(ListTamu &L, adrTamu P) {
    if (L.firstParent == nullptr) {
        L.firstParent = P;
    } else {
        P->next = L.firstParent;
        L.firstParent = P;
    }
}

adrTamu cariTamu(ListTamu L, string id) {
    adrTamu P = L.firstParent;
    while (P != nullptr) {
        if (P->info.idTamu == id) {
            return P;
        }
        P = P->next;
    }
    return nullptr;
}

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
        cout << no++ << "  | " << P->info.idTamu << "    | " << P->info.nama << "\t  | " << P->info.noTelepon << "\n";
        P = P->next;
    }
    cout << "---------------------------------------------------\n";
}