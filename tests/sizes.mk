# --------------------------------------------------------------------------------------------------
# SPDX-FileCopyrightText: juFFTe developers
# SPDX-License-Identifier: Apache-2.0
# --------------------------------------------------------------------------------------------------

# Sizes the tests run at, read by CMakeLists.txt and included by the Makefiles in tests/c
# and tests/fortran. One entry per size; a quoted entry has one length per dimension.
#
# Length 2 alone never needs a second radix-3 stage (9), radix 5 (100), every radix (120)
# or a non-square shape, which is how the single-precision fft3b constant fixed in e253422
# went unnoticed. 20x60 keeps 2-D radix 5 below the direct DFT's N < 4000. The six-step
# branch (1-D n > 174762) is not covered yet: it crashes at the default 8 MB stack, and
# its out-of-place backward and 1-D r2c paths are broken.
SIZES_1D = 2 9 96 100 120 1024
SIZES_2D = "2 2" "9 96" "20 60" "96 64" "120 100" "256 256"
SIZES_3D = "2 2 2" "9 16 20" "12 18 20" "32 32 32"

# Added by -DTHOROUGH_TESTS=ON or `make test THOROUGH=1`: every 2-3-5 length up to 128,
# powers of each radix, the size caps (65536 in 1-D and 2-D, 4096 per 3-D dimension), and
# lopsided shapes. 1-D stays at 65536 or below, the cap of the 1-D real transforms.
THOROUGH_1D = 3 4 5 6 8 10 12 15 16 18 20 24 25 27 30 32 36 40 45 48 50 54 60 64 72 75 80 81 \
              90 108 125 128 243 256 360 500 625 729 768 2048 2187 3125 4096 6561 8192 15625 \
              16384 32768 46656 59049 65536
THOROUGH_2D = "3 5" "5 3" "4 6" "16 9" "25 27" "64 128" "128 64" "243 32" "1000 100" \
              "512 512" "1024 729" "2048 2" "2 2048" "65536 2" "2 65536"
THOROUGH_3D = "2 3 5" "3 4 5" "5 4 3" "8 27 25" "45 32 16" "6 25 81" "100 30 8" "64 64 64" \
              "128 128 128" "4096 2 2" "2 4096 2" "2 2 4096"
