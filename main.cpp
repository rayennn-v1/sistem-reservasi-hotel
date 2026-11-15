#include <iostream>
#include "Tamu.h"
#include "Kamar.h"
#include "BST.h"
#include "Relasi.h"

using namespace std;

void muatDataDummy(ListTamu &LT, ListKamar &LK, adrBST &rootBST) {
    int noKamar[] = {203, 105, 308, 101, 150, 250, 410};
    string tipe[] = {"Deluxe", "Standard", "Suite", "Standard", "Standard", "Deluxe", "President"};
    double harga[] = {500000, 300000, 850000, 300000, 350000, 550000, 1200000};

    for (int i = 0; i < 7; i++) {
        adrKamar K = alokasiKamar(noKamar[i], tipe[i], harga[i]);
        insertKamar(LK, K);              // Masuk ke List Child 
        insertBST(rootBST, alokasiBST(K)); // Masuk ke BST
    }

    // Data Dummy Tamu
    insertTamu(LT, alokasiTamu("T001", "Andi Pratama", "081234567801"));
    insertTamu(LT, alokasiTamu("T002", "Budi Santoso", "081234567802"));
    insertTamu(LT, alokasiTamu("T003", "Citra Lestari", "081234567803"));
}

int main() {
    ListTamu LT;
    ListKamar LK;
    ListRelasi LR;
    adrBST rootBST;

    createListTamu(LT);
    createListKamar(LK);
    createListRelasi(LR);
    createBST(rootBST);

    muatDataDummy(LT, LK, rootBST);

    int pilihan;
    do {
        cout << "\n====================================\n";
        cout << "      SISTEM RESERVASI HOTEL        \n";
        cout << "       [PROGRESS 1 - 50%]           \n";
        cout << "====================================\n";
        cout << "1. Kelola Data Kamar\n";
        cout << "2. Kelola Data Tamu\n";
        cout << "3. Reservasi Kamar\n";
        cout << "4. Kelola Reservasi\n";
        cout << "5. Pencarian Data\n";
        cout << "6. Tampilkan Data\n";
        cout << "7. Keluar\n";
        cout << "====================================\n";
        cout << "Pilih menu (1-7): ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: {
                int sub;
                do {
                    cout << "\n--- KELOLA DATA KAMAR ---\n";
                    cout << "1. Tambah Kamar\n";
                    cout << "2. Tampilkan Semua Kamar\n";
                    cout << "3. Hapus Kamar\n"; //next progress
                    cout << "0. Kembali ke Menu Utama\n";
                    cout << "Pilih (0-3): ";
                    cin >> sub;

                    if (sub == 1) {
                        int nomor;
                        string tipe;
                        double harga;
                        cout << "Masukkan Nomor Kamar : ";
                        cin >> nomor;
                        if (searchBST(rootBST, nomor) != nullptr) {
                            cout << "  [!] Gagal: Nomor kamar " << nomor << " sudah ada!\n";
                        } else {
                            cout << "Masukkan Tipe Kamar  : ";
                            cin >> ws;
                            getline(cin, tipe);
                            cout << "Masukkan Harga Kamar : ";
                            cin >> harga;
                            adrKamar K = alokasiKamar(nomor, tipe, harga);
                            insertKamar(LK, K);
                            insertBST(rootBST, alokasiBST(K));
                            cout << "  [v] Kamar berhasil disimpan.\n";
                        }
                    } else if (sub == 2) {
                        tampilKamar(LK);
                    } else if (sub == 3) {
                        cout << "  [i] Fitur hapus kamar akan dikerjakan pada Progress 2.\n";
                    } else if (sub == 0) {
                        cout << "  -> Kembali ke Menu Utama...\n";
                    } else {
                        cout << "  [!] Pilihan tidak valid.\n";
                    }
                } while (sub != 0);
                break;
            }
            case 2: {
                int sub;
                do {
                    cout << "\n--- KELOLA DATA TAMU ---\n";
                    cout << "1. Tambah Tamu\n";
                    cout << "2. Tampilkan Semua Tamu\n";
                    cout << "3. Hapus Tamu\n"; //next progress
                    cout << "0. Kembali ke Menu Utama\n";
                    cout << "Pilih (0-3): ";
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
                            cout << "  [v] Tamu berhasil ditambahkan.\n";
                        }
                    } else if (sub == 2) {
                        tampilTamu(LT);
                    } else if (sub == 3) {
                        cout << "  [i] Fitur hapus tamu belum ada.\n";
                    } else if (sub == 0) {
                        cout << "  -> Kembali ke Menu Utama...\n";
                    } else {
                        cout << "  [!] Pilihan tidak valid.\n";
                    }
                } while (sub != 0);
                break;
            }
            case 3:
            case 4: {
                int sub;
                do {
                    cout << "\n--- MENU RESERVASI ---\n"; //next progress
                    cout << "  [i] Modul Transaksi & Relasi MLL-02 (Insert After & Delete Relasi)\n";
                    cout << "      akan dilanjutkan di progress selanjutnya\n";
                    cout << "0. Kembali ke Menu Utama\n";
                    cout << "Pilih (0): ";
                    cin >> sub;
                    if (sub != 0) {
                        cout << "  [!] Masukkan angka 0 untuk kembali.\n";
                    }
                } while (sub != 0);
                break;
            }
            case 5: {
                int sub;
                do {
                    cout << "\n--- PENCARIAN DATA ---\n";
                    cout << "1. Cari Kamar berdasarkan Nomor\n";
                    cout << "2. Cari Tamu berdasarkan ID\n";
                    cout << "0. Kembali ke Menu Utama\n";
                    cout << "Pilih (0-2): ";
                    cin >> sub;

                    if (sub == 1) {
                        int no;
                        cout << "Masukkan Nomor Kamar yang dicari: ";
                        cin >> no;
                        adrBST hasil = searchBST(rootBST, no);
                        if (hasil != nullptr) {
                            cout << "  [v] Kamar Ditemukan di BST!\n";
                            cout << "      Nomor Kamar : " << hasil->infoKamar->info.nomorKamar << "\n";
                            cout << "      Tipe Kamar  : " << hasil->infoKamar->info.tipeKamar << "\n";
                            cout << "      Harga/Malam : Rp " << (long)hasil->infoKamar->info.harga << "\n";
                        } else {
                            cout << "  [!] Kamar nomor " << no << " tidak ditemukan.\n";
                        }
                    } else if (sub == 2) {
                        string id;
                        cout << "Masukkan ID Tamu yang dicari: ";
                        cin >> id;
                        adrTamu hasil = cariTamu(LT, id);
                        if (hasil != nullptr) {
                            cout << "  [v] Tamu Ditemukan di List Parent!\n";
                            cout << "      ID Tamu     : " << hasil->info.idTamu << "\n";
                            cout << "      Nama        : " << hasil->info.nama << "\n";
                            cout << "      No. Telepon : " << hasil->info.noTelepon << "\n";
                        } else {
                            cout << "  [!] Tamu dengan ID " << id << " tidak ditemukan.\n";
                        }
                    } else if (sub == 0) {
                        cout << "  -> Kembali ke Menu Utama...\n";
                    } else {
                        cout << "  [!] Pilihan tidak valid.\n";
                    }
                } while (sub != 0);
                break;
            }
            case 6: {
                int sub;
                do {
                    cout << "\n--- DATA ORDER ---\n";
                    cout << "1. In-Order Traversal\n";
                    cout << "2. Pre-Order Traversal\n"; //next progress
                    cout << "3. Post-Order Traversal\n"; //next progress
                    cout << "0. Kembali ke Menu Utama\n";
                    cout << "Pilih (0-3): ";
                    cin >> sub;

                    if (sub == 1) {
                        cout << "\nHasil In-Order Traversal:\n";
                        inorder(rootBST);
                    } else if (sub == 2 || sub == 3) {
                        cout << "  [i] Pre-Order dan Post-Order Traversal akan ditambahkan pada progress selanjutnya.\n";
                    } else if (sub == 0) {
                        cout << "  -> Kembali ke Menu Utama...\n";
                    } else {
                        cout << "  [!] Pilihan tidak valid.\n";
                    }
                } while (sub != 0);
                break;
            }
            case 7:
                cout << "Program selesai. Terima kasih!\n";
                break;
            default:
                cout << "  [!] Pilihan tidak valid.\n";
        }
    } while (pilihan != 7);

    return 0;
}