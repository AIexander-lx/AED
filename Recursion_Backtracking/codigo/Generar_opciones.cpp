// Generar todas las opciones: subconjuntos, permutaciones, combinaciones - CS2023
// Material de estudio de referencia generado con ayuda de IA (Claude).
#include <bits/stdc++.h>
using namespace std;

int n, k;
int a[20];
bool tomado[20];
int elegido[20];

// SUBCONJUNTOS: en cada posicion i decido "lo tomo / no lo tomo".  2^n hojas.
void subconjuntos(int i, int cnt) {
    if (i == n) {
        cout << "{ ";
        for (int j = 0; j < cnt; ++j) cout << elegido[j] << " ";
        cout << "}\n";
        return;
    }
    elegido[cnt] = a[i];
    subconjuntos(i + 1, cnt + 1);                // lo tomo
    subconjuntos(i + 1, cnt);                    // no lo tomo
}

// PERMUTACIONES: en la posicion pos pruebo cada elemento no usado.  n! hojas.
void permutaciones(int pos) {
    if (pos == n) {
        for (int j = 0; j < n; ++j) cout << elegido[j] << " ";
        cout << "\n";
        return;
    }
    for (int i = 0; i < n; ++i) {
        if (tomado[i]) continue;
        tomado[i] = true;  elegido[pos] = a[i];
        permutaciones(pos + 1);
        tomado[i] = false;                       // deshacer (backtrack)
    }
}

// COMBINACIONES de k elementos de {1..n}, en orden creciente.  C(n,k) hojas.
// Poda: si los numeros que quedan (n - x + 1) no alcanzan para completar
// los que faltan (k - cnt), esa rama no puede dar solucion.
void combinaciones(int x, int cnt) {
    if (cnt == k) {
        for (int j = 0; j < k; ++j) cout << elegido[j];
        cout << "\n";
        return;
    }
    if (n - x + 1 < k - cnt) return;             // PODA
    elegido[cnt] = x;
    combinaciones(x + 1, cnt + 1);               // tomo x
    combinaciones(x + 1, cnt);                   // no tomo x
}

int main() {
    n = 3; a[0] = 1; a[1] = 2; a[2] = 3;
    cout << "Subconjuntos:\n";   subconjuntos(0, 0);    // 8
    cout << "Permutaciones:\n";  permutaciones(0);      // 6
    n = 4; k = 2;
    cout << "Combinaciones C(4,2):\n"; combinaciones(1, 0); // 12 13 14 23 24 34
    return 0;
}
