# --------------------------------------------------------------------------------------------------
# SPDX-FileCopyrightText: juFFTe developers
# SPDX-License-Identifier: Apache-2.0
# --------------------------------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.15)
project(JUFFTE LANGUAGES C Fortran)

include(GNUInstallDirs)

# =========================
# Options
# =========================
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
option(WITHSPRL "Build with Spiral backend" OFF)
option(WITHSVE "Build with SVE backend" OFF)
option(WITHRVV "Build with RVV backend" OFF)
option(WITH_REFERENCE_FFTW "Build the comparisons against a reference FFTW" OFF)

# =========================
# Validate options
# =========================
if(WITHSVE AND NOT WITHSPRL)
    message(WARNING "WITHSVE requires WITHSPRL. Setting WITHSPRL=ON.")
    set(WITHSPRL ON)
endif()

if(WITHRVV AND NOT WITHSPRL)
    message(WARNING "WITHRVV requires WITHSPRL. Setting WITHSPRL=ON.")
    set(WITHSPRL ON)
endif()

# FFTW is optional, used only by the benchmark comparison. No FindFFTW module exists.
if(WITH_REFERENCE_FFTW)
    find_package(PkgConfig QUIET)
    if(PkgConfig_FOUND)
        pkg_check_modules(FFTW IMPORTED_TARGET fftw3)
    else()
        message(WARNING "pkg-config not found; cannot locate FFTW.")
    endif()

    # fftw3_omp ships without a .pc file on most distros.
    find_library(FFTW_OMP_LIBRARY
        NAMES fftw3_omp fftw3_threads
        HINTS ${FFTW_LIBRARY_DIRS} ${FFTW_LIBDIR}
    )

    if(FFTW_FOUND AND FFTW_OMP_LIBRARY)
        message(STATUS "FFTW found (${FFTW_VERSION}): enabling FFTW support")
        message(STATUS "FFTW threading library: ${FFTW_OMP_LIBRARY}")
    elseif(FFTW_FOUND)
        message(WARNING "FFTW found but neither fftw3_omp nor fftw3_threads was; "
                        "FFTW support will be disabled.")
        set(WITH_REFERENCE_FFTW OFF)
    else()
        message(WARNING "FFTW not found. FFTW support will be disabled.")
        set(WITH_REFERENCE_FFTW OFF)
    endif()
else()
    set(WITH_REFERENCE_FFTW OFF)
endif()

# =========================
# Set build type
# =========================
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

# Compiler info
message(STATUS "C Compiler: ${CMAKE_C_COMPILER}")
message(STATUS "Fortran Compiler: ${CMAKE_Fortran_COMPILER}")
message(STATUS "CMake Generator: ${CMAKE_GENERATOR}")

set(CMAKE_Fortran_FLAGS_DEBUG "-O0 -g")
set(CMAKE_Fortran_FLAGS_RELEASE "-O3 -g")
set(CMAKE_C_FLAGS_DEBUG "-O0 -g")
set(CMAKE_C_FLAGS_RELEASE "-O3 -g")

# =========================
# Detect architecture and CPU features
# =========================
# ARCH may be set on the command line; a vector backend pins it to its own ISA.
set(ARCH "" CACHE STRING "Target architecture (default: CMAKE_SYSTEM_PROCESSOR)")

if(WITHRVV)
    set(ARCH "riscv64")
elseif(WITHSVE)
    set(ARCH "aarch64")
elseif(NOT ARCH)
    set(ARCH "${CMAKE_SYSTEM_PROCESSOR}")
endif()

string(TOLOWER "${ARCH}" ARCH)

if(ARCH MATCHES "x86_64|amd64")
  set(IS_X86 TRUE)
elseif(ARCH MATCHES "aarch64|arm64")
  set(IS_ARM TRUE)
elseif(ARCH MATCHES "riscv64")
  set(IS_RISCV TRUE)
endif()

message(STATUS "Target architecture: ${ARCH}")

# Static executables cannot link .so files (e.g. libgomp.so); prefer archives.
if(CMAKE_EXE_LINKER_FLAGS MATCHES "-static")
    list(INSERT CMAKE_FIND_LIBRARY_SUFFIXES 0 ".a")
endif()

find_package(OpenMP)

# =========================
# Detect compiler-specific flags
# =========================
if(CMAKE_Fortran_COMPILER_ID MATCHES "Flang")
    set(CMAKE_Fortran_FLAGS "${CMAKE_Fortran_FLAGS} -Wno-ignored-directive -ffast-math -mepi")
elseif(CMAKE_Fortran_COMPILER_ID MATCHES "NVHPC")
    # Placeholder: add NVIDIA Fortran flags if needed
endif()

# =========================
# Source lists
# =========================
set(OBJ_COMMON
    ${CMAKE_CURRENT_SOURCE_DIR}/src/param.F90
    ${CMAKE_CURRENT_SOURCE_DIR}/src/utils_m.F90
    ${CMAKE_CURRENT_SOURCE_DIR}/src/factor_m.F90
    ${CMAKE_CURRENT_SOURCE_DIR}/src/kernel_m.F90
    ${CMAKE_CURRENT_SOURCE_DIR}/src/fft235_m.F90
)

set(OBJ_TRANSFORMS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/zfft1d_m.F90
    ${CMAKE_CURRENT_SOURCE_DIR}/src/zfft2d_m.F90
    ${CMAKE_CURRENT_SOURCE_DIR}/src/zfft3d_m.F90
    ${CMAKE_CURRENT_SOURCE_DIR}/src/dzfft2d_m.F90
    ${CMAKE_CURRENT_SOURCE_DIR}/src/zdfft2d_m.F90
    ${CMAKE_CURRENT_SOURCE_DIR}/src/dzfft3d_m.F90
    ${CMAKE_CURRENT_SOURCE_DIR}/src/zdfft3d_m.F90
    ${CMAKE_CURRENT_SOURCE_DIR}/src/juffte.F90
)

set(OBJ_STD  ${OBJ_COMMON} ${OBJ_TRANSFORMS})
set(OBJ_SPRL ${OBJ_COMMON} ${CMAKE_CURRENT_SOURCE_DIR}/src/fft235s_m.F90 ${OBJ_TRANSFORMS})

# =========================
# Conditional logic for SPIRAL / SVE / RVV
# =========================
if(WITHSPRL)
    add_definitions(-DSPRL)

    # TODO: only the RVV kernels are in the tree.
    if(WITHSVE)
        message(FATAL_ERROR "TODO: the SVE Spiral backend is not implemented yet. Use -DWITHRVV=ON.")
    elseif(NOT WITHRVV)
        message(FATAL_ERROR "TODO: the generic C Spiral backend is not implemented yet. Use -DWITHRVV=ON.")
    endif()

    # Resolve the variant BEFORE add_library(): it captures the source list, and
    # directory-level options only reach targets created afterwards.
    if(WITHSVE)
        set(SPRL_VARIANT   "sve")
        set(SPRL_PATH      "${CMAKE_CURRENT_SOURCE_DIR}/src/spiral/sve")
        set(SPRL_ARCH_FLAG "-march=armv8.2-a+sve")
    elseif(WITHRVV)
        set(SPRL_VARIANT   "rvv")
        set(SPRL_PATH      "${CMAKE_CURRENT_SOURCE_DIR}/src/spiral/rvv")
        set(SPRL_ARCH_FLAG "-march=rv64gcv")
    else()
        set(SPRL_VARIANT   "c")
        set(SPRL_PATH      "${CMAKE_CURRENT_SOURCE_DIR}/src/spiral/c")
        set(SPRL_ARCH_FLAG "")
    endif()

    file(GLOB SPRL_C_SOURCES CONFIGURE_DEPENDS "${SPRL_PATH}/*.c")
    message(STATUS "Enabling Spiral backend (${SPRL_VARIANT}) from ${SPRL_PATH}")

    set(JUFFTE_SOURCES ${OBJ_SPRL} ${SPRL_C_SOURCES})
else()
    set(JUFFTE_SOURCES ${OBJ_STD})
endif()

# FFTW compatibility layer; its symbols are juffte_-prefixed, so it can live here.
list(APPEND JUFFTE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/juffte_fftw.c)


# =========================
# Library
# =========================
# The library is always named juffte, whichever backend is compiled in.
if(BUILD_SHARED_LIBS)
    set(LIB_TARGET juffte_shared)
    add_library(${LIB_TARGET} SHARED ${JUFFTE_SOURCES})
    target_link_libraries(${LIB_TARGET} PUBLIC m)
    set_target_properties(${LIB_TARGET} PROPERTIES OUTPUT_NAME juffte)
else()
    set(LIB_TARGET juffte)
    add_library(${LIB_TARGET} STATIC ${JUFFTE_SOURCES})
endif()

# Keep the library's .mod files apart from the tests' and benchmark's.
set(JUFFTE_MODULE_DIR ${CMAKE_CURRENT_BINARY_DIR}/modules)
set_target_properties(${LIB_TARGET} PROPERTIES Fortran_MODULE_DIRECTORY ${JUFFTE_MODULE_DIR})

target_include_directories(${LIB_TARGET} PUBLIC
    $<BUILD_INTERFACE:${JUFFTE_MODULE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

if(OpenMP_Fortran_FOUND)
    target_link_libraries(${LIB_TARGET} PUBLIC OpenMP::OpenMP_Fortran)
endif()
if(OpenMP_C_FOUND)
    # Compile-only: OpenMP::OpenMP_C in the link interface would force every
    # consumer to enable the C language. The runtime comes in with the Fortran target.
    separate_arguments(JUFFTE_OMP_C_FLAGS NATIVE_COMMAND "${OpenMP_C_FLAGS}")
    target_compile_options(${LIB_TARGET} PRIVATE
        $<$<COMPILE_LANGUAGE:C>:${JUFFTE_OMP_C_FLAGS}>)
endif()

# The Spiral kernels use ISA intrinsics and need the matching -march.
if(SPRL_ARCH_FLAG
   AND CMAKE_C_COMPILER_ID MATCHES "^(GNU|Clang|AppleClang)$"
   AND CMAKE_Fortran_COMPILER_ID MATCHES "^(GNU|Flang|LLVMFlang)$")
    target_compile_options(${LIB_TARGET} PRIVATE ${SPRL_ARCH_FLAG})
endif()

# =========================
# Install
# =========================
install(TARGETS ${LIB_TARGET}
    EXPORT juffteTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(DIRECTORY ${JUFFTE_MODULE_DIR}/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILES_MATCHING PATTERN "*.mod"
)

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/juffte.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(EXPORT juffteTargets
    FILE juffteTargets.cmake
    NAMESPACE juffte::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/juffte
)

include(CMakePackageConfigHelpers)
configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/juffteConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/juffteConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/juffte
)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/juffteConfig.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/juffte
)

# =========================
# Benchmark
# =========================
add_executable(fftbench
    ${CMAKE_CURRENT_SOURCE_DIR}/benchmark/bench_utils_m.F90
    ${CMAKE_CURRENT_SOURCE_DIR}/benchmark/fftbench.F90
)
target_link_libraries(fftbench PRIVATE ${LIB_TARGET})

if(WITH_REFERENCE_FFTW AND FFTW_FOUND)
    target_sources(fftbench PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/benchmark/fftw_m.F90)
    target_link_libraries(fftbench PRIVATE ${FFTW_OMP_LIBRARY} PkgConfig::FFTW)
    target_compile_definitions(fftbench PRIVATE USE_REFERENCE_FFTW)
    message(STATUS "FFTW enabled for benchmark")
endif()

# =========================
# Tests
# =========================
enable_testing()

set(JUFFTE_TEST_TARGETS "")
set(JUFFTE_TESTS "")

# Lengths the round-trip tests run at. Length 2 alone never needs a second radix-3
# stage (9), radix 5 (100), every radix (120) or a non-square shape, which is how the
# single-precision fft3b constant fixed in e253422 went unnoticed. The six-step branch
# (1-D n > 174762) is not covered yet: it crashes at the default 8 MB stack, and its
# out-of-place backward and 1-D r2c paths are broken.
set(JUFFTE_SIZES_1D "2" "9" "96" "100" "120" "1024")
set(JUFFTE_SIZES_2D "2 2" "9 96" "96 64" "120 100" "256 256")
set(JUFFTE_SIZES_3D "2 2 2" "9 16 20" "12 18 20" "32 32 32")

# One CTest case per size, named <target>_<size>, e.g. test2d_9x96. Each size runs in
# its own process: initialising a second size in one process hits the single-plan limit.
function(juffte_add_test_sizes target)
    foreach(size IN LISTS ARGN)
        string(REPLACE " " ";" args "${size}")
        string(REPLACE " " "x" tag "${size}")
        add_test(NAME ${target}_${tag} COMMAND ${target} ${args})
        list(APPEND JUFFTE_TESTS ${target}_${tag})
    endforeach()
    set(JUFFTE_TESTS ${JUFFTE_TESTS} PARENT_SCOPE)
endfunction()

# C tests; juffte.h comes from the library's public include directories.
function(juffte_add_c_test name source)
    add_executable(${name} ${CMAKE_CURRENT_SOURCE_DIR}/${source})
    target_link_libraries(${name} PRIVATE ${LIB_TARGET} m)
    juffte_add_test_sizes(${name} ${ARGN})
    set(JUFFTE_TESTS ${JUFFTE_TESTS} PARENT_SCOPE)
    set(JUFFTE_TEST_TARGETS ${JUFFTE_TEST_TARGETS} ${name} PARENT_SCOPE)
endfunction()

# These exercise the FFTW shim, which is always built into the library.
function(juffte_add_fftw_test name source)
    juffte_add_c_test(${name} ${source} ${ARGN})
    if(CMAKE_Fortran_COMPILER_ID STREQUAL "GNU")
        target_link_libraries(${name} PRIVATE gfortran)
    endif()
    set(JUFFTE_TESTS ${JUFFTE_TESTS} PARENT_SCOPE)
    set(JUFFTE_TEST_TARGETS ${JUFFTE_TEST_TARGETS} PARENT_SCOPE)
endfunction()

juffte_add_c_test(ctest1d  ctests/test1d.c  ${JUFFTE_SIZES_1D})
juffte_add_c_test(ctest2d  ctests/test2d.c  ${JUFFTE_SIZES_2D})
juffte_add_c_test(ctest3d  ctests/test3d.c  ${JUFFTE_SIZES_3D})
juffte_add_c_test(crtest1d ctests/rtest1d.c ${JUFFTE_SIZES_1D})
juffte_add_c_test(crtest2d ctests/rtest2d.c ${JUFFTE_SIZES_2D})
juffte_add_c_test(crtest3d ctests/rtest3d.c ${JUFFTE_SIZES_3D})

# These print their output but check nothing, so more sizes would add no coverage.
juffte_add_fftw_test(fftw-test   ctests/fftw-test.c   "2")
juffte_add_fftw_test(fftw-test2d ctests/fftw-test2d.c "2 2")
juffte_add_fftw_test(fftw-test3d ctests/fftw-test3d.c "2 2 2")

# Fortran tests
add_library(test_utils_m_obj OBJECT ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_utils_m.F90)

function(juffte_add_fortran_test name source)
    add_executable(${name}
        ${CMAKE_CURRENT_SOURCE_DIR}/${source}
        $<TARGET_OBJECTS:test_utils_m_obj>
    )
    target_link_libraries(${name} PRIVATE ${LIB_TARGET})
    juffte_add_test_sizes(${name} ${ARGN})
    set(JUFFTE_TESTS ${JUFFTE_TESTS} PARENT_SCOPE)
    set(JUFFTE_TEST_TARGETS ${JUFFTE_TEST_TARGETS} ${name} PARENT_SCOPE)
endfunction()

juffte_add_fortran_test(test1d         tests/test1d.F90         ${JUFFTE_SIZES_1D})
juffte_add_fortran_test(test1d-out     tests/test1d-out.F90     ${JUFFTE_SIZES_1D})
juffte_add_fortran_test(test1dni       tests/test1dni.F90       ${JUFFTE_SIZES_1D})
juffte_add_fortran_test(test1d-fftwint tests/test1d-fftwint.F90 ${JUFFTE_SIZES_1D})
juffte_add_fortran_test(test2d         tests/test2d.F90         ${JUFFTE_SIZES_2D})
juffte_add_fortran_test(test2d-out     tests/test2d-out.F90     ${JUFFTE_SIZES_2D})
juffte_add_fortran_test(test2d-fftwint tests/test2d-fftwint.F90 ${JUFFTE_SIZES_2D})
juffte_add_fortran_test(test3d         tests/test3d.F90         ${JUFFTE_SIZES_3D})
juffte_add_fortran_test(test3d-out     tests/test3d-out.F90     ${JUFFTE_SIZES_3D})
juffte_add_fortran_test(test3d-fftwint tests/test3d-fftwint.F90 ${JUFFTE_SIZES_3D})
juffte_add_fortran_test(rtest1d        tests/rtest1d.F90        ${JUFFTE_SIZES_1D})
juffte_add_fortran_test(rtest2d        tests/rtest2d.F90        ${JUFFTE_SIZES_2D})
juffte_add_fortran_test(rtest3d        tests/rtest3d.F90        ${JUFFTE_SIZES_3D})

# Forward transform against a direct DFT, element by element. Catches what a round
# trip cancels: a wrong sign convention, a consistent scaling error.
add_executable(accuracy ${CMAKE_CURRENT_SOURCE_DIR}/tests/accuracy.F90)
target_link_libraries(accuracy PRIVATE ${LIB_TARGET})
juffte_add_test_sizes(accuracy ${JUFFTE_SIZES_1D} ${JUFFTE_SIZES_2D} ${JUFFTE_SIZES_3D})
list(APPEND JUFFTE_TEST_TARGETS accuracy)

# The tests exit non-zero on failure. Do not add PASS_REGULAR_EXPRESSION: it makes
# CTest ignore the exit status and report failures as passes.
set_tests_properties(${JUFFTE_TESTS} PROPERTIES FAIL_REGULAR_EXPRESSION "FAIL")

add_custom_target(run_tests
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Running tests:"
    DEPENDS ${JUFFTE_TEST_TARGETS}
)

# =========================
# Summary
# =========================
message(STATUS "")
message(STATUS "------------------------------------------------------------")
message(STATUS " juFFTe Configuration Summary")
message(STATUS "------------------------------------------------------------")
message(STATUS "  Build type:        ${CMAKE_BUILD_TYPE}")
message(STATUS "  Architecture:      ${ARCH}")
message(STATUS "  Build shared libs: ${BUILD_SHARED_LIBS}")
message(STATUS "  With SPIRAL:       ${WITHSPRL}")
message(STATUS "  With SVE:          ${WITHSVE}")
message(STATUS "  With RVV:          ${WITHRVV}")
message(STATUS "  Reference FFTW:    ${WITH_REFERENCE_FFTW}")
message(STATUS "  Fortran compiler:  ${CMAKE_Fortran_COMPILER}")
message(STATUS "  OpenMP:            ${OpenMP_Fortran_FOUND}")
message(STATUS "  Cross compiling:   ${CMAKE_CROSSCOMPILING}")
message(STATUS "  Install prefix:    ${CMAKE_INSTALL_PREFIX}")
message(STATUS "------------------------------------------------------------")
