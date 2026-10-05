#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// Estructura para representar un nodo en la lista de adyacencia
typedef struct NodoLista {
    int destino;
    int peso;
    struct NodoLista* siguiente;
} NodoLista;
// Estructura para representar un Grafo con Lista de Adyacencia
typedef struct {
    int numVertices;
    bool esDirigido;
    NodoLista** listas; // Array de punteros a nodos (las cabeceras de cada lista)
} GrafoLista;
// Función para crear e inicializar el grafo con Lista de Adyacencia
GrafoLista* crearGrafoLista(int vertices, bool esDirigido) {
    GrafoLista* grafo = (GrafoLista*)malloc(sizeof(GrafoLista));
    grafo->numVertices = vertices;
    grafo->esDirigido = esDirigido;
    // Asignación dinámica de memoria para el arreglo de listas (cabeceras)
    grafo->listas = (NodoLista**)malloc(vertices * sizeof(NodoLista*));
    for (int i = 0; i < vertices; i++) {
        // Inicializamos cada lista como vacía (puntero NULL)
        grafo->listas[i] = NULL;
    }
    return grafo;
}
// Función auxiliar para crear un nuevo nodo de la lista
NodoLista* crearNodo(int destino, int peso) {
    NodoLista* nuevoNodo = (NodoLista*)malloc(sizeof(NodoLista));
    nuevoNodo->destino = destino;
    nuevoNodo->peso = peso;
    nuevoNodo->siguiente = NULL;
    return nuevoNodo;
}
// Función para agregar una arista al grafo (insertando al inicio de la lista)
void agregarAristaLista(GrafoLista* grafo, int origen, int destino, int peso) {
    if (origen >= 0 && origen < grafo->numVertices && destino >= 0 && destino < grafo->numVertices) {
        // Insertamos el nodo al principio de la lista del vértice 'origen'
        NodoLista* nuevo = crearNodo(destino, peso);
        nuevo->siguiente = grafo->listas[origen];
        grafo->listas[origen] = nuevo;
        // Simetría para grafos no dirigidos
        if (!grafo->esDirigido) {
            NodoLista* nuevoSimetrico = crearNodo(origen, peso);
            nuevoSimetrico->siguiente = grafo->listas[destino];
            grafo->listas[destino] = nuevoSimetrico;
        }
    }
}
// Función para imprimir la lista de adyacencia
void imprimirLista(GrafoLista* grafo) {
    printf("\n--- LISTA DE ADYACENCIA ---\n");
    for (int i = 0; i < grafo->numVertices; i++) {
        NodoLista* actual = grafo->listas[i];
        printf("V%crtice %d: ", 130, i);
        while (actual != NULL) {
            printf(" -> [Destino: %d, Peso: %d]", actual->destino, actual->peso);
            actual = actual->siguiente;
        }
        printf(" -> NULL\n");
    }
}

// Función para liberar la memoria dinámica asignada de manera anidada
void liberarGrafoLista(GrafoLista* grafo) {
    for (int i = 0; i < grafo->numVertices; i++) {
        NodoLista* actual = grafo->listas[i];
        while (actual != NULL) {
            NodoLista* temporal = actual;
            actual = actual->siguiente;
            free(temporal); // Liberamos cada nodo de la lista enlazada
        }
    }
    free(grafo->listas); // Liberamos el arreglo de punteros
    free(grafo);         // Liberamos la estructura del grafo
}
// --- AQUÍ ESTÁ EL INT MAIN QUE FALTABA ---
int main() {
    int vertices, tipo, opcion;
    int origen, destino, peso;
    bool esDirigido;
    printf("=== CREADOR DE GRAFO INTERACTIVO (LISTAS) ===\n");
    printf("Ingrese la cantidad de v%crtices del grafo: ", 130);
    scanf("%d", &vertices);
    // Tu validación do-while adaptada perfectamente aquí
    do {
        printf("Seleccione el tipo de grafo (1: Dirigido, 0: No Dirigido): ");
        scanf("%d", &tipo);      
        if (tipo == 1) {
            esDirigido = true; 
        } else if (tipo == 0) {
            esDirigido = false; 
        } else {
            printf("Error, solo puede elegir los d%cgitos 0 o 1. Intente nuevamente.\n", 161);
        }
    } while (tipo != 0 && tipo != 1);
    // Inicializamos el grafo utilizando listas de adyacencia
    GrafoLista* miGrafo = crearGrafoLista(vertices, esDirigido);
    do {
        printf("\n--- MEN%c DE OPCIONES ---", 233);
        printf("\n1. Agregar una arista o conexi%cn", 162);
        printf("\n2. Mostrar Lista de Adyacencia");
        printf("\n3. Salir");
        printf("\nSeleccione una opci%cn: ", 162);
        scanf("%d", &opcion);
        switch (opcion) {
            case 1:
                printf("\n--- Agregar Arista ---\n");
                printf("V%crtice origen (0 a %d): ", 130, vertices - 1);
                scanf("%d", &origen);
                printf("V%crtice destino (0 a %d): ", 130, vertices - 1);
                scanf("%d", &destino);
                printf("Ingrese el peso de la arista: ");
                scanf("%d", &peso);
                // Validación de límites antes de insertar el nodo
                if (origen >= 0 && origen < vertices && destino >= 0 && destino < vertices) {
                    agregarAristaLista(miGrafo, origen, destino, peso);
                    printf("%cArista agregada correctamente!\n", 173); // 173 es '¡'
                } else {
                    printf("Error: Los v%crtices ingresados est%cn fuera del rango v%clido.\n", 130, 160, 160);
                }
                break;
            case 2:
                imprimirLista(miGrafo);
                break;
            case 3:
                printf("\nLiberando memoria din%cmica y cerrando el programa...\n", 160);
                liberarGrafoLista(miGrafo);
                break;
            default:
                printf("Opci%cn inv%clida. Intente de nuevo.\n", 162, 160);
        }
    } while (opcion != 3);
    return 0;
}
