#include <bits/stdc++.h>
using namespace std;

// Copia de estudio del my_map usado en B.cpp por el profesor.
// Los archivos originales del profesor no se modificaron.
template<typename key_type, typename value_type>
struct my_map {
    int m;
    int _size;
    vector<vector<pair<key_type, value_type>>> chains;

    my_map(int m = 1) : m(m), _size(0) {
        chains.resize(m);
    }

    value_type& operator [] (const key_type &key) {
        int chain_position = _hash(key);
        int at = 0;
        while (at < chains[chain_position].size() and chains[chain_position][at].first != key) {
            ++at;
        }
        if (at == chains[chain_position].size()) {
            chains[chain_position].emplace_back(key, value_type());
            ++_size;
        }
        return chains[chain_position][at].second;
    }

    void erase(const key_type &key) {
        int chain_position = _hash(key);
        int at = 0;
        while (at < chains[chain_position].size() and chains[chain_position][at].first != key) {
            ++at;
        }
        if (at != chains[chain_position].size()) {
            if (at + 1 < chains[chain_position].size()) {
                swap(chains[chain_position][at], chains[chain_position].back());
            }
            chains[chain_position].pop_back();
            --_size;
        }
    }

    bool has_key (const key_type &key) const {
        int chain_position = _hash(key);
        int at = 0;
        while (at < chains[chain_position].size() and chains[chain_position][at].first != key) {
            ++at;
        }
        if (at == chains[chain_position].size()) {
            return false;
        }
        return true;
    }

    int _hash(key_type key) const {
        // Para enteros: misma funcion usada en el codigo de clase.
        const int B = 311;
        const int MOD = 1e9 + 7;
        int hash_value = 0;
        while (key > 0) {
            int d = key % 10;
            hash_value = (1ll * hash_value * B + (d + 1)) % MOD;
            key /= 10;
        }
        return hash_value % m;
    }

    int size() const {
        return _size;
    }

    void print() {
        for (int i = 0; i < m; ++i) {
            cout << "Bucket " << i << ": " << endl;
            for (auto &e : chains[i]) {
                cout << e.first << " --> " << e.second << endl;
            }
            cout << "End bucket" << endl;
        }
    }
};

// ===== PATRONES OPCIONALES =====
// Estas funciones usan my_map sin cambiar la implementacion del profesor.
// En un examen, copia solo las que necesites y adapta la entrada/salida.

my_map<int, int> contar_frecuencias(const vector<int>& a) {
    my_map<int, int> frecuencia(max(1, 2 * static_cast<int>(a.size())));
    for (int x : a) ++frecuencia[x];
    return frecuencia;
}

int frecuencia_de(my_map<int, int>& frecuencia, int x) {
    // Consultar con [] directamente insertaria x si no existe.
    return frecuencia.has_key(x) ? frecuencia[x] : 0;
}

int contar_distintos(const vector<int>& a) {
    my_map<int, int> frecuencia = contar_frecuencias(a);
    return frecuencia.size();
}

bool existe_par_suma(const vector<int>& a, int objetivo) {
    my_map<int, int> vistos(max(1, 2 * static_cast<int>(a.size())));
    for (int x : a) {
        long long complemento = 1LL * objetivo - x;
        if (complemento >= INT_MIN && complemento <= INT_MAX &&
            vistos.has_key(static_cast<int>(complemento))) {
            return true;
        }
        vistos[x] = 1; // consultar antes de insertar evita usar el mismo elemento
    }
    return false;
}

bool mismos_multiconjunto(const vector<int>& a, const vector<int>& b) {
    if (a.size() != b.size()) return false;
    my_map<int, int> frecuencia = contar_frecuencias(a);
    for (int x : b) {
        if (!frecuencia.has_key(x)) return false;
        --frecuencia[x];
        if (frecuencia[x] == 0) frecuencia.erase(x);
    }
    return frecuencia.size() == 0;
}

bool primer_no_repetido(const vector<int>& a, int& resultado) {
    my_map<int, int> frecuencia = contar_frecuencias(a);
    for (int x : a) {
        if (frecuencia[x] == 1) {
            resultado = x;
            return true;
        }
    }
    return false;
}

#ifndef HASH_FORMULARIO_NO_MAIN
int main() {
    // Ejemplo de B.cpp: cantidad de valores distintos.
    int n;
    cin >> n;
    my_map<int, int> frecuencias(2 * n);
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        ++frecuencias[x];
    }
    cout << frecuencias.size() << '\n';
    return 0;
}
#endif
