# Задаем минимально необходимую версию для CMake.
cmake_minimum_required(VERSION 3.14)

# Включение модуля FetchContent для загрузки внешних зависимостей.
include(FetchContent)

# Установка имени и языка проекта.
project(ae_tests
        LANGUAGES CXX)

# Установить стандарт C++ на 17.
set(CMAKE_CXX_STANDARD 17)

# Включение требования использования стандарта C++ в проекте.
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ----------------------------------------------------------------
# Настройки
# ----------------------------------------------------------------

set(gtest_force_shared_crt ON CACHE BOOL
        "Установка переменной gtest_force_shared_crt значение ON, чтобы использовать общий CRT в Google Test.")

set(AE_LIBRARY_OPTION_RUNTIME_ALLOCATOR_INIT_STDLIB ON CACHE BOOL
        "Использовать функции из stdlib для инициализации распределителя времени выполнения.")

set(AE_LIBRARY_OPTION_FILL_ZERO_AFTER_MEMORY_ALLOCATE ON CACHE BOOL
        "Новый выделенный участок памяти заполняется нулями.")

set(AE_LIBRARY_OPTION_USE_STD_WCHAR ON CACHE BOOL
        "Использовать стандартный тип wchar_t.")

# ----------------------------------------------------------------
# Получение репозиториев
# ----------------------------------------------------------------

# Объявление ae как внешнюю зависимость.
FetchContent_Declare(ae
        GIT_REPOSITORY https://github.com/cyaneor/ae.git
        GIT_TAG HEAD
)

# Объявление googletest как внешнюю зависимость.
FetchContent_Declare(googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.15.2
)

# ----------------------------------------------------------------
# Подключение репозиториев
# ----------------------------------------------------------------

# Делаем контент AE доступным для использования в проекте.
FetchContent_MakeAvailable(ae)

# Делаем контент Google Test доступным для использования в проекте.
FetchContent_MakeAvailable(googletest)

# ----------------------------------------------------------------
# Сборка тестов
# ----------------------------------------------------------------

# Добавление исходных файлов тестов.
add_executable(${PROJECT_NAME}
        src/numeric_limits.cpp
        src/memory_block.cpp
        src/memory_range.cpp
        src/memory_raw.cpp
        src/wstr_raw.cpp
        src/str_raw.cpp
        src/main.cpp)

# Добавление зависимостей и связка с библиотеками.
target_link_libraries(${PROJECT_NAME} gtest gmock ae)

# Копирование библиотеки ae в директорию с исполняемым файлом
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:ae> $<TARGET_FILE_DIR:${PROJECT_NAME}>
)

# ----------------------------------------------------------------
# Тестирование
# ----------------------------------------------------------------

# Включаем тестирование.
enable_testing()

# Включаем модуль Google Test.
include(GoogleTest)

# Находим и запускаем тесты с помощью Google Test.
gtest_discover_tests(${PROJECT_NAME})