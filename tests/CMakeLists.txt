set(RUNTIME_OUTPUT_DIRECTORY tests)

add_executable(ohc-matrix-multiplication-test ohc-matrix-multiplication-test.c)
target_link_libraries(ohc-matrix-multiplication-test PUBLIC qc Matrix)
add_test(NAME ohc-matrix-multiplication-test COMMAND ohc-matrix-multiplication-test)
