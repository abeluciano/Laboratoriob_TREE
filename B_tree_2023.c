#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct bt_Nodo *b_Tree;

#define MAX_LLAVES (3)

struct bt_Nodo {
    int esHoja;
    int numLLaves;    //////// ¿Cuántas llaves contiene este nodo? */
    int LLaves[MAX_LLAVES];
    struct bt_Nodo *hijos[MAX_LLAVES+1];  //////// Ramificación
};

//////// Crear un árbol vacio */
b_Tree btree_Crear(void);

//////// liberar espacio */
void btree_Liberar(b_Tree b);

//////// funcion que devuelve un valor distinto de cero si la llave está presente en el árbol */
int btree_Buscar(b_Tree b, int key);

//////// insertar un nuevo elemento en el árbol */
void btree_Insertar(b_Tree b, int key);

//////// imprimir todas las claves del árbol en orden */
void btree_Print(b_Tree b);






b_Tree btree_Crear(void) {
    b_Tree b;
    b = malloc(sizeof(*b));
    assert(b);

    b->esHoja = 1;
    b->numLLaves = 0;

    return b;
}

void btree_Liberar(b_Tree b) {
    int i;

    if(!b->esHoja) {
        for(i = 0; i < b->numLLaves + 1; i++) {
            btree_Liberar(b->hijos[i]);
        }
    }

    free(b);
}

//////// devuelve el índice más pequeño "i" en una matriz ordenada de modo que la llave <= a[i] */
//////// (o n si no existe ese indice) */
static int btree_BuscarLLave(int n, const int *a, int llave) {
    int inf;
    int sup;
    int med;


    inf = -1;
    sup = n;

    while(inf + 1 < sup) {
        med = (inf+sup)/2;
        if(a[med] == llave) {
            return med;
        } else if(a[med] < llave) {
            inf = med;
        } else {
            sup = med;
        }
    }
    return sup;
}

int btree_Buscar(b_Tree b, int llave) {
    int pos;

    /* es vacio? */
    if(b->numLLaves == 0) {
        return 0;
    }

    /* busque la posición más cercana a la llave  */
    pos = btree_BuscarLLave(b->numLLaves, b->LLaves, llave);

    if(pos < b->numLLaves && b->LLaves[pos] == llave) {
        return 1;
    } else {
        return(!b->esHoja && btree_Buscar(b->hijos[pos], llave));
    }
}



void btree_Insertar(b_Tree b, int llave) {
    int pos;
    pos = btree_BuscarLLave(b->numLLaves, b->LLaves, llave); //busco el lugar para insertar
    if(pos < b->numLLaves && b->LLaves[pos] == llave) {//mira si la llave ya existe
        return;
    }

    if(b->esHoja) {//insertar una llave en una hoja
        for(int i = b->numLLaves; i > pos; i--) {
            b->LLaves[i] = b->LLaves[i-1];
        }
        b->LLaves[pos] = llave;
        b->numLLaves++;
    }else{
        if(b->hijos[pos]->numLLaves == MAX_LLAVES) {
            b_tree nuevo_hijo;
            nuevo_hijo = malloc(sizeof(*nuevo_hijo));
            assert(nuevo_hijo);

            nuevo_hijo->esHoja = 0;
            nuevo_hijo->numLLaves = 0;
            nuevo_hijo->hijos[0] = b->hijos[pos];

            b->hijos[pos] = nuevo_hijo;
            b->numLLaves++;
            btree_Insertar(nuevo_hijo, b->LLaves[pos]);
            pos = btree_BuscarLLave(b->numLLaves, b->LLaves, llave);
        }
        btree_Insertar(b->hijos[pos], llave);
    }
}

void btree_Print(b_Tree b) {
    int i;
    if(b->esHoja) {
        for(i = 0; i < b->numLLaves;i++) {
            printf("%d", b->LLaves[i]);
        }
    } else {
        for(i = 0; i < b->numLLaves; i++) {
            btree_Print(b->hijos[i]);
            printf("%d", b->LLaves[i]);
        }
        btree_Print(b->hijos[i]);
    }
}


int main(){
////// pruebe su código
     btree_Crear();
    return 0;
}