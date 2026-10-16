// BST completo (iterativo, con puntero al padre) - CS2023
// Material de estudio de referencia generado con ayuda de IA (Claude).
#include <bits/stdc++.h>
using namespace std;

template<typename T>
struct BST {
    struct Node {
        T key;
        Node* left;
        Node* right;
        Node* parent;
        Node(T k) : key(k), left(nullptr), right(nullptr), parent(nullptr) {}
    };

    Node* root = nullptr;

    // ---------- Buscar O(h) ----------
    Node* search(T key) {
        Node* cur = root;
        while (cur != nullptr && cur->key != key)
            cur = (key < cur->key) ? cur->left : cur->right;
        return cur;                               // nullptr si no esta
    }

    Node* min_node(Node* u) { while (u->left != nullptr) u = u->left; return u; }
    Node* max_node(Node* u) { while (u->right != nullptr) u = u->right; return u; }

    // ---------- Insertar O(h) ----------
    void insert(T key) {
        Node* z = new Node(key);
        Node* y = nullptr;
        Node* x = root;
        while (x != nullptr) {                    // bajar buscando el lugar
            y = x;
            x = (key < x->key) ? x->left : x->right;
        }
        z->parent = y;
        if (y == nullptr) root = z;               // arbol vacio
        else if (key < y->key) y->left = z;
        else y->right = z;
    }

    // ---------- Sucesor / Predecesor O(h) ----------
    Node* successor(Node* x) {
        if (x->right != nullptr) return min_node(x->right);
        Node* y = x->parent;
        while (y != nullptr && x == y->right) { x = y; y = y->parent; }
        return y;
    }

    Node* predecessor(Node* x) {
        if (x->left != nullptr) return max_node(x->left);
        Node* y = x->parent;
        while (y != nullptr && x == y->left) { x = y; y = y->parent; }
        return y;
    }

    // ---------- Transplantar: v ocupa el lugar de u (no borra u) ----------
    void transplant(Node* u, Node* v) {
        if (u->parent == nullptr) root = v;
        else if (u == u->parent->left) u->parent->left = v;
        else u->parent->right = v;
        if (v != nullptr) v->parent = u->parent;
    }

    // ---------- Eliminar O(h): los 3 casos ----------
    void erase(Node* z) {
        if (z->left == nullptr) {                 // 0 hijos o solo hijo derecho
            transplant(z, z->right);
        } else if (z->right == nullptr) {         // solo hijo izquierdo
            transplant(z, z->left);
        } else {                                  // 2 hijos: usar el sucesor
            Node* y = min_node(z->right);
            if (y->parent != z) {                 // sucesor no es hijo directo
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
        }
        delete z;
    }
    void erase(T key) {
        Node* z = search(key);
        if (z != nullptr) erase(z);
    }

    // ---------- Recorridos ----------
    void inorder(Node* u) {
        if (u == nullptr) return;
        inorder(u->left); cout << u->key << " "; inorder(u->right);
    }
    void preorder(Node* u) {
        if (u == nullptr) return;
        cout << u->key << " "; preorder(u->left); preorder(u->right);
    }
    void postorder(Node* u) {
        if (u == nullptr) return;
        postorder(u->left); postorder(u->right); cout << u->key << " ";
    }
    int height(Node* u) {
        if (u == nullptr) return -1;
        return 1 + max(height(u->left), height(u->right));
    }
};

int main() {
    BST<int> B;
    int datos[] = {8, 3, 10, 1, 6, 14, 4, 7, 13};
    for (int x : datos) B.insert(x);
    B.inorder(B.root);  cout << "\n";              // 1 3 4 6 7 8 10 13 14
    B.preorder(B.root); cout << "\n";
    cout << "Altura: " << B.height(B.root) << "\n";

    cout << "Sucesor de 7: " << B.successor(B.search(7))->key << "\n";  // 8

    B.erase(1);   // hoja
    B.erase(10);  // un hijo
    B.erase(3);   // dos hijos
    B.inorder(B.root); cout << "\n";               // 4 6 7 8 13 14
    return 0;
}
