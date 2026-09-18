# Formulario de hash (C++)

`FORMULARIO_HASH.cpp` conserva la estructura `my_map<key_type, value_type>` del código `B.cpp` usado en clase. Usa buckets de `vector<vector<pair<key_type, value_type>>>`; **no** usa `map` ni `unordered_map`. Los archivos originales del profesor no fueron modificados.

## Operaciones

| Expresión | Efecto |
| --- | --- |
| `my_map<int, int> h(2*n);` | Crea una tabla para claves y valores `int`, con `2*n` buckets (si `n` puede ser 0, usa al menos 1). |
| `h[clave]` | Devuelve el valor; si no existe, crea la clave con valor inicial `0` para `int`. |
| `h.has_key(clave)` | Comprueba existencia sin insertar. |
| `h.erase(clave)` | Elimina la clave si existe; no devuelve valor. |
| `h.size()` | Cantidad de claves; `h.size() == 0` indica que está vacía. |

Las operaciones cuestan `O(1 + longitud del bucket)`; pueden ser `O(1)` **esperado** si las claves se distribuyen bien y `m` es proporcional a `n`. En el peor caso cuestan `O(n)`. El espacio es `O(n + m)`. **Este código no hace rehash**: el tamaño `m` se decide al construir la tabla. Además, la función `_hash` del profesor manda las claves negativas y el cero al mismo bucket; las operaciones siguen dando el resultado correcto, pero pueden ralentizarse.

Con `-Wall -Wextra`, MinGW avisa que en `my_map` se compara `int at` con `vector::size()` (un tipo sin signo). Es un aviso del código base del profesor, no un error de compilación; se dejó tal cual para estudiar su versión.

## Cómo practicar

1. Compila `FORMULARIO_HASH.cpp`: su `main` cuenta cuántos valores distintos hay, como en `B.cpp`.
2. Compila y ejecuta `PRACTICA_HASH.cpp`: verifica inserción, actualización, búsqueda, eliminación y claves negativas.
3. Para un problema nuevo, copia la estructura `my_map` y reemplaza el `main` por la lógica del problema. No copies el `main` de frecuencia si el problema pide otra cosa.

## Patrones listos para adaptar

Debajo de `my_map` hay funciones **opcionales**, separadas del código del profesor:

| Si el problema pide... | Función de ejemplo | Idea que debes entender |
| --- | --- | --- |
| Frecuencias | `contar_frecuencias` y `frecuencia_de` | `++h[x]`; para consultar sin insertar, primero `has_key(x)`. |
| Cantidad de distintos | `contar_distintos` | Cada clave se inserta una sola vez; la respuesta es `size()`. |
| Un par que sume `T` | `existe_par_suma` | Buscar `T-x` antes de insertar `x`. |
| Dos multiconjuntos iguales | `mismos_multiconjunto` | Sumar frecuencias de uno y restar las del otro. |
| Primer elemento único | `primer_no_repetido` | Contar y luego recorrer otra vez en orden original. |

Estas funciones muestran **patrones de razonamiento**, no sustituyen leer las restricciones de cada enunciado. Por ejemplo, si las claves son `string`, el `_hash` actual del profesor no sirve sin adaptarlo.

Comandos con MinGW:

```powershell
g++ -std=c++17 -Wall -Wextra FORMULARIO_HASH.cpp -o formulario_hash.exe
g++ -std=c++17 -Wall -Wextra PRACTICA_HASH.cpp -o practica_hash.exe
.\practica_hash.exe
```

## Ejercicios de práctica

1. Contar cuántos números **distintos** aparecen: usa `size()` al terminar de leer (ejemplo del formulario).
2. Contar cuántas veces aparece cada número y responder consultas.
3. Detectar si existe un par de posiciones distintas cuya suma sea `T`: antes de insertar `x`, consulta si ya existe `T-x`.

Si el enunciado exige **listas enlazadas por bucket**, esta versión con vectores no cumple esa restricción y habría que adaptar la estructura. Confirma también las reglas del examen sobre código propio y acceso a GitHub.
