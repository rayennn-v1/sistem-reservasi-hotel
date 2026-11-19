#include "BST.h"

// Mulai BST dalam keadaan kosong.
void createBST(adrBST &root) {
    root = nullptr;
}

// Bikin node indeks BST yang menunjuk ke data kamar asli di linked list.
adrBST alokasiBST(adrKamar kamar) {
    if (kamar == nullptr) return nullptr;

    adrBST node = new elmBST;
    node->key = kamar->nomorKamar;
    node->infoKamar = kamar;
    node->left = nullptr;
    node->right = nullptr;
    return node;
}

// Masukin kamar ke posisi yang sesuai berdasarkan nomor kamarnya.
void insertBST(adrBST &root, adrKamar kamar) {
    if (kamar == nullptr) return;

    if (root == nullptr) {
        root = alokasiBST(kamar);
    } else if (kamar->nomorKamar < root->key) {
        insertBST(root->left, kamar);
    } else if (kamar->nomorKamar > root->key) {
        insertBST(root->right, kamar);
    }
}

// Cari nomor kamar dengan mengikuti cabang kiri atau kanan BST.
adrBST cariBST(adrBST root, int nomorKamar) {
    if (root == nullptr || root->key == nomorKamar) return root;
    if (nomorKamar < root->key) return cariBST(root->left, nomorKamar);
    return cariBST(root->right, nomorKamar);
}

// Ambil node dengan key terkecil; dipakai saat node BST punya dua anak.
static adrBST ambilTerkecil(adrBST &root) {
    if (root->left == nullptr) {
        adrBST terkecil = root;
        root = root->right;
        terkecil->right = nullptr;
        return terkecil;
    }
    return ambilTerkecil(root->left);
}

// Menghapus node BST.
bool hapusNodeBST(adrBST &root, int nomorKamar) {
    if (root == nullptr) return false;
    if (nomorKamar < root->key) return hapusNodeBST(root->left, nomorKamar);
    if (nomorKamar > root->key) return hapusNodeBST(root->right, nomorKamar);

    adrBST terhapus = root;
    if (root->left == nullptr) {
        root = root->right;
    } else if (root->right == nullptr) {
        root = root->left;
    } else {
        adrBST penerus = ambilTerkecil(root->right);
        penerus->left = root->left;
        penerus->right = root->right;
        root = penerus;
    }
    delete terhapus;
    return true;
}

// Nampilin data kamar yang ditunjuk oleh satu node BST.
static void tampilNodeBST(adrBST root) {
    cout << root->infoKamar->nomorKamar << " | "
         << root->infoKamar->tipeKamar << " | Rp "
         << static_cast<long>(root->infoKamar->harga) << "\n";
}

// Kunjungi kiri, node ini, lalu kanan; hasilnya nomor kamar urut naik.
void inorderBST(adrBST root) {
    if (root != nullptr) {
        inorderBST(root->left);
        tampilNodeBST(root);
        inorderBST(root->right);
    }
}

// Kunjungi node ini dulu, baru cabang kiri dan kanan.
void preorderBST(adrBST root) {
    if (root != nullptr) {
        tampilNodeBST(root);
        preorderBST(root->left);
        preorderBST(root->right);
    }
}

// Kunjungi cabang kiri dan kanan dulu, baru node ini.
void postorderBST(adrBST root) {
    if (root != nullptr) {
        postorderBST(root->left);
        postorderBST(root->right);
        tampilNodeBST(root);
    }
}

// Bersihin semua node indeks BST saat program selesai.
void hapusBST(adrBST &root) {
    if (root != nullptr) {
        hapusBST(root->left);
        hapusBST(root->right);
        delete root;
        root = nullptr;
    }
}
