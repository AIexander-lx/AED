// Permutaciones distintas de una palabra con letras repetidas - CS2023
// Material de estudio de referencia generado con ayuda de IA (Claude).
// Idea: en cada posicion decidir QUE LETRA (no que posicion), usando cnt[x].
// Asi nunca se generan repetidos: "aabc" da 4!/2! = 12 palabras.
#include <bits/stdc++.h>
using namespace std;

int n;
int cnt[26];
string p;

void palabras() {
    if ((int)p.size() == n) {
        cout << p << "\n";
        return;
    }
    for (int x = 0; x < 26; ++x) {               // cada letra distinta, en orden
        if (cnt[x] == 0) continue;
        cnt[x]--;  p.push_back('a' + x);
        palabras();
        p.pop_back();  cnt[x]++;                 // deshacer
    }
}

int main() {
    string w = "aabc";
    n = w.size();
    for (char c : w) cnt[c - 'a']++;
    palabras();                                  // 12 palabras, orden alfabetico
    return 0;
}
