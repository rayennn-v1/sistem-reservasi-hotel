#ifndef BST_H
#define BST_H

#include "Kamar.h"

typedef struct NodeBST *adrBST;

struct NodeBST {
    int nomorKamar;      // Key pencarian
    adrKamar infoKamar;  // Pointer ke node Kamar pada List Child
    adrBST left;
    adrBST right;
};


void createBST(adrBST &root);
adrBST alokasiBST(adrKamar kamar);
void insertBST(adrBST &root, adrBST node);
adrBST searchBST(adrBST root, int nomorKamar);
void inorder(adrBST root);

#endif