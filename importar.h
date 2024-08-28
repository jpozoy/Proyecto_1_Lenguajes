#ifndef IMPORTAR_H
#define IMPORTAR_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>

typedef struct
{
    int venta_id;
    char fecha[20];
    int producto_id;
    char producto_nombre[50];
    char categoria[50];
    int cantidad;
    float precio_unitario;
    float total;
} Venta;

// Funcion para leer un archivo y retornar su contenido
char* readFile(const char* rutaArchivo);

// Funcion para obtener el tamaño de un archivo
long getFileSize(FILE *file);

// Funcion para convertir cJSON a Venta
Venta* cJSONtoVenta(cJSON *json, size_t *count);


#endif