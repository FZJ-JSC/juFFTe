# --------------------------------------------------------------------------------------------------
# SPDX-FileCopyrightText: juFFTe developers
# SPDX-License-Identifier: Apache-2.0
# --------------------------------------------------------------------------------------------------
#
#   cmake -S . -B build-riscv -DCMAKE_TOOLCHAIN_FILE=cmake/riscv-rvv.cmake \
#         -DWITHSPRL=ON -DWITHRVV=ON
#
# Executables are linked statically so qemu-riscv64-static can run them directly.

set(CMAKE_SYSTEM_NAME      Linux)
set(CMAKE_SYSTEM_PROCESSOR riscv64)

set(RISCV_TOOLCHAIN_PREFIX "/opt/riscv" CACHE PATH "Root of the RISC-V cross toolchain")
set(RISCV_TARGET_TRIPLE "riscv64-unknown-linux-gnu" CACHE STRING "Cross toolchain target triple")

if(NOT CMAKE_C_COMPILER AND NOT DEFINED ENV{CC})
    set(CMAKE_C_COMPILER       ${RISCV_TOOLCHAIN_PREFIX}/bin/${RISCV_TARGET_TRIPLE}-gcc)
endif()
if(NOT CMAKE_Fortran_COMPILER AND NOT DEFINED ENV{FC})
    set(CMAKE_Fortran_COMPILER ${RISCV_TOOLCHAIN_PREFIX}/bin/${RISCV_TARGET_TRIPLE}-gfortran)
endif()

set(CMAKE_EXE_LINKER_FLAGS_INIT "-static")

# Libraries and headers come from the toolchain tree; programs from the host.
set(CMAKE_FIND_ROOT_PATH
    ${RISCV_TOOLCHAIN_PREFIX}
    ${RISCV_TOOLCHAIN_PREFIX}/${RISCV_TARGET_TRIPLE}
    ${RISCV_TOOLCHAIN_PREFIX}/sysroot
)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

find_program(QEMU_RISCV64_EXECUTABLE qemu-riscv64-static)
if(QEMU_RISCV64_EXECUTABLE)
    set(CMAKE_CROSSCOMPILING_EMULATOR ${QEMU_RISCV64_EXECUTABLE})
endif()
