# Znajdź wszystkie pliki .cpp i .h w tym katalogu
file(GLOB LAB4_SOURCES "*.cpp" "*.h")

# Utwórz plik wykonywalny o nazwie "Lab4"
add_executable(Lab4 ${LAB4_SOURCES})