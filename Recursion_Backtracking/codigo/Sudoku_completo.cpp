// Sudoku 9x9 con backtracking - CS2023
// Material de estudio de referencia generado con ayuda de IA (Claude).
// Entrada: 9 lineas de 9 caracteres, '.' = casilla vacia.
// Tres tablas de booleanos hacen cada verificacion en O(1).
#include <bits/stdc++.h>
using namespace std;

const int N = 9;
string s[N];
bool fila[N][N + 1], col[N][N + 1], bloque[N][N + 1];
int vr[81], vc[81], vacias = 0;                  // lista de casillas vacias

int idBloque(int r, int c) { return (r / 3) * 3 + c / 3; }

void marcar(int r, int c, int v, bool val) {
    fila[r][v] = col[c][v] = bloque[idBloque(r, c)][v] = val;
}

// Predicado: Sudoku(k) llena las casillas vacias k, k+1, ...; true si lo logra
bool sudoku(int k) {
    if (k == vacias) return true;                // todo lleno
    int r = vr[k], c = vc[k], b = idBloque(r, c);
    for (int v = 1; v <= 9; ++v) {
        if (fila[r][v] || col[c][v] || bloque[b][v]) continue;   // PODA
        s[r][c] = '0' + v;  marcar(r, c, v, true);
        if (sudoku(k + 1)) return true;          // se detiene en la 1ra solucion
        s[r][c] = '.';      marcar(r, c, v, false);              // retroceder
    }
    return false;
}

int main() {
    for (int i = 0; i < N; ++i) cin >> s[i];
    for (int r = 0; r < N; ++r)
        for (int c = 0; c < N; ++c) {
            if (s[r][c] == '.') { vr[vacias] = r; vc[vacias] = c; vacias++; }
            else marcar(r, c, s[r][c] - '0', true);
        }
    if (sudoku(0)) for (int i = 0; i < N; ++i) cout << s[i] << "\n";
    else cout << "Sin solucion\n";
    return 0;
}
