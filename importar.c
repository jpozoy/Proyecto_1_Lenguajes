#include "importar.h"
#include <stdio.h>
#include <cjson/cJSON.h>
#include <string.h>
#include <stdlib.h>

#define RUTA_ARCHIVO "../data/ventas.json"

char* readFile(const char* rutaArchivo) {
    FILE *archivo = fopen(rutaArchivo, "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo: %s\n", rutaArchivo);
        return NULL;
    }
    long fileSize = getFileSize(archivo);
    char *buffer = (char *)malloc(fileSize + 1); //Agregar un byte para el terminador nulo
    if (buffer == NULL) {
        printf("Error al asignar memoria\n");
        fclose(archivo);
        return NULL;
    }

    size_t bytesRead = fread(buffer, 1, fileSize, archivo);
    buffer[bytesRead] = '\0'; // Agregar el terminador nulo
    if (bytesRead != fileSize) {
        printf("Error al leer el archivo.\n");
        free(buffer);
        fclose(archivo);
        return NULL;
    }
    fclose(archivo);
    return buffer;
}

long getFileSize(FILE *file) {
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);
    return size;
}

Venta* cJSONtoVenta(cJSON *json, size_t *count) {
    if (!cJSON_IsArray(json)) {
        printf("Error: el archivo no contiene un array de ventas\n");
        return NULL;
    }
    
    size_t arraySize = cJSON_GetArraySize(json); // Obtener el tamaño del array de objetos
    Venta *ventas= (Venta *)malloc(arraySize * sizeof(Venta)); // Reservar memoria para el array de ventas
    if (ventas == NULL) {
        printf("Error al asignar memoria\n");
        return NULL;
    }

    for (size_t i = 0; i < arraySize; ++i) {
        cJSON *item = cJSON_GetArrayItem(json, i);
        if (item != NULL) {
            cJSON *venta_id = cJSON_GetObjectItem(item, "venta_id");
            cJSON *fecha = cJSON_GetObjectItem(item, "producto");
            cJSON *producto_id = cJSON_GetObjectItem(item, "producto_id");
            cJSON *producto_nombre = cJSON_GetObjectItem(item, "producto_nombre");
            cJSON *categoria = cJSON_GetObjectItem(item, "Accesorios");
            cJSON *cantidad = cJSON_GetObjectItem(item, "cantidad");
            cJSON *precio_unitario = cJSON_GetObjectItem(item, "precio_unitario");
            cJSON *total  = cJSON_GetObjectItem(item, "total");

            if(cJSON_IsNumber(venta_id)){
                ventas[i].venta_id = venta_id->valueint;
            }
            if(cJSON_IsString(fecha)){
                strcpy(ventas[i].fecha, fecha->valuestring);
            }
            if(cJSON_IsNumber(producto_id)){
                ventas[i].producto_id = producto_id->valueint;
            }
            if(cJSON_IsString(producto_nombre)){
                strcpy(ventas[i].producto_nombre, producto_nombre->valuestring);
            }
            if (cJSON_IsString(categoria)){
                strcpy(ventas[i].categoria, categoria->valuestring);
            }
            if (cJSON_IsNumber(cantidad)){
                ventas[i].cantidad = cantidad->valueint;
            }
            if (cJSON_IsNumber(precio_unitario)){
                ventas[i].precio_unitario = precio_unitario->valuedouble;
            }
            if (cJSON_IsNumber(total)){
                ventas[i].total = total->valuedouble;
            }
        }
    }
    *count = arraySize;
    return ventas;
    
}
