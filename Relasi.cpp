#include "Relasi.h"

// Nentuin apakah tahun punya satu hari tambahan di bulan Februari.
static bool tahunKabisat(int tahun) {
    return tahun % 400 == 0 || (tahun % 4 == 0 && tahun % 100 != 0);
}

// Cek tanggal YYYY-MM-DD, lalu ubah jadi angka hari biar rentangnya gampang dibandingin.
static bool parseTanggalISO(const string &tanggal, int &serial) {
    if (tanggal.size() != 10 || tanggal[4] != '-' || tanggal[7] != '-') return false;
    for (int i = 0; i < 10; ++i) {
        if (i == 4 || i == 7) continue;
        if (tanggal[i] < '0' || tanggal[i] > '9') return false;
    }

    int tahun = stoi(tanggal.substr(0, 4));
    int bulan = stoi(tanggal.substr(5, 2));
    int hari = stoi(tanggal.substr(8, 2));
    if (tahun < 1 || bulan < 1 || bulan > 12 || hari < 1) return false;

    const int hariPerBulan[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int batasHari = hariPerBulan[bulan - 1];
    if (bulan == 2 && tahunKabisat(tahun)) batasHari = 29;
    if (hari > batasHari) return false;

    // Ubah tanggal menjadi jumlah hari relatif untuk membandingkan rentang.
    int y = tahun - 1;
    serial = y * 365 + y / 4 - y / 100 + y / 400;
    for (int b = 1; b < bulan; ++b) {
        serial += hariPerBulan[b - 1];
        if (b == 2 && tahunKabisat(tahun)) ++serial;
    }
    serial += hari;
    return true;
}

// Dipakai menu untuk nolak format atau tanggal kalender yang tidak masuk akal.
bool tanggalISOValid(string tanggal) {
    int serial;
    return parseTanggalISO(tanggal, serial);
}

// Cek apakah kamar kosong selama tanggal check-in sampai akhir masa menginap.
bool kamarTersedia(ListRelasi L, adrKamar C, string tanggalCheckIn, int durasi) {
    int mulaiBaru;
    if (C == nullptr || durasi <= 0 || !parseTanggalISO(tanggalCheckIn, mulaiBaru)) return false;
    long long akhirBaru = static_cast<long long>(mulaiBaru) + durasi;

    adrRelasi R = L.first;
    while (R != nullptr) {
        if (R->child == C) {
            int mulaiLama;
            if (!parseTanggalISO(R->tanggalCheckIn, mulaiLama) || R->durasi <= 0) return false;
            long long akhirLama = static_cast<long long>(mulaiLama) + R->durasi;
            if (static_cast<long long>(mulaiBaru) < akhirLama &&
                static_cast<long long>(mulaiLama) < akhirBaru) {
                return false;
            }
        }
        R = R->next;
    }
    return true;
}

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

// Menghapus reservasi untuk pasangan tamu dan kamar yang diberikan.
bool batalkanReservasi(ListRelasi &L, adrTamu P, adrKamar C) {
    adrRelasi R = cariRelasi(L, P, C);
    if (R == nullptr) return false;

    if (R->prev != nullptr) R->prev->next = R->next;
    else L.first = R->next;

    if (R->next != nullptr) R->next->prev = R->prev;
    else L.last = R->prev;

    delete R;
    return true;
}

// Menghapus semua relasi milik tamu sebelum node tamu dibebaskan.
int hapusReservasiTamu(ListRelasi &L, adrTamu P) {
    int jumlah = 0;
    adrRelasi R = L.first;
    while (R != nullptr) {
        adrRelasi berikutnya = R->next;
        if (R->parent == P) {
            if (R->prev != nullptr) R->prev->next = R->next;
            else L.first = R->next;
            if (R->next != nullptr) R->next->prev = R->prev;
            else L.last = R->prev;
            delete R;
            jumlah++;
        }
        R = berikutnya;
    }
    return jumlah;
}

// Menghapus semua relasi yang menunjuk ke kamar sebelum kamar dibebaskan.
int hapusReservasiKamar(ListRelasi &L, adrKamar C) {
    int jumlah = 0;
    adrRelasi R = L.first;
    while (R != nullptr) {
        adrRelasi berikutnya = R->next;
        if (R->child == C) {
            if (R->prev != nullptr) R->prev->next = R->next;
            else L.first = R->next;
            if (R->next != nullptr) R->next->prev = R->prev;
            else L.last = R->prev;
            delete R;
            jumlah++;
        }
        R = berikutnya;
    }
    return jumlah;
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

// Menghitung jumlah reservasi yang dimiliki satu tamu.
int hitungReservasiTamu(ListRelasi LR, adrTamu P) {
    int jumlah = 0;
    adrRelasi R = LR.first;
    while (R != nullptr) {
        if (R->parent == P) jumlah++;
        R = R->next;
    }
    return jumlah;
}

// Menampilkan jumlah reservasi setiap tamu beserta nilai terbanyak/tersedikit.
void statistikReservasi(ListTamu LT, ListRelasi LR) {
    if (LT.firstParent == nullptr) {
        cout << "  [!] Belum ada data tamu.\n";
        return;
    }

    int terbanyak = -1;
    int tersedikit = -1;
    adrTamu P = LT.firstParent;
    while (P != nullptr) {
        int jumlah = hitungReservasiTamu(LR, P);
        cout << P->idTamu << " | " << P->nama << " | "
             << jumlah << " reservasi\n";
        if (terbanyak == -1 || jumlah > terbanyak) terbanyak = jumlah;
        if (tersedikit == -1 || jumlah < tersedikit) tersedikit = jumlah;
        P = P->next;
    }

    cout << "\nTamu dengan reservasi terbanyak (" << terbanyak << "):";
    P = LT.firstParent;
    while (P != nullptr) {
        if (hitungReservasiTamu(LR, P) == terbanyak)
            cout << "\n- " << P->nama << " (" << P->idTamu << ")";
        P = P->next;
    }

    cout << "\nTamu dengan reservasi tersedikit (" << tersedikit << "):";
    P = LT.firstParent;
    while (P != nullptr) {
        if (hitungReservasiTamu(LR, P) == tersedikit)
            cout << "\n- " << P->nama << " (" << P->idTamu << ")";
        P = P->next;
    }
    cout << "\n";
}
