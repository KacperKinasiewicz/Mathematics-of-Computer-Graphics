# Znajdź wszystkie pliki .cpp i .h w tym katalogu
file(GLOB LAB3_SOURCES "*.cpp" "*.h")

# Utwórz plik wykonywalny o nazwie "Lab3"
add_executable(Lab3 ${LAB3_SOURCES})