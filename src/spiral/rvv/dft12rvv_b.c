// --------------------------------------------------------------------------------------------------
// SPDX-FileCopyrightText: juFFTe developers
// SPDX-License-Identifier: Apache-2.0
// --------------------------------------------------------------------------------------------------

/*
*/

#include <stdint.h>
#include <riscv_vector.h>

void dft12b_(double *Y, double *X, double *TW1, int *lp1, int *mp1) {
    double a1713, a1714, a1715, a1716, a1717, a1718, a1719, a1720, 
            a1721, a1722, a1723, a1724, a1725, a1726, a1727, a1728, 
            a1729, a1730, a1731, a1732, a1733, a1734;
    int a1711, a1712, j1, l1, m1;
    vfloat64m1x2_t r193, r194, r195, r196, r197, r198, r199, r200, 
            r201, r202, r203, r204, r205, r206, r207, r208, 
            r209, r210, r211, r212, r213, r214, r215, r216, 
            rvvx2_13, rvvx2_14, rvvx2_15, rvvx2_16, rvvx2_17, rvvx2_18, rvvx2_19, rvvx2_20, 
            rvvx2_21, rvvx2_22, rvvx2_23, rvvx2_24;
    vfloat64m1_t  s860, s861, s862, s863, s864, s865, s866, s867, 
            s868, s869, s870, s871, s872, s873, s874, s875, 
            s876, s877, s878, s879, s880, s881, s882, s883, 
            s884, s885, s886, s887, s888, s889, s890, s891, 
            s892, s893, s894, s895, s896, s897, s898, s899, 
            s900, s901, s902, s903, s904, s905, s906, s907, 
            s908, s909, s910, s911, s912, s913, s914, s915, 
            s916, s917, s918, s919, s920, s921, s922, s923, 
            s924, s925, s926, s927, s928, s929, t2715, t2716, 
            t2717, t2718, t2719, t2720, t2721, t2722, t2723, t2724, 
            t2725, t2726, t2727, t2728, t2729, t2730, t2731, t2732, 
            t2733, t2734, t2735, t2736, t2737, t2738, t2739, t2740, 
            t2741, t2742, t2743, t2744, t2745, t2746, t2747, t2748, 
            t2749, t2750, t2751, t2752, t2753, t2754, t2755, t2756, 
            t2757, t2758, t2759, t2760, t2761, t2762, t2763, t2764, 
            t2765, t2766, t2767, t2768, t2769, t2770, t2771, t2772, 
            t2773, t2774, t2775, t2776, t2777, t2778;
    size_t vl1;
    l1 = *(lp1);
    m1 = *(mp1);
    for(int j1 = 1; j1 < l1; j1++) {
        for (size_t k1 = 0; k1 < m1; k1 += vl1) {
            vl1 = __riscv_vsetvl_e64m1(m1 - k1);
            a1711 = (k1 + ((j1)*(m1)));
            r193 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*(a1711))), vl1);
            s860 = __riscv_vget_f64m1(r193, 0);
            s861 = __riscv_vget_f64m1(r193, 1);
            r194 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((a1711 + ((l1)*(m1)))))), vl1);
            s862 = __riscv_vget_f64m1(r194, 0);
            s863 = __riscv_vget_f64m1(r194, 1);
            r195 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((a1711 + ((((2)*(l1)))*(m1)))))), vl1);
            s864 = __riscv_vget_f64m1(r195, 0);
            s865 = __riscv_vget_f64m1(r195, 1);
            r196 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((a1711 + ((((3)*(l1)))*(m1)))))), vl1);
            s866 = __riscv_vget_f64m1(r196, 0);
            s867 = __riscv_vget_f64m1(r196, 1);
            r197 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((a1711 + ((((4)*(l1)))*(m1)))))), vl1);
            s868 = __riscv_vget_f64m1(r197, 0);
            s869 = __riscv_vget_f64m1(r197, 1);
            r198 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((a1711 + ((((5)*(l1)))*(m1)))))), vl1);
            s870 = __riscv_vget_f64m1(r198, 0);
            s871 = __riscv_vget_f64m1(r198, 1);
            r199 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((a1711 + ((((6)*(l1)))*(m1)))))), vl1);
            s872 = __riscv_vget_f64m1(r199, 0);
            s873 = __riscv_vget_f64m1(r199, 1);
            r200 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((a1711 + ((((7)*(l1)))*(m1)))))), vl1);
            s874 = __riscv_vget_f64m1(r200, 0);
            s875 = __riscv_vget_f64m1(r200, 1);
            r201 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((a1711 + ((((8)*(l1)))*(m1)))))), vl1);
            s876 = __riscv_vget_f64m1(r201, 0);
            s877 = __riscv_vget_f64m1(r201, 1);
            r202 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((a1711 + ((((9)*(l1)))*(m1)))))), vl1);
            s878 = __riscv_vget_f64m1(r202, 0);
            s879 = __riscv_vget_f64m1(r202, 1);
            r203 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((a1711 + ((((10)*(l1)))*(m1)))))), vl1);
            s880 = __riscv_vget_f64m1(r203, 0);
            s881 = __riscv_vget_f64m1(r203, 1);
            r204 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((a1711 + ((((11)*(l1)))*(m1)))))), vl1);
            s882 = __riscv_vget_f64m1(r204, 0);
            s883 = __riscv_vget_f64m1(r204, 1);
            t2715 = __riscv_vfadd(s860, s872, vl1);
            t2716 = __riscv_vfadd(s861, s873, vl1);
            t2717 = __riscv_vfsub(s860, s872, vl1);
            t2718 = __riscv_vfsub(s861, s873, vl1);
            t2719 = __riscv_vfadd(s866, s878, vl1);
            t2720 = __riscv_vfadd(s867, s879, vl1);
            t2721 = __riscv_vfsub(s866, s878, vl1);
            t2722 = __riscv_vfsub(s867, s879, vl1);
            t2723 = __riscv_vfadd(t2715, t2719, vl1);
            t2724 = __riscv_vfadd(t2716, t2720, vl1);
            t2725 = __riscv_vfsub(t2715, t2719, vl1);
            t2726 = __riscv_vfsub(t2716, t2720, vl1);
            t2727 = __riscv_vfadd(t2717, t2722, vl1);
            t2728 = __riscv_vfsub(t2718, t2721, vl1);
            t2729 = __riscv_vfsub(t2717, t2722, vl1);
            t2730 = __riscv_vfadd(t2718, t2721, vl1);
            t2731 = __riscv_vfadd(s862, s874, vl1);
            t2732 = __riscv_vfadd(s863, s875, vl1);
            t2733 = __riscv_vfsub(s862, s874, vl1);
            t2734 = __riscv_vfsub(s863, s875, vl1);
            t2735 = __riscv_vfadd(s868, s880, vl1);
            t2736 = __riscv_vfadd(s869, s881, vl1);
            t2737 = __riscv_vfsub(s868, s880, vl1);
            t2738 = __riscv_vfsub(s869, s881, vl1);
            t2739 = __riscv_vfadd(t2731, t2735, vl1);
            t2740 = __riscv_vfadd(t2732, t2736, vl1);
            t2741 = __riscv_vfsub(t2731, t2735, vl1);
            t2742 = __riscv_vfsub(t2732, t2736, vl1);
            s922 = __riscv_vfmacc(t2741, 1.7320508075688772, t2742, vl1);
            s884 = __riscv_vfmul(s922, 0.5, vl1);
            s923 = __riscv_vfnmsac(t2742, 1.7320508075688772, t2741, vl1);
            s885 = __riscv_vfmul(s923, 0.5, vl1);
            t2743 = __riscv_vfadd(t2733, t2738, vl1);
            t2744 = __riscv_vfsub(t2734, t2737, vl1);
            t2745 = __riscv_vfsub(t2733, t2738, vl1);
            t2746 = __riscv_vfadd(t2734, t2737, vl1);
            s924 = __riscv_vfmacc(t2743, 0.57735026918962584, t2744, vl1);
            s886 = __riscv_vfmul(s924, 0.8660254037844386, vl1);
            s925 = __riscv_vfnmsac(t2744, 0.57735026918962584, t2743, vl1);
            s887 = __riscv_vfmul(s925, 0.8660254037844386, vl1);
            t2747 = __riscv_vfadd(s864, s876, vl1);
            t2748 = __riscv_vfadd(s865, s877, vl1);
            t2749 = __riscv_vfsub(s864, s876, vl1);
            t2750 = __riscv_vfsub(s865, s877, vl1);
            t2751 = __riscv_vfadd(s870, s882, vl1);
            t2752 = __riscv_vfadd(s871, s883, vl1);
            t2753 = __riscv_vfsub(s870, s882, vl1);
            t2754 = __riscv_vfsub(s871, s883, vl1);
            t2755 = __riscv_vfadd(t2747, t2751, vl1);
            t2756 = __riscv_vfadd(t2748, t2752, vl1);
            t2757 = __riscv_vfsub(t2747, t2751, vl1);
            t2758 = __riscv_vfsub(t2748, t2752, vl1);
            s926 = __riscv_vfnmsac(t2758, 0.57735026918962584, t2757, vl1);
            s888 = __riscv_vfmul(s926, 0.8660254037844386, vl1);
            s927 = __riscv_vfmacc(t2757, 0.57735026918962584, t2758, vl1);
            s889 = __riscv_vfmul(s927, 0.8660254037844386, vl1);
            t2759 = __riscv_vfadd(t2749, t2754, vl1);
            t2760 = __riscv_vfsub(t2750, t2753, vl1);
            t2761 = __riscv_vfsub(t2749, t2754, vl1);
            t2762 = __riscv_vfadd(t2750, t2753, vl1);
            s928 = __riscv_vfmacc(t2759, 1.7320508075688772, t2760, vl1);
            s890 = __riscv_vfmul(s928, 0.5, vl1);
            s929 = __riscv_vfnmsac(t2760, 1.7320508075688772, t2759, vl1);
            s891 = __riscv_vfmul(s929, 0.5, vl1);
            t2763 = __riscv_vfadd(t2739, t2755, vl1);
            t2764 = __riscv_vfadd(t2740, t2756, vl1);
            t2765 = __riscv_vfnmsac(t2723, 0.5, t2763, vl1);
            t2766 = __riscv_vfnmsac(t2724, 0.5, t2764, vl1);
            s892 = __riscv_vfmul(__riscv_vfsub(t2740, t2756, vl1), 0.8660254037844386, vl1);
            s893 = __riscv_vfmul(__riscv_vfsub(t2739, t2755, vl1), 0.8660254037844386, vl1);
            s894 = __riscv_vfadd(t2765, s892, vl1);
            s895 = __riscv_vfsub(t2766, s893, vl1);
            s896 = __riscv_vfsub(t2765, s892, vl1);
            s897 = __riscv_vfadd(t2766, s893, vl1);
            t2767 = __riscv_vfadd(s886, s890, vl1);
            t2768 = __riscv_vfadd(s887, s891, vl1);
            t2769 = __riscv_vfnmsac(t2727, 0.5, t2767, vl1);
            t2770 = __riscv_vfnmsac(t2728, 0.5, t2768, vl1);
            s898 = __riscv_vfmul(__riscv_vfsub(s887, s891, vl1), 0.8660254037844386, vl1);
            s899 = __riscv_vfmul(__riscv_vfsub(s886, s890, vl1), 0.8660254037844386, vl1);
            s900 = __riscv_vfadd(t2727, t2767, vl1);
            s901 = __riscv_vfadd(t2728, t2768, vl1);
            s902 = __riscv_vfadd(t2769, s898, vl1);
            s903 = __riscv_vfsub(t2770, s899, vl1);
            s904 = __riscv_vfsub(t2769, s898, vl1);
            s905 = __riscv_vfadd(t2770, s899, vl1);
            t2771 = __riscv_vfadd(s884, s888, vl1);
            t2772 = __riscv_vfsub(s885, s889, vl1);
            t2773 = __riscv_vfnmsac(t2725, 0.5, t2771, vl1);
            t2774 = __riscv_vfnmsac(t2726, 0.5, t2772, vl1);
            s906 = __riscv_vfmul(__riscv_vfadd(s885, s889, vl1), 0.8660254037844386, vl1);
            s907 = __riscv_vfmul(__riscv_vfsub(s884, s888, vl1), 0.8660254037844386, vl1);
            s908 = __riscv_vfadd(t2725, t2771, vl1);
            s909 = __riscv_vfadd(t2726, t2772, vl1);
            s910 = __riscv_vfadd(t2773, s906, vl1);
            s911 = __riscv_vfsub(t2774, s907, vl1);
            s912 = __riscv_vfsub(t2773, s906, vl1);
            s913 = __riscv_vfadd(t2774, s907, vl1);
            t2775 = __riscv_vfsub(t2746, t2761, vl1);
            t2776 = __riscv_vfadd(t2745, t2762, vl1);
            t2777 = __riscv_vfnmsac(t2729, 0.5, t2775, vl1);
            t2778 = __riscv_vfmacc(t2730, 0.5, t2776, vl1);
            s914 = __riscv_vfmul(__riscv_vfsub(t2762, t2745, vl1), 0.8660254037844386, vl1);
            s915 = __riscv_vfmul(__riscv_vfadd(t2746, t2761, vl1), 0.8660254037844386, vl1);
            s916 = __riscv_vfadd(t2729, t2775, vl1);
            s917 = __riscv_vfsub(t2730, t2776, vl1);
            s918 = __riscv_vfadd(t2777, s914, vl1);
            s919 = __riscv_vfsub(t2778, s915, vl1);
            s920 = __riscv_vfsub(t2777, s914, vl1);
            s921 = __riscv_vfadd(t2778, s915, vl1);
            a1712 = ((22)*(j1));
            a1713 = TW1[a1712];
            a1714 = TW1[(a1712 + 1)];
            a1715 = TW1[(a1712 + 2)];
            a1716 = TW1[(a1712 + 3)];
            a1717 = TW1[(a1712 + 4)];
            a1718 = TW1[(a1712 + 5)];
            a1719 = TW1[(a1712 + 6)];
            a1720 = TW1[(a1712 + 7)];
            a1721 = TW1[(a1712 + 8)];
            a1722 = TW1[(a1712 + 9)];
            a1723 = TW1[(a1712 + 10)];
            a1724 = TW1[(a1712 + 11)];
            a1725 = TW1[(a1712 + 12)];
            a1726 = TW1[(a1712 + 13)];
            a1727 = TW1[(a1712 + 14)];
            a1728 = TW1[(a1712 + 15)];
            a1729 = TW1[(a1712 + 16)];
            a1730 = TW1[(a1712 + 17)];
            a1731 = TW1[(a1712 + 18)];
            a1732 = TW1[(a1712 + 19)];
            a1733 = TW1[(a1712 + 20)];
            a1734 = TW1[(a1712 + 21)];
            r205 = __riscv_vset(__riscv_vset(rvvx2_13, 0, __riscv_vfadd(t2723, t2763, vl1)), 1, __riscv_vfadd(t2724, t2764, vl1));
            __riscv_vsseg2e64((Y + ((2)*((k1 + ((((12)*(j1)))*(m1)))))), r205, vl1);
            r206 = __riscv_vset(__riscv_vset(rvvx2_14, 0, __riscv_vfsub(__riscv_vfmul(s900, a1713, vl1), __riscv_vfmul(s901, a1714, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s900, a1714, vl1), __riscv_vfmul(s901, a1713, vl1), vl1));
            __riscv_vsseg2e64((Y + ((2)*((k1 + ((((12)*(j1)))*(m1)) + m1)))), r206, vl1);
            r207 = __riscv_vset(__riscv_vset(rvvx2_15, 0, __riscv_vfsub(__riscv_vfmul(s908, a1715, vl1), __riscv_vfmul(s909, a1716, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s908, a1716, vl1), __riscv_vfmul(s909, a1715, vl1), vl1));
            __riscv_vsseg2e64((Y + ((2)*((k1 + ((((12)*(j1)))*(m1)) + ((2)*(m1)))))), r207, vl1);
            r208 = __riscv_vset(__riscv_vset(rvvx2_16, 0, __riscv_vfsub(__riscv_vfmul(s916, a1717, vl1), __riscv_vfmul(s917, a1718, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s916, a1718, vl1), __riscv_vfmul(s917, a1717, vl1), vl1));
            __riscv_vsseg2e64((Y + ((2)*((k1 + ((((12)*(j1)))*(m1)) + ((3)*(m1)))))), r208, vl1);
            r209 = __riscv_vset(__riscv_vset(rvvx2_17, 0, __riscv_vfsub(__riscv_vfmul(s894, a1719, vl1), __riscv_vfmul(s895, a1720, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s894, a1720, vl1), __riscv_vfmul(s895, a1719, vl1), vl1));
            __riscv_vsseg2e64((Y + ((2)*((k1 + ((((12)*(j1)))*(m1)) + ((4)*(m1)))))), r209, vl1);
            r210 = __riscv_vset(__riscv_vset(rvvx2_18, 0, __riscv_vfsub(__riscv_vfmul(s902, a1721, vl1), __riscv_vfmul(s903, a1722, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s902, a1722, vl1), __riscv_vfmul(s903, a1721, vl1), vl1));
            __riscv_vsseg2e64((Y + ((2)*((k1 + ((((12)*(j1)))*(m1)) + ((5)*(m1)))))), r210, vl1);
            r211 = __riscv_vset(__riscv_vset(rvvx2_19, 0, __riscv_vfsub(__riscv_vfmul(s910, a1723, vl1), __riscv_vfmul(s911, a1724, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s910, a1724, vl1), __riscv_vfmul(s911, a1723, vl1), vl1));
            __riscv_vsseg2e64((Y + ((2)*((k1 + ((((12)*(j1)))*(m1)) + ((6)*(m1)))))), r211, vl1);
            r212 = __riscv_vset(__riscv_vset(rvvx2_20, 0, __riscv_vfsub(__riscv_vfmul(s918, a1725, vl1), __riscv_vfmul(s919, a1726, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s918, a1726, vl1), __riscv_vfmul(s919, a1725, vl1), vl1));
            __riscv_vsseg2e64((Y + ((2)*((k1 + ((((12)*(j1)))*(m1)) + ((7)*(m1)))))), r212, vl1);
            r213 = __riscv_vset(__riscv_vset(rvvx2_21, 0, __riscv_vfsub(__riscv_vfmul(s896, a1727, vl1), __riscv_vfmul(s897, a1728, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s896, a1728, vl1), __riscv_vfmul(s897, a1727, vl1), vl1));
            __riscv_vsseg2e64((Y + ((2)*((k1 + ((((12)*(j1)))*(m1)) + ((8)*(m1)))))), r213, vl1);
            r214 = __riscv_vset(__riscv_vset(rvvx2_22, 0, __riscv_vfsub(__riscv_vfmul(s904, a1729, vl1), __riscv_vfmul(s905, a1730, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s904, a1730, vl1), __riscv_vfmul(s905, a1729, vl1), vl1));
            __riscv_vsseg2e64((Y + ((2)*((k1 + ((((12)*(j1)))*(m1)) + ((9)*(m1)))))), r214, vl1);
            r215 = __riscv_vset(__riscv_vset(rvvx2_23, 0, __riscv_vfsub(__riscv_vfmul(s912, a1731, vl1), __riscv_vfmul(s913, a1732, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s912, a1732, vl1), __riscv_vfmul(s913, a1731, vl1), vl1));
            __riscv_vsseg2e64((Y + ((2)*((k1 + ((((12)*(j1)))*(m1)) + ((10)*(m1)))))), r215, vl1);
            r216 = __riscv_vset(__riscv_vset(rvvx2_24, 0, __riscv_vfsub(__riscv_vfmul(s920, a1733, vl1), __riscv_vfmul(s921, a1734, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s920, a1734, vl1), __riscv_vfmul(s921, a1733, vl1), vl1));
            __riscv_vsseg2e64((Y + ((2)*((k1 + ((((12)*(j1)))*(m1)) + ((11)*(m1)))))), r216, vl1);
        }
    }
}
