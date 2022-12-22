
set(TESTNAME ${PROJECT_NAME}_test)

# define my tests
enable_testing()


file(GLOB_RECURSE SOURCES *.cpp)
add_executable(${TESTNAME} ${SOURCES})
target_link_libraries(${TESTNAME} ${PROJECT_NAME} ${CONAN_LIBS})
add_test(NAME ${TESTNAME} COMMAND $<TARGET_FILE:${TESTNAME}> --no-version)
