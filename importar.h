#ifndef IMPORTAR_H
#define IMPORTAR_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>

// Estructura de una venta
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

// Estructura para almacenar las ventas por mes y año
typedef struct {
    int year;
    int month;
    double totalVentas;
} VentasPorMes;

// Estructura para almacenar las categorías y sus totales
typedef struct CategoriaTotal {
    char *categoria;
    float total;
} CategoriaTotal;

// Estructura para almacenar los totales de ventas por mes
typedef struct {
    char mes[8]; // Mes en formato "AAAA-MM"
    double totalVentas;
} TotalVentasMes;


/*
Entrada: rutaArchivo: const char*,
Salida: char*,
Funcionamiento: Lee un archivo y lo guarda en un buffer,
Restricciones: La ruta del archivo debe ser válida.
*/
char* readFile(const char* rutaArchivo);

/*
Entrada: file: FILE*,
Salida: long,
Funcionamiento: Obtiene el tamaño de un archivo.
Restricciones: Ninguna
*/
long getFileSize(FILE *file);

/*
Entrada: json: cJSON*, size_t* count,
Salida: Venta*,
Funcionamiento: Convierte un objeto JSON en un objeto de Venta.
Restricciones: El archivo debe contener un array de ventas.
*/
Venta* cJSONtoVenta(cJSON *json, size_t *count);

/*
Entrada: rutaArchivo: const char*, Venta** ventas, size_t* count, size_t* capacity,
Salida: void,
Funcionamiento: Carga un archivo JSON y lo convierte en un array de ventas.
Restricciones: La ruta del archivo debe ser válida, El objeto JSON debe contener un array de ventas.

*/
void cargarArchivo(const char *rutaArchivo, Venta **ventas, size_t *count, size_t *capacity);

/*
Entrada: cadena: char**, const char* mensaje,
Salida: void,
Funcionamiento: Pide una cadena al usuario con mensaje.
Restricciones: Ninguna
*/
void pedir_cadena(char** cadena, const char* mensaje);

/*
Entrada: ventas: Venta*, count: size_t,
Salida: void,
Funcionamiento: Imprime las ventas.
Restricciones: Ninguna
*/

void imprimirVentas(Venta *ventas, size_t count);

/*
Entrada: ventas: Venta*, count: size_t,
Salida: void,
Funcionamiento: Completa las cantidades faltantes con el promedio,
Restricciones: Ninguna
*/
void completarCantidadConPromedio(Venta *ventas, size_t count);


/*
Entrada: ventas: Venta*, count: size_t,
Salida: int,
Funcionamiento: Compara dos floats para determinar si son iguales, utilazado en qsort.
Restricciones: Ninguna
*/
int compararFloat(const void *a, const void *b);

/*
Entrada: precios: float*, count: size_t,
Salida: float,
Funcionamiento: Calcula la moda de un array de floats.
Restricciones: Ninguna
*/
float calcularModa(float *precios, size_t count);

/*
Entrada: ventas: Venta*, count: size_t,
Salida: void,
Funcionamiento: Completa los precios faltantes con la moda.
Restricciones: Ninguna
*/
void completarPrecioConModa(Venta *ventas, size_t count);

/*
Entrada: ventas: Venta*, count: size_t,
Salida: void,
Funcionamiento: Actualiza los totales faltantes con las cantidades y precios.
Restricciones: Ninguna
 */
void actualizarTotal(Venta *ventas, size_t count);

/*
Entrada: ventas: Venta*, count: size_t,
Salida: void,
Funcionamiento: Imprime el total de la suma de todas las ventas.
Restricciones: Ninguna 
*/
void imprimirTotalDeVentas(Venta *ventas, size_t count);

/*
Entrada: fecha: const char*, year: int*, month: int*,
Salida: void,
Funcionamiento: Parsea una fecha en formato "AAAA-MM-DD" y guarda el año y mes.
Restricciones: Ninguna
*/
void parsearFecha(const char *fecha, int *year, int *month);

/*
Entrada: ventas: Venta*, count: size_t,
Salida: void,
Funcionamiento: Calcula las ventas por mes y año.
Restricciones: Ninguna
*/
void calcularVentasPorMesYAnio(Venta *ventas, size_t count);

/*
Entrada: ventas: Venta*, count: size_t,
Salida: void,
Funcionamiento: Muestra el total de ventas por año.
Restricciones: Ninguna
*/
void mostrarTotalVentasPorAnio(Venta *ventas, size_t count);

/*
Entrada: ventas: Venta*, count: size_t,
Salida: void,
Funcionamiento: Muestra las 5 categorías con más ventas.
Restricciones: Ninguna
*/
void mostrarTopCategorias(Venta *ventas, size_t count);

/*
Entrada: ventas: Venta*, count: size_t,
Salida: void,
Funcionamiento: Determina si dos ventas son iguales.
Restricciones: Ninguna
*/
int sonVentasIguales(Venta *venta1, Venta *venta2);

/*
Entrada: ventas: Venta**, count: size_t*,
Salida: void,
Funcionamiento: Elimina las ventas duplicadas.
Restricciones: Ninguna
*/
void eliminarDuplicados(Venta **ventas, size_t *count);

/*
Entrada: ventas: Venta*, count: size_t,
Salida: void,
Funcionamiento: Encuentra el mes con mayor venta.
Restricciones: Ninguna
*/
void mesConMayorVenta(Venta *ventas, size_t count);


#endif