#include <iostream>
#include <string>
using namespace std;

// ============================================================
// NODO SIMPLE
// Usado por la pila y por la cola.
// ============================================================

template <typename T>
struct Node {
    T data;
    Node<T>* next;

    Node(T value, Node<T>* next = nullptr)
        : data(value), next(next) {}
};


// ============================================================
// 1. PILA ENLAZADA (STACK)
// LIFO: el ultimo que entra es el primero que sale.
// ============================================================

template <typename T>
struct Stack {
    Node<T>* topNode = nullptr;
    int sz = 0;

    ~Stack() {
        clear();
    }

    bool empty() const {
        return topNode == nullptr;
    }

    int size() const {
        return sz;
    }

    T& top() {
        return topNode->data;       // Precondicion: pila no vacia
    }

    const T& top() const {
        return topNode->data;
    }

    void push(T value) {
        topNode = new Node<T>(value, topNode);
        sz++;
    }

    void pop() {
        if (empty()) return;

        Node<T>* removed = topNode;
        topNode = topNode->next;

        delete removed;
        sz--;
    }

    void clear() {
        while (!empty()) {
            pop();
        }
    }

    void print() const {
        for (Node<T>* current = topNode;
             current != nullptr;
             current = current->next) {
            cout << current->data << ' ';
        }
        cout << '\n';
    }
};


// ============================================================
// 2. COLA ENLAZADA (QUEUE)
// FIFO: el primero que entra es el primero que sale.
// ============================================================

template <typename T>
struct Queue {
    Node<T>* head = nullptr;
    Node<T>* tail = nullptr;
    int sz = 0;

    ~Queue() {
        clear();
    }

    bool empty() const {
        return head == nullptr;
    }

    int size() const {
        return sz;
    }

    T& front() {
        return head->data;          // Precondicion: cola no vacia
    }

    const T& front() const {
        return head->data;
    }

    T& back() {
        return tail->data;          // Precondicion: cola no vacia
    }

    const T& back() const {
        return tail->data;
    }

    void enqueue(T value) {
        Node<T>* nuevo = new Node<T>(value);

        if (tail == nullptr) {
            head = tail = nuevo;
        } else {
            tail->next = nuevo;
            tail = nuevo;
        }

        sz++;
    }

    void dequeue() {
        if (empty()) return;

        Node<T>* removed = head;
        head = head->next;

        delete removed;
        sz--;

        if (head == nullptr) {
            tail = nullptr;
        }
    }

    void clear() {
        while (!empty()) {
            dequeue();
        }
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
// NODO DOBLE
// Usado por la cola doble.
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


// ============================================================
// 3. COLA DOBLE (DEQUE)
// Permite insertar y eliminar por ambos extremos.
// ============================================================

template <typename T>
struct Deque {
    DoubleNode<T>* head = nullptr;
    DoubleNode<T>* tail = nullptr;
    int sz = 0;

    ~Deque() {
        clear();
    }

    bool empty() const {
        return head == nullptr;
    }

    int size() const {
        return sz;
    }

    T& front() {
        return head->data;          // Precondicion: deque no vacio
    }

    const T& front() const {
        return head->data;
    }

    T& back() {
        return tail->data;          // Precondicion: deque no vacio
    }

    const T& back() const {
        return tail->data;
    }

    void push_front(T value) {
        DoubleNode<T>* nuevo =
            new DoubleNode<T>(value, head, nullptr);

        if (head == nullptr) {
            head = tail = nuevo;
        } else {
            head->prev = nuevo;
            head = nuevo;
        }

        sz++;
    }

    void push_back(T value) {
        DoubleNode<T>* nuevo =
            new DoubleNode<T>(value, nullptr, tail);

        if (tail == nullptr) {
            head = tail = nuevo;
        } else {
            tail->next = nuevo;
            tail = nuevo;
        }

        sz++;
    }

    void pop_front() {
        if (empty()) return;

        DoubleNode<T>* removed = head;
        head = head->next;

        if (head == nullptr) {
            tail = nullptr;
        } else {
            head->prev = nullptr;
        }

        delete removed;
        sz--;
    }

    void pop_back() {
        if (empty()) return;

        DoubleNode<T>* removed = tail;
        tail = tail->prev;

        if (tail == nullptr) {
            head = nullptr;
        } else {
            tail->next = nullptr;
        }

        delete removed;
        sz--;
    }

    void clear() {
        while (!empty()) {
            pop_front();
        }
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
// PATRONES CON PILAS
// ============================================================

bool matchingPair(char opening, char closing) {
    return (opening == '(' && closing == ')') ||
           (opening == '[' && closing == ']') ||
           (opening == '{' && closing == '}');
}

bool validBrackets(const string& text) {
    Stack<char> pending;

    for (char symbol : text) {
        if (symbol == '(' || symbol == '[' || symbol == '{') {
            pending.push(symbol);
        } else if (symbol == ')' || symbol == ']' || symbol == '}') {
            if (pending.empty()) return false;
            if (!matchingPair(pending.top(), symbol)) return false;
            pending.pop();
        }
    }

    return pending.empty();
}

void nextGreaterRight(const int values[], int n, int answer[]) {
    Stack<int> indexes;

    for (int i = n - 1; i >= 0; i--) {
        while (!indexes.empty() &&
               values[indexes.top()] <= values[i]) {
            indexes.pop();
        }

        answer[i] = indexes.empty()
                    ? -1
                    : values[indexes.top()];

        indexes.push(i);
    }
}


// ============================================================
// PATRON CON COLA DOBLE: MAXIMO DE CADA VENTANA
// answer debe tener espacio para n - windowSize + 1 valores.
// ============================================================

void slidingWindowMaximum(const int values[],
                          int n,
                          int windowSize,
                          int answer[]) {
    if (windowSize <= 0 || windowSize > n) return;

    Deque<int> indexes;
    int answerSize = 0;

    for (int i = 0; i < n; i++) {
        while (!indexes.empty() &&
               indexes.front() <= i - windowSize) {
            indexes.pop_front();
        }

        while (!indexes.empty() &&
               values[indexes.back()] <= values[i]) {
            indexes.pop_back();
        }

        indexes.push_back(i);

        if (i >= windowSize - 1) {
            answer[answerSize] = values[indexes.front()];
            answerSize++;
        }
    }
}

