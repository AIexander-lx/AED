// AVL Tree completo (recursivo, sin puntero al padre) - CS2023
// Material de estudio de referencia generado con ayuda de IA (Claude).
// Convenciones del curso: h(nulo) = -1, FB = h(izq) - h(der).
#include <bits/stdc++.h>
using namespace std;

template<typename T>
struct AVL {
    struct Node {
        T key;
        int height;
        Node* left;
        Node* right;
        Node(T k) : key(k), height(0), left(nullptr), right(nullptr) {}
    };

    Node* root = nullptr;

    // ---------- Auxiliares O(1) ----------
    int h(Node* u) { return u == nullptr ? -1 : u->height; }
    void update(Node* u) { u->height = 1 + max(h(u->left), h(u->right)); }
    int FB(Node* u) { return h(u->left) - h(u->right); }

    // ---------- Rotaciones: devuelven la nueva raiz del subarbol ----------
    Node* rotate_right(Node* y) {
        Node* x = y->left;
        y->left = x->right;
        x->right = y;
        update(y);   // primero y (ahora esta abajo)
        update(x);
        return x;
    }

    Node* rotate_left(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        y->left = x;
        update(x);
        update(y);
        return y;
    }

    // ---------- Rebalancear (casos LL, LR, RR, RL) ----------
    Node* rebalance(Node* u) {
        update(u);
        if (FB(u) > 1) {                          // cargado a la izquierda
            if (FB(u->left) < 0)                  // LR: primero enderezar
                u->left = rotate_left(u->left);
            return rotate_right(u);               // LL
        }
        if (FB(u) < -1) {                         // cargado a la derecha
            if (FB(u->right) > 0)                 // RL: primero enderezar
                u->right = rotate_right(u->right);
            return rotate_left(u);                // RR
        }
        return u;
    }

    // ---------- Buscar O(lg n) ----------
    bool search(T key) {
        Node* cur = root;
        while (cur != nullptr) {
            if (key == cur->key) return true;
            cur = (key < cur->key) ? cur->left : cur->right;
        }
        return false;
    }

    Node* min_node(Node* u) {
        while (u->left != nullptr) u = u->left;
        return u;
    }

    // ---------- Insertar O(lg n) ----------
    Node* insert(Node* u, T key) {
        if (u == nullptr) return new Node(key);
        if (key < u->key) u->left = insert(u->left, key);
        else if (key > u->key) u->right = insert(u->right, key);
        else return u;                            // no se permiten repetidos
        return rebalance(u);
    }
    void insert(T key) { root = insert(root, key); }

    // ---------- Eliminar O(lg n) ----------
    Node* erase(Node* u, T key) {
        if (u == nullptr) return nullptr;         // no estaba
        if (key < u->key) u->left = erase(u->left, key);
        else if (key > u->key) u->right = erase(u->right, key);
        else {
            // Caso 1 y 2: 0 o 1 hijo -> lo reemplaza su unico hijo (o nulo)
            if (u->left == nullptr || u->right == nullptr) {
                Node* child = (u->left != nullptr) ? u->left : u->right;
                delete u;
                return child;
            }
            // Caso 3: 2 hijos -> copiar el sucesor y borrarlo de la derecha
            Node* s = min_node(u->right);
            u->key = s->key;
            u->right = erase(u->right, s->key);
        }
        return rebalance(u);                      // rebalancear al volver
    }
    void erase(T key) { root = erase(root, key); }

    // ---------- Recorridos ----------
    void inorder(Node* u) {
        if (u == nullptr) return;
        inorder(u->left);
        cout << u->key << " ";
        inorder(u->right);
    }
    void preorder(Node* u) {                      // muestra clave(altura)
        if (u == nullptr) return;
        cout << u->key << "(" << u->height << ") ";
        preorder(u->left);
        preorder(u->right);
    }
    void print() {
        inorder(root);  cout << "\n";
        preorder(root); cout << "\n";
    }

    // ---------- Verificar que sigue siendo AVL (para pruebas) ----------
    bool check(Node* u) {
        if (u == nullptr) return true;
        if (abs(FB(u)) > 1) return false;
        return check(u->left) && check(u->right);
    }
};

int main() {
    AVL<int> T;
    int datos[] = {10, 20, 30, 25, 28, 27};
    for (int x : datos) T.insert(x);
    T.print();          // esperado preorden: 25(2) 20(1) 10(0) 28(1) 27(0) 30(0)

    T.erase(10);        // 20 queda hoja; 25 sigue balanceado
    T.erase(25);        // raiz con 2 hijos -> la reemplaza su sucesor 27
    T.print();
    cout << (T.check(T.root) ? "Es AVL" : "NO es AVL") << "\n";
    return 0;
}
