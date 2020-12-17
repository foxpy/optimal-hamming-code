add_library(Hamming
    hamming_parameters.c
    hamming_H.c
    hamming_G.c
    hamming_decode.c
)
target_link_libraries(Hamming PUBLIC Matrix)
target_include_directories(Hamming INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
