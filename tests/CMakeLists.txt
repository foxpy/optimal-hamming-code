set(RUNTIME_OUTPUT_DIRECTORY tests)

function(ohc_add_test target)
    add_executable(${target} ${target}.c)
    target_link_libraries(${target} PUBLIC qc Matrix Hamming)
    add_test(NAME ${target} COMMAND ${target})
endfunction()

ohc_add_test(ohc-matrix-multiplication-test)
ohc_add_test(ohc-matrix-to-string-test)
ohc_add_test(ohc-hamming-H-test)
ohc_add_test(ohc-matrix-to-systematic-test)
ohc_add_test(ohc-matrix-clone-test)
ohc_add_test(ohc-matrix-transpose)
ohc_add_test(ohc-matrix-swap-columns-rows)
ohc_add_test(ohc-hamming-G-test)
ohc_add_test(ohc-hamming-encoding-test)
ohc_add_test(ohc-hamming-n-test)
