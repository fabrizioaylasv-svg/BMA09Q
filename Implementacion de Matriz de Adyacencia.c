#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// Estructura para representar un Grafo con Matriz de Adyacencia
typedef struct {
    int numVertices;
    int** matriz;
    bool esDirigido;
} GrafoMatriz;
// Función para crear e inicializar el grafo con Matriz de Adyacencia
GrafoMatriz* crearGrafoMatriz(int vertices, bool esDirigido) {
    GrafoMatriz* grafo = (GrafoMatriz*)malloc(sizeof(GrafoMatriz));
    grafo->numVertices = vertices;
    grafo->esDirigido = esDirigido;
    // Asignación dinámica de memoria para las filas
    grafo->matriz = (int**)malloc(vertices * sizeof(int*));
    for (int i = 0; i < vertices; i++) {
        // Asignación de memoria para las columnas e inicialización en 0
        grafo->matriz[i] = (int*)calloc(vertices, sizeof(int));
    }
    return grafo;
}
// Función para agregar una arista al grafo
void agregarAristaMatriz(GrafoMatriz* grafo, int origen, int destino, int peso) {
    if (origen >= 0 && origen < grafo->numVertices && destino >= 0 && destino < grafo->numVertices) {
        grafo->matriz[origen][destino] = peso;
        if (!grafo->esDirigido) {
            grafo->matriz[destino][origen] = peso; // Simetría para no dirigidos
        }
    }
}
// Función para imprimir la matriz de adyacencia
void imprimirMatriz(GrafoMatriz* grafo) {
    printf("\n--- MATRIZ DE ADYACENCIA ---\n  ");
    for (int i = 0; i < grafo->numVertices; i++) printf("%d ", i);
    printf("\n");
    for (int i = 0; i < grafo->numVertices; i++) {
        printf("%d ", i);
        for (int j = 0; j < grafo->numVertices; j++) {
            printf("%d ", grafo->matriz[i][j]);
        }
        printf("\n");
    }
}
// Función para liberar la memoria dinámica asignada
void liberarGrafoMatriz(GrafoMatriz* grafo) {
    for (int i = 0; i < grafo->numVertices; i++) {
        free(grafo->matriz[i]);
    }
    free(grafo->matriz);
    free(grafo);
}
int main() {
    int vertices, tipo, opcion;
    int origen, destino, peso;
    bool esDirigido;
    printf("=== CREA GRAFO INTERACTIVO ===\n");
    printf("Ingrese la cantidad de v%crtices del grafo: ", 130);
    scanf("%d", &vertices);
do
{
    printf("Seleccione el tipo de grafo (1: Dirigido, 0: No Dirigido): ");
    scanf("%d", &tipo);
    if (tipo != 0 && tipo != 1)
	{
        printf("Error, solo puede elegir los d%cgitos 0 o 1. Intente nuevamente.\n", 161);
    }
}
while (tipo != 0 && tipo != 1);
    // Inicializamos el grafo de verdad con tus funciones estructuradas
    GrafoMatriz* miGrafo = crearGrafoMatriz(vertices, esDirigido);
    do {
        printf("\n--- MEN%c DE OPCIONES ---", 233);
        printf("\n1. Agregar una arista o conexi%cn", 162);
        printf("\n2. Mostrar Matriz de Adyacencia");
        printf("\n3. Salir");
        printf("\nSeleccione una opci%cn: ", 162);
        scanf("%d", &opcion);
        switch (opcion) {
            case 1:
                printf("\n--- Agregar Arista ---\n");
                printf("V%crtice origen (0 a %d): ", 130,  vertices - 1);
                scanf("%d", &origen);
                printf("V%crtice destino (0 a %d): ", 130,  vertices - 1);
                scanf("%d", &destino);
                printf("Ingrese el peso de la arista: ");
                scanf("%d", &peso);
                // Validación simple de límites
                if (origen >= 0 && origen < vertices && destino >= 0 && destino < vertices) {
                    agregarAristaMatriz(miGrafo, origen, destino, peso);
                    printf("¡Arista agregada correctamente!\n");
                } else {
                    printf("Error: Los v%crtices ingresados están fuera del rango válido.\n", 130);
                }
                break;
            case 2:
                imprimirMatriz(miGrafo);
                break;
            case 3:
                printf("\nCerrando el programa...\n");
                liberarGrafoMatriz(miGrafo);
                break;
            default:
                printf("Opci%cn inv%clida. Intente de nuevo.\n", 162, 160);
        }
    } while (opcion != 3);
    return 0;
}
