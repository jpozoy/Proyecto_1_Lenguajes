#ifndef IMPORTAR_H
#define IMPORTAR_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>

typedef struct
{
    int venta_id;
    char fecha[11];
    int producto_id;
    char* producto_nombre;
    char* categoria;
    int cantidad;
    float precio_unitario;
    float total;
} Venta;

typedef struct {
    int year;
    int month;
    double totalVentas;
} VentasPorMes;

// Funcion para leer un archivo y retornar su contenido
char* readFile(const char* rutaArchivo);

// Funcion para obtener el tamaño de un archivo
long getFileSize(FILE *file);

// Funcion para convertir cJSON a Venta
Venta* cJSONtoVenta(cJSON *json, size_t *count);

//Funcion para cargar varios archivos
void cargarArchivo(const char *rutaArchivo, Venta **ventas, size_t *count, size_t *capacity);

// Funcion para solicitar datos al usuario
void pedir_cadena(char** cadena, const char* mensaje);

// Función para imprimir ventas
void imprimirVentas(Venta *ventas, size_t count);

// Función para procesar datos de cantidad
void completarCantidadConPromedio(Venta *ventas, size_t count);

// Función para procesar datos de precio unitario

int compararFloat(const void *a, const void *b);

float calcularModa(float *precios, size_t count);

void completarPrecioConModa(Venta *ventas, size_t count);

void actualizarTotal(Venta *ventas, size_t count);

// Analisis de datos

// Total de ventas
void imprimirTotalDeVentas(Venta *ventas, size_t count);

// Ventas anuales y por mes
void parsearFecha(const char *fecha, int *year, int *month);

void calcularVentasPorMesYAnio(Venta *ventas, size_t count);


void mostrarTotalVentasPorAno(Venta *ventas, size_t count);


#endif