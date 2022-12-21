
set(LIB ${PROJECT_NAME})
file(GLOB_RECURSE SOURCES *.cpp)
add_library(${LIB} STATIC ${SOURCES})
target_include_directories(${LIB} PUBLIC "${CMAKE_SOURCE_DIR}/inc")
