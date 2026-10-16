// Red-Black Tree completo (con padre y centinela NIL) - CS2023
// Sigue el pseudocodigo de la clase "Implementacion de Red-Black Tree" (Semana 9).
// Material de estudio de referencia generado con ayuda de IA (Claude).
#include <bits/stdc++.h>
using namespace std;

enum Color { RED, BLACK };

template<typename T>
struct RBTree {
    struct Node {
        T key;
        Color color;
        Node* left;
        Node* right;
        Node* parent;
    };

    Node* NIL;    // centinela: negro, hace de todas las hojas y del padre de la raiz
    Node* root;

    RBTree() {
        NIL = new Node{T(), BLACK, nullptr, nullptr, nullptr};
        NIL->left = NIL->right = NIL->parent = NIL;
        root = NIL;
    }

    // ---------- Rotaciones con padre ----------
    void rotate_left(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        if (y->left != NIL) y->left->parent = x;
        y->parent = x->parent;
        if (x->parent == NIL) root = y;
        else if (x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    void rotate_right(Node* x) {
        Node* y = x->left;
        x->left = y->right;
        if (y->right != NIL) y->right->parent = x;
        y->parent = x->parent;
        if (x->parent == NIL) root = y;
        else if (x == x->parent->right) x->parent->right = y;
        else x->parent->left = y;
        y->right = x;
        x->parent = y;
    }

    // ---------- Buscar ----------
    Node* search(T key) {
        Node* x = root;
        while (x != NIL && x->key != key)
            x = (key < x->key) ? x->left : x->right;
        return x;                                 // NIL si no esta
    }

    Node* min_node(Node* x) { while (x->left != NIL) x = x->left; return x; }

    // ---------- Insertar: como BST, entra ROJO, luego arreglar ----------
    void insert(T key) {
        Node* z = new Node{key, RED, NIL, NIL, NIL};
        Node* y = NIL;
        Node* x = root;
        while (x != NIL) {
            y = x;
            x = (z->key < x->key) ? x->left : x->right;
        }
        z->parent = y;
        if (y == NIL) root = z;
        else if (z->key < y->key) y->left = z;
        else y->right = z;
        insert_fixup(z);
    }

    // Mientras haya dos rojos seguidos, mirar al TIO
    void insert_fixup(Node* z) {
        while (z->parent->color == RED) {
            if (z->parent == z->parent->parent->left) {
                Node* t = z->parent->parent->right;          // tio
                if (t->color == RED) {                       // Caso 1: recolorear y subir
                    z->parent->color = BLACK;
                    t->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->right) {             // Caso 2: zigzag -> linea
                        z = z->parent;
                        rotate_left(z);
                    }
                    z->parent->color = BLACK;                // Caso 3: recolorear y rotar
                    z->parent->parent->color = RED;
                    rotate_right(z->parent->parent);
                }
            } else {                                         // espejo
                Node* t = z->parent->parent->left;
                if (t->color == RED) {
                    z->parent->color = BLACK;
                    t->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        rotate_right(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rotate_left(z->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }

    // ---------- Transplantar (siempre asigna padre, aunque v sea NIL) ----------
    void transplant(Node* u, Node* v) {
        if (u->parent == NIL) root = v;
        else if (u == u->parent->left) u->parent->left = v;
        else u->parent->right = v;
        v->parent = u->parent;
    }

    // ---------- Eliminar ----------
    void erase(T key) {
        Node* z = search(key);
        if (z == NIL) return;
        Node* y = z;
        Color c = y->color;                                  // color original de y
        Node* x;
        if (z->left == NIL) {
            x = z->right;
            transplant(z, z->right);
        } else if (z->right == NIL) {
            x = z->left;
            transplant(z, z->left);
        } else {
            y = min_node(z->right);
            c = y->color;
            x = y->right;
            if (y->parent == z) {
                x->parent = y;
            } else {
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        delete z;
        if (c == BLACK) erase_fixup(x);                      // hay un "negro extra"
    }

    // Mientras x sea "doblemente negro", mirar al HERMANO w
    void erase_fixup(Node* x) {
        while (x != root && x->color == BLACK) {
            if (x == x->parent->left) {
                Node* w = x->parent->right;
                if (w->color == RED) {                       // Caso 1: hermano rojo
                    w->color = BLACK;
                    x->parent->color = RED;
                    rotate_left(x->parent);
                    w = x->parent->right;
                }
                if (w->left->color == BLACK && w->right->color == BLACK) {
                    w->color = RED;                          // Caso 2: subir el negro
                    x = x->parent;
                } else {
                    if (w->right->color == BLACK) {          // Caso 3: hijo izq rojo
                        w->left->color = BLACK;
                        w->color = RED;
                        rotate_right(w);
                        w = x->parent->right;
                    }
                    w->color = x->parent->color;             // Caso 4: hijo der rojo
                    x->parent->color = BLACK;
                    w->right->color = BLACK;
                    rotate_left(x->parent);
                    x = root;
                }
            } else {                                         // espejo
                Node* w = x->parent->left;
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    rotate_right(x->parent);
                    w = x->parent->left;
                }
                if (w->right->color == BLACK && w->left->color == BLACK) {
                    w->color = RED;
                    x = x->parent;
                } else {
                    if (w->left->color == BLACK) {
                        w->right->color = BLACK;
                        w->color = RED;
                        rotate_left(w);
                        w = x->parent->left;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->left->color = BLACK;
                    rotate_right(x->parent);
                    x = root;
                }
            }
        }
        x->color = BLACK;
    }

    // ---------- Recorrido: clave + R/B ----------
    void preorder(Node* u) {
        if (u == NIL) return;
        cout << u->key << (u->color == RED ? "R " : "B ");
        preorder(u->left);
        preorder(u->right);
    }
    void print() { preorder(root); cout << "\n"; }

    // ---------- Verificar propiedades (devuelve altura negra, -1 si falla) ----------
    int check(Node* u) {
        if (u == NIL) return 1;
        if (u->color == RED && (u->left->color == RED || u->right->color == RED)) return -1;
        int l = check(u->left), r = check(u->right);
        if (l == -1 || r == -1 || l != r) return -1;
        return l + (u->color == BLACK ? 1 : 0);
    }
    bool valid() { return root->color == BLACK && check(root) != -1; }
};

int main() {
    RBTree<int> T;
    int datos[] = {41, 38, 31, 12, 19, 8};          // ejemplo de la clase
    for (int x : datos) T.insert(x);
    T.print();      // esperado: 38B 19R 12B 8R 31B 41B
    cout << (T.valid() ? "Es Red-Black" : "NO es Red-Black") << "\n";

    T.erase(8);
    T.erase(12);
    T.erase(19);
    T.print();
    cout << (T.valid() ? "Es Red-Black" : "NO es Red-Black") << "\n";
    return 0;
}
