#include <stdio.h>
#include <cjson/cJSON.h>

int main() {
    printf("Hola, Mundo!\n");
        // Crear un objeto JSON
    cJSON *root = cJSON_CreateObject();
    if (root == NULL) {
        fprintf(stderr, "Error al crear el objeto JSON\n");
        return 1;
    }

    // Crear un array de ventas
    cJSON *ventas = cJSON_CreateArray();
    if (ventas == NULL) {
        cJSON_Delete(root);
        fprintf(stderr, "Error al crear el array JSON\n");
        return 1;
    }

    // Crear y añadir el primer objeto de venta
    cJSON *venta1 = cJSON_CreateObject();
    cJSON_AddStringToObject(venta1, "producto", "Laptop");
    cJSON_AddNumberToObject(venta1, "cantidad", 5);
    cJSON_AddNumberToObject(venta1, "precio", 1200.50);
    cJSON_AddItemToArray(ventas, venta1);

    // Crear y añadir el segundo objeto de venta
    cJSON *venta2 = cJSON_CreateObject();
    cJSON_AddStringToObject(venta2, "producto", "Smartphone");
    cJSON_AddNumberToObject(venta2, "cantidad", 10);
    cJSON_AddNumberToObject(venta2, "precio", 800.00);
    cJSON_AddItemToArray(ventas, venta2);

    // Añadir el array de ventas al objeto raíz
    cJSON_AddItemToObject(root, "ventas", ventas);

    // Convertir el objeto JSON a una cadena
    char *json_string = cJSON_Print(root);
    if (json_string == NULL) {
        cJSON_Delete(root);
        fprintf(stderr, "Error al convertir el objeto JSON a cadena\n");
        return 1;
    }

    // Abrir el archivo para escritura
    FILE *file = fopen("ventas.json", "w");
    if (file == NULL) {
        cJSON_Delete(root);
        free(json_string);
        perror("No se pudo abrir el archivo");
        return 1;
    }

    // Escribir la cadena JSON en el archivo
    fprintf(file, "%s", json_string);

    // Cerrar el archivo y liberar memoria
    fclose(file);
    cJSON_Delete(root);
    free(json_string);

    printf("Archivo JSON escrito con éxito.\n");
    return 0;
}