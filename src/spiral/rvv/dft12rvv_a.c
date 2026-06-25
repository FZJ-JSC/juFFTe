// --------------------------------------------------------------------------------------------------
// SPDX-FileCopyrightText: juFFTe developers
// SPDX-License-Identifier: Apache-2.0
// --------------------------------------------------------------------------------------------------

/*
*/

#include <stdint.h>
#include <riscv_vector.h>

void dft12a_(double *Y, double *X, double *TW1, int *lp1) {
    int l1;
    double *a1602;
    vfloat64m1x2_t r85, r86, r87, r88, r89, r90, r91, r92, 
            r93, r94, r95, r96;
    vfloat64m1_t  a1603, a1604, a1605, a1606, a1607, a1608, a1609, a1610, 
            a1611, a1612, a1613, a1614, a1615, a1616, a1617, a1618, 
            a1619, a1620, a1621, a1622, a1623, a1624, s884, s885, 
            s886, s887, s888, s889, s890, s891, s892, s893, 
            s894, s895, s896, s897, s898, s899, s900, s901, 
            s902, s903, s904, s905, s906, s907, s908, s909, 
            s910, s911, s912, s913, s914, s915, s916, s917, 
            s918, s919, s920, s921, s922, s923, s924, s925, 
            s926, s927, s928, s929, s930, s931, s932, s933, 
            s934, s935, s936, s937, s938, s939, s940, s941, 
            s942, s943, s944, s945, s946, s947, s948, s949, 
            s950, s951, s952, s953, s954, s955, s956, s957, 
            s958, s959, s960, s961, s962, s963, s964, s965, 
            s966, s967, s968, s969, s970, s971, s972, s973, 
            s974, s975, s976, s977, t2715, t2716, t2717, t2718, 
            t2719, t2720, t2721, t2722, t2723, t2724, t2725, t2726, 
            t2727, t2728, t2729, t2730, t2731, t2732, t2733, t2734, 
            t2735, t2736, t2737, t2738, t2739, t2740, t2741, t2742, 
            t2743, t2744, t2745, t2746, t2747, t2748, t2749, t2750, 
            t2751, t2752, t2753, t2754, t2755, t2756, t2757, t2758, 
            t2759, t2760, t2761, t2762, t2763, t2764, t2765, t2766, 
            t2767, t2768, t2769, t2770, t2771, t2772, t2773, t2774, 
            t2775, t2776, t2777, t2778;
    size_t vl1;
    l1 = *(lp1);
    for (size_t j1 = 0; j1 < l1; j1 += vl1) {
        vl1 = __riscv_vsetvl_e64m1(l1 - j1);
        r85 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*(j1))), vl1);
        s884 = __riscv_vget_f64m1(r85, 0);
        s885 = __riscv_vget_f64m1(r85, 1);
        r86 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((j1 + l1)))), vl1);
        s886 = __riscv_vget_f64m1(r86, 0);
        s887 = __riscv_vget_f64m1(r86, 1);
        r87 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((j1 + ((2)*(l1)))))), vl1);
        s888 = __riscv_vget_f64m1(r87, 0);
        s889 = __riscv_vget_f64m1(r87, 1);
        r88 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((j1 + ((3)*(l1)))))), vl1);
        s890 = __riscv_vget_f64m1(r88, 0);
        s891 = __riscv_vget_f64m1(r88, 1);
        r89 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((j1 + ((4)*(l1)))))), vl1);
        s892 = __riscv_vget_f64m1(r89, 0);
        s893 = __riscv_vget_f64m1(r89, 1);
        r90 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((j1 + ((5)*(l1)))))), vl1);
        s894 = __riscv_vget_f64m1(r90, 0);
        s895 = __riscv_vget_f64m1(r90, 1);
        r91 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((j1 + ((6)*(l1)))))), vl1);
        s896 = __riscv_vget_f64m1(r91, 0);
        s897 = __riscv_vget_f64m1(r91, 1);
        r92 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((j1 + ((7)*(l1)))))), vl1);
        s898 = __riscv_vget_f64m1(r92, 0);
        s899 = __riscv_vget_f64m1(r92, 1);
        r93 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((j1 + ((8)*(l1)))))), vl1);
        s900 = __riscv_vget_f64m1(r93, 0);
        s901 = __riscv_vget_f64m1(r93, 1);
        r94 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((j1 + ((9)*(l1)))))), vl1);
        s902 = __riscv_vget_f64m1(r94, 0);
        s903 = __riscv_vget_f64m1(r94, 1);
        r95 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((j1 + ((10)*(l1)))))), vl1);
        s904 = __riscv_vget_f64m1(r95, 0);
        s905 = __riscv_vget_f64m1(r95, 1);
        r96 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((j1 + ((11)*(l1)))))), vl1);
        s906 = __riscv_vget_f64m1(r96, 0);
        s907 = __riscv_vget_f64m1(r96, 1);
        t2715 = __riscv_vfadd(s884, s896, vl1);
        t2716 = __riscv_vfadd(s885, s897, vl1);
        t2717 = __riscv_vfsub(s884, s896, vl1);
        t2718 = __riscv_vfsub(s885, s897, vl1);
        t2719 = __riscv_vfadd(s890, s902, vl1);
        t2720 = __riscv_vfadd(s891, s903, vl1);
        t2721 = __riscv_vfsub(s890, s902, vl1);
        t2722 = __riscv_vfsub(s891, s903, vl1);
        t2723 = __riscv_vfadd(t2715, t2719, vl1);
        t2724 = __riscv_vfadd(t2716, t2720, vl1);
        t2725 = __riscv_vfsub(t2715, t2719, vl1);
        t2726 = __riscv_vfsub(t2716, t2720, vl1);
        t2727 = __riscv_vfadd(t2717, t2722, vl1);
        t2728 = __riscv_vfsub(t2718, t2721, vl1);
        t2729 = __riscv_vfsub(t2717, t2722, vl1);
        t2730 = __riscv_vfadd(t2718, t2721, vl1);
        t2731 = __riscv_vfadd(s886, s898, vl1);
        t2732 = __riscv_vfadd(s887, s899, vl1);
        t2733 = __riscv_vfsub(s886, s898, vl1);
        t2734 = __riscv_vfsub(s887, s899, vl1);
        t2735 = __riscv_vfadd(s892, s904, vl1);
        t2736 = __riscv_vfadd(s893, s905, vl1);
        t2737 = __riscv_vfsub(s892, s904, vl1);
        t2738 = __riscv_vfsub(s893, s905, vl1);
        t2739 = __riscv_vfadd(t2731, t2735, vl1);
        t2740 = __riscv_vfadd(t2732, t2736, vl1);
        t2741 = __riscv_vfsub(t2731, t2735, vl1);
        t2742 = __riscv_vfsub(t2732, t2736, vl1);
        s970 = __riscv_vfmacc(t2741, 1.7320508075688772, t2742, vl1);
        s908 = __riscv_vfmul(s970, 0.5, vl1);
        s971 = __riscv_vfnmsac(t2742, 1.7320508075688772, t2741, vl1);
        s909 = __riscv_vfmul(s971, 0.5, vl1);
        t2743 = __riscv_vfadd(t2733, t2738, vl1);
        t2744 = __riscv_vfsub(t2734, t2737, vl1);
        t2745 = __riscv_vfsub(t2733, t2738, vl1);
        t2746 = __riscv_vfadd(t2734, t2737, vl1);
        s972 = __riscv_vfmacc(t2743, 0.57735026918962584, t2744, vl1);
        s910 = __riscv_vfmul(s972, 0.8660254037844386, vl1);
        s973 = __riscv_vfnmsac(t2744, 0.57735026918962584, t2743, vl1);
        s911 = __riscv_vfmul(s973, 0.8660254037844386, vl1);
        t2747 = __riscv_vfadd(s888, s900, vl1);
        t2748 = __riscv_vfadd(s889, s901, vl1);
        t2749 = __riscv_vfsub(s888, s900, vl1);
        t2750 = __riscv_vfsub(s889, s901, vl1);
        t2751 = __riscv_vfadd(s894, s906, vl1);
        t2752 = __riscv_vfadd(s895, s907, vl1);
        t2753 = __riscv_vfsub(s894, s906, vl1);
        t2754 = __riscv_vfsub(s895, s907, vl1);
        t2755 = __riscv_vfadd(t2747, t2751, vl1);
        t2756 = __riscv_vfadd(t2748, t2752, vl1);
        t2757 = __riscv_vfsub(t2747, t2751, vl1);
        t2758 = __riscv_vfsub(t2748, t2752, vl1);
        s974 = __riscv_vfnmsac(t2758, 0.57735026918962584, t2757, vl1);
        s912 = __riscv_vfmul(s974, 0.8660254037844386, vl1);
        s975 = __riscv_vfmacc(t2757, 0.57735026918962584, t2758, vl1);
        s913 = __riscv_vfmul(s975, 0.8660254037844386, vl1);
        t2759 = __riscv_vfadd(t2749, t2754, vl1);
        t2760 = __riscv_vfsub(t2750, t2753, vl1);
        t2761 = __riscv_vfsub(t2749, t2754, vl1);
        t2762 = __riscv_vfadd(t2750, t2753, vl1);
        s976 = __riscv_vfmacc(t2759, 1.7320508075688772, t2760, vl1);
        s914 = __riscv_vfmul(s976, 0.5, vl1);
        s977 = __riscv_vfnmsac(t2760, 1.7320508075688772, t2759, vl1);
        s915 = __riscv_vfmul(s977, 0.5, vl1);
        t2763 = __riscv_vfadd(t2739, t2755, vl1);
        t2764 = __riscv_vfadd(t2740, t2756, vl1);
        t2765 = __riscv_vfnmsac(t2723, 0.5, t2763, vl1);
        t2766 = __riscv_vfnmsac(t2724, 0.5, t2764, vl1);
        s916 = __riscv_vfmul(__riscv_vfsub(t2740, t2756, vl1), 0.8660254037844386, vl1);
        s917 = __riscv_vfmul(__riscv_vfsub(t2739, t2755, vl1), 0.8660254037844386, vl1);
        s918 = __riscv_vfadd(t2723, t2763, vl1);
        s919 = __riscv_vfadd(t2724, t2764, vl1);
        s920 = __riscv_vfadd(t2765, s916, vl1);
        s921 = __riscv_vfsub(t2766, s917, vl1);
        s922 = __riscv_vfsub(t2765, s916, vl1);
        s923 = __riscv_vfadd(t2766, s917, vl1);
        t2767 = __riscv_vfadd(s910, s914, vl1);
        t2768 = __riscv_vfadd(s911, s915, vl1);
        t2769 = __riscv_vfnmsac(t2727, 0.5, t2767, vl1);
        t2770 = __riscv_vfnmsac(t2728, 0.5, t2768, vl1);
        s924 = __riscv_vfmul(__riscv_vfsub(s911, s915, vl1), 0.8660254037844386, vl1);
        s925 = __riscv_vfmul(__riscv_vfsub(s910, s914, vl1), 0.8660254037844386, vl1);
        s926 = __riscv_vfadd(t2727, t2767, vl1);
        s927 = __riscv_vfadd(t2728, t2768, vl1);
        s928 = __riscv_vfadd(t2769, s924, vl1);
        s929 = __riscv_vfsub(t2770, s925, vl1);
        s930 = __riscv_vfsub(t2769, s924, vl1);
        s931 = __riscv_vfadd(t2770, s925, vl1);
        t2771 = __riscv_vfadd(s908, s912, vl1);
        t2772 = __riscv_vfsub(s909, s913, vl1);
        t2773 = __riscv_vfnmsac(t2725, 0.5, t2771, vl1);
        t2774 = __riscv_vfnmsac(t2726, 0.5, t2772, vl1);
        s932 = __riscv_vfmul(__riscv_vfadd(s909, s913, vl1), 0.8660254037844386, vl1);
        s933 = __riscv_vfmul(__riscv_vfsub(s908, s912, vl1), 0.8660254037844386, vl1);
        s934 = __riscv_vfadd(t2725, t2771, vl1);
        s935 = __riscv_vfadd(t2726, t2772, vl1);
        s936 = __riscv_vfadd(t2773, s932, vl1);
        s937 = __riscv_vfsub(t2774, s933, vl1);
        s938 = __riscv_vfsub(t2773, s932, vl1);
        s939 = __riscv_vfadd(t2774, s933, vl1);
        t2775 = __riscv_vfsub(t2746, t2761, vl1);
        t2776 = __riscv_vfadd(t2745, t2762, vl1);
        t2777 = __riscv_vfnmsac(t2729, 0.5, t2775, vl1);
        t2778 = __riscv_vfmacc(t2730, 0.5, t2776, vl1);
        s940 = __riscv_vfmul(__riscv_vfsub(t2762, t2745, vl1), 0.8660254037844386, vl1);
        s941 = __riscv_vfmul(__riscv_vfadd(t2746, t2761, vl1), 0.8660254037844386, vl1);
        s942 = __riscv_vfadd(t2729, t2775, vl1);
        s943 = __riscv_vfsub(t2730, t2776, vl1);
        s944 = __riscv_vfadd(t2777, s940, vl1);
        s945 = __riscv_vfsub(t2778, s941, vl1);
        s946 = __riscv_vfsub(t2777, s940, vl1);
        s947 = __riscv_vfadd(t2778, s941, vl1);
        a1602 = (TW1 + ((22)*(j1)));
        a1603 = __riscv_vlse64_v_f64m1(a1602, sizeof(double) * 22, vl1);
        a1604 = __riscv_vlse64_v_f64m1((a1602 + 1), sizeof(double) * 22, vl1);
        s948 = __riscv_vfmsac(__riscv_vfmul(a1604, s927, vl1), a1603, s926, vl1);
        s949 = __riscv_vfmacc(__riscv_vfmul(a1603, s927, vl1), a1604, s926, vl1);
        a1605 = __riscv_vlse64_v_f64m1((a1602 + 2), sizeof(double) * 22, vl1);
        a1606 = __riscv_vlse64_v_f64m1((a1602 + 3), sizeof(double) * 22, vl1);
        s950 = __riscv_vfmsac(__riscv_vfmul(a1606, s935, vl1), a1605, s934, vl1);
        s951 = __riscv_vfmacc(__riscv_vfmul(a1605, s935, vl1), a1606, s934, vl1);
        a1607 = __riscv_vlse64_v_f64m1((a1602 + 4), sizeof(double) * 22, vl1);
        a1608 = __riscv_vlse64_v_f64m1((a1602 + 5), sizeof(double) * 22, vl1);
        s952 = __riscv_vfmsac(__riscv_vfmul(a1608, s943, vl1), a1607, s942, vl1);
        s953 = __riscv_vfmacc(__riscv_vfmul(a1607, s943, vl1), a1608, s942, vl1);
        a1609 = __riscv_vlse64_v_f64m1((a1602 + 6), sizeof(double) * 22, vl1);
        a1610 = __riscv_vlse64_v_f64m1((a1602 + 7), sizeof(double) * 22, vl1);
        s954 = __riscv_vfmsac(__riscv_vfmul(a1610, s921, vl1), a1609, s920, vl1);
        s955 = __riscv_vfmacc(__riscv_vfmul(a1609, s921, vl1), a1610, s920, vl1);
        a1611 = __riscv_vlse64_v_f64m1((a1602 + 8), sizeof(double) * 22, vl1);
        a1612 = __riscv_vlse64_v_f64m1((a1602 + 9), sizeof(double) * 22, vl1);
        s956 = __riscv_vfmsac(__riscv_vfmul(a1612, s929, vl1), a1611, s928, vl1);
        s957 = __riscv_vfmacc(__riscv_vfmul(a1611, s929, vl1), a1612, s928, vl1);
        a1613 = __riscv_vlse64_v_f64m1((a1602 + 10), sizeof(double) * 22, vl1);
        a1614 = __riscv_vlse64_v_f64m1((a1602 + 11), sizeof(double) * 22, vl1);
        s958 = __riscv_vfmsac(__riscv_vfmul(a1614, s937, vl1), a1613, s936, vl1);
        s959 = __riscv_vfmacc(__riscv_vfmul(a1613, s937, vl1), a1614, s936, vl1);
        a1615 = __riscv_vlse64_v_f64m1((a1602 + 12), sizeof(double) * 22, vl1);
        a1616 = __riscv_vlse64_v_f64m1((a1602 + 13), sizeof(double) * 22, vl1);
        s960 = __riscv_vfmsac(__riscv_vfmul(a1616, s945, vl1), a1615, s944, vl1);
        s961 = __riscv_vfmacc(__riscv_vfmul(a1615, s945, vl1), a1616, s944, vl1);
        a1617 = __riscv_vlse64_v_f64m1((a1602 + 14), sizeof(double) * 22, vl1);
        a1618 = __riscv_vlse64_v_f64m1((a1602 + 15), sizeof(double) * 22, vl1);
        s962 = __riscv_vfmsac(__riscv_vfmul(a1618, s923, vl1), a1617, s922, vl1);
        s963 = __riscv_vfmacc(__riscv_vfmul(a1617, s923, vl1), a1618, s922, vl1);
        a1619 = __riscv_vlse64_v_f64m1((a1602 + 16), sizeof(double) * 22, vl1);
        a1620 = __riscv_vlse64_v_f64m1((a1602 + 17), sizeof(double) * 22, vl1);
        s964 = __riscv_vfmsac(__riscv_vfmul(a1620, s931, vl1), a1619, s930, vl1);
        s965 = __riscv_vfmacc(__riscv_vfmul(a1619, s931, vl1), a1620, s930, vl1);
        a1621 = __riscv_vlse64_v_f64m1((a1602 + 18), sizeof(double) * 22, vl1);
        a1622 = __riscv_vlse64_v_f64m1((a1602 + 19), sizeof(double) * 22, vl1);
        s966 = __riscv_vfmsac(__riscv_vfmul(a1622, s939, vl1), a1621, s938, vl1);
        s967 = __riscv_vfmacc(__riscv_vfmul(a1621, s939, vl1), a1622, s938, vl1);
        a1623 = __riscv_vlse64_v_f64m1((a1602 + 20), sizeof(double) * 22, vl1);
        a1624 = __riscv_vlse64_v_f64m1((a1602 + 21), sizeof(double) * 22, vl1);
        s968 = __riscv_vfmsac(__riscv_vfmul(a1624, s947, vl1), a1623, s946, vl1);
        s969 = __riscv_vfmacc(__riscv_vfmul(a1623, s947, vl1), a1624, s946, vl1);
        __riscv_vsse64((Y + ((24)*(j1))), sizeof(double) * 24, s918, vl1);
        __riscv_vsse64((1 + Y + ((24)*(j1))), sizeof(double) * 24, s919, vl1);
        __riscv_vsse64((2 + Y + ((24)*(j1))), sizeof(double) * 24, s948, vl1);
        __riscv_vsse64((3 + Y + ((24)*(j1))), sizeof(double) * 24, s949, vl1);
        __riscv_vsse64((4 + Y + ((24)*(j1))), sizeof(double) * 24, s950, vl1);
        __riscv_vsse64((5 + Y + ((24)*(j1))), sizeof(double) * 24, s951, vl1);
        __riscv_vsse64((6 + Y + ((24)*(j1))), sizeof(double) * 24, s952, vl1);
        __riscv_vsse64((7 + Y + ((24)*(j1))), sizeof(double) * 24, s953, vl1);
        __riscv_vsse64((8 + Y + ((24)*(j1))), sizeof(double) * 24, s954, vl1);
        __riscv_vsse64((9 + Y + ((24)*(j1))), sizeof(double) * 24, s955, vl1);
        __riscv_vsse64((10 + Y + ((24)*(j1))), sizeof(double) * 24, s956, vl1);
        __riscv_vsse64((11 + Y + ((24)*(j1))), sizeof(double) * 24, s957, vl1);
        __riscv_vsse64((12 + Y + ((24)*(j1))), sizeof(double) * 24, s958, vl1);
        __riscv_vsse64((13 + Y + ((24)*(j1))), sizeof(double) * 24, s959, vl1);
        __riscv_vsse64((14 + Y + ((24)*(j1))), sizeof(double) * 24, s960, vl1);
        __riscv_vsse64((15 + Y + ((24)*(j1))), sizeof(double) * 24, s961, vl1);
        __riscv_vsse64((16 + Y + ((24)*(j1))), sizeof(double) * 24, s962, vl1);
        __riscv_vsse64((17 + Y + ((24)*(j1))), sizeof(double) * 24, s963, vl1);
        __riscv_vsse64((18 + Y + ((24)*(j1))), sizeof(double) * 24, s964, vl1);
        __riscv_vsse64((19 + Y + ((24)*(j1))), sizeof(double) * 24, s965, vl1);
        __riscv_vsse64((20 + Y + ((24)*(j1))), sizeof(double) * 24, s966, vl1);
        __riscv_vsse64((21 + Y + ((24)*(j1))), sizeof(double) * 24, s967, vl1);
        __riscv_vsse64((22 + Y + ((24)*(j1))), sizeof(double) * 24, s968, vl1);
        __riscv_vsse64((23 + Y + ((24)*(j1))), sizeof(double) * 24, s969, vl1);
    }
}
