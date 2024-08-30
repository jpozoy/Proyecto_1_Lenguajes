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

// // Funciones para manejar cada opción del menú
// void option1() {

//     int subChoice;
//     char *ruta_archivo = NULL;

//     while (1)
//     {
//     // Mostrar el submenú
//     printf("---- SUBMENÚ IMPORTACIÓN----\n");
//     printf("(1) Importar ventas\n"); // Solicitar ruta de archivo para importar los registros
//     printf("(2) Agregar ventas\n"); // Solicitar ruta de archivo diferente para guardar los nuevos registros ???
//     printf("(3) Regresar al menú principal\n");
//     printf("Ingrese su elección: ");
//     scanf("%d", &subChoice);
//     // Limpiar el buffer de entrada
//     while (getchar() != '\n');
//     switch (subChoice)
//     {
//     case 1:
        
//         break;
//     case 2:
//         printf("Agregando ventas\n");
        
//         break;
//     case 3:
//         printf("Regresando al menú principal\n");
//         return;
//     default:
//         break;
//     }
//     }
    
    
// }

void option2() {
    printf("Opción 2 seleccionada.\n");
    char *variableNombre = NULL;
    // pedir_cadena(&variableNombre, "Ingrese el nombre de la variable: ");
}

void option3() {
    printf("Opción 3 seleccionada.\n");
}

void option4() {
    printf("Opción 4 seleccionada.\n");
}

void option5() {
    printf("Opción 5 seleccionada.\n");
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
        printf("---- MENÚ PRINCIPAL----\n");
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
                // option1();
                
                break;
            case 2:
                char *rutaArchivo = NULL;
                pedir_cadena(&rutaArchivo, "Ingrese la ruta del archivo JSON: ");
                cargarArchivo(rutaArchivo, &ventasGlobal, &ventasCount, &ventasCapacity);
                free(rutaArchivo);
                imprimirVentas(ventasGlobal, ventasCount);
                break;
                option2();
                break;
            case 3:
                if (ventasCount > 0) {
                    completarCantidadConPromedio(ventasGlobal, ventasCount);
                    completarPrecioConModa(ventasGlobal, ventasCount);
                    actualizarTotal(ventasGlobal, ventasCount);
                    imprimirVentas(ventasGlobal, ventasCount);
                } else {
                    printf("No hay ventas cargadas para completar cantidades.\n");
                }
                break;
                option3();
                break;
            case 4:
                imprimirTotalDeVentas(ventasGlobal, ventasCount);
                if(ventasCount > 0) {
                    calcularVentasPorMesYAnio(ventasGlobal, ventasCount);
                } else {
                    printf("No hay ventas cargadas para calcular ventas por mes y año.\n");
                }
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