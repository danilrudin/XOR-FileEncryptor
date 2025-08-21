cmake_minimum_required(VERSION 3.31.6 FATAL_ERROR)

project(XOR-FileEncryptor C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/bin)

set(HEADERS
    src/constants.h
    src/encryptors/xor_encryptor.h
    src/cli/args.h
    src/cli/arg_handlers.h
    src/cli/arg_flags.h
)

set(SOURCES
    src/main.c
    src/encryptors/xor_encryptor.c
    src/cli/args.c
    src/cli/arg_handlers.c
)

add_executable(xor-file-encryptor
    ${HEADERS}
    ${SOURCES}
)