#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char*nombre,*club;
    int posicion, edad;
} _Jugador;

typedef _Jugador* Jugador;

typedef struct nodo{
    Jugador jug;
    struct nodo*left,*right;
} Nodo;

Jugador copy_jugador(Jugador jug){
    return jug;
} 

Jugador crear_jugador(int edad){
    Jugador jug = malloc(sizeof(_Jugador));
    jug->club = "b";
    jug->nombre = "a";
    jug->posicion = 0;
    jug->edad = edad;
    return jug;
}

// Function to create a new tree Nodo
Nodo* createNode(Jugador j) {
    Nodo* newNode = (Nodo*)malloc(sizeof(Nodo));
    newNode->jug = copy_jugador(j);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}


// Function to insert a jug into the tree
Nodo* insert(Nodo* root, Jugador jug) {
    if (root == NULL) {
        return createNode(jug);
    }
    if (jug->edad < root->jug->edad) {
        root->left = insert(root->left, jug);
    } else {
        root->right = insert(root->right, jug);
    }
    return root;
}

// Function to filter the tree
Nodo* filterTree(Nodo* root, int edad_min , int edad_max) {
    if (root == NULL) {
        return NULL;
    }
    
    // Recursive calls to filter left and right subtrees
    Nodo* leftFiltered = filterTree(root->left,edad_min,edad_max);
    Nodo* rightFiltered = filterTree(root->right,edad_min,edad_max);
    
    // Check the current Nodo's jug
    if (root->jug->edad > edad_min && root->jug->edad < edad_max) {
        // Create a new Nodo for the filtered tree
        Nodo* newNode = createNode(root->jug);
        newNode->left = leftFiltered;
        newNode->right = rightFiltered;
        return newNode;
    }

    if (root->jug->edad <= edad_max) {
        return rightFiltered; // Only the right subtree could have valid nodes
    } else {
        return leftFiltered;  // Only the left subtree could have valid nodes
    }
}

void tree_inorder(Nodo* arbol){
    if(arbol == NULL) return;

    tree_inorder(arbol->left);
    printf("%i\n",arbol->jug->edad);
    tree_inorder(arbol->right);
}

int main() {
    Nodo* root = NULL;

    // Inserting values into the tree
    Jugador jug1 = crear_jugador(5);
    Jugador jug2 = crear_jugador(15);
    Jugador jug3 = crear_jugador(25);
    Jugador jug4 = crear_jugador(12);
    Jugador jug5 = crear_jugador(18);
    Jugador jug6 = crear_jugador(7);
    Jugador jug7 = crear_jugador(12);


    root = insert(root, jug1);
    root = insert(root, jug2);
    root = insert(root, jug3);
    root = insert(root, jug4);
    root = insert(root, jug5);
    root = insert(root, jug6);
    root = insert(root, jug7);

    // Filter the tree
    Nodo* filteredRoot = filterTree(root,10,20);

    // Your code to print or use the filtered tree would go here
    tree_inorder(filteredRoot);
    return 0;
}