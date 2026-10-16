# Recursión y Backtracking (CS2023)

> Resumen de estudio basado en las clases de la Semana 10. Material de referencia elaborado con ayuda de IA (Claude).

## Archivos

| Carpeta / archivo | Contenido |
|---|---|
| `teoria/01_Recursion_y_Backtracking.pdf` | Receta, pila de llamadas, árbol de recursión, subconjuntos y permutaciones |
| `teoria/02_Problemas_Recursion_Backtracking.pdf` | Hanói, prefija, paréntesis, palabras con repetidas, Sudoku |
| `codigo/Recursion_basica.cpp` | Potencia, Suma, Dígitos, Hanói |
| `codigo/Generar_opciones.cpp` | Subconjuntos, permutaciones, combinaciones con poda |
| `codigo/Prefija.cpp` | Evaluar notación prefija (devuelve valor y posición) |
| `codigo/Parentesis.cpp` | Paréntesis balanceados con poda |
| `codigo/Permutaciones_repetidas.cpp` | Palabras distintas con letras repetidas |
| `codigo/Sudoku_completo.cpp` | Sudoku 9×9 con backtracking |
| `codigo/Hanoi.cpp`, `PagoExacto.cpp`, `Sudoku.cpp` | Código de clase (`Sudoku.cpp` está incompleto) |

---

## 1. La receta recursiva

1. **Predicado:** qué calcula la función, **en palabras**, y de qué argumentos depende.
   Ejemplo: `Suma(A, i)` = "A[i] + … + A[n−1]".
2. **Casos base:** valores de los argumentos que se resuelven **sin llamarse a sí misma**.
   Ejemplo: `i = n → 0`.
3. **Paso recursivo:** armar la respuesta **confiando en el predicado** para las llamadas más chicas.
   Ejemplo: `A[i] + Suma(A, i+1)`.

- Las llamadas tienen que **acercarse al caso base**.
- Si el paso recursivo no sale, **fortalece el predicado**. Ejemplo: en Hanói, "mover de A a C" pasa a ser "mover de cualquier varilla a cualquier otra".

## 2. La pila de llamadas

- Cada llamada tiene su **marco**: su copia de los argumentos y el punto donde debe continuar.
- Es una **pila (LIFO)**: la última llamada que entra es la primera que termina.
- Al bajar, se **apilan** las llamadas; al volver, se **desapilan** y cada una devuelve su valor.
- **Memoria:** la profundidad máxima de la pila. Por ejemplo, `Suma` usa O(n) de pila.
- **Stack overflow:** ocurre si **falta el caso base** o si **las llamadas no se acercan a él**. La pila tiene unos pocos MB.

```
Potencia(3,13)
  → Potencia(3,6)
    → Potencia(3,3)
      → Potencia(3,1)
        → Potencia(3,0) = 1
Al volver: 3 → 27 → 729 → 1 594 323
```

## 3. Costo con el árbol de recursión

Hay que contar **cuántas llamadas hace cada una** y **cuántos niveles hay**:

| Función | Llamadas por nivel | Niveles | Recurrencia | Costo |
|---|---|---|---|---|
| Suma(A, i) | 1 | n | T(n) = T(n−1) + 1 | **O(n)** |
| Potencia(a, n) | 1, y n se divide entre 2 | lg n | T(n) = T(n/2) + 1 | **O(lg n)** |
| Dígitos(n) | 1, y n se divide entre 10 | log₁₀ n | T(n) = T(n/10) + 1 | **O(log n)** |
| Hanói(n) | 2 | n | T(n) = 2T(n−1) + 1 | **2ⁿ − 1** |
| f con 3 llamadas a f(n−1) | 3 | n | T(n) = 3T(n−1) + 1 | **O(3ⁿ)** |

**Hanói:** T(0) = 0, T(n) = 2T(n−1) + 1, así que **T(n) = 2ⁿ − 1** (1, 3, 7, 15, …).
**Es el mínimo:** el disco n se mueve al menos una vez, y para eso los otros n − 1 deben estar juntos en la tercera varilla y después volver encima. Eso da al menos T(n−1) + 1 + T(n−1).

**Cuidado:** 1 + 2 + 4 + … + 2ⁿ⁻¹ = **2ⁿ − 1**, no 2ⁿ.

## 4. Generar todas las opciones

| Qué | Decisión en cada paso | Cantidad |
|---|---|---|
| Subconjuntos | tomo / no tomo | **2ⁿ** |
| Permutaciones | qué elemento no usado va en esta posición | **n!** |
| Combinaciones (k de n) | tomo / no tomo, hasta completar k | **C(n,k) = n! / (k!(n−k)!)** |
| Cadenas de largo n con m letras | qué letra va aquí | **mⁿ** |

**Patrón de backtracking:** *elegir → llamar → deshacer.*

```
para cada opción válida:
    aplicar opción         // marcar
    Recursión(siguiente)
    deshacer opción        // desmarcar (backtrack)
```

## 5. Backtracking y poda

- **Backtracking:** se construye la solución paso a paso y **se retrocede apenas se sabe que no se puede completar**.
- **Poda:** una regla que corta ramas que **no pueden llegar a una solución**.
- Una poda es **válida** si nunca corta una rama que tenía solución.

**Cómo justificar una poda (3 pasos):**
1. **Situación:** qué ya se rompió en esta rama.
2. **Dato clave:** por qué agregar más elementos no lo arregla.
3. **Conclusión:** ninguna solución pasa por esa rama, así que cortarla no pierde respuestas.

Ejemplo, PagoExacto: *"Si s < 0, ya se pagó más de S. Como las monedas son positivas, agregar más solo disminuye s, así que nunca volverá a 0. Ninguna solución pasa por esa rama."*

## 6. Problemas de clase

| Problema | Idea | Poda / detalle | Costo |
|---|---|---|---|
| **Notación prefija** `* + 2 3 - 7 4` = 15 | Una expresión es un número o un operador seguido de dos expresiones | La función devuelve **(valor, posición siguiente)** | **O(n)**: cada símbolo se lee una vez |
| **Paréntesis balanceados** | Contadores `ab` (abiertos) y `ce` (cerrados) | `(` si ab < n; `)` si ce < ab. **Toda hoja es respuesta** | Proporcional a la salida. Cantidad: **Catalan** 1, 2, 5, 14, 42… (~4ⁿ), contra 2²ⁿ sin poda |
| **Palabras con letras repetidas** (`aabc` → 4!/2! = **12**) | Decidir **qué letra**, no qué posición, con `cnt[x]` | Cada letra distinta se prueba una sola vez por posición, así que **no hay repetidos** | Proporcional a la salida |
| **Sudoku** | Llenar casillas vacías en orden y probar valores 1–9 | Tablas `fila[r][v]`, `col[c][v]`, `bloque[b][v]` en **O(1)**. Se detiene en la 1ra solución | Exponencial en el peor caso, pero la poda corta casi todo |

**Mejora del Sudoku:** llenar primero la casilla **con menos opciones**. Si tiene 1, no genera ramas; si tiene 0, se retrocede de inmediato.

## 7. Errores típicos en el examen

- Predicado demasiado largo: debe decir **solo qué calcula**, no cómo lo hace.
- Caso base dicho como "empieza en 0": debe ser **un valor del argumento** (`si i = n`).
- Paso recursivo al revés: lo grande va a la izquierda y la llamada chica a la derecha.
- Confundir costos: 1 llamada que resta → O(n); 1 llamada que divide → O(log n); 2 llamadas → O(2ⁿ).
- Olvidar el **deshacer** en el backtracking.
- Justificar una poda solo con el dato clave, sin decir que **ninguna solución pasa por esa rama**.
