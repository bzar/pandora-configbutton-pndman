cmake_minimum_required(VERSION 2.6)

find_package(CURL REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(EXPAT REQUIRED)

include_directories(${JANSSON_BINARY_DIR}/include/ src/include ${OPENSSL_INCLUDE_DIR} ${CURL_INCLUDE_DIR} ${EXPAT_INCLUDE_DIR})

file (GLOB_RECURSE PNDMAN_SRCS src/lib/*.c)
add_definitions(-fPIC)
add_library(pndman ${PNDMAN_SRCS})
target_link_libraries(pndman jansson ${OPENSSL_LIBRARIES} ${CURL_LIBRARY} ${EXPAT_LIBRARY})
