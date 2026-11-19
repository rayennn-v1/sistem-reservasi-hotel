#include "Menu.h"

// Isi beberapa data contoh.
static void muatDataDummy(ListTamu &LT, ListKamar &LK, ListRelasi &LR, adrBST &root) {
    insertKamar(LK, alokasiKamar(203, "Deluxe", 500000));
    insertKamar(LK, alokasiKamar(105, "Standard", 300000));
    insertKamar(LK, alokasiKamar(308, "Suite", 850000));

    adrKamar K = LK.firstChild;
    while (K != nullptr) {
        insertBST(root, K);
        K = K->next;
    }

    insertTamu(LT, alokasiTamu("T001", "Andi Pratama", "081234567801"));
    insertTamu(LT, alokasiTamu("T002", "Budi Santoso", "081234567802"));

    adrTamu tamu1 = cariTamu(LT, "T001");
    adrKamar kamar203 = cariKamar(LK, 203);
    if (tamu1 != nullptr && kamar203 != nullptr) {
        buatReservasi(LR, tamu1, kamar203, "2026-11-16", 2);
    }
}

// Siapin semua struktur, jalankan aplikasi, lalu beresin node BST sebelum keluar.
int main() {
    ListTamu LT;
    ListKamar LK;
    ListRelasi LR;
    adrBST root;

    createListTamu(LT);
    createListKamar(LK);
    createListRelasi(LR);
    createBST(root);

    muatDataDummy(LT, LK, LR, root);
    jalankanMenu(LT, LK, LR, root);

    hapusBST(root);
    return 0;
}
