// Evaluar una expresion en notacion prefija - CS2023
// Material de estudio de referencia generado con ayuda de IA (Claude).
// Una expresion es un numero, o un operador seguido de dos expresiones.
// Evaluar(i) devuelve DOS cosas: el valor y la posicion donde termino.  O(n)
#include <bits/stdc++.h>
using namespace std;

vector<string> t;

pair<long long, int> evaluar(int i) {
    string s = t[i];
    if (s != "+" && s != "-" && s != "*" && s != "/")
        return {stoll(s), i + 1};                // caso base: un numero
    auto [x, j] = evaluar(i + 1);                // primer operando
    auto [y, k] = evaluar(j);                    // segundo operando (empieza en j)
    if (s == "+") return {x + y, k};
    if (s == "-") return {x - y, k};
    if (s == "*") return {x * y, k};
    return {x / y, k};
}

int main() {
    t = {"*", "+", "2", "3", "-", "7", "4"};     // (2 + 3) * (7 - 4)
    cout << evaluar(0).first << "\n";            // 15
    return 0;
}
