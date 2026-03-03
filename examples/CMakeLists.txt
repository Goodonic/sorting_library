# Функция для добавления примера
function(add_sorting_example example_name example_source)
    get_filename_component(example_abs_path ${example_source} ABSOLUTE)

    # Проверяем существование файла
    if(NOT EXISTS ${example_abs_path})
        message(WARNING "Example source file not found: ${example_abs_path}")
        return()
    endif()

    add_executable(${example_name} ${example_abs_path})

    target_link_libraries(${example_name}
            PRIVATE
            sorting
    )

    target_include_directories(${example_name}
            PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/../include
    )

    # Добавляем зависимость от библиотеки sorting
    add_dependencies(${example_name} sorting)

    # Копируем скрипты визуализации если нужно
    if(ENABLE_VISUALIZATION AND Python3_FOUND)
        add_custom_command(TARGET ${example_name} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_CURRENT_SOURCE_DIR}/../scripts/visualize_sorting.py
                ${CMAKE_CURRENT_BINARY_DIR}/
        )
    endif()
endfunction()

# Добавление примеров с проверкой существования файлов
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/examples.c)
    add_sorting_example(sorting_examples examples.c)
else()
    message(WARNING "examples.c not found, looking for alternative example files...")

    # Ищем другие возможные файлы примеров
    file(GLOB EXAMPLE_FILES "*.c")
    foreach(example_file ${EXAMPLE_FILES})
        get_filename_component(example_name ${example_file} NAME_WE)
        add_sorting_example(${example_name} ${example_file})
    endforeach()
endif()

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/simple_sorts.c)
    add_sorting_example(simple_sorts simple_sorts.c)
else()
    message(WARNING "simple_sorts.c not found, looking for alternative example files...")

    # Ищем другие возможные файлы примеров
    file(GLOB EXAMPLE_FILES "*.c")
    foreach(example_file ${EXAMPLE_FILES})
        get_filename_component(example_name ${example_file} NAME_WE)
        add_sorting_example(${example_name} ${example_file})
    endforeach()
endif()

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/stud3.c)
    add_sorting_example(stud3 stud3.c)
else()
    message(WARNING "stud3.c not found, looking for alternative example files...")

    # Ищем другие возможные файлы примеров
    file(GLOB EXAMPLE_FILES "*.c")
    foreach(example_file ${EXAMPLE_FILES})
        get_filename_component(example_name ${example_file} NAME_WE)
        add_sorting_example(${example_name} ${example_file})
    endforeach()
endif()