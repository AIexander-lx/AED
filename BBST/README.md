# BBST — Árboles Binarios de Búsqueda Balanceados (CS2023)

> Resumen de estudio basado en las clases de la Semana 9. Material de referencia elaborado con ayuda de IA (Claude).

## Archivos

| Carpeta / archivo | Contenido |
|---|---|
| `teoria/00_BST_base.pdf` | BST: buscar, insertar, sucesor, eliminar |
| `teoria/01_BBST_Teoria_AVL_RedBlack.pdf` | Por qué balancear, rotaciones, AVL, Red-Black |
| `teoria/02_Implementacion_AVL.pdf` | AVL recursivo |
| `teoria/03_Implementacion_Red_Black.pdf` | Red-Black con padre y `T.nil` |
| `codigo/BST_completo.cpp` | BST con padre: insert, search, sucesor, predecesor, transplant, erase |
| `codigo/AVL_completo.cpp` | AVL recursivo completo (insert + erase + rebalance) |
| `codigo/RedBlack.cpp` | Red-Black completo (insert/erase con sus fixups) |
| `codigo/AVL.cpp`, `rotaciones_a_mano.cpp`, `es_un_avl.cpp`, `alturas_en_un_avl.cpp` | Código de clase y problemas |

---

## 1. ¿Por qué balancear?

- En un BST todo cuesta **O(h)**. Si insertas 1, 2, …, n en orden, el árbol es una cadena: **h = n − 1**, así que todo cuesta O(n).
- Exigir que el árbol sea **completo** no funciona: mantenerlo así cuesta **Θ(n)** por inserción.
- Se busca una condición más débil que garantice **h = O(lg n)** y que se pueda restaurar en **O(lg n)**.

## 2. Rotaciones

```
        y                         x
       / \    rotar der. en y    / \
      x   C   ────────────────►  A   y
     / \      ◄────────────────     / \
    A   B     rotar izq. en x      B   C
```

- El **inorder no cambia** (A x B y C), así que la propiedad BST se conserva.
- Cambian 3 punteros: **O(1)**.
- A sube un nivel, C baja uno y B cambia de padre: la rotación **pasa altura de un lado al otro**.

## 3. AVL

- **h(nulo) = −1**, **FB(v) = h(izq) − h(der)**.
- Un árbol es AVL si **|FB(v)| ≤ 1 en todo nodo**.
- **Altura:** el AVL mínimo de altura h tiene N(h) = N(h−1) + N(h−2) + 1 nodos (crece como Fibonacci), así que **h ≤ ~1.44 lg n = O(lg n)**.
- Cada nodo **guarda su altura**, así `h`, `Actualizar` y `FB` cuestan O(1). Hay que llamar a `Actualizar(v)` **cada vez que cambia un hijo de v** y, en una rotación, **primero al nodo que baja**.
- Implementación **recursiva y sin padre**: cada función recibe la raíz de un subárbol y **devuelve la nueva raíz** (`v.izq ← Insertar(v.izq, k)`).

### Casos de rebalanceo

| Nodo | Hijo del lado pesado | Caso | Arreglo |
|---|---|---|---|
| FB = +2 | FB(izq) ≥ 0 | **LL** | rotar der. en el nodo |
| FB = +2 | FB(izq) < 0 | **LR** | rotar izq. en el hijo, luego der. en el nodo |
| FB = −2 | FB(der) ≤ 0 | **RR** | rotar izq. en el nodo |
| FB = −2 | FB(der) > 0 | **RL** | rotar der. en el hijo, luego izq. en el nodo |

**Regla:** si el desbalance va en línea recta, basta **1 rotación**. Si va en zigzag, se endereza primero: **2 rotaciones**.

- **Insertar:** como en el BST, y se rebalancea al volver de la recursión. Con **una** rotación (simple o doble) basta.
- **Eliminar:** como en el BST (0, 1 o 2 hijos; con 2 hijos se usa el sucesor) y se rebalancea al volver. Puede rotar en **todos los niveles: O(lg n) rotaciones**.

## 4. Red-Black

### Propiedades
1. Cada nodo es **rojo o negro**.
2. La **raíz es negra**.
3. Las hojas **NIL son negras** (centinela `T.nil`).
4. Un nodo **rojo tiene hijos negros**: no hay dos rojos seguidos.
5. Todo camino de un nodo a sus NIL tiene **la misma cantidad de negros** (altura negra, `bh`).

**Altura:** por la propiedad 4, h ≤ 2·bh, y un subárbol tiene al menos 2^bh − 1 nodos. De ahí sale **h ≤ 2 lg(n+1)**.

**Centinela `T.nil`:** es un único nodo negro que reemplaza a todos los nulos y al padre de la raíz. Así, preguntar el color del tío o del hermano **siempre funciona**.

**¿Por qué se implementa con padre?** Sus arreglos miran **hacia arriba** (tío, abuelo, hermano) y se resuelven subiendo en un ciclo. Los del AVL miran **hacia abajo** (hijos), por eso el AVL se hace recursivo y sin padre.

### Insertar: el nodo entra ROJO (no altera la altura negra) y se mira al **tío** t

| Caso | Cuándo | Qué se hace |
|---|---|---|
| 1 | t **rojo** | padre y tío negros, abuelo rojo; **z ← abuelo** (el problema sube 2 niveles) |
| 2 | t negro, z en **zigzag** | rotar en el padre; se convierte en el caso 3 |
| 3 | t negro, z **en línea** | padre negro, abuelo rojo, rotar en el abuelo: **fin** |

Al final, `raíz.color ← negro`. Costo: **O(lg n)**, con **como máximo 2 rotaciones**.

### Eliminar: si el nodo quitado era **negro**, x carga un **negro extra**; se mira al **hermano** w

| Caso | Cuándo | Qué se hace |
|---|---|---|
| 1 | w **rojo** | w negro, padre rojo, rotar en el padre: queda un hermano negro (pasa a 2, 3 o 4) |
| 2 | w negro, **dos hijos negros** | w rojo, **x ← padre** (el negro extra sube) |
| 3 | w negro, hijo cercano rojo y lejano negro | recolorear y rotar en w: pasa al caso 4 |
| 4 | w negro, **hijo lejano rojo** | w toma el color del padre, padre y el hijo lejano negros, rotar en el padre: **fin** |

Si el nodo eliminado era **rojo**, no se rompe nada. Costo: **O(lg n)**, con **como máximo 3 rotaciones**.

## 5. AVL vs Red-Black

| | AVL | Red-Black |
|---|---|---|
| Condición | \|FB\| ≤ 1 | 5 propiedades de color |
| Altura | ≤ ~1.44 lg n | ≤ 2 lg(n+1) |
| Búsqueda | algo más rápida (más bajo) | algo más lenta |
| Rotaciones al insertar | ≤ 2 (una simple o una doble) | ≤ 2 |
| Rotaciones al eliminar | **O(lg n)** | **≤ 3** |
| Implementación | recursiva, sin padre | iterativa, con padre y `T.nil` |
| Buscar / insertar / eliminar | O(lg n) | O(lg n) |

## 6. Ejemplos para verificar

- **AVL**, insertar 10, 20, 30, 25, 28, 27 → preorden `25(2) 20(1) 10(0) 28(1) 27(0) 30(0)`:
  - 30: **RR** en 10
  - 28: **LR** en 30
  - 27: **RL** en 20
- **Red-Black**, insertar 41, 38, 31, 12, 19, 8 → `38B 19R 12B 8R 31B 41B`:
  - 31: caso 3
  - 12: caso 1
  - 19: casos 2 y 3
  - 8: caso 1

## 7. Errores típicos en el examen

- Olvidar que **h(nulo) = −1**, de modo que una hoja tiene altura 0.
- No actualizar alturas después de rotar, o actualizarlas en el orden incorrecto.
- Confundir LR con RL: mira **el signo del FB del hijo**.
- En Red-Black, olvidar **pintar la raíz de negro** al final.
- Dar la complejidad sin justificarla. El profe exige justificación en todas las respuestas.
