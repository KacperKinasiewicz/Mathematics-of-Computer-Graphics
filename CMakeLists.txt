cmake_minimum_required(VERSION 3.10)
project(MathematicsOfComputerGraphics)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Opcjonalnie: włącz obsługę folderów w IDE (np. Visual Studio)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Dodawanie podkatalogów. 

add_subdirectory("Laboratorium 2 - wektory")
add_subdirectory("Laboratorium 3 - macierze")
add_subdirectory("Laboratorium 4 - kwaterniony")
add_subdirectory("Laboratorium 5 - obliczanie przeciec")
add_subdirectory("Laboratorium 6 - wizualizacja wynikow")