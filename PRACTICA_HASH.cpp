#define HASH_FORMULARIO_NO_MAIN
#include "FORMULARIO_HASH.cpp"
#include <cassert>

int main() {
    my_map<int, int> h(2008); // el formulario del profesor pide m al construir

    assert(h.size() == 0);
    assert(!h.has_key(-7));
    h[-7] = 10;
    h[0] = 20;
    h[7] = 30;
    h[INT_MIN] = 40;
    assert(h.size() == 4);
    assert(h[-7] == 10 && h[0] == 20);
    assert(h[7] == 30 && h[INT_MIN] == 40);

    h[-7] += 5;
    assert(h[-7] == 15);
    assert(h.size() == 4); // actualizar no agrega otra clave

    h.erase(7);
    assert(!h.has_key(7));
    h.erase(7); // eliminar una clave ausente no cambia el size
    assert(h.size() == 3);

    for (int i = 1; i <= 1000; ++i) h[i] = i * 2;
    for (int i = 1; i <= 1000; ++i) assert(h[i] == i * 2);
    assert(h.size() == 1003);

    vector<int> a = {4, -2, 4, 7, -2, 4};
    my_map<int, int> frecuencia = contar_frecuencias(a);
    assert(frecuencia_de(frecuencia, 4) == 3);
    assert(frecuencia_de(frecuencia, 99) == 0);
    assert(frecuencia.size() == 3); // consultar 99 no debe insertarlo
    assert(contar_distintos(a) == 3);
    assert(contar_distintos({}) == 0);

    assert(existe_par_suma({2, 7, 11}, 9));
    assert(!existe_par_suma({5}, 10)); // un solo 5 no forma un par
    assert(existe_par_suma({5, 5}, 10));
    assert(existe_par_suma({INT_MIN, INT_MAX}, -1));
    assert(!existe_par_suma({INT_MIN, 0}, INT_MAX));

    assert(mismos_multiconjunto({1, 2, 1}, {2, 1, 1}));
    assert(!mismos_multiconjunto({1, 1, 2}, {1, 2, 2}));
    assert(mismos_multiconjunto({}, {}));

    int primero = 0;
    assert(primer_no_repetido({4, 4, -1, 7, 7}, primero) && primero == -1);
    assert(!primer_no_repetido({4, 4}, primero));

    cout << "Pruebas de hash superadas\n";
    return 0;
}
