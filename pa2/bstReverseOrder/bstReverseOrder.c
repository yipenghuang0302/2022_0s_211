#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include <stdlib.h>
#include <stdio.h>

// A program to perform a REVERSE ORDER (DEPTH-FIRST) TRAVERSAL of a binary search tree

// BINARY SEARCH TREE

typedef struct BSTNode BSTNode;
struct BSTNode {
    int key;
    struct BSTNode* l_child; // nodes with smaller key will be in left subtree
    struct BSTNode* r_child; // nodes with larger key will be in right subtree
};

// Add new data to the BST using recursion
struct BSTNode* insert ( struct BSTNode* root, int key ) {

    // Base case: If the BSTNode here doesn't yet exist
    if (root==NULL) {
        root = malloc(sizeof(BSTNode));
        root->l_child = NULL;
        root->r_child = NULL;
        root->key = key;
    }

    // If the BSTNode already exists, then insert key in correct subtree
    if ( key<root->key ) {
        root->l_child = insert( root->l_child, key );
    } else if ( key==root->key ) {
        // duplicates are ignored
    } else { // key>root->key
        root->r_child = insert( root->r_child, key );
    }
    return root;
}

void depth_first ( struct BSTNode* root ) {
    if(root!=NULL) // checking if the root is not null
    {
        depth_first(root->r_child);// visiting right child
        printf(" %d ", root->key); // printing data at root
        depth_first(root->l_child); // visiting left child
    }
}

// Delete the BST using recursion
void delete_bst ( BSTNode* root ) {
    if ( root->r_child!=NULL ) {
        delete_bst (root->r_child);
    }
    if ( root->l_child!=NULL ) {
        delete_bst (root->l_child);
    }
    free (root);
}

int main ( int argc, char* argv[] ) {

    // READ INPUT FILE TO CREATE BINARY SEARCH TREE
    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }
    BSTNode* root = NULL;
    int key;
    while ( fscanf(fp, "%d", &key)!=EOF ) {
        root = insert (root, key);
    }
    fclose(fp);

    depth_first(root);

    delete_bst(root);
    return EXIT_SUCCESS;
}
