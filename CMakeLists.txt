cmake_minimum_required(VERSION 3.22)
project(EncryptionApp)

set(CMAKE_CXX_STANDARD 23)

# Path to the PostgreSQL location
set(PostgreSQL_ROOT "C:/msys64/mingw64")

include_directories("${PostgreSQL_ROOT}/include")
link_directories("${PostgreSQL_ROOT}/lib")

add_executable(EncryptionApp main.cpp App.cpp App.h)

target_include_directories(EncryptionApp PRIVATE ${PostgreSQL_INCLUDE_DIRS})

# Linking libraries so linker does not crash
target_link_libraries(EncryptionApp PRIVATE pq) # Especially this one