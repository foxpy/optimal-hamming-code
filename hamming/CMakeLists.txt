add_library(Hamming
    hamming_parameters.c
)
target_include_directories(Hamming INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
