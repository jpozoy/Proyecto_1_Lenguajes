# Ruta relativa al repositorio clonado
add_subdirectory(cJSON)

# Incluir el directorio de encabezados de cJSON
include_directories(cJSON/include)

# Ejemplo de cómo crear un ejecutable
add_executable(main main.c)

# Enlazar cJSON a tu ejecutable
target_link_libraries(main cjson)