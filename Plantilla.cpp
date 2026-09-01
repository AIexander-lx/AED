#include <iostream>
using namespace std;

// ============================================================
// NODO DE LISTA SIMPLE
// ============================================================

template <typename T>
struct Node {
    T data;
    Node<T>* next;

    Node(T value, Node<T>* next = nullptr)
        : data(value), next(next) {}
};


// ============================================================
// LISTA SIMPLEMENTE ENLAZADA
// ============================================================

template <typename T>
struct LinkedList {
    Node<T>* head = nullptr;
    Node<T>* tail = nullptr;
    int sz = 0;

    ~LinkedList() {
        clear();
    }

    bool empty() const {
        return head == nullptr;
    }

    int size() const {
        return sz;
    }

    T& front() {
        return head->data;       // Precondicion: lista no vacia
    }

    T& back() {
        return tail->data;       // Precondicion: lista no vacia
    }

    void push_front(T value) {
        Node<T>* nuevo = new Node<T>(value, head);
        head = nuevo;

        if (tail == nullptr) {
            tail = nuevo;
        }

        sz++;
    }

    void push_back(T value) {
        Node<T>* nuevo = new Node<T>(value);

        if (tail == nullptr) {
            head = tail = nuevo;
        } else {
            tail->next = nuevo;
            tail = nuevo;
        }

        sz++;
    }

    // Inserta despues de node.
    void insert_after(Node<T>* node, T value) {
        if (node == nullptr) return;

        Node<T>* nuevo = new Node<T>(value, node->next);
        node->next = nuevo;

        if (node == tail) {
            tail = nuevo;
        }

        sz++;
    }

    // Inserta en la posicion k: 0 <= k <= sz.
    void insert(int k, T value) {
        if (k < 0 || k > sz) return;

        if (k == 0) {
            push_front(value);
            return;
        }

        if (k == sz) {
            push_back(value);
            return;
        }

        Node<T>* current = head;
        for (int i = 0; i < k - 1; i++) {
            current = current->next;
        }

        insert_after(current, value);
    }

    void pop_front() {
        if (head == nullptr) return;

        Node<T>* eliminado = head;
        head = head->next;
        delete eliminado;
        sz--;

        if (head == nullptr) {
            tail = nullptr;
        }
    }

    void pop_back() {
        if (head == nullptr) return;

        if (head == tail) {
            delete head;
            head = tail = nullptr;
            sz = 0;
            return;
        }

        Node<T>* previous = head;
        while (previous->next != tail) {
            previous = previous->next;
        }

        delete tail;
        tail = previous;
        tail->next = nullptr;
        sz--;
    }

    // Elimina el nodo que esta despues de node.
    void erase_after(Node<T>* node) {
        if (node == nullptr || node->next == nullptr) return;

        Node<T>* eliminado = node->next;
        node->next = eliminado->next;

        if (eliminado == tail) {
            tail = node;
        }

        delete eliminado;
        sz--;
    }

    // Elimina la posicion k: 0 <= k < sz.
    void erase(int k) {
        if (k < 0 || k >= sz) return;

        if (k == 0) {
            pop_front();
            return;
        }

        Node<T>* previous = head;
        for (int i = 0; i < k - 1; i++) {
            previous = previous->next;
        }

        erase_after(previous);
    }

    Node<T>* find(T value) const {
        Node<T>* current = head;

        while (current != nullptr && current->data != value) {
            current = current->next;
        }

        return current;
    }

    void reverse() {
        Node<T>* previous = nullptr;
        Node<T>* current = head;
        tail = head;

        while (current != nullptr) {
            Node<T>* following = current->next;
            current->next = previous;
            previous = current;
            current = following;
        }

        head = previous;
    }

    void clear() {
        while (head != nullptr) {
            Node<T>* following = head->next;
            delete head;
            head = following;
        }

        tail = nullptr;
        sz = 0;
    }

    void print() const {
        for (Node<T>* current = head;
             current != nullptr;
             current = current->next) {
            cout << current->data << ' ';
        }
        cout << '\n';
    }
};


// ============================================================
// PATRONES IMPORTANTES PARA PROBLEMAS DE LISTAS SIMPLES
// Las funciones reciben la cabeza y devuelven la nueva cabeza.
// ============================================================

// Reverse Linked List
template <typename T>
Node<T>* reverse_list(Node<T>* head) {
    Node<T>* previous = nullptr;
    Node<T>* current = head;

    while (current != nullptr) {
        Node<T>* following = current->next;
        current->next = previous;
        previous = current;
        current = following;
    }

    return previous;
}

// Middle of the Linked List (si hay dos centros, devuelve el segundo).
template <typename T>
Node<T>* middle_node(Node<T>* head) {
    Node<T>* slow = head;
    Node<T>* fast = head;

    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}

// Linked List Cycle: algoritmo de Floyd.
template <typename T>
bool has_cycle(Node<T>* head) {
    Node<T>* slow = head;
    Node<T>* fast = head;

    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast) return true;
    }

    return false;
}

// Merge Two Sorted Lists. Reutiliza los nodos existentes.
template <typename T>
Node<T>* merge_sorted(Node<T>* a, Node<T>* b) {
    Node<T> dummy(T{});
    Node<T>* last = &dummy;

    while (a != nullptr && b != nullptr) {
        if (a->data <= b->data) {
            last->next = a;
            a = a->next;
        } else {
            last->next = b;
            b = b->next;
        }
        last = last->next;
    }

    last->next = (a != nullptr) ? a : b;
    return dummy.next;
}

// Remove Duplicates from Sorted List.
template <typename T>
Node<T>* remove_duplicates(Node<T>* head) {
    Node<T>* current = head;

    while (current != nullptr && current->next != nullptr) {
        if (current->data == current->next->data) {
            Node<T>* eliminado = current->next;
            current->next = eliminado->next;
            delete eliminado;
        } else {
            current = current->next;
        }
    }

    return head;
}

// Remove Nth Node From End of List.
template <typename T>
Node<T>* remove_nth_from_end(Node<T>* head, int n) {
    Node<T> dummy(T{}, head);
    Node<T>* slow = &dummy;
    Node<T>* fast = &dummy;

    for (int i = 0; i < n; i++) {
        if (fast->next == nullptr) return head; // n invalido
        fast = fast->next;
    }

    while (fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next;
    }

    Node<T>* eliminado = slow->next;
    slow->next = eliminado->next;
    delete eliminado;

    return dummy.next;
}

// Rotate List: rota k posiciones hacia la derecha.
template <typename T>
Node<T>* rotate_right(Node<T>* head, int k) {
    if (head == nullptr || head->next == nullptr || k == 0) {
        return head;
    }

    int length = 1;
    Node<T>* tail = head;

    while (tail->next != nullptr) {
        tail = tail->next;
        length++;
    }

    k %= length;
    if (k == 0) return head;

    tail->next = head; // forma un circulo temporal

    int steps = length - k - 1;
    Node<T>* new_tail = head;
    for (int i = 0; i < steps; i++) {
        new_tail = new_tail->next;
    }

    Node<T>* new_head = new_tail->next;
    new_tail->next = nullptr;
    return new_head;
}

// Reverse Linked List II: invierte desde left hasta right (1-indexado).
template <typename T>
Node<T>* reverse_between(Node<T>* head, int left, int right) {
    if (head == nullptr || left == right) return head;

    Node<T> dummy(T{}, head);
    Node<T>* before = &dummy;

    for (int i = 1; i < left; i++) {
        before = before->next;
    }

    Node<T>* current = before->next;

    for (int i = 0; i < right - left; i++) {
        Node<T>* moved = current->next;
        current->next = moved->next;
        moved->next = before->next;
        before->next = moved;
    }

    return dummy.next;
}

// Partition List: menores que x primero; conserva el orden relativo.
template <typename T>
Node<T>* partition_list(Node<T>* head, T x) {
    Node<T> less_dummy(T{});
    Node<T> greater_dummy(T{});
    Node<T>* less = &less_dummy;
    Node<T>* greater = &greater_dummy;

    while (head != nullptr) {
        Node<T>* following = head->next;
        head->next = nullptr;

        if (head->data < x) {
            less->next = head;
            less = head;
        } else {
            greater->next = head;
            greater = head;
        }

        head = following;
    }

    less->next = greater_dummy.next;
    return less_dummy.next;
}

// Sort List: merge sort.
template <typename T>
Node<T>* sort_list(Node<T>* head) {
    if (head == nullptr || head->next == nullptr) return head;

    Node<T>* slow = head;
    Node<T>* fast = head->next;

    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }

    Node<T>* second = slow->next;
    slow->next = nullptr;

    Node<T>* left = sort_list(head);
    Node<T>* right = sort_list(second);
    return merge_sorted(left, right);
}


// ============================================================
// LISTA DOBLEMENTE ENLAZADA
// ============================================================

template <typename T>
struct DoubleNode {
    T data;
    DoubleNode<T>* next;
    DoubleNode<T>* prev;

    DoubleNode(T value,
               DoubleNode<T>* next = nullptr,
               DoubleNode<T>* prev = nullptr)
        : data(value), next(next), prev(prev) {}
};

template <typename T>
struct DoublyLinkedList {
    DoubleNode<T>* head = nullptr;
    DoubleNode<T>* tail = nullptr;
    int sz = 0;

    ~DoublyLinkedList() {
        clear();
    }

    bool empty() const {
        return head == nullptr;
    }

    int size() const {
        return sz;
    }

    void push_front(T value) {
        DoubleNode<T>* nuevo = new DoubleNode<T>(value, head);

        if (head != nullptr) {
            head->prev = nuevo;
        } else {
            tail = nuevo;
        }

        head = nuevo;
        sz++;
    }

    void push_back(T value) {
        DoubleNode<T>* nuevo = new DoubleNode<T>(value, nullptr, tail);

        if (tail != nullptr) {
            tail->next = nuevo;
        } else {
            head = nuevo;
        }

        tail = nuevo;
        sz++;
    }

    void insert_after(DoubleNode<T>* node, T value) {
        if (node == nullptr) return;

        if (node == tail) {
            push_back(value);
            return;
        }

        DoubleNode<T>* nuevo =
            new DoubleNode<T>(value, node->next, node);

        node->next->prev = nuevo;
        node->next = nuevo;
        sz++;
    }

    // Elimina exactamente el nodo recibido.
    void erase(DoubleNode<T>* node) {
        if (node == nullptr) return;

        if (node->prev != nullptr) {
            node->prev->next = node->next;
        } else {
            head = node->next;
        }

        if (node->next != nullptr) {
            node->next->prev = node->prev;
        } else {
            tail = node->prev;
        }

        delete node;
        sz--;
    }

    void pop_front() {
        erase(head);
    }

    void pop_back() {
        erase(tail);
    }

    DoubleNode<T>* find(T value) const {
        DoubleNode<T>* current = head;

        while (current != nullptr && current->data != value) {
            current = current->next;
        }

        return current;
    }

    void clear() {
        while (head != nullptr) {
            DoubleNode<T>* following = head->next;
            delete head;
            head = following;
        }

        tail = nullptr;
        sz = 0;
    }

    void print() const {
        for (DoubleNode<T>* current = head;
             current != nullptr;
             current = current->next) {
            cout << current->data << ' ';
        }
        cout << '\n';
    }

    void print_reverse() const {
        for (DoubleNode<T>* current = tail;
             current != nullptr;
             current = current->prev) {
            cout << current->data << ' ';
        }
        cout << '\n';
    }
};


// ============================================================
// LISTA CIRCULAR SIMPLEMENTE ENLAZADA
// Invariante: si no esta vacia, tail->next == head.
// ============================================================

template <typename T>
struct CircularList {
    Node<T>* head = nullptr;
    Node<T>* tail = nullptr;
    int sz = 0;

    ~CircularList() {
        clear();
    }

    bool empty() const {
        return head == nullptr;
    }

    int size() const {
        return sz;
    }

    void push_front(T value) {
        Node<T>* nuevo = new Node<T>(value);

        if (head == nullptr) {
            head = tail = nuevo;
            nuevo->next = nuevo;
        } else {
            nuevo->next = head;
            head = nuevo;
            tail->next = head;
        }

        sz++;
    }

    void push_back(T value) {
        Node<T>* nuevo = new Node<T>(value);

        if (head == nullptr) {
            head = tail = nuevo;
            nuevo->next = nuevo;
        } else {
            nuevo->next = head;
            tail->next = nuevo;
            tail = nuevo;
        }

        sz++;
    }

    void pop_front() {
        if (head == nullptr) return;

        Node<T>* eliminado = head;

        if (head == tail) {
            head = tail = nullptr;
        } else {
            head = head->next;
            tail->next = head;
        }

        delete eliminado;
        sz--;
    }

    void pop_back() {
        if (head == nullptr) return;

        if (head == tail) {
            pop_front();
            return;
        }

        Node<T>* previous = head;
        while (previous->next != tail) {
            previous = previous->next;
        }

        delete tail;
        tail = previous;
        tail->next = head;
        sz--;
    }

    // Una rotacion hacia la izquierda.
    void rotate_left() {
        if (head == nullptr || head == tail) return;
        head = head->next;
        tail = tail->next;
    }

    void clear() {
        while (head != nullptr) {
            pop_front();
        }
    }

    void print() const {
        if (head == nullptr) {
            cout << '\n';
            return;
        }

        Node<T>* current = head;
        do {
            cout << current->data << ' ';
            current = current->next;
        } while (current != head);

        cout << '\n';
    }
};

