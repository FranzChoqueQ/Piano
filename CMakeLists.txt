cmake_minimum_required(VERSION 3.10)
project(ProyectoBaseSDL2)

# Configuración básica
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Configuración específica para MSYS2/UCRT64
set(CMAKE_PREFIX_PATH "C:/msys64/ucrt64")

# --------------------------------------------------
# Configuración CRUCIAL de rutas de inclusión
# --------------------------------------------------
include_directories(
    ${CMAKE_SOURCE_DIR}  # Raíz del proyecto (para includes relativos desde src/)
    ${CMAKE_SOURCE_DIR}/engine/core
    ${CMAKE_SOURCE_DIR}/engine/graphics
    ${CMAKE_SOURCE_DIR}/game/States
    ${CMAKE_SOURCE_DIR}/game
)

# Rutas manuales para MSYS2 (UCRT64)
include_directories(
    C:/msys64/ucrt64/include/SDL2
)

link_directories(
    C:/msys64/ucrt64/lib
)

# --------------------------------------------------
# Lista explícita de archivos fuente (mejor que GLOB)
# --------------------------------------------------
set(SOURCE_FILES
    src/main.cpp
    engine/core/Game.cpp
    engine/core/EventHandler.cpp
    engine/core/Window.cpp
    engine/graphics/TextRenderer.cpp
    game/States/MenuState.cpp
    game/States/PlayState.cpp
    game/States/PauseState.cpp
    game/States/StateManager.cpp
    game/States/StateRequest.cpp
    game/MainGame.cpp
)

# Crear ejecutable
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# Enlazar bibliotecas
target_link_libraries(${PROJECT_NAME}
    mingw32
    SDL2main
    SDL2
    SDL2_ttf
)

# --------------------------------------------------
# Manejo de DLLs en Windows
# --------------------------------------------------
if(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_PREFIX_PATH}/bin/SDL2.dll"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_PREFIX_PATH}/bin/SDL2_ttf.dll"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
    
    # Copiar assets (fuentes, etc.)
    file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
endif()