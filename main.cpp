#include <iostream>
#include "Tamu.h"
#include "Kamar.h"
#include "Relasi.h"

using namespace std;

// Fungsi untuk mengisi data awal (Dummy Data) otomatis saat program dibuka
void muatDataDummy(ListTamu &LT, ListKamar &LK, ListRelasi &LR) {
    // 1. Tambah 3 Kamar awal (Insert Last)
    insertKamar(LK, alokasiKamar(203, "Deluxe", 500000));
    insertKamar(LK, alokasiKamar(105, "Standard", 300000));
    insertKamar(LK, alokasiKamar(308, "Suite", 850000));

    // 2. Tambah 2 Tamu awal (Insert First)
    insertTamu(LT, alokasiTamu("T001", "Andi Pratama", "081234567801"));
    insertTamu(LT, alokasiTamu("T002", "Budi Santoso", "081234567802"));

    // 3. Buat 1 Reservasi awal (Insert After) antara Tamu T001 dan Kamar 203
    adrTamu tamu1 = cariTamu(LT, "T001");
    adrKamar kamar203 = cariKamar(LK, 203);
    if (tamu1 != nullptr && kamar203 != nullptr) {
        buatReservasi(LR, tamu1, kamar203, "2026-11-16", 2);
    }
}

int main() {
    // Deklarasi ke-3 List (MLL-02: Parent, Child, Relasi)
    ListTamu LT;
    ListKamar LK;
    ListRelasi LR;

    // Inisialisasi List
    createListTamu(LT);
    createListKamar(LK);
    createListRelasi(LR);

    // Muat data dummy
    muatDataDummy(LT, LK, LR);

    int pilihan;
    do {
        cout << "\n====================================\n";
        cout << "      SISTEM RESERVASI HOTEL        \n";
        cout << "====================================\n";
        cout << "1. Kelola Data Kamar\n";
        cout << "2. Kelola Data Tamu\n";
        cout << "3. Kelola Reservasi\n";
        cout << "4. Pencarian & Katalog Kamar\n"; //next progress
        cout << "5. Keluar\n";
        cout << "====================================\n";
        cout << "Pilih menu (1-5): ";
        cin >> pilihan;

        switch (pilihan) {

            // MENU 1: KELOLA DATA KAMAR

            case 1: {
                int sub;
                do {
                    cout << "\n--- KELOLA DATA KAMAR ---\n";
                    cout << "1. Tambah Kamar Baru\n";
                    cout << "2. Tampilkan Semua Kamar\n";
                    cout << "3. Ubah Data Kamar\n";
                    cout << "4. Hapus Data Kamar\n";
                    cout << "0. Kembali ke Menu Utama\n";
                    cout << "Pilih (0-4): ";
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
                            cout << "  [v] Kamar berhasil ditambahkan di akhir list.\n";
                        }
                    } else if (sub == 2) {
                        tampilKamar(LK);
                    } else if (sub == 3 || sub == 4) {
                        cout << "  [i] Fitur Update Kamar akan dikerjakan pada Progress 2.\n";
                    } else if (sub == 4) {
                        cout << "  [i] Fitur Delete Kamar akan dikerjakan pada Progress 2.\n";
                    } else if (sub == 0) {
                        cout << "  -> Kembali ke Menu Utama...\n";
                    } else {
                        cout << "  [!] Pilihan tidak valid.\n";
                    }
                } while (sub != 0);
                break;
            }

            // MENU 2: KELOLA DATA TAMU
            case 2: {
                int sub;
                do {
                    cout << "\n--- KELOLA DATA TAMU ---\n";
                    cout << "1. Tambah Tamu Baru\n";
                    cout << "2. Tampilkan Semua Tamu\n";
                    cout << "3. Ubah Data Tamu\n";
                    cout << "4. Hapus Data Tamu\n";
                    cout << "0. Kembali ke Menu Utama\n";
                    cout << "Pilih (0-4): ";
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
                        cout << "  [i] Fitur Update Tamu akan dikerjakan pada Progress 2.\n";
                    } else if (sub == 4) {
                        cout << "  [i] Fitur Delete Tamu akan dikerjakan pada Progress 2.\n";
                    } else if (sub == 0) {
                        cout << "  -> Kembali ke Menu Utama...\n";
                    } else {
                        cout << "  [!] Pilihan tidak valid.\n";
                    }
                } while (sub != 0);
                break;
            }

            // MENU 3: KELOLA RESERVASI (RELASI MLL-02)
            case 3: {
                int sub;
                do {
                    cout << "\n--- KELOLA RESERVASI ---\n";
                    cout << "1. Buat Reservasi Kamar\n";
                    cout << "2. Tampilkan Semua Tamu & Kamar Dipesan\n";
                    cout << "3. Ubah Durasi Reservasi\n"; //next progress
                    cout << "4. Batalkan Reservasi\n";//next progress
                    cout << "0. Kembali ke Menu Utama\n";
                    cout << "Pilih (0-4): ";
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
                        if (cariRelasi(LR, P, K) != nullptr) {
                            cout << "  [!] Tamu ini sudah memesan kamar nomor " << noKamar << "!\n";
                            continue;
                        }
                        cout << "Tanggal Check-In (YYYY-MM-DD): ";
                        cin >> tanggal;
                        cout << "Durasi Menginap (malam)      : ";
                        cin >> durasi;

                        buatReservasi(LR, P, K, tanggal, durasi);
                        cout << "  [v] Reservasi berhasil dibuat (Insert After).\n";
                    } else if (sub == 2) {
                        tampilSemuaReservasi(LT, LR);
                    } else if (sub == 3) {
                        cout << "  [i] Fitur Update Reservasi akan dikerjakan pada Progress 2.\n";
                    } else if (sub == 4) {
                        cout << "  [i] Fitur Pembatalan Reservasi akan dikerjakan pada Progress 2.\n";
                    } else if (sub == 0) {
                        cout << "  -> Kembali ke Menu Utama...\n";
                    } else {
                        cout << "  [!] Pilihan tidak valid.\n";
                    }
                } while (sub != 0);
                break;
            }

            // MENU 4: BINARY SEARCH TREE (NEXT PROGRESS)
            case 4: {
                int sub;
                do {
                    cout << "\n--- PENCARIAN & Katalog Kamar ---\n";
                    cout << "  [i] Pembuatan file BST.h & BST.cpp untuk indeks pencarian cepat\n";
                    cout << "      serta In-Order, Pre-Order, Post-Order akan dikerjakan di Progress selanjutnya.\n";
                    cout << "0. Kembali ke Menu Utama\n";
                    cout << "Pilih (0): ";
                    cin >> sub;
                } while (sub != 0);
                break;
            }

            case 5:
                cout << "Program selesai. Terima kasih!\n";
                break;

            default:
                cout << "  [!] Pilihan tidak valid.\n";
        }
    } while (pilihan != 5);

    return 0;
}