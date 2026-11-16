#include "Relasi.h"

// Menginisialisasi List Relasi (Reservasi) menjadi kosong
void createListRelasi(ListRelasi &L) {
    L.first = nullptr;
    L.last = nullptr;
}

// Membuat node transaksi Reservasi baru di memori
adrRelasi alokasiRelasi(adrTamu P, adrKamar C, string tanggal, int durasi) {
    adrRelasi R = new elmRelasi;
    R->tanggalCheckIn = tanggal;
    R->durasi = durasi;
    R->parent = P; // Hubungkan ke alamat Tamu
    R->child = C;  // Hubungkan ke alamat Kamar
    R->next = nullptr;
    R->prev = nullptr;
    return R;
}

// Menyisipkan elemen Reservasi menggunakan metode Insert After pada Doubly Linked List
void insertAfterRelasi(ListRelasi &L, adrRelasi Prec, adrRelasi R) {
    if (L.first == nullptr) {
        // Jika list reservasi masih kosong, R menjadi elemen pertama sekaligus terakhir
        L.first = R;
        L.last = R;
    } else if (Prec != nullptr) {
        // Menyisipkan R tepat setelah elemen Prec
        R->next = Prec->next;
        R->prev = Prec;
        if (Prec->next != nullptr) {
            Prec->next->prev = R;
        } else {
            L.last = R; // Jika Prec adalah elemen terakhir, update last menjadi R
        }
        Prec->next = R;
    }
}

// Fungsi pembungkus untuk membuat reservasi baru (disisipkan setelah elemen terakhir)
void buatReservasi(ListRelasi &L, adrTamu P, adrKamar C, string tanggal, int durasi) {
    adrRelasi R = alokasiRelasi(P, C, tanggal, durasi);
    insertAfterRelasi(L, L.last, R);
}

// Mengecek apakah Tamu P sudah pernah memesan Kamar C
adrRelasi cariRelasi(ListRelasi L, adrTamu P, adrKamar C) {
    adrRelasi R = L.first;
    while (R != nullptr) {
        if (R->parent == P && R->child == C) {
            return R;
        }
        R = R->next;
    }
    return nullptr;
}

// Menampilkan daftar seluruh Tamu beserta Kamar yang mereka pesan
void tampilSemuaReservasi(ListTamu LT, ListRelasi LR) {
    if (LT.firstParent == nullptr) {
        cout << "  [!] Belum ada data tamu.\n";
        return;
    }
    
    // Telusuri setiap tamu di List Parent
    adrTamu P = LT.firstParent;
    while (P != nullptr) {
        cout << "\n===================================================\n";
        cout << "Tamu : " << P->nama << " (ID: " << P->idTamu << " | Telp: " << P->noTelepon << ")\n";
        cout << "---------------------------------------------------\n";
        
        // Cari di List Relasi apakah ada reservasi milik tamu P ini
        adrRelasi R = LR.first;
        bool adaPesanan = false;
        while (R != nullptr) {
            if (R->parent == P) {
                cout << "  * Kamar " << R->child->nomorKamar << " (" << R->child->tipeKamar << ")"<< " | Check-In: " << R->tanggalCheckIn << " | Durasi: " << R->durasi << " malam\n";
                adaPesanan = true;
            }
            R = R->next;
        }
        
        if (!adaPesanan) {
            cout << "  (Belum ada kamar yang dipesan)\n";
        }
        P = P->next;
    }
    cout << "===================================================\n";
}