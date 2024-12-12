# CMake funciona como un lenguaje de scripting, todas sus variables son strings, para tener un punto de referencia

cmake_minimum_required(VERSION 3.1)

project(Block_Device)

set(CMAKE_CXX_STANDARD 17) # Se define el standard de C++ que usaremos
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

# Definir los archivos a compilar

# Para llamar al nombre del proyecto debemos de ahuevo poner un '$' seguido de {}
add_executable(${CMAKE_PROJECT_NAME} blockDevice.cpp
                                    blockDevice.hpp
                                    main.cpp)

# Poner los nombres de los archivos usados durante el proyecto nos ayuda a documentar el proyecto, al ser los archivos requeridos para el funcionamiento

# basicamente le decimos al programa que requiere, si o si, la version de C++ especificada en CMake_CXX_Standard