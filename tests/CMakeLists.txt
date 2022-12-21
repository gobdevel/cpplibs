
set(TESTNAME ${PROJECT_NAME}_test)

# define my tests
enable_testing()

add_executable(${TESTNAME} cacheTest.cpp)
target_link_libraries(${TESTNAME} ${PROJECT_NAME} ${CONAN_LIBS})
add_test(NAME ${TESTNAME} COMMAND $<TARGET_FILE:${TESTNAME}> --no-version)
