#Especificar donde se encuentran los ficheros cpp a compilar
target_sources(libModulos PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/Animacion.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Bloque.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/BRoto.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Mapa.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Personaje.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Pengo.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/SnoBee.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Juego.cpp"
)

#Y donde se encuentran los .h
target_include_directories(libModulos PUBLIC 
"${CMAKE_CURRENT_SOURCE_DIR}"
)

