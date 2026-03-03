cmake_minimum_required(VERSION 3.30)
project(sorting C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(LIB_SOURCES
        src/algorithms/efficient/heapsort.c
        src/algorithms/efficient/introsort.c
        src/algorithms/efficient/mergesort.c
        src/algorithms/efficient/quicksort.c
        src/algorithms/efficient/timsort.c

        src/tests/correctness_tests.c
        src/tests/property_tests.c
        src/tests/stress_tests.c
        src/tests/unit_tests.c
)

set(LIB_HEADERS
        include/efficient_sorts.h
        include/sorting.h
        include/sorting_types.h
)

add_library(AlgorithmicCombinatoricsLab STATIC ${LIB_SOURCES} ${LIB_HEADERS})

target_include_directories(AlgorithmicCombinatoricsLab
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)


# Добавляем цели для форматирования кода
find_program(CLANG_FORMAT "clang-format")
if(CLANG_FORMAT)
    add_custom_target(format
            COMMAND ${CLANG_FORMAT} -i -style=file ${ALL_SOURCE_FILES}
            COMMENT "Formatting all source files with clang-format"
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )
endif()

# Добавляем цели для статического анализа
find_program(CLANG_TIDY "clang-tidy")
if(CLANG_TIDY AND EXISTS ${CMAKE_SOURCE_DIR}/.clang-tidy)
    add_custom_target(tidy
            COMMAND ${CLANG_TIDY} ${ALL_SOURCE_FILES} -config=""
            COMMENT "Running clang-tidy on all source files"
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )
endif()

