add_library(Matrix
    matrix_new.c
    matrix_free.c
    matrix_multiply.c
    matrix_to_string.c
    matrix_fill_random.c
)
target_link_libraries(Matrix PUBLIC qc)
target_include_directories(Matrix INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
