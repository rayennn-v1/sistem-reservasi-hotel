#include "BST.h"

void createBST(adrBST &root) {
    root = nullptr;
}

adrBST alokasiBST(adrKamar kamar) {
    adrBST node = new NodeBST;
    node->nomorKamar = kamar->info.nomorKamar;
    node->infoKamar = kamar;
    node->left = nullptr;
    node->right = nullptr;
    return node;
}

void insertBST(adrBST &root, adrBST node) {
    if (root == nullptr) {
        root = node;
    } else if (node->nomorKamar < root->nomorKamar) {
        insertBST(root->left, node);
    } else if (node->nomorKamar > root->nomorKamar) {
        insertBST(root->right, node);
    }
}

adrBST searchBST(adrBST root, int nomorKamar) {
    if (root == nullptr || root->nomorKamar == nomorKamar) {
        return root;
    }
    if (nomorKamar < root->nomorKamar) {
        return searchBST(root->left, nomorKamar);
    }
    return searchBST(root->right, nomorKamar);
}

void inorder(adrBST root) {
    if (root != nullptr) {
        inorder(root->left);
        cout << "  -> Kamar [" << root->nomorKamar << "] | Tipe: " << root->infoKamar->info.tipeKamar << " | Harga: Rp " << (long)root->infoKamar->info.harga << "\n";
        inorder(root->right);
    }
}