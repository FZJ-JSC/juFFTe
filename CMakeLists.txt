# --------------------------------------------------------------------------------------------------
# SPDX-FileCopyrightText: juFFTe developers
# SPDX-License-Identifier: Apache-2.0
# --------------------------------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.15)
project(JUFFTE LANGUAGES C CXX Fortran)

# =========================
# Options
# =========================
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
option(WITHSPRL "Build with Spiral backend" OFF)
option(WITHSVE "Build with SVE backend" OFF)
option(WITHRVV "Build with RVV backend" OFF)
option(WITHFFTW "Build with FFTW support" OFF)

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

if(WITHFFTW)
    find_package(FFTW)
    if(FFTW_FOUND)
        message(STATUS "FFTW found: enabling FFTW support")
    else()
        message(WARNING "FFTW not found. FFTW support will be disabled.")
        set(WITHFFTW OFF)
    endif()
else()
    set(WITHFFTW OFF)
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
string(TOLOWER "${CMAKE_SYSTEM_PROCESSOR}" ARCH)

if(ARCH MATCHES "x86_64|amd64")
  set(IS_X86 TRUE)
elseif(ARCH MATCHES "aarch64|arm64")
  set(IS_ARM TRUE)
elseif(ARCH MATCHES "riscv64")
  set(IS_RISCV TRUE)
endif()

message(STATUS "Detected architecture: ${ARCH}")

# Enable OpenMP if available
find_package(OpenMP)
if(OpenMP_Fortran_FOUND)
    set(CMAKE_Fortran_FLAGS "${CMAKE_Fortran_FLAGS} ${OpenMP_Fortran_FLAGS}")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    message(STATUS "OpenMP found: enabling parallel builds")
endif()

# =========================
# Detect compiler-specific flags
# =========================
if(CMAKE_Fortran_COMPILER_ID MATCHES "Intel")
    set(CMAKE_Fortran_FLAGS "${CMAKE_Fortran_FLAGS} -qopenmp")
elseif(CMAKE_Fortran_COMPILER_ID MATCHES "Flang")
    set(CMAKE_Fortran_FLAGS "${CMAKE_Fortran_FLAGS} -Wno-ignored-directive -ffast-math -mepi")
elseif(CMAKE_Fortran_COMPILER_ID MATCHES "NVHPC")
    # Placeholder: add NVIDIA Fortran flags if needed
endif()

# =========================
# Source lists
# =========================
set(OBJ_COMMON
    ${CMAKE_SOURCE_DIR}/src/param.F90
    ${CMAKE_SOURCE_DIR}/src/utils_m.F90
    ${CMAKE_SOURCE_DIR}/src/factor_m.F90
    ${CMAKE_SOURCE_DIR}/src/kernel_m.F90
    ${CMAKE_SOURCE_DIR}/src/fft235_m.F90
)

set(OBJ_STD
    ${OBJ_COMMON}
    ${CMAKE_SOURCE_DIR}/src/zfft1d_m.F90
    ${CMAKE_SOURCE_DIR}/src/zfft2d_m.F90
    ${CMAKE_SOURCE_DIR}/src/zfft3d_m.F90
    ${CMAKE_SOURCE_DIR}/src/dzfft2d_m.F90
    ${CMAKE_SOURCE_DIR}/src/zdfft2d_m.F90
    ${CMAKE_SOURCE_DIR}/src/dzfft3d_m.F90
    ${CMAKE_SOURCE_DIR}/src/zdfft3d_m.F90
    ${CMAKE_SOURCE_DIR}/src/juffte.F90
)

set(OBJ_SPRL
    ${OBJ_COMMON}
    ${CMAKE_SOURCE_DIR}/src/fft235s_m.F90
    ${CMAKE_SOURCE_DIR}/src/zfft1d_m.F90
    ${CMAKE_SOURCE_DIR}/src/zfft2d_m.F90
    ${CMAKE_SOURCE_DIR}/src/zfft3d_m.F90
    ${CMAKE_SOURCE_DIR}/src/dzfft2d_m.F90
    ${CMAKE_SOURCE_DIR}/src/zdfft2d_m.F90
    ${CMAKE_SOURCE_DIR}/src/dzfft3d_m.F90
    ${CMAKE_SOURCE_DIR}/src/zdfft3d_m.F90
    ${CMAKE_SOURCE_DIR}/src/juffte.F90
)

# =========================
# Conditional logic for SPIRAL / SVE / RVV
# =========================
if(WITHSPRL)
    add_definitions(-DSPRL)
    set(SPRL_PATH "${CMAKE_SOURCE_DIR}/src/spiral/c")
    file(GLOB SPRL_C_SOURCES "${SPRL_PATH}/*.c")
    
    if(BUILD_SHARED_LIBS)
        add_library(jufftesp_shared SHARED ${OBJ_SPRL} ${SPRL_C_SOURCES})
        target_include_directories(jufftesp_shared PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
        target_link_libraries(jufftesp_shared PUBLIC m)
        set_target_properties(jufftesp_shared PROPERTIES OUTPUT_NAME jufftesp)
    else()
        add_library(jufftesp STATIC ${OBJ_SPRL} ${SPRL_C_SOURCES})
        target_include_directories(jufftesp PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
    endif()
    message(STATUS "Enabling Spiral backend")
    
    if(WITHSVE)
        set(SPRL_PATH "${CMAKE_SOURCE_DIR}/src/spiral/sve")
        file(GLOB SPRL_C_SOURCES "${SPRL_PATH}/*.c")
        message(STATUS "Enabling SVE backend")
        if (CMAKE_C_COMPILER_ID STREQUAL "GNU" AND CMAKE_FORTRAN_COMPILER_ID STREQUAL "GNU")
            add_compile_options(-march=armv8.2-a+sve)
        endif()
    elseif(WITHRVV)
        set(SPRL_PATH "${CMAKE_SOURCE_DIR}/src/spiral/rvv")
        file(GLOB SPRL_C_SOURCES "${SPRL_PATH}/*.c")
        message(STATUS "Enabling RVV backend")
        if (CMAKE_C_COMPILER_ID STREQUAL "GNU" AND CMAKE_FORTRAN_COMPILER_ID STREQUAL "GNU")
            add_compile_options(-march=rv64gcv)
        endif()
    endif()

    if(WITHSPRL)
        if(WITHSVE)
            if(NOT EXISTS "${CMAKE_SOURCE_DIR}/src/spiral/sve/dft2sve_a.c")
                message(FATAL_ERROR "No spiral file found for architecture (sve)")
            endif()
        elseif(WITHRVV)
            if(NOT EXISTS "${CMAKE_SOURCE_DIR}/src/spiral/rvv/dft2rvv_a.c")
                message(FATAL_ERROR "No spiral file found for architecture (rvv)")
            endif()
        else()
            if(NOT EXISTS "${CMAKE_SOURCE_DIR}/src/spiral/c/dft2_a.c")
                message(FATAL_ERROR "No spiral file found for architecture (c)")
            endif()
        endif()
    endif()
else()  
    # Default build
    if(BUILD_SHARED_LIBS)
        add_library(juffte_shared SHARED ${OBJ_STD})
        target_include_directories(juffte_shared PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
        target_link_libraries(juffte_shared PUBLIC m)
        set_target_properties(juffte_shared PROPERTIES OUTPUT_NAME juffte)
    else()
        add_library(juffte STATIC ${OBJ_STD})
        target_include_directories(juffte PUBLIC ${CMAKE_BINARY_DIR})
    endif()
endif()

# =========================
# Install library first
# =========================
include(GNUInstallDirs)

if(WITHSPRL)
    if(BUILD_SHARED_LIBS)
        install(TARGETS jufftesp_shared
            ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        )
    else()
        install(TARGETS jufftesp
            ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        )
    endif()
else()
    if(BUILD_SHARED_LIBS)
        install(TARGETS juffte_shared
            ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        )
    else()
        install(TARGETS juffte
            ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        )
    endif()
endif()

install(DIRECTORY ${CMAKE_BINARY_DIR}/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILES_MATCHING PATTERN "*.mod"
)

# =========================
# Benchmark
# =========================
add_executable(fftbench ${CMAKE_SOURCE_DIR}/benchmark/bench_utils_m.F90 ${CMAKE_SOURCE_DIR}/benchmark/fftbench.F90)

if(WITHSPRL)
    set(LIB_NAME jufftesp)
else()
    set(LIB_NAME juffte)
endif()

if(BUILD_SHARED_LIBS)
    set(LIB_TARGET "${LIB_NAME}_shared")
else()
    set(LIB_TARGET "${LIB_NAME}")
endif()

target_link_libraries(fftbench PRIVATE ${LIB_TARGET})

if(WITHFFTW AND FFTW_FOUND)
    target_sources(fftbench PRIVATE ${CMAKE_SOURCE_DIR}/benchmark/fftw_m.F90)
    target_include_directories(fftbench PRIVATE ${FFTW_INCLUDE_DIR})
    target_link_libraries(fftbench PRIVATE FFTW::fftw3 FFTW::fftw3_omp)
    target_compile_definitions(fftbench PRIVATE FFTW_ENABLED)
    message(STATUS "FFTW enabled for benchmark")
endif()

# =========================
# C tests
# =========================
add_executable(ctest1d ${CMAKE_SOURCE_DIR}/ctests/test1d.c)
target_link_libraries(ctest1d PRIVATE ${LIB_TARGET})

add_executable(ctest2d ${CMAKE_SOURCE_DIR}/ctests/test2d.c)
target_link_libraries(ctest2d PRIVATE ${LIB_TARGET})

add_executable(ctest3d ${CMAKE_SOURCE_DIR}/ctests/test3d.c)
target_link_libraries(ctest3d PRIVATE ${LIB_TARGET})

add_executable(crtest2d ${CMAKE_SOURCE_DIR}/ctests/rtest2d.c)
target_link_libraries(crtest2d PRIVATE ${LIB_TARGET})

add_executable(crtest3d ${CMAKE_SOURCE_DIR}/ctests/rtest3d.c)
target_link_libraries(crtest3d PRIVATE ${LIB_TARGET})

add_executable(fftw-test ${CMAKE_SOURCE_DIR}/ctests/fftw-test.c)
target_include_directories(fftw-test PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_compile_definitions(fftw-test PRIVATE FFTW)
target_link_libraries(fftw-test PRIVATE ${LIB_TARGET} m gfortran)

# =========================
# Fortran tests
# =========================
add_library(test_utils_m_obj OBJECT ${CMAKE_SOURCE_DIR}/tests/test_utils_m.F90)

add_executable(test1d ${CMAKE_SOURCE_DIR}/tests/test1d.F90 $<TARGET_OBJECTS:test_utils_m_obj>)
target_link_libraries(test1d PRIVATE ${LIB_TARGET})

add_executable(test1d-out ${CMAKE_SOURCE_DIR}/tests/test1d-out.F90 $<TARGET_OBJECTS:test_utils_m_obj>)
target_link_libraries(test1d-out PRIVATE ${LIB_TARGET})

add_executable(test1d-fftwint ${CMAKE_SOURCE_DIR}/tests/test1d-fftwint.F90 $<TARGET_OBJECTS:test_utils_m_obj>)
target_link_libraries(test1d-fftwint PRIVATE ${LIB_TARGET})

add_executable(test1dni ${CMAKE_SOURCE_DIR}/tests/test1dni.F90 $<TARGET_OBJECTS:test_utils_m_obj>)
target_link_libraries(test1dni PRIVATE ${LIB_TARGET})

add_executable(test2d ${CMAKE_SOURCE_DIR}/tests/test2d.F90 $<TARGET_OBJECTS:test_utils_m_obj>)
target_link_libraries(test2d PRIVATE ${LIB_TARGET})

add_executable(test3d ${CMAKE_SOURCE_DIR}/tests/test3d.F90 $<TARGET_OBJECTS:test_utils_m_obj>)
target_link_libraries(test3d PRIVATE ${LIB_TARGET})

add_executable(rtest1d ${CMAKE_SOURCE_DIR}/tests/rtest1d.F90 $<TARGET_OBJECTS:test_utils_m_obj>)
target_link_libraries(rtest1d PRIVATE ${LIB_TARGET})

add_executable(rtest2d ${CMAKE_SOURCE_DIR}/tests/rtest2d.F90 $<TARGET_OBJECTS:test_utils_m_obj>)
target_link_libraries(rtest2d PRIVATE ${LIB_TARGET})

add_executable(rtest3d ${CMAKE_SOURCE_DIR}/tests/rtest3d.F90 $<TARGET_OBJECTS:test_utils_m_obj>)
target_link_libraries(rtest3d PRIVATE ${LIB_TARGET})

# =========================
# Test target
# =========================
enable_testing()

# C tests
add_test(NAME ctest1d COMMAND ${CMAKE_BINARY_DIR}/ctest1d 2)
add_test(NAME ctest2d COMMAND ${CMAKE_BINARY_DIR}/ctest2d 2 2)
add_test(NAME ctest3d COMMAND ${CMAKE_BINARY_DIR}/ctest3d 2 2 2)
add_test(NAME crtest2d COMMAND ${CMAKE_BINARY_DIR}/crtest2d 2 2)
add_test(NAME crtest3d COMMAND ${CMAKE_BINARY_DIR}/crtest3d 2 2 2)
add_test(NAME fftw-test COMMAND ${CMAKE_BINARY_DIR}/fftw-test 2)

# Fortran tests
add_test(NAME test1d COMMAND ${CMAKE_BINARY_DIR}/test1d 2)
add_test(NAME test1d_out COMMAND ${CMAKE_BINARY_DIR}/test1d-out 2)
add_test(NAME test1d-fftwint COMMAND ${CMAKE_BINARY_DIR}/test1d-fftwint 2)
add_test(NAME test1dni COMMAND ${CMAKE_BINARY_DIR}/test1dni 2)
add_test(NAME test2d COMMAND ${CMAKE_BINARY_DIR}/test2d 2 2)
add_test(NAME test3d COMMAND ${CMAKE_BINARY_DIR}/test3d 2 2 2)
add_test(NAME rtest1d COMMAND ${CMAKE_BINARY_DIR}/rtest1d 2)
add_test(NAME rtest2d COMMAND ${CMAKE_BINARY_DIR}/rtest2d 2 2)
add_test(NAME rtest3d COMMAND ${CMAKE_BINARY_DIR}/rtest3d 2 2 2)

set(CTEST_RESOURCE_SPEC_FILE "")
set_tests_properties(
    ctest1d ctest2d ctest3d crtest2d crtest3d fftw-test
    test1d test1d_out test1d-fftwint test1dni test2d test3d
    rtest1d rtest2d rtest3d
    PROPERTIES
    PASS_REGULAR_EXPRESSION "."
)

add_custom_target(run_tests
    COMMAND bash -c 'ctest --output-on-failure'
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running tests:"
    DEPENDS ctest1d ctest2d ctest3d crtest2d crtest3d fftw-test
           test1d test1d_out test1d-fftwint test1dni test2d test3d
           rtest1d rtest2d rtest3d
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
message(STATUS "  With FFTW:         ${WITHFFTW}")
message(STATUS "  Fortran compiler:  ${CMAKE_Fortran_COMPILER}")
message(STATUS "  OpenMP:            ${OpenMP_Fortran_FOUND}")
message(STATUS "  Install prefix:    ${CMAKE_INSTALL_PREFIX}")
message(STATUS "------------------------------------------------------------")
