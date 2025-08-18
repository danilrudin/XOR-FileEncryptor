cmake_minimum_required(VERSION 3.31.6 FATAL_ERROR)

project(XOR-FileEncryptor C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/bin)

set(HEADERS
    src/constants.h
    src/encryptors/xorencryptor.h
    src/cli/args.h
    src/cli/argHandlers.h
    src/cli/argFlags.h
)

set(SOURCES
    src/main.c
    src/encryptors/xorencryptor.c
    src/cli/args.c
    src/cli/argHandlers.c
)

add_executable(xor-file-encryptor
    ${HEADERS}
    ${SOURCES}
)