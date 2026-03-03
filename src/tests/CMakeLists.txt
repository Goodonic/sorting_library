# На Windows не используем pkg-config
if(WIN32)
    message(STATUS "Windows detected, using FetchContent for Unity")
else()
    find_package(PkgConfig QUIET)
endif()

# Использование Unity для тестов
include(FetchContent)
FetchContent_Declare(
        unity
        GIT_REPOSITORY https://github.com/ThrowTheSwitch/Unity.git
        GIT_TAG master
)
FetchContent_MakeAvailable(unity)

# Отключаем проблемные флаги для Unity при компиляции MinGW
if(MINGW)
    set_target_properties(unity PROPERTIES COMPILE_FLAGS "-w")
endif()

# Функция для добавления теста
function(add_sorting_test test_name test_source)
    get_filename_component(test_abs_path ${test_source} ABSOLUTE)
    add_executable(${test_name} ${test_abs_path})

    target_link_libraries(${test_name}
            PRIVATE
            sorting
            unity
    )

    target_include_directories(${test_name}
            PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}
            ${CMAKE_CURRENT_SOURCE_DIR}/../../include
            ${unity_SOURCE_DIR}/src
    )

    # Добавляем зависимость от библиотеки sorting
    add_dependencies(${test_name} sorting)

    add_test(NAME ${test_name} COMMAND ${test_name})
endfunction()

# Добавление тестов - проверяем существование файлов
#if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/unit_tests.c)
#    add_sorting_test(unit_tests unit_tests.c)
#endif()

#if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/correctness_tests.c)
#    add_sorting_test(correctness_tests correctness_tests.c)
#endif()

if(EXISTS test_introsort.c)
    add_sorting_test(test_introsort test_introsort.c)
endif()

if(EXISTS test_simple_sorts.c)
    add_sorting_test(test_simple_sorts test_simple_sorts.c)
endif()

# Специальная цель для запуска всех тестов
add_custom_target(check
        COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
        DEPENDS unit_tests correctness_tests test_introsort
)