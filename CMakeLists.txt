cmake_minimum_required(VERSION 3.10)
project(FastBoot)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON) # bibliotecas compartilhadas normalmente precisam de PIC

# mensagens úteis para os logs do CI
message(STATUS "CMAKE_SYSTEM_NAME=${CMAKE_SYSTEM_NAME}")
message(STATUS "ANDROID_ABI=${ANDROID_ABI}")
message(STATUS "ANDROID_PLATFORM=${ANDROID_PLATFORM}")
message(STATUS "ANDROID_NDK=${ANDROID_NDK}")

add_library(${PROJECT_NAME} SHARED
  include/mod/config.cpp
  src/main.cpp
  src/socialclub.cpp
  src/startmode.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
  ${CMAKE_SOURCE_DIR}/include
)

# link com a lib de log do Android (procura via find_library quando o toolchain está ativo)
if(ANDROID)
  find_library(LOG_LIB log)
  if(LOG_LIB)
    message(STATUS "Found log lib: ${LOG_LIB}")
    target_link_libraries(${PROJECT_NAME} PRIVATE ${LOG_LIB})
  else()
    message(WARNING "Android log library not found via find_library; falling back to 'log' name")
    target_link_libraries(${PROJECT_NAME} PRIVATE log)
  endif()
else()
  target_link_libraries(${PROJECT_NAME} PRIVATE log)
endif()

target_compile_options(${PROJECT_NAME} PRIVATE -O3)
target_link_options(${PROJECT_NAME} PRIVATE -s)
