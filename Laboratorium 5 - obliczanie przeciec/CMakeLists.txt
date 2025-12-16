# Znajdź wszystkie pliki .cpp i .h w tym katalogu
file(GLOB LAB5_SOURCES "*.cpp" "*.h")

# Utwórz plik wykonywalny o nazwie "Lab5"
add_executable(Lab5 ${LAB5_SOURCES})