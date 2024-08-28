#include <stdio.h>
#include <cjson/cJSON.h>

#include <stdio.h>
#include <stdlib.h>

#include <importar.h>

// Funciones para manejar cada opción del menú
void option1() {

    int subChoice;
    const char *ruta_archivo = "../data/ventas.json";

    
    while (1)
    {
    // Mostrar el submenú
    printf("---- SUBMENÚ IMPORTACIÓN----\n");
    printf("(1) Importar ventas\n"); // Solicitar ruta de archivo para importar los registros
    printf("(2) Agregar ventas\n"); // Solicitar ruta de archivo diferente para guardar los nuevos registros ???
    printf("(3) Regresar al menú principal\n");
    printf("Ingrese su elección: ");
    scanf("%d", &subChoice);
    switch (subChoice)
    {
    case 1:
        printf("Importando ventas\n");
        char* data = readFile(ruta_archivo);
        if(ruta_archivo == NULL){
            printf("Error al leer el archivo\n");
        }
        else{
            printf("Archivo leído correctamente:\n%s\n", data);
        }
        //Codigo de prueba
        cJSON *json = cJSON_Parse(data);
        if (json == NULL) {
            printf("Error al parsear el archivo\n");
        }
        else{
            printf("Archivo parseado correctamente\n");
        }

        size_t count = 0;
        Venta *ventas = cJSONtoVenta(json, &count);
        if (ventas != NULL) {
            for (size_t i = 0; i < count; ++i){
                printf("Venta %zu\n", i + 1);
                printf("ID: %d\n", ventas[i].venta_id);
                printf("Fecha: %s\n", ventas[i].fecha);
                printf("Producto ID: %d\n", ventas[i].producto_id);
                printf("Producto: %s\n", ventas[i].producto_nombre);
                printf("Categoria: %s\n", ventas[i].categoria);
                printf("Cantidad: %d\n", ventas[i].cantidad);
                printf("Precio unitario: %.2f\n", ventas[i].precio_unitario);
                printf("Total: %.2f\n", ventas[i].total);
            }
        }
        cJSON_Delete(json);
        free(data);
        break;
    case 2:
        printf("Agregando ventas\n");
        break;
    case 3:
        printf("Regresando al menú principal\n");
        return;
    default:
        break;
    }
    }
    
    
}

void option2() {
    printf("Opción 2 seleccionada.\n");
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