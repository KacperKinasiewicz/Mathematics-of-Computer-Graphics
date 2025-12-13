# Znajdź wszystkie pliki .cpp i .h w tym katalogu
file(GLOB LAB2_SOURCES "*.cpp" "*.h")

# Utwórz plik wykonywalny o nazwie "Lab2"
add_executable(Lab2 ${LAB2_SOURCES})