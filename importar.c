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
            cJSON *fecha = cJSON_GetObjectItem(item, "fecha");
            cJSON *producto_id = cJSON_GetObjectItem(item, "producto_id");
            cJSON *producto_nombre = cJSON_GetObjectItem(item, "producto_nombre");
            cJSON *categoria = cJSON_GetObjectItem(item, "categoria");
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
                ventas[i].producto_nombre = strdup(producto_nombre->valuestring);
            }
            if (cJSON_IsString(categoria)){
                ventas[i].categoria = strdup(categoria->valuestring);
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

// Función para cargar un archivo JSON y agregar sus datos al array global de ventas
void cargarArchivo(const char *rutaArchivo, Venta **ventas, size_t *count, size_t *capacity) {
    char *buffer = readFile(rutaArchivo);
    if (buffer == NULL) {
        return;
    }

    cJSON *json = cJSON_Parse(buffer);
    free(buffer);
    
    if (json == NULL) {
        printf("Error al parsear JSON del archivo: %s\n", rutaArchivo);
        return;
    }
    
    size_t arraySize;
    Venta *nuevasVentas = cJSONtoVenta(json, &arraySize);
    cJSON_Delete(json);
    
    if (nuevasVentas == NULL) {
        return;
    }

    // Expandir el array global si es necesario
    if (*count + arraySize > *capacity) {
        size_t nuevaCapacidad = (*capacity) * 2;
        while (*count + arraySize > nuevaCapacidad) {
            nuevaCapacidad *= 2;
        }
        *ventas = (Venta *)realloc(*ventas, nuevaCapacidad * sizeof(Venta));
        if (*ventas == NULL) {
            printf("Error al asignar memoria\n");
            free(nuevasVentas);
            exit(EXIT_FAILURE);
        }
        *capacity = nuevaCapacidad;
    }

    // Copiar las nuevas ventas al array global
    memcpy(*ventas + *count, nuevasVentas, arraySize * sizeof(Venta));
    *count += arraySize;

    free(nuevasVentas);
}

void pedir_cadena(char **cadena, const char *mensaje) {
    size_t tamano = 0;
    printf("%s", mensaje);
    getline(cadena, &tamano, stdin);

    // Eliminar el salto de línea al final
    (*cadena)[strcspn(*cadena, "\n")] = 0;
}

void imprimirVentas(Venta *ventas, size_t count) {
    for (size_t i = 0; i < count; ++i) {
        printf("Venta %zu\n", i + 1);
        printf("ID de venta: %d\n", ventas[i].venta_id);
        printf("Fecha: %s\n", ventas[i].fecha);
        printf("ID de producto: %d\n", ventas[i].producto_id);
        printf("Nombre de producto: %s\n", ventas[i].producto_nombre);
        printf("Categoria: %s\n", ventas[i].categoria);
        printf("Cantidad: %d\n", ventas[i].cantidad);
        printf("Precio unitario: %.2f\n", ventas[i].precio_unitario);
        printf("Total: %.2f\n", ventas[i].total);
        printf("\n");
    }
}

void completarCantidadConPromedio(Venta *ventas, size_t count) {
    int suma = 0;
    int cantidadValidas = 0;

    // Calcular la suma de las cantidades válidas y contar cuántas ventas tienen cantidad válida
    for (size_t i = 0; i < count; ++i) {
        if (ventas[i].cantidad > 0) { // Considerar solo cantidades válidas (mayores que 0)
            suma += ventas[i].cantidad;
            cantidadValidas++;
        }
    }

    // Calcular el promedio
    int promedio = (cantidadValidas > 0) ? suma / cantidadValidas : 0;

    // Completar las ventas que no tienen cantidad con el promedio calculado
    for (size_t i = 0; i < count; ++i) {
        if (ventas[i].cantidad == 0) {
            ventas[i].cantidad = promedio;
        }
    }

    printf("Las cantidades faltantes fueron completadas con el promedio de %d\n", promedio);
}

int compararFloat(const void *a, const void *b) {
    float fa = *(const float *)a;
    float fb = *(const float *)b;
    return (fa > fb) - (fa < fb);
}

float calcularModa(float *precios, size_t count) {
    qsort(precios, count, sizeof(float), compararFloat);

    float moda = precios[0];
    int maxCount = 1;
    int countActual = 1;

    for (size_t i = 1; i < count; ++i) {
        if (precios[i] == precios[i - 1]) {
            countActual++;
        } else {
            countActual = 1;
        }

        if (countActual > maxCount) {
            maxCount = countActual;
            moda = precios[i];
        }
    }

    return moda;
}

void completarPrecioConModa(Venta *ventas, size_t count) {
    // Contar cuántas ventas tienen precio válido
    size_t countValidos = 0;
    for (size_t i = 0; i < count; ++i) {
        if (ventas[i].precio_unitario > 0) {
            countValidos++;
        }
    }

    // Crear un array temporal con los precios válidos
    float *preciosValidos = (float *)malloc(countValidos * sizeof(float));
    if (preciosValidos == NULL) {
        printf("Error al asignar memoria para precios válidos\n");
        return;
    }

    size_t index = 0;
    for (size_t i = 0; i < count; ++i) {
        if (ventas[i].precio_unitario > 0) {
            preciosValidos[index++] = ventas[i].precio_unitario;
        }
    }

    // Calcular la moda de los precios válidos
    float moda = calcularModa(preciosValidos, countValidos);
    free(preciosValidos);

    // Completar los precios faltantes con la moda
    for (size_t i = 0; i < count; ++i) {
        if (ventas[i].precio_unitario == 0) {
            ventas[i].precio_unitario = moda;
        }
    }

    printf("Los precios faltantes fueron completados con la moda de %.2f\n", moda);
}

void actualizarTotal(Venta *ventas, size_t count) {
    for (size_t i = 0; i < count; ++i) {
        if (ventas[i].total == 0) {  // Si el total está en blanco
            ventas[i].total = ventas[i].cantidad * ventas[i].precio_unitario;
        }
    }
    printf("Los totales faltantes han sido actualizados.\n");
}

void imprimirTotalDeVentas(Venta *ventas, size_t count) {
    double sumaTotal = 0.0;

    for (size_t i = 0; i < count; ++i) {
        sumaTotal += ventas[i].total;
    }

    printf("El total de todas las ventas es: %.2f\n", sumaTotal);
}

void parsearFecha(const char *fecha, int *year, int *month) {
    sscanf(fecha, "%d-%d", year, month);
}

void calcularVentasPorMesYAnio(Venta *ventas, size_t count) {
    size_t maxMeses = 12 * 100; 
    VentasPorMes *ventasPorMes = (VentasPorMes *)calloc(maxMeses, sizeof(VentasPorMes));
    size_t numMeses = 0;

    for (size_t i = 0; i < count; ++i) {
        int year, month;
        parsearFecha(ventas[i].fecha, &year, &month);

        // Buscar si ya existe una entrada para este mes y año
        size_t j;
        for (j = 0; j < numMeses; ++j) {
            if (ventasPorMes[j].year == year && ventasPorMes[j].month == month) {
                ventasPorMes[j].totalVentas += ventas[i].total;
                break;
            }
        }

        // Si no existe, agregar una nueva entrada
        if (j == numMeses) {
            ventasPorMes[numMeses].year = year;
            ventasPorMes[numMeses].month = month;
            ventasPorMes[numMeses].totalVentas = ventas[i].total;
            ++numMeses;
        }
    }

    // Imprimir los resultados
    for (size_t i = 0; i < numMeses; ++i) {
        printf("Total de ventas en %02d/%d: %.2f\n", 
               ventasPorMes[i].month, ventasPorMes[i].year, ventasPorMes[i].totalVentas);
    }

    free(ventasPorMes);
}
