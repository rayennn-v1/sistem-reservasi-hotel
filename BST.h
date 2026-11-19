#ifndef BST_H
#define BST_H

#include "Kamar.h"

// Node BST menyimpan kunci nomor kamar dan pointer ke data kamar di ListKamar.
typedef struct elmBST *adrBST;

struct elmBST {
    int key;
    adrKamar infoKamar;
    adrBST left;
    adrBST right;
};

void createBST(adrBST &root);
adrBST alokasiBST(adrKamar kamar);
void insertBST(adrBST &root, adrKamar kamar);
adrBST cariBST(adrBST root, int nomorKamar);
bool hapusNodeBST(adrBST &root, int nomorKamar);
void inorderBST(adrBST root);
void preorderBST(adrBST root);
void postorderBST(adrBST root);
void hapusBST(adrBST &root);

#endif
