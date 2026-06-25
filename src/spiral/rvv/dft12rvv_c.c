// --------------------------------------------------------------------------------------------------
// SPDX-FileCopyrightText: juFFTe developers
// SPDX-License-Identifier: Apache-2.0
// --------------------------------------------------------------------------------------------------

/*
*/

#include <stdint.h>
#include <riscv_vector.h>

void dft12c_(double *Y, double *X, int *lp1, int *mp1) {
    int l1, m1;
    vfloat64m1x2_t r193, r194, r195, r196, r197, r198, r199, r200, 
            r201, r202, r203, r204, r205, r206, r207, r208, 
            r209, r210, r211, r212, r213, r214, r215, r216, 
            rvvx2_13, rvvx2_14, rvvx2_15, rvvx2_16, rvvx2_17, rvvx2_18, rvvx2_19, rvvx2_20, 
            rvvx2_21, rvvx2_22, rvvx2_23, rvvx2_24;
    vfloat64m1_t  s794, s795, s796, s797, s798, s799, s800, s801, 
            s802, s803, s804, s805, s806, s807, s808, s809, 
            s810, s811, s812, s813, s814, s815, s816, s817, 
            s818, s819, s820, s821, s822, s823, s824, s825, 
            s826, s827, s828, s829, s830, s831, s832, s833, 
            s834, s835, s836, s837, s838, s839, s840, s841, 
            t2714, t2715, t2716, t2717, t2718, t2719, t2720, t2721, 
            t2722, t2723, t2724, t2725, t2726, t2727, t2728, t2729, 
            t2730, t2731, t2732, t2733, t2734, t2735, t2736, t2737, 
            t2738, t2739, t2740, t2741, t2742, t2743, t2744, t2745, 
            t2746, t2747, t2748, t2749, t2750, t2751, t2752, t2753, 
            t2754, t2755, t2756, t2757, t2758, t2759, t2760, t2761, 
            t2762, t2763, t2764, t2765, t2766, t2767, t2768, t2769, 
            t2770, t2771, t2772, t2773, t2774, t2775, t2776, t2777;
    size_t vl1;
    l1 = *(lp1);
    m1 = *(mp1);
    for (size_t k1 = 0; k1 < m1; k1 += vl1) {
        vl1 = __riscv_vsetvl_e64m1(m1 - k1);
        r193 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*(k1))), vl1);
        s794 = __riscv_vget_f64m1(r193, 0);
        s795 = __riscv_vget_f64m1(r193, 1);
        r194 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((l1)*(m1)))))), vl1);
        s796 = __riscv_vget_f64m1(r194, 0);
        s797 = __riscv_vget_f64m1(r194, 1);
        r195 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((((2)*(l1)))*(m1)))))), vl1);
        s798 = __riscv_vget_f64m1(r195, 0);
        s799 = __riscv_vget_f64m1(r195, 1);
        r196 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((((3)*(l1)))*(m1)))))), vl1);
        s800 = __riscv_vget_f64m1(r196, 0);
        s801 = __riscv_vget_f64m1(r196, 1);
        r197 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((((4)*(l1)))*(m1)))))), vl1);
        s802 = __riscv_vget_f64m1(r197, 0);
        s803 = __riscv_vget_f64m1(r197, 1);
        r198 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((((5)*(l1)))*(m1)))))), vl1);
        s804 = __riscv_vget_f64m1(r198, 0);
        s805 = __riscv_vget_f64m1(r198, 1);
        r199 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((((6)*(l1)))*(m1)))))), vl1);
        s806 = __riscv_vget_f64m1(r199, 0);
        s807 = __riscv_vget_f64m1(r199, 1);
        r200 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((((7)*(l1)))*(m1)))))), vl1);
        s808 = __riscv_vget_f64m1(r200, 0);
        s809 = __riscv_vget_f64m1(r200, 1);
        r201 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((((8)*(l1)))*(m1)))))), vl1);
        s810 = __riscv_vget_f64m1(r201, 0);
        s811 = __riscv_vget_f64m1(r201, 1);
        r202 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((((9)*(l1)))*(m1)))))), vl1);
        s812 = __riscv_vget_f64m1(r202, 0);
        s813 = __riscv_vget_f64m1(r202, 1);
        r203 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((((10)*(l1)))*(m1)))))), vl1);
        s814 = __riscv_vget_f64m1(r203, 0);
        s815 = __riscv_vget_f64m1(r203, 1);
        r204 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((((11)*(l1)))*(m1)))))), vl1);
        s816 = __riscv_vget_f64m1(r204, 0);
        s817 = __riscv_vget_f64m1(r204, 1);
        t2714 = __riscv_vfadd(s794, s806, vl1);
        t2715 = __riscv_vfadd(s795, s807, vl1);
        t2716 = __riscv_vfsub(s794, s806, vl1);
        t2717 = __riscv_vfsub(s795, s807, vl1);
        t2718 = __riscv_vfadd(s800, s812, vl1);
        t2719 = __riscv_vfadd(s801, s813, vl1);
        t2720 = __riscv_vfsub(s800, s812, vl1);
        t2721 = __riscv_vfsub(s801, s813, vl1);
        t2722 = __riscv_vfadd(t2714, t2718, vl1);
        t2723 = __riscv_vfadd(t2715, t2719, vl1);
        t2724 = __riscv_vfsub(t2714, t2718, vl1);
        t2725 = __riscv_vfsub(t2715, t2719, vl1);
        t2726 = __riscv_vfadd(t2716, t2721, vl1);
        t2727 = __riscv_vfsub(t2717, t2720, vl1);
        t2728 = __riscv_vfsub(t2716, t2721, vl1);
        t2729 = __riscv_vfadd(t2717, t2720, vl1);
        t2730 = __riscv_vfadd(s796, s808, vl1);
        t2731 = __riscv_vfadd(s797, s809, vl1);
        t2732 = __riscv_vfsub(s796, s808, vl1);
        t2733 = __riscv_vfsub(s797, s809, vl1);
        t2734 = __riscv_vfadd(s802, s814, vl1);
        t2735 = __riscv_vfadd(s803, s815, vl1);
        t2736 = __riscv_vfsub(s802, s814, vl1);
        t2737 = __riscv_vfsub(s803, s815, vl1);
        t2738 = __riscv_vfadd(t2730, t2734, vl1);
        t2739 = __riscv_vfadd(t2731, t2735, vl1);
        t2740 = __riscv_vfsub(t2730, t2734, vl1);
        t2741 = __riscv_vfsub(t2731, t2735, vl1);
        s834 = __riscv_vfmacc(t2740, 1.7320508075688772, t2741, vl1);
        s818 = __riscv_vfmul(s834, 0.5, vl1);
        s835 = __riscv_vfnmsac(t2741, 1.7320508075688772, t2740, vl1);
        s819 = __riscv_vfmul(s835, 0.5, vl1);
        t2742 = __riscv_vfadd(t2732, t2737, vl1);
        t2743 = __riscv_vfsub(t2733, t2736, vl1);
        t2744 = __riscv_vfsub(t2732, t2737, vl1);
        t2745 = __riscv_vfadd(t2733, t2736, vl1);
        s836 = __riscv_vfmacc(t2742, 0.57735026918962584, t2743, vl1);
        s820 = __riscv_vfmul(s836, 0.8660254037844386, vl1);
        s837 = __riscv_vfnmsac(t2743, 0.57735026918962584, t2742, vl1);
        s821 = __riscv_vfmul(s837, 0.8660254037844386, vl1);
        t2746 = __riscv_vfadd(s798, s810, vl1);
        t2747 = __riscv_vfadd(s799, s811, vl1);
        t2748 = __riscv_vfsub(s798, s810, vl1);
        t2749 = __riscv_vfsub(s799, s811, vl1);
        t2750 = __riscv_vfadd(s804, s816, vl1);
        t2751 = __riscv_vfadd(s805, s817, vl1);
        t2752 = __riscv_vfsub(s804, s816, vl1);
        t2753 = __riscv_vfsub(s805, s817, vl1);
        t2754 = __riscv_vfadd(t2746, t2750, vl1);
        t2755 = __riscv_vfadd(t2747, t2751, vl1);
        t2756 = __riscv_vfsub(t2746, t2750, vl1);
        t2757 = __riscv_vfsub(t2747, t2751, vl1);
        s838 = __riscv_vfnmsac(t2757, 0.57735026918962584, t2756, vl1);
        s822 = __riscv_vfmul(s838, 0.8660254037844386, vl1);
        s839 = __riscv_vfmacc(t2756, 0.57735026918962584, t2757, vl1);
        s823 = __riscv_vfmul(s839, 0.8660254037844386, vl1);
        t2758 = __riscv_vfadd(t2748, t2753, vl1);
        t2759 = __riscv_vfsub(t2749, t2752, vl1);
        t2760 = __riscv_vfsub(t2748, t2753, vl1);
        t2761 = __riscv_vfadd(t2749, t2752, vl1);
        s840 = __riscv_vfmacc(t2758, 1.7320508075688772, t2759, vl1);
        s824 = __riscv_vfmul(s840, 0.5, vl1);
        s841 = __riscv_vfnmsac(t2759, 1.7320508075688772, t2758, vl1);
        s825 = __riscv_vfmul(s841, 0.5, vl1);
        t2762 = __riscv_vfadd(t2738, t2754, vl1);
        t2763 = __riscv_vfadd(t2739, t2755, vl1);
        t2764 = __riscv_vfnmsac(t2722, 0.5, t2762, vl1);
        t2765 = __riscv_vfnmsac(t2723, 0.5, t2763, vl1);
        s826 = __riscv_vfmul(__riscv_vfsub(t2739, t2755, vl1), 0.8660254037844386, vl1);
        s827 = __riscv_vfmul(__riscv_vfsub(t2738, t2754, vl1), 0.8660254037844386, vl1);
        t2766 = __riscv_vfadd(s820, s824, vl1);
        t2767 = __riscv_vfadd(s821, s825, vl1);
        t2768 = __riscv_vfnmsac(t2726, 0.5, t2766, vl1);
        t2769 = __riscv_vfnmsac(t2727, 0.5, t2767, vl1);
        s828 = __riscv_vfmul(__riscv_vfsub(s821, s825, vl1), 0.8660254037844386, vl1);
        s829 = __riscv_vfmul(__riscv_vfsub(s820, s824, vl1), 0.8660254037844386, vl1);
        t2770 = __riscv_vfadd(s818, s822, vl1);
        t2771 = __riscv_vfsub(s819, s823, vl1);
        t2772 = __riscv_vfnmsac(t2724, 0.5, t2770, vl1);
        t2773 = __riscv_vfnmsac(t2725, 0.5, t2771, vl1);
        s830 = __riscv_vfmul(__riscv_vfadd(s819, s823, vl1), 0.8660254037844386, vl1);
        s831 = __riscv_vfmul(__riscv_vfsub(s818, s822, vl1), 0.8660254037844386, vl1);
        t2774 = __riscv_vfsub(t2745, t2760, vl1);
        t2775 = __riscv_vfadd(t2744, t2761, vl1);
        t2776 = __riscv_vfnmsac(t2728, 0.5, t2774, vl1);
        t2777 = __riscv_vfmacc(t2729, 0.5, t2775, vl1);
        s832 = __riscv_vfmul(__riscv_vfsub(t2761, t2744, vl1), 0.8660254037844386, vl1);
        s833 = __riscv_vfmul(__riscv_vfadd(t2745, t2760, vl1), 0.8660254037844386, vl1);
        r205 = __riscv_vset(__riscv_vset(rvvx2_13, 0, __riscv_vfadd(t2722, t2762, vl1)), 1, __riscv_vfadd(t2723, t2763, vl1));
        __riscv_vsseg2e64((Y + ((2)*(k1))), r205, vl1);
        r206 = __riscv_vset(__riscv_vset(rvvx2_14, 0, __riscv_vfadd(t2726, t2766, vl1)), 1, __riscv_vfadd(t2727, t2767, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + m1)))), r206, vl1);
        r207 = __riscv_vset(__riscv_vset(rvvx2_15, 0, __riscv_vfadd(t2724, t2770, vl1)), 1, __riscv_vfadd(t2725, t2771, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + ((2)*(m1)))))), r207, vl1);
        r208 = __riscv_vset(__riscv_vset(rvvx2_16, 0, __riscv_vfadd(t2728, t2774, vl1)), 1, __riscv_vfsub(t2729, t2775, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + ((3)*(m1)))))), r208, vl1);
        r209 = __riscv_vset(__riscv_vset(rvvx2_17, 0, __riscv_vfadd(t2764, s826, vl1)), 1, __riscv_vfsub(t2765, s827, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + ((4)*(m1)))))), r209, vl1);
        r210 = __riscv_vset(__riscv_vset(rvvx2_18, 0, __riscv_vfadd(t2768, s828, vl1)), 1, __riscv_vfsub(t2769, s829, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + ((5)*(m1)))))), r210, vl1);
        r211 = __riscv_vset(__riscv_vset(rvvx2_19, 0, __riscv_vfadd(t2772, s830, vl1)), 1, __riscv_vfsub(t2773, s831, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + ((6)*(m1)))))), r211, vl1);
        r212 = __riscv_vset(__riscv_vset(rvvx2_20, 0, __riscv_vfadd(t2776, s832, vl1)), 1, __riscv_vfsub(t2777, s833, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + ((7)*(m1)))))), r212, vl1);
        r213 = __riscv_vset(__riscv_vset(rvvx2_21, 0, __riscv_vfsub(t2764, s826, vl1)), 1, __riscv_vfadd(t2765, s827, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + ((8)*(m1)))))), r213, vl1);
        r214 = __riscv_vset(__riscv_vset(rvvx2_22, 0, __riscv_vfsub(t2768, s828, vl1)), 1, __riscv_vfadd(t2769, s829, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + ((9)*(m1)))))), r214, vl1);
        r215 = __riscv_vset(__riscv_vset(rvvx2_23, 0, __riscv_vfsub(t2772, s830, vl1)), 1, __riscv_vfadd(t2773, s831, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + ((10)*(m1)))))), r215, vl1);
        r216 = __riscv_vset(__riscv_vset(rvvx2_24, 0, __riscv_vfsub(t2776, s832, vl1)), 1, __riscv_vfadd(t2777, s833, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + ((11)*(m1)))))), r216, vl1);
    }
}
