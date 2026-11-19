#include "Menu.h"
#include <iostream>
using namespace std;

// Ngurus pilihan pengguna buat tambah, tampil, atau hapus kamar.
static void menuKamar(ListKamar &LK, ListRelasi &LR, adrBST &root) {
    int sub;
    do {
        cout << "\n--- KELOLA DATA KAMAR ---\n"
             << "1. Tambah Kamar Baru\n2. Tampilkan Semua Kamar\n"
             << "3. Ubah Data Kamar\n4. Hapus Data Kamar\n"
             << "0. Kembali ke Menu Utama\nPilih (0-4): ";
        cin >> sub;

        if (sub == 1) {
            int nomor;
            string tipe;
            double harga;
            cout << "Masukkan Nomor Kamar : ";
            cin >> nomor;
            if (cariKamar(LK, nomor) != nullptr) {
                cout << "  [!] Gagal: Nomor kamar " << nomor << " sudah ada!\n";
            } else {
                cout << "Masukkan Tipe Kamar  : ";
                cin >> ws;
                getline(cin, tipe);
                cout << "Masukkan Harga Kamar : ";
                cin >> harga;
                insertKamar(LK, alokasiKamar(nomor, tipe, harga));
                insertBST(root, cariKamar(LK, nomor));
                cout << "  [v] Kamar berhasil ditambahkan di akhir list.\n";
            }
        } else if (sub == 2) {
            tampilKamar(LK);
        } else if (sub == 3) {
            cout << "  [i] Fitur Update Kamar ditunda.\n";
        } else if (sub == 4) {
            int nomor;
            cout << "Masukkan Nomor Kamar yang akan dihapus: ";
            cin >> nomor;
            adrKamar kamar = cariKamar(LK, nomor);
            if (kamar == nullptr) {
                cout << "  [!] Kamar tidak ditemukan.\n";
            } else {
                int jumlahRelasi = hapusReservasiKamar(LR, kamar);
                adrKamar kamarDihapus = lepasKamar(LK, nomor);
                hapusNodeBST(root, nomor);
                delete kamarDihapus;
                cout << "  [v] Kamar dihapus; " << jumlahRelasi
                     << " reservasi terkait ikut dihapus.\n";
            }
        } else if (sub == 0) {
            cout << "  -> Kembali ke Menu Utama...\n";
        } else {
            cout << "  [!] Pilihan tidak valid.\n";
        }
    } while (sub != 0);
}

// Ngurus pilihan pengguna buat tambah, tampil, atau hapus data tamu.
static void menuTamu(ListTamu &LT, ListRelasi &LR) {
    int sub;
    do {
        cout << "\n--- KELOLA DATA TAMU ---\n"
             << "1. Tambah Tamu Baru\n2. Tampilkan Semua Tamu\n"
             << "3. Ubah Data Tamu\n4. Hapus Data Tamu\n"
             << "0. Kembali ke Menu Utama\nPilih (0-4): ";
        cin >> sub;

        if (sub == 1) {
            string id, nama, telp;
            cout << "Masukkan ID Tamu     : ";
            cin >> id;
            if (cariTamu(LT, id) != nullptr) {
                cout << "  [!] Gagal: ID Tamu " << id << " sudah terdaftar!\n";
            } else {
                cout << "Masukkan Nama Tamu   : ";
                cin >> ws;
                getline(cin, nama);
                cout << "Masukkan No. Telepon : ";
                cin >> telp;
                insertTamu(LT, alokasiTamu(id, nama, telp));
                cout << "  [v] Tamu berhasil ditambahkan di awal list.\n";
            }
        } else if (sub == 2) {
            tampilTamu(LT);
        } else if (sub == 3) {
            cout << "  [i] Fitur Update Tamu ditunda.\n";
        } else if (sub == 4) {
            string id;
            cout << "Masukkan ID Tamu yang akan dihapus: ";
            cin >> id;
            adrTamu tamu = cariTamu(LT, id);
            if (tamu == nullptr) {
                cout << "  [!] Tamu tidak ditemukan.\n";
            } else {
                int jumlahRelasi = hapusReservasiTamu(LR, tamu);
                hapusTamu(LT, id);
                cout << "  [v] Tamu dihapus; " << jumlahRelasi
                     << " reservasi terkait ikut dihapus.\n";
            }
        } else if (sub == 0) {
            cout << "  -> Kembali ke Menu Utama...\n";
        } else {
            cout << "  [!] Pilihan tidak valid.\n";
        }
    } while (sub != 0);
}

// Ngurus pembuatan, tampilan, pembatalan, dan statistik reservasi.
static void menuReservasi(ListTamu &LT, ListKamar &LK, ListRelasi &LR) {
    int sub;
    do {
        cout << "\n--- KELOLA RESERVASI ---\n"
             << "1. Buat Reservasi Kamar\n2. Tampilkan Semua Tamu & Kamar Dipesan\n"
             << "3. Ubah Durasi Reservasi (ditunda)\n4. Batalkan Reservasi\n"
             << "5. Statistik Reservasi\n0. Kembali ke Menu Utama\nPilih (0-5): ";
        cin >> sub;

        if (sub == 1) {
            string id, tanggal;
            int noKamar, durasi;
            cout << "Masukkan ID Tamu             : ";
            cin >> id;
            adrTamu P = cariTamu(LT, id);
            if (P == nullptr) {
                cout << "  [!] Tamu dengan ID " << id << " tidak ditemukan!\n";
                continue;
            }
            cout << "Masukkan Nomor Kamar         : ";
            cin >> noKamar;
            adrKamar K = cariKamar(LK, noKamar);
            if (K == nullptr) {
                cout << "  [!] Kamar nomor " << noKamar << " tidak ditemukan!\n";
                continue;
            }
            cout << "Tanggal Check-In (YYYY-MM-DD): ";
            cin >> tanggal;
            cout << "Durasi Menginap (malam)      : ";
            cin >> durasi;
            if (!tanggalISOValid(tanggal)) {
                cout << "  [!] Format/tanggal tidak valid. Gunakan YYYY-MM-DD.\n";
                continue;
            }
            if (durasi <= 0) {
                cout << "  [!] Durasi harus lebih dari 0 malam.\n";
                continue;
            }
            if (!kamarTersedia(LR, K, tanggal, durasi)) {
                cout << "  [!] Kamar sudah dipesan pada rentang tanggal tersebut.\n";
                continue;
            }
            buatReservasi(LR, P, K, tanggal, durasi);
            cout << "  [v] Reservasi berhasil dibuat (Insert After).\n";
        } else if (sub == 2) {
            tampilSemuaReservasi(LT, LR);
        } else if (sub == 3) {
            cout << "  [i] Fitur ubah durasi ditunda.\n";
        } else if (sub == 4) {
            string id;
            int noKamar;
            cout << "Masukkan ID Tamu     : ";
            cin >> id;
            adrTamu P = cariTamu(LT, id);
            if (P == nullptr) {
                cout << "  [!] Tamu dengan ID " << id << " tidak ditemukan!\n";
                continue;
            }
            cout << "Masukkan Nomor Kamar : ";
            cin >> noKamar;
            adrKamar K = cariKamar(LK, noKamar);
            if (K == nullptr) {
                cout << "  [!] Kamar nomor " << noKamar << " tidak ditemukan!\n";
                continue;
            }
            if (batalkanReservasi(LR, P, K))
                cout << "  [v] Reservasi berhasil dibatalkan.\n";
            else
                cout << "  [!] Reservasi untuk tamu dan kamar tersebut tidak ditemukan.\n";
        } else if (sub == 5) {
            statistikReservasi(LT, LR);
        } else if (sub == 0) {
            cout << "  -> Kembali ke Menu Utama...\n";
        } else {
            cout << "  [!] Pilihan tidak valid.\n";
        }
    } while (sub != 0);
}

// Ngurus pencarian kamar di BST dan pilihan traversal katalog.
static void menuKatalog(adrBST root) {
    int sub;
    do {
        cout << "\n--- PENCARIAN & KATALOG KAMAR ---\n"
             << "1. Cari Kamar berdasarkan Nomor\n"
             << "2. Tampilkan In-Order (nomor menaik)\n"
             << "3. Tampilkan Pre-Order\n4. Tampilkan Post-Order\n"
             << "0. Kembali ke Menu Utama\nPilih (0-4): ";
        cin >> sub;

        if (sub == 1) {
            int nomor;
            cout << "Masukkan Nomor Kamar: ";
            cin >> nomor;
            adrBST hasil = cariBST(root, nomor);
            if (hasil == nullptr) {
                cout << "  [!] Kamar tidak ditemukan.\n";
            } else {
                cout << "No. Kamar | Tipe Kamar | Harga per Malam\n"
                     << hasil->infoKamar->nomorKamar << " | "
                     << hasil->infoKamar->tipeKamar << " | Rp "
                     << static_cast<long>(hasil->infoKamar->harga) << "\n";
            }
        } else if (sub >= 2 && sub <= 4) {
            if (root == nullptr) {
                cout << "  [!] Data kamar masih kosong.\n";
            } else {
                cout << "No. Kamar | Tipe Kamar | Harga per Malam\n";
                if (sub == 2) inorderBST(root);
                else if (sub == 3) preorderBST(root);
                else postorderBST(root);
            }
        } else if (sub != 0) {
            cout << "  [!] Pilihan tidak valid.\n";
        }
    } while (sub != 0);
}

// Jadi pintu masuk semua menu.
void jalankanMenu(ListTamu &LT, ListKamar &LK, ListRelasi &LR, adrBST &root) {
    int pilihan;
    do {
        cout << "\n====================================\n"
             << "      SISTEM RESERVASI HOTEL        \n"
             << "====================================\n"
             << "1. Kelola Data Kamar\n2. Kelola Data Tamu\n"
             << "3. Kelola Reservasi\n4. Pencarian & Katalog Kamar\n"
             << "5. Keluar\n====================================\nPilih menu (1-5): ";
        cin >> pilihan;

        if (pilihan == 1) menuKamar(LK, LR, root);
        else if (pilihan == 2) menuTamu(LT, LR);
        else if (pilihan == 3) menuReservasi(LT, LK, LR);
        else if (pilihan == 4) menuKatalog(root);
        else if (pilihan == 5) cout << "Program selesai. Terima kasih!\n";
        else cout << "  [!] Pilihan tidak valid.\n";
    } while (pilihan != 5);
}
