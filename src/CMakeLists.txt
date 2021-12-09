# download cpp-peglib header
  if(NOT EXISTS "${CMAKE_BINARY_DIR}/peglib.h")
    message(
      STATUS
        "Downloading peglib.h from https://github.com/yhirose/cpp-peglib")
    file(
      DOWNLOAD
      "https://raw.githubusercontent.com/yhirose/cpp-peglib/master/peglib.h"
      "${CMAKE_BINARY_DIR}/peglib.h"
      EXPECTED_HASH
        b03dab2378c4a041b9220e1e7140208c9267ff5c46ca06ede0ed9ce280b2f02b
      TLS_VERIFY ON)
  endif()

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_library(peglib INTERFACE) 
target_include_directories(peglib INTERFACE ${CMAKE_BINARY_DIR})
target_link_libraries(peglib INTERFACE Threads::Threads)

add_executable(diffeq diffeq.cpp)
target_link_libraries(diffeq PRIVATE peglib project_options)

