// Recursion basica: Potencia, Suma, Digitos, Hanoi - CS2023
// Material de estudio de referencia generado con ayuda de IA (Claude).
#include <bits/stdc++.h>
using namespace std;

// Predicado: Potencia(a, n) = a^n, con n >= 0.   O(lg n)
long long potencia(long long a, int n) {
    if (n == 0) return 1;                        // caso base
    long long h = potencia(a, n / 2);            // confiar en el predicado
    if (n % 2 == 0) return h * h;
    return h * h * a;
}

// Predicado: suma(A, i, n) = A[i] + ... + A[n-1].   O(n) tiempo, O(n) pila
int suma(int A[], int i, int n) {
    if (i == n) return 0;                        // no queda nada
    return A[i] + suma(A, i + 1, n);
}

// Predicado: digitos(n) = cantidad de digitos de n.   O(log10 n)
int digitos(long long n) {
    if (n < 10) return 1;
    return 1 + digitos(n / 10);
}

// Predicado (fortalecido): mover n discos de 'origen' a 'destino'.
// T(n) = 2T(n-1) + 1 = 2^n - 1 movimientos (y es el minimo).
void hanoi(int n, char origen, char destino, char apoyo) {
    if (n == 0) return;
    hanoi(n - 1, origen, apoyo, destino);        // n-1 discos al apoyo
    cout << "disco " << n << ": " << origen << " -> " << destino << "\n";
    hanoi(n - 1, apoyo, destino, origen);        // n-1 discos encima
}

int main() {
    cout << potencia(3, 13) << "\n";             // 1594323
    int A[] = {5, 2, 7};
    cout << suma(A, 0, 3) << "\n";               // 14
    cout << digitos(482) << "\n";                // 3
    hanoi(3, 'A', 'C', 'B');                     // 7 movimientos
    return 0;
}
