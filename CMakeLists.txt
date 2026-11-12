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
option(WITH_EPI "Vectorise with -mepi if the compiler is EPI's LLVM" ON)

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
# flang warns about each !DIR$ VECTOR ALIGNED it ignores, as in src/Makefile.
if(CMAKE_Fortran_COMPILER_ID MATCHES "Flang")
    add_compile_options("$<$<COMPILE_LANGUAGE:Fortran>:-Wno-ignored-directive>")
endif()

# EPI's LLVM (BSC) vectorises for RVV with -mepi, which turns the cos/sin loops of the
# twiddle tables into calls to its vector math library, libprovector-vecclonevp; the
# library has to link it. Upstream flang rejects -mepi, hence the test instead of the
# compiler ID.
set(JUFFTE_EPI OFF)
if(WITH_EPI)
    include(CheckFortranCompilerFlag)
    check_fortran_compiler_flag(-mepi JUFFTE_EPI_COMPILER)
    set(JUFFTE_EPI "${JUFFTE_EPI_COMPILER}")
endif()
if(JUFFTE_EPI)
    # The library belongs to the toolchain: look next to the real compiler and where it
    # links its own runtime, not in a cross build's sysroot.
    get_filename_component(EPI_BIN_DIR ${CMAKE_Fortran_COMPILER} REALPATH)
    get_filename_component(EPI_BIN_DIR ${EPI_BIN_DIR} DIRECTORY)
    find_library(EPI_VECMATH_LIBRARY provector-vecclonevp
        HINTS ${EPI_BIN_DIR}/../lib ${CMAKE_Fortran_IMPLICIT_LINK_DIRECTORIES}
        NO_CMAKE_FIND_ROOT_PATH)
    if(NOT EPI_VECMATH_LIBRARY)
        message(FATAL_ERROR "The EPI compiler needs libprovector-vecclonevp, which is not in "
                            "${EPI_BIN_DIR}/../lib: set EPI_VECMATH_LIBRARY to its path, or "
                            "build without -mepi with -DWITH_EPI=OFF.")
    endif()
    message(STATUS "EPI compiler: -mepi, linking ${EPI_VECMATH_LIBRARY}")
    # CMake leaves the directories the compiler links from by default, where EPI's flang
    # keeps the library, out of the run paths it computes, so name it for a shared one.
    get_filename_component(EPI_VECMATH_DIR ${EPI_VECMATH_LIBRARY} DIRECTORY)
    list(APPEND CMAKE_BUILD_RPATH ${EPI_VECMATH_DIR})
endif()

if(CMAKE_Fortran_COMPILER_ID MATCHES "NVHPC")
    # Placeholder: add NVIDIA Fortran flags if needed
endif()

# =========================
# Source lists
# =========================
set(OBJ_COMMON
    ${CMAKE_CURRENT_SOURCE_DIR}/src/param.F90
    ${CMAKE_CURRENT_SOURCE_DIR}/src/utils_m.F90
    ${CMAKE_CURRENT_SOURCE_DIR}/src/factor_m.F90
    ${CMAKE_CURRENT_SOURCE_DIR}/src/plan_m.F90
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

# PUBLIC: if the user also puts -mepi into CMAKE_<LANG>_FLAGS, as in #22, the tests,
# the benchmark and their own programs call the vector library too, also when libjuffte
# is shared. The install RPATH lets an installed shared libjuffte find a shared one.
if(JUFFTE_EPI)
    target_compile_options(${LIB_TARGET} PRIVATE
        "$<$<COMPILE_LANGUAGE:Fortran>:-ffast-math;-mepi>")
    target_link_libraries(${LIB_TARGET} PUBLIC ${EPI_VECMATH_LIBRARY})
    set_property(TARGET ${LIB_TARGET} APPEND PROPERTY INSTALL_RPATH ${EPI_VECMATH_DIR})
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

# One case per process, named like f_real_bw_9x96, c_complex_fw_1024_fftw,
# c_complex_bw_96_with_100 (-o 100) or f_complex_fw_96_threads (-p). Without FFTW, sizes
# with N >= 4000 have no reference and are reported as skipped (exit status 77). The
# thorough sizes carry the label "thorough" (ctest -L thorough / -LE thorough).
function(juffte_add_test lang type dir size label)
    string(REPLACE " " ";" n "${size}")
    string(REPLACE " " "x" tag "${size}")
    set(name ${lang}_${type}_${dir}_${tag})
    set(args ${ARGN})
    while(args)
        list(POP_FRONT args opt)
        if(opt STREQUAL "-p")
            string(APPEND name _threads)
        elseif(opt STREQUAL "-o")
            list(POP_FRONT args val)
            string(APPEND name _with_${val})
        else()
            list(POP_FRONT args val)
            string(APPEND name _${val})
        endif()
    endwhile()
    add_test(NAME ${name} COMMAND juffte_test_${lang} -t ${type} -d ${dir} ${ARGN} ${n})
    # Do not add PASS_REGULAR_EXPRESSION: it makes CTest ignore the exit status and
    # report failures as passes.
    set_tests_properties(${name} PROPERTIES SKIP_RETURN_CODE 77 FAIL_REGULAR_EXPRESSION "FAIL"
                                            LABELS ${label})
endfunction()

# Every case for one size: complex, real and the FFTW layer from both languages, the
# native API with a plan of the caller's own (plan=) from Fortran, and fft_init/fft_execute
# in 1-D.
function(juffte_add_size size label)
    string(REPLACE " " ";" n "${size}")
    list(LENGTH n dim)
    foreach(lang c f)
        foreach(dir fw bw)
            foreach(type complex real)
                juffte_add_test(${lang} ${type} ${dir} "${size}" ${label})
                if(lang STREQUAL "f")
                    juffte_add_test(${lang} ${type} ${dir} "${size}" ${label} -a plan)
                endif()
            endforeach()
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
    foreach(size IN LISTS JUFFTE_${kind}_1D JUFFTE_${kind}_2D JUFFTE_${kind}_3D
                          JUFFTE_${kind}_SIXSTEP)
        juffte_add_size("${size}" ${label})
    endforeach()
endforeach()

# Several plans at once, label "plans". Each pair of PLANS is a shape to check and one to
# make plans of around it (-o). Whether one plan disturbs another depends neither on the
# direction nor on the language of the native call (the C one is a thin wrapper), so these
# run forward, natively from Fortran, with plan=, and through both FFTW layers. The THREADS
# sizes run from four threads at once (-p): natively, each thread with its own references
# to the shared plans, and with plan= and the FFTW layer, all on one plan.
# fft_init/fft_execute only take 1-D shapes.
function(juffte_add_plans pair)
    string(REPLACE " " ";" shapes "${pair}")
    list(GET shapes 0 shape)
    list(GET shapes 1 other)
    string(REPLACE "x" " " shape "${shape}")
    foreach(type complex real)
        juffte_add_test(f ${type} fw "${shape}" plans -o ${other})
        juffte_add_test(f ${type} fw "${shape}" plans -a plan -o ${other})
    endforeach()
    foreach(lang c f)
        juffte_add_test(${lang} complex fw "${shape}" plans -a fftw -o ${other})
    endforeach()
    if(NOT pair MATCHES "x")
        juffte_add_test(f complex fw "${shape}" plans -a simple -o ${other})
    endif()
endfunction()

function(juffte_add_threads size)
    foreach(dir fw bw)
        foreach(type complex real)
            juffte_add_test(f ${type} ${dir} "${size}" plans -p)
            juffte_add_test(f ${type} ${dir} "${size}" plans -a plan -p)
        endforeach()
        juffte_add_test(f complex ${dir} "${size}" plans -a fftw -p)
        if(NOT size MATCHES " ")
            juffte_add_test(f complex ${dir} "${size}" plans -a simple -p)
        endif()
    endforeach()
endfunction()

foreach(pair IN LISTS JUFFTE_PLANS)
    juffte_add_plans("${pair}")
endforeach()
foreach(size IN LISTS JUFFTE_THREADS)
    juffte_add_threads("${size}")
endforeach()

# The plans themselves where the transform tests cannot reach them in a deterministic way
# (tests/fortran/plan_test.F90). MALLOC_PERTURB_ makes a plan freed too early show.
add_executable(plan_test ${CMAKE_CURRENT_SOURCE_DIR}/tests/fortran/plan_test.F90)
target_link_libraries(plan_test PRIVATE ${LIB_TARGET})
add_test(NAME f_plan_internals COMMAND plan_test)
set_tests_properties(f_plan_internals PROPERTIES ENVIRONMENT MALLOC_PERTURB_=165
                                                 FAIL_REGULAR_EXPRESSION "FAIL" LABELS plans)

# A length the library cannot handle must stop it with a message. Here, and only here,
# the output decides: the exit status is that of the library's error stop.
foreach(lang c f)
    add_test(NAME ${lang}_rejects_length_14 COMMAND juffte_test_${lang} 14)
    set_tests_properties(${lang}_rejects_length_14 PROPERTIES
        PASS_REGULAR_EXPRESSION "length 14 is not a product of 2, 3 and 5")
endforeach()
foreach(case "unmade|zfft1d: plan= holds no plan"
             "other-shape|zfft1d: plan= holds a zfft1d plan for length 16 in FP64, not a zfft1d plan for length 32"
             "other-transform|dzfft2d: plan= holds a zfft2d plan for 4 x 4 in FP64, not a dzfft2d plan"
             "too-large|zfft3d: 2048 x 2048 x 1024 has more than 2147483647 elements"
             "work-too-large|zfft2d: 2 x 134217728 needs per-thread work arrays of more than"
             "bad-iopt|zfft1d: iopt is -2; use juffte_init")
    string(REPLACE "|" ";" case "${case}")
    list(GET case 0 what)
    list(GET case 1 message)
    add_test(NAME f_rejects_plan_${what} COMMAND plan_test ${what})
    set_tests_properties(f_rejects_plan_${what} PROPERTIES PASS_REGULAR_EXPRESSION "${message}")
endforeach()

add_custom_target(run_tests
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Running tests:"
    DEPENDS juffte_test_c juffte_test_f plan_test
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
