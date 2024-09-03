#include <stdio.h>
#include <cjson/cJSON.h>

#include <stdio.h>
#include <stdlib.h>

#include <importar.h>

#define INICIAL_CAPACIDAD 10

// Definir el array global y su tamaño
Venta *ventasGlobal = NULL;
size_t ventasCount = 0;
size_t ventasCapacity = INICIAL_CAPACIDAD;

// Funciones para manejar cada opción del menú
void option1() {
    char *rutaArchivo = NULL;
    pedir_cadena(&rutaArchivo, "Ingrese la ruta del archivo JSON: ");
    cargarArchivo(rutaArchivo, &ventasGlobal, &ventasCount, &ventasCapacity);
    free(rutaArchivo);
    imprimirVentas(ventasGlobal, ventasCount);

}

void option2() {
    int subChoice;

    while (1) {
        // Mostrar submenu
        printf("---- SUBMENÚ PROCESAMIENTO ----\n");
        printf("(1) Completar datos faltantes\n");
        printf("(2) Eliminar duplicados\n");
        printf("(3) Regresar al menú principal\n");
        printf("Ingrese su elección: ");
        scanf("%d", &subChoice);
        // Limpiar el buffer de entrada
        // while (getchar() != '\n');
        
        switch (subChoice) {
            case 1:
                if (ventasCount > 0) {
                    completarCantidadConPromedio(ventasGlobal, ventasCount);
                    completarPrecioConModa(ventasGlobal, ventasCount);
                    actualizarTotal(ventasGlobal, ventasCount);
                    imprimirVentas(ventasGlobal, ventasCount);
                } else {
                    printf("No hay ventas cargadas para completar cantidades.\n");
                }
                break;
            case 2:
                eliminarDuplicados(&ventasGlobal, &ventasCount);
                printf("Eliminando duplicados\n");
                break;
            case 3:
                printf("Regresando al menú principal\n");
                return;
            default:
                break;
        }
    }
}

void option3() {
    printf("---- Analisis de datos ----\n");
    printf("Total de ventas.\n");
    imprimirTotalDeVentas(ventasGlobal, ventasCount);
    if(ventasCount > 0) {
        printf("Ventas por mes.\n");
        calcularVentasPorMesYAnio(ventasGlobal, ventasCount);
        printf("Ventas por año.\n");
        mostrarTotalVentasPorAno(ventasGlobal, ventasCount);
    } else {
        printf("No hay ventas cargadas para calcular ventas por mes y año.\n");
    }
}

void option4() {
    printf("Opción 4 seleccionada.\n");
    imprimirVentas(ventasGlobal, ventasCount);
    
}

void option5() {
    printf("Opción 5 seleccionada.\n");
    mostrarTopCategorias(ventasGlobal, ventasCount);
}

void quit() {
    printf("Saliendo del programa...\n");
    exit(0);
}


int main() {
    int choice;
        // Inicializar el array global de ventas
    ventasGlobal = (Venta *)malloc(ventasCapacity * sizeof(Venta));
    if (ventasGlobal == NULL) {
        printf("Error al asignar memoria\n");
        return EXIT_FAILURE;
    }

    while (1) {
        // Mostrar el menú
        printf("---- MENÚ PRINCIPAL ----\n");
        printf("(1) Importacion de datos\n");
        printf("(2) Procesamiento de datos\n");
        printf("(3) Analisis de datos\n");
        printf("(4) Analisis temporal\n");
        printf("(5) Estadísticas\n");
        printf("(6) Salir\n");
        printf("Ingrese su elección: ");
        scanf("%d", &choice);

        // Limpiar el buffer de entrada
        while (getchar() != '\n');

        // Manejar la opción seleccionada
        switch (choice) {
            case 1:
                option1();     
                break;
            case 2:
                option2();
                break;
            case 3:
                option3();
                break;
            case 4:
                option4();
                break;
            case 5:
                option5();
                break;
            case 6:
                quit();
                break;
            default:
                printf("Opción no válida. Intente de nuevo.\n");
                break;
        }
    }

    return 0;
}