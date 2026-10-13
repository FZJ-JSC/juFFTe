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
option(BUILD_EXAMPLES "Build the example programs in examples/" ON)
option(THOROUGH_TESTS "Test many more sizes (tests/sizes.mk)" OFF)

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

# FFTW is optional: the tests use it as their reference, and the benchmark compares
# against it. No FindFFTW module exists.
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

    if(FFTW_FOUND)
        message(STATUS "FFTW found (${FFTW_VERSION}): enabling FFTW support")
        if(FFTW_OMP_LIBRARY)
            message(STATUS "FFTW threading library: ${FFTW_OMP_LIBRARY}")
        else()
            message(WARNING "Neither fftw3_omp nor fftw3_threads found; "
                            "the benchmark will not compare against FFTW.")
        endif()
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

if(WITH_REFERENCE_FFTW AND FFTW_OMP_LIBRARY)
    target_sources(fftbench PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/benchmark/fftw_m.F90)
    target_link_libraries(fftbench PRIVATE ${FFTW_OMP_LIBRARY} PkgConfig::FFTW)
    target_compile_definitions(fftbench PRIVATE USE_REFERENCE_FFTW)
    message(STATUS "FFTW enabled for benchmark")
endif()

# =========================
# Tests
# =========================
enable_testing()

# One program per language, tests/c/juffte_test.c and tests/fortran/juffte_test.F90,
# checks one transform per run against FFTW (WITH_REFERENCE_FFTW) or else a direct DFT.
add_executable(juffte_test_c ${CMAKE_CURRENT_SOURCE_DIR}/tests/c/juffte_test.c)
target_link_libraries(juffte_test_c PRIVATE ${LIB_TARGET} m)
if(CMAKE_Fortran_COMPILER_ID STREQUAL "GNU")
    target_link_libraries(juffte_test_c PRIVATE gfortran)
endif()

add_executable(juffte_test_f ${CMAKE_CURRENT_SOURCE_DIR}/tests/fortran/juffte_test.F90)
target_link_libraries(juffte_test_f PRIVATE ${LIB_TARGET})

if(WITH_REFERENCE_FFTW)
    foreach(t juffte_test_c juffte_test_f)
        target_link_libraries(${t} PRIVATE PkgConfig::FFTW)
        target_compile_definitions(${t} PRIVATE USE_REFERENCE_FFTW)
    endforeach()
endif()

# The size lists live in tests/sizes.mk, which the Makefiles in tests/c and tests/fortran
# include: JUFFTE_SIZES_1D ... JUFFTE_THOROUGH_3D, one list entry per size.
set(JUFFTE_SIZES_FILE ${CMAKE_CURRENT_SOURCE_DIR}/tests/sizes.mk)
set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS ${JUFFTE_SIZES_FILE})
file(READ ${JUFFTE_SIZES_FILE} sizes_mk)
string(REPLACE "\\\n" " " sizes_mk "${sizes_mk}")
string(REGEX MATCHALL "\n[A-Z0-9_]+ *=[^\n]*" size_lines "${sizes_mk}")
foreach(line IN LISTS size_lines)
    string(REGEX MATCH "([A-Z0-9_]+) *=(.*)" _ "${line}")
    set(name ${CMAKE_MATCH_1})
    string(REGEX MATCHALL "\"[^\"]*\"|[0-9]+" entries "${CMAKE_MATCH_2}")
    string(REPLACE "\"" "" entries "${entries}")
    set(JUFFTE_${name} ${entries})
endforeach()

# One case per process, named like f_real_bw_9x96 or c_complex_fw_1024_fftw: a second
# size in one process hits the single-plan limit. Without FFTW, sizes with N >= 4000
# have no reference and are reported as skipped (exit status 77). The thorough sizes
# carry the label "thorough" (ctest -L thorough / -LE thorough).
function(juffte_add_test lang type dir size label)
    string(REPLACE " " ";" n "${size}")
    string(REPLACE " " "x" tag "${size}")
    set(name ${lang}_${type}_${dir}_${tag})
    if(ARGN)
        list(GET ARGN 1 api)
        set(name ${name}_${api})
    endif()
    add_test(NAME ${name} COMMAND juffte_test_${lang} -t ${type} -d ${dir} ${ARGN} ${n})
    # Do not add PASS_REGULAR_EXPRESSION: it makes CTest ignore the exit status and
    # report failures as passes.
    set_tests_properties(${name} PROPERTIES SKIP_RETURN_CODE 77 FAIL_REGULAR_EXPRESSION "FAIL"
                                            LABELS ${label})
endfunction()

# Every case for one size: complex, real and the FFTW layer from both languages, and
# fft_init/fft_execute in 1-D. COMPLEX_ONLY leaves out the real transforms.
function(juffte_add_size size label)
    string(REPLACE " " ";" n "${size}")
    list(LENGTH n dim)
    foreach(lang c f)
        foreach(dir fw bw)
            juffte_add_test(${lang} complex ${dir} "${size}" ${label})
            if(NOT "${ARGN}" STREQUAL "COMPLEX_ONLY")
                juffte_add_test(${lang} real ${dir} "${size}" ${label})
            endif()
            juffte_add_test(${lang} complex ${dir} "${size}" ${label} -a fftw)
            if(lang STREQUAL "f" AND dim EQUAL 1)
                juffte_add_test(${lang} complex ${dir} "${size}" ${label} -a simple)
            endif()
        endforeach()
    endforeach()
endfunction()

set(kinds SIZES)
if(THOROUGH_TESTS)
    list(APPEND kinds THOROUGH)
endif()
foreach(kind IN LISTS kinds)
    string(TOLOWER ${kind} label)
    foreach(size IN LISTS JUFFTE_${kind}_1D JUFFTE_${kind}_2D JUFFTE_${kind}_3D)
        juffte_add_size("${size}" ${label})
    endforeach()
    foreach(size IN LISTS JUFFTE_${kind}_SIXSTEP)
        juffte_add_size("${size}" ${label} COMPLEX_ONLY)
    endforeach()
endforeach()

# A length the library cannot handle must stop it with a message. Here, and only here,
# the output decides: the exit status is that of the library's error stop.
foreach(lang c f)
    add_test(NAME ${lang}_rejects_length_14 COMMAND juffte_test_${lang} 14)
    set_tests_properties(${lang}_rejects_length_14 PROPERTIES
        PASS_REGULAR_EXPRESSION "length 14 is not a product of 2, 3 and 5")
endforeach()

add_custom_target(run_tests
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Running tests:"
    DEPENDS juffte_test_c juffte_test_f
)

# =========================
# Examples
# =========================
# C and Fortran examples share names, so the targets are prefixed and the programs go
# to examples/c and examples/fortran in the build tree.
if(BUILD_EXAMPLES)
    foreach(ex test1d test2d test3d rtest1d rtest2d rtest3d fftw-test fftw-test2d fftw-test3d)
        add_executable(example_c_${ex} ${CMAKE_CURRENT_SOURCE_DIR}/examples/c/${ex}.c)
        target_link_libraries(example_c_${ex} PRIVATE ${LIB_TARGET} m)
        if(CMAKE_Fortran_COMPILER_ID STREQUAL "GNU")
            target_link_libraries(example_c_${ex} PRIVATE gfortran)
        endif()
        set_target_properties(example_c_${ex} PROPERTIES OUTPUT_NAME ${ex}
            RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/examples/c)
    endforeach()

    add_library(example_utils OBJECT ${CMAKE_CURRENT_SOURCE_DIR}/examples/fortran/test_utils_m.F90)
    foreach(ex test1d test1d-out test1dni test1d-fftwint test2d test2d-out test2d-fftwint
               test3d test3d-out test3d-fftwint rtest1d rtest2d rtest3d)
        add_executable(example_f_${ex} ${CMAKE_CURRENT_SOURCE_DIR}/examples/fortran/${ex}.F90)
        target_link_libraries(example_f_${ex} PRIVATE example_utils ${LIB_TARGET})
        set_target_properties(example_f_${ex} PROPERTIES OUTPUT_NAME ${ex}
            RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/examples/fortran)
    endforeach()
endif()

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
message(STATUS "  Examples:          ${BUILD_EXAMPLES}")
message(STATUS "  Fortran compiler:  ${CMAKE_Fortran_COMPILER}")
message(STATUS "  OpenMP:            ${OpenMP_Fortran_FOUND}")
message(STATUS "  Cross compiling:   ${CMAKE_CROSSCOMPILING}")
message(STATUS "  Install prefix:    ${CMAKE_INSTALL_PREFIX}")
message(STATUS "------------------------------------------------------------")
