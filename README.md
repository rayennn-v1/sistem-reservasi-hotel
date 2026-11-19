# Sistem Reservasi Hotel

Program berbasis C++ untuk mengelola data kamar, data tamu, dan reservasi hotel. Proyek ini dibuat sebagai Tugas Besar mata kuliah Struktur Data dan berjalan melalui antarmuka command line (CLI).

## Struktur Data

- **Singly linked list tamu (Parent)** menyimpan ID, nama, dan nomor telepon tamu. Tamu baru ditambahkan di awal list.
- **Singly linked list kamar (Child)** menyimpan nomor, tipe, dan harga kamar per malam. Kamar baru ditambahkan di akhir list.
- **Doubly linked list reservasi (Relasi)** menghubungkan tamu dan kamar, serta menyimpan tanggal check-in dan durasi menginap. Reservasi baru ditambahkan di akhir list melalui operasi insert after.
- Hubungan Parent, Child, dan Relasi membentuk konsep **Multi Linked List (MLL)**.

## Fitur yang Tersedia

- Memuat data contoh tamu, kamar, dan satu reservasi saat program dimulai.
- Menambahkan dan menampilkan data tamu serta kamar.
- Memeriksa ID tamu dan nomor kamar agar tidak duplikat ketika menambah data.
- Membuat reservasi dengan validasi bahwa tamu dan kamar terdaftar.
- Memvalidasi tanggal ISO dan durasi positif, serta mencegah pemesanan kamar pada tanggal yang bertumpang tindih.
- Membatalkan reservasi berdasarkan ID tamu dan nomor kamar.
- Menghapus data tamu atau kamar beserta reservasi terkait; penghapusan kamar juga memperbarui BST.
- Menampilkan daftar reservasi berdasarkan tamu.
- Menampilkan jumlah reservasi setiap tamu serta tamu dengan jumlah terbanyak dan tersedikit.
- Mencari tamu berdasarkan ID dan kamar berdasarkan nomor melalui linked list.
- Mencari kamar melalui BST dan menampilkan traversal inorder, preorder, serta postorder.

## Fitur yang Belum Diimplementasikan

- Mengubah data tamu dan kamar.
- Mengubah durasi reservasi (ditunda; bukan kebutuhan fungsional pada proposal).
- Menghapus kamar secara aman dari linked list dan BST (belum tersedia; BST saat ini dibersihkan saat program keluar).

Menu fitur tersebut tersedia sebagai rencana pengembangan, tetapi operasinya belum tersedia pada kode saat ini.

## Struktur File

| File | Kegunaan |
|---|---|
| `main.cpp` | Inisialisasi list, memuat data contoh, dan menjalankan menu utama serta submenu. |
| `Menu.h` / `Menu.cpp` | Menampilkan menu dan menangani input pengguna untuk kamar, tamu, reservasi, dan katalog BST. |
| `Tamu.h` / `Tamu.cpp` | Definisi node dan list tamu serta operasi inisialisasi, alokasi, insert first, pencarian, dan tampilan. |
| `Kamar.h` / `Kamar.cpp` | Definisi node dan list kamar serta operasi inisialisasi, alokasi, insert last, pencarian, dan tampilan. |
| `Relasi.h` / `Relasi.cpp` | Definisi node dan list reservasi serta operasi insert after, pencarian relasi, pembuatan, dan tampilan reservasi. |
| `BST.h` / `BST.cpp` | Indeks BST kamar, pencarian berdasarkan nomor, traversal inorder/preorder/postorder, dan pembersihan node BST. Node BST menunjuk data kamar pada linked list. |

## Data Contoh

Saat aplikasi dibuka, program membuat tiga kamar (203 Deluxe, 105 Standard, 308 Suite), dua tamu (Andi Pratama dan Budi Santoso), serta reservasi Andi untuk kamar 203 selama dua malam dengan check-in `2026-11-16`.

Data dimuat ulang setiap kali program dijalankan. Data yang dimasukkan selama sesi hanya disimpan di memori dan hilang setelah program ditutup.

## Menu Program

1. Kelola Data Kamar
2. Kelola Data Tamu
3. Kelola Reservasi
4. Pencarian & Katalog Kamar (pencarian BST dan traversal)
5. Keluar

## Kompilasi dan Menjalankan
Dari direktori proyek, kompilasi seluruh berkas sumber dengan compiler C++ yang mendukung C++11 atau lebih baru:

```bash
g++ -std=c++11 -Wall -Wextra -pedantic main.cpp Menu.cpp Tamu.cpp Kamar.cpp Relasi.cpp BST.cpp -o hotel
```

Jalankan hasil kompilasi:

```bash
./hotel
```

Di Windows dengan MinGW, jalankan `hotel.exe` setelah kompilasi.
