cmake_minimum_required(VERSION 3.16)
project(SortingLibrary VERSION 1.0.0 LANGUAGES C)

# Настройки компиляции
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Опции сборки
option(BUILD_TESTS "Build unit tests" ON)           # Включено по умолчанию
option(BUILD_EXAMPLES "Build examples" ON)
option(BUILD_SHARED_LIBS "Build shared library" ON)
option(ENABLE_VISUALIZATION "Enable visualization support" OFF)
option(ENABLE_OPENMP "Enable OpenMP parallelization" OFF)

# Установка путей
include(GNUInstallDirs)

# Поиск зависимостей
find_package(Threads REQUIRED)

if(ENABLE_OPENMP)
    find_package(OpenMP)
    if(OpenMP_C_FOUND)
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    endif()
endif()

if(ENABLE_VISUALIZATION)
    # Для генерации графиков через Python (опционально)
    find_package(Python3 COMPONENTS Interpreter)
endif()

# Заголовочные файлы (публичные)
set(PUBLIC_HEADERS
        include/sorting.h
        include/sorting_types.h
        include/efficient_sorts.h
        include/simple_sorts.h
        include/specialized_sorts.h
        include/sorting_core.h
)

# Исходные файлы библиотеки
set(LIBRARY_SOURCES
#        # Core utilities
#        src/core/utils.c
#        src/core/comparator.c
#        src/core/memory_manager.c

        # Simple sorts (Student 1)
        src/algorithms/simple/insertion.c
        src/algorithms/simple/selection.c
        src/algorithms/simple/bubble.c
        src/algorithms/simple/gnome_stooge.c
        src/algorithms/simple/shell.c
        src/algorithms/simple/utils.c

        # Efficient sorts (Student 2)
        src/algorithms/efficient/quicksort.c
        src/algorithms/efficient/mergesort.c
        src/algorithms/efficient/heapsort.c
        src/algorithms/efficient/timsort.c
        src/algorithms/efficient/introsort.c

#        # Specialized sorts (Student 3)
#        src/algorithms/specialized/counting.c
#        src/algorithms/specialized/radix.c
#        src/algorithms/specialized/bucket.c
#        src/algorithms/specialized/dutch_flag.c
#        src/algorithms/specialized/kway_merge.c
#        src/algorithms/specialized/exotic.c
#
#        # Core integration (Student 4)
#        src/algorithms/core/unified_api.c
#        src/algorithms/core/benchmark.c
#        src/algorithms/core/adaptive.c
#        src/algorithms/core/testing.c
#        src/algorithms/core/visualization.c
#        src/algorithms/core/external_sort.c
)

# Создание библиотеки
if(BUILD_SHARED_LIBS)
    add_library(sorting SHARED ${LIBRARY_SOURCES})

    # Для Windows - экспорт символов
    if(WIN32)
        target_compile_definitions(sorting PRIVATE SORTING_LIBRARY_EXPORTS _WINDLL)
        set_target_properties(sorting PROPERTIES
                WINDOWS_EXPORT_ALL_SYMBOLS ON
                ENABLE_EXPORTS ON
        )
    endif()
else()
    add_library(sorting STATIC ${LIBRARY_SOURCES})
endif()

# Указываем include директории
target_include_directories(sorting
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/src/algorithms/efficient
)

# Линковка с зависимостями
target_link_libraries(sorting
        PUBLIC
        Threads::Threads
        PRIVATE
        ${CMAKE_DL_LIBS}
)

if(OpenMP_C_FOUND)
    target_link_libraries(sorting PUBLIC OpenMP::OpenMP_C)
endif()

# Определения для конфигурации
target_compile_definitions(sorting PRIVATE
        _GNU_SOURCE
        $<$<BOOL:${ENABLE_VISUALIZATION}>:ENABLE_VISUALIZATION>
        $<$<BOOL:${ENABLE_OPENMP}>:ENABLE_OPENMP>
)

# Для общих библиотек в Unix подобных системах
if(UNIX AND BUILD_SHARED_LIBS)
    set_target_properties(sorting PROPERTIES
            POSITION_INDEPENDENT_CODE ON
    )
endif()

# Установка библиотеки
set_target_properties(sorting PROPERTIES
        PUBLIC_HEADER "${PUBLIC_HEADERS}"
        VERSION ${PROJECT_VERSION}
        SOVERSION ${PROJECT_VERSION_MAJOR}
)

install(TARGETS sorting
        EXPORT SortingTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/sorting
)

# Экспорт конфигурации для find_package
install(EXPORT SortingTargets
        FILE SortingTargets.cmake
        NAMESPACE Sorting::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Sorting
)

# Генерация pkg-config файла
configure_file(
        "sorting.pc.in"
        "${CMAKE_CURRENT_BINARY_DIR}/sorting.pc"
        @ONLY
)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/sorting.pc"
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig
)

# Добавление поддиректорий
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(src/tests)
endif()

if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

#if(BUILD_BENCHMARKS)
#    add_subdirectory(benchmarks)
#endif()

## Дополнительная цель для документации
#add_custom_target(docs
#        COMMENT "Generating documentation (requires Doxygen)"
#        COMMAND ${CMAKE_COMMAND} -E echo "Run 'doxygen Doxyfile' in docs directory"
#)

# Информация о сборке
message(STATUS "Sorting Library Configuration:")
message(STATUS "  Tests: ${BUILD_TESTS}")
message(STATUS "  Examples: ${BUILD_EXAMPLES}")
message(STATUS "  Benchmarks: ${BUILD_BENCHMARKS}")
message(STATUS "  Shared library: ${BUILD_SHARED_LIBS}")
message(STATUS "  Visualization: ${ENABLE_VISUALIZATION}")
message(STATUS "  OpenMP: ${ENABLE_OPENMP} (${OpenMP_C_FOUND})")