// Parentesis balanceados con poda - CS2023
// Material de estudio de referencia generado con ayuda de IA (Claude).
// Poda: '(' solo si ab < n;  ')' solo si ce < ab.
// Toda hoja es respuesta: la cantidad es el numero de Catalan (1,2,5,14,42...).
#include <bits/stdc++.h>
using namespace std;

int n;

void parentesis(string s, int ab, int ce) {
    if ((int)s.size() == 2 * n) {
        cout << s << "\n";
        return;
    }
    if (ab < n)  parentesis(s + "(", ab + 1, ce);
    if (ce < ab) parentesis(s + ")", ab, ce + 1);
}

int main() {
    n = 3;
    parentesis("", 0, 0);   // ((())) (()()) (())() ()(()) ()()()
    return 0;
}
