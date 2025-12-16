# Znajdź wszystkie pliki .cpp i .h w tym katalogu
file(GLOB LAB6_SOURCES "*.cpp" "*.h")

# Utwórz plik wykonywalny o nazwie "Lab6"
add_executable(Lab6 ${LAB6_SOURCES})