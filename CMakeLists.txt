# Ruta relativa al repositorio clonado
add_subdirectory(cJSON)

# Incluir el directorio de encabezados de cJSON
include_directories(cJSON/include)

# Incluir el directorio actual donde se encuentran los encabezados
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Ejemplo de cómo crear un ejecutable
add_executable(main main.c importar.c)

# Enlazar cJSON a tu ejecutable
target_link_libraries(main cjson)