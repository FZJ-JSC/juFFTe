// --------------------------------------------------------------------------------------------------
// SPDX-FileCopyrightText: juFFTe developers
// SPDX-License-Identifier: Apache-2.0
// --------------------------------------------------------------------------------------------------

/*
*/

#include <stdint.h>
#include <riscv_vector.h>

void dft7c_r32_(float *Y, float *X, int64_t *lp1, int64_t *mp1) {
    int64_t l1, m1;
    vfloat32m1x2_t r113, r114, r115, r116, r117, r118, r119, r120, 
            r121, r122, r123, r124, r125, r126, rvvx2_10, rvvx2_11, 
            rvvx2_12, rvvx2_13, rvvx2_14, rvvx2_8, rvvx2_9;
    vfloat32m1_t  s698, s699, s700, s701, s702, s703, s704, s705, 
            s706, s707, s708, s709, s710, s711, s712, s713, 
            s714, s715, s716, s717, s718, s719, s720, s721, 
            s722, s723, s724, s725, s726, s727, s728, s729, 
            s730, s731, s732, s733, s734, s735, s736, s737, 
            s738, s739, s740, s741, s742, s743, s744, s745, 
            s746, s747, s748, s749, s750, s751, s752, s753, 
            t1798, t1799, t1800, t1801, t1802, t1803, t1804, t1805, 
            t1806, t1807, t1808, t1809, t1810, t1811, t1812, t1813, 
            t1814, t1815, t1816, t1817, t1818, t1819, t1820, t1821, 
            t1822, t1823, t1824, t1825, t1826, t1827, t1828, t1829, 
            t1830, t1831, t1832, t1833, t1834, t1835, t1836, t1837, 
            t1838, t1839, t1840, t1841, t1842, t1843, t1844, t1845, 
            t1846, t1847, t1848, t1849;
    size_t vl1;
    l1 = *(lp1);
    m1 = *(mp1);
    for (size_t k1 = 0; k1 < m1; k1 += vl1) {
        vl1 = __riscv_vsetvl_e32m1(m1 - k1);
        r113 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*(k1))), vl1);
        s698 = __riscv_vget_f32m1(r113, 0);
        s699 = __riscv_vget_f32m1(r113, 1);
        r114 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*((k1 + ((l1)*(m1)))))), vl1);
        s700 = __riscv_vget_f32m1(r114, 0);
        s701 = __riscv_vget_f32m1(r114, 1);
        r115 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*((k1 + ((((2)*(l1)))*(m1)))))), vl1);
        s702 = __riscv_vget_f32m1(r115, 0);
        s703 = __riscv_vget_f32m1(r115, 1);
        r116 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*((k1 + ((((3)*(l1)))*(m1)))))), vl1);
        s704 = __riscv_vget_f32m1(r116, 0);
        s705 = __riscv_vget_f32m1(r116, 1);
        r117 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*((k1 + ((((4)*(l1)))*(m1)))))), vl1);
        s706 = __riscv_vget_f32m1(r117, 0);
        s707 = __riscv_vget_f32m1(r117, 1);
        r118 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*((k1 + ((((5)*(l1)))*(m1)))))), vl1);
        s708 = __riscv_vget_f32m1(r118, 0);
        s709 = __riscv_vget_f32m1(r118, 1);
        r119 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*((k1 + ((((6)*(l1)))*(m1)))))), vl1);
        s710 = __riscv_vget_f32m1(r119, 0);
        s711 = __riscv_vget_f32m1(r119, 1);
        t1798 = __riscv_vfadd(s702, s706, vl1);
        t1799 = __riscv_vfadd(s703, s707, vl1);
        t1800 = __riscv_vfadd(s700, t1798, vl1);
        t1801 = __riscv_vfadd(s701, t1799, vl1);
        t1802 = __riscv_vfnmsac(s700, 0.5, t1798, vl1);
        t1803 = __riscv_vfnmsac(s701, 0.5, t1799, vl1);
        s712 = __riscv_vfmul(__riscv_vfsub(s703, s707, vl1), 0.8660254037844386, vl1);
        s713 = __riscv_vfmul(__riscv_vfsub(s702, s706, vl1), 0.8660254037844386, vl1);
        t1804 = __riscv_vfadd(t1802, s712, vl1);
        t1805 = __riscv_vfsub(t1803, s713, vl1);
        t1806 = __riscv_vfsub(t1802, s712, vl1);
        t1807 = __riscv_vfadd(t1803, s713, vl1);
        t1808 = __riscv_vfadd(s710, s708, vl1);
        t1809 = __riscv_vfadd(s711, s709, vl1);
        t1810 = __riscv_vfadd(s704, t1808, vl1);
        t1811 = __riscv_vfadd(s705, t1809, vl1);
        t1812 = __riscv_vfnmsac(s704, 0.5, t1808, vl1);
        t1813 = __riscv_vfnmsac(s705, 0.5, t1809, vl1);
        s714 = __riscv_vfmul(__riscv_vfsub(s711, s709, vl1), 0.8660254037844386, vl1);
        s715 = __riscv_vfmul(__riscv_vfsub(s710, s708, vl1), 0.8660254037844386, vl1);
        t1814 = __riscv_vfadd(t1812, s714, vl1);
        t1815 = __riscv_vfsub(t1813, s715, vl1);
        t1816 = __riscv_vfsub(t1812, s714, vl1);
        t1817 = __riscv_vfadd(t1813, s715, vl1);
        s738 = __riscv_vfmacc(t1814, 1.7320508075688772, t1815, vl1);
        s716 = __riscv_vfmul(s738, 0.5, vl1);
        s739 = __riscv_vfnmsac(t1815, 1.7320508075688772, t1814, vl1);
        s717 = __riscv_vfmul(s739, 0.5, vl1);
        s740 = __riscv_vfnmsac(t1817, 0.57735026918962584, t1816, vl1);
        s718 = __riscv_vfmul(s740, 0.8660254037844386, vl1);
        s741 = __riscv_vfmacc(t1816, 0.57735026918962584, t1817, vl1);
        s719 = __riscv_vfmul(s741, 0.8660254037844386, vl1);
        t1818 = __riscv_vfadd(t1800, t1810, vl1);
        t1819 = __riscv_vfadd(t1801, t1811, vl1);
        t1820 = __riscv_vfadd(t1804, s716, vl1);
        t1821 = __riscv_vfadd(t1805, s717, vl1);
        t1822 = __riscv_vfsub(t1804, s716, vl1);
        t1823 = __riscv_vfsub(t1805, s717, vl1);
        t1824 = __riscv_vfadd(t1806, s718, vl1);
        t1825 = __riscv_vfsub(t1807, s719, vl1);
        t1826 = __riscv_vfsub(t1806, s718, vl1);
        t1827 = __riscv_vfadd(t1807, s719, vl1);
        t1828 = __riscv_vfnmsac(s698, 0.16666666666666666, t1818, vl1);
        t1829 = __riscv_vfnmsac(s699, 0.16666666666666666, t1819, vl1);
        s742 = __riscv_vfmacc(t1820, 0.41908315722758338, t1821, vl1);
        s720 = __riscv_vfmul(s742, 0.4066888930575896, vl1);
        s743 = __riscv_vfnmsac(t1821, 0.41908315722758338, t1820, vl1);
        s721 = __riscv_vfmul(s743, 0.4066888930575896, vl1);
        s744 = __riscv_vfmacc(t1824, 0.49572725516748389, t1825, vl1);
        s722 = __riscv_vfmul(s744, 0.39507823426270006, vl1);
        s745 = __riscv_vfnmsac(t1825, 0.49572725516748389, t1824, vl1);
        s723 = __riscv_vfmul(s745, 0.39507823426270006, vl1);
        s724 = __riscv_vfmul(__riscv_vfsub(t1801, t1811, vl1), 0.44095855184409843, vl1);
        s725 = __riscv_vfmul(__riscv_vfsub(t1800, t1810, vl1), 0.44095855184409843, vl1);
        s746 = __riscv_vfnmsac(t1822, 0.49572725516748389, t1823, vl1);
        s726 = __riscv_vfmul(s746, 0.39507823426270006, vl1);
        s747 = __riscv_vfmacc(t1822, 2.0172382889501304, t1823, vl1);
        s727 = __riscv_vfmul(s747, 0.1958510486474645, vl1);
        s748 = __riscv_vfnmsac(t1827, 2.386161273135941, t1826, vl1);
        s728 = __riscv_vfmul(s748, 0.17043646531196566, vl1);
        s749 = __riscv_vfmacc(t1826, 2.386161273135941, t1827, vl1);
        s729 = __riscv_vfmul(s749, 0.17043646531196566, vl1);
        t1830 = __riscv_vfadd(s722, s726, vl1);
        t1831 = __riscv_vfadd(s723, s727, vl1);
        t1832 = __riscv_vfadd(t1828, t1830, vl1);
        t1833 = __riscv_vfadd(t1829, t1831, vl1);
        t1834 = __riscv_vfnmsac(t1828, 0.5, t1830, vl1);
        t1835 = __riscv_vfnmsac(t1829, 0.5, t1831, vl1);
        s730 = __riscv_vfmul(__riscv_vfsub(s723, s727, vl1), 0.8660254037844386, vl1);
        s731 = __riscv_vfmul(__riscv_vfsub(s722, s726, vl1), 0.8660254037844386, vl1);
        t1836 = __riscv_vfadd(t1834, s730, vl1);
        t1837 = __riscv_vfsub(t1835, s731, vl1);
        t1838 = __riscv_vfsub(t1834, s730, vl1);
        t1839 = __riscv_vfadd(t1835, s731, vl1);
        t1840 = __riscv_vfadd(s724, s728, vl1);
        t1841 = __riscv_vfadd(s725, s729, vl1);
        t1842 = __riscv_vfadd(s720, t1840, vl1);
        t1843 = __riscv_vfsub(s721, t1841, vl1);
        t1844 = __riscv_vfnmsac(s720, 0.5, t1840, vl1);
        t1845 = __riscv_vfmacc(s721, 0.5, t1841, vl1);
        s732 = __riscv_vfmul(__riscv_vfsub(s729, s725, vl1), 0.8660254037844386, vl1);
        s733 = __riscv_vfmul(__riscv_vfsub(s724, s728, vl1), 0.8660254037844386, vl1);
        t1846 = __riscv_vfadd(t1844, s732, vl1);
        t1847 = __riscv_vfsub(t1845, s733, vl1);
        t1848 = __riscv_vfsub(t1844, s732, vl1);
        t1849 = __riscv_vfadd(t1845, s733, vl1);
        s750 = __riscv_vfmacc(t1846, 1.7320508075688772, t1847, vl1);
        s734 = __riscv_vfmul(s750, 0.5, vl1);
        s751 = __riscv_vfnmsac(t1847, 1.7320508075688772, t1846, vl1);
        s735 = __riscv_vfmul(s751, 0.5, vl1);
        s752 = __riscv_vfnmsac(t1849, 0.57735026918962584, t1848, vl1);
        s736 = __riscv_vfmul(s752, 0.8660254037844386, vl1);
        s753 = __riscv_vfmacc(t1848, 0.57735026918962584, t1849, vl1);
        s737 = __riscv_vfmul(s753, 0.8660254037844386, vl1);
        r120 = __riscv_vset(__riscv_vset(rvvx2_8, 0, __riscv_vfadd(s698, t1818, vl1)), 1, __riscv_vfadd(s699, t1819, vl1));
        __riscv_vsseg2e32((Y + ((2)*(k1))), r120, vl1);
        r121 = __riscv_vset(__riscv_vset(rvvx2_9, 0, __riscv_vfadd(t1832, t1842, vl1)), 1, __riscv_vfadd(t1833, t1843, vl1));
        __riscv_vsseg2e32((Y + ((2)*((k1 + m1)))), r121, vl1);
        r122 = __riscv_vset(__riscv_vset(rvvx2_10, 0, __riscv_vfadd(t1838, s736, vl1)), 1, __riscv_vfsub(t1839, s737, vl1));
        __riscv_vsseg2e32((Y + ((2)*((k1 + ((2)*(m1)))))), r122, vl1);
        r123 = __riscv_vset(__riscv_vset(rvvx2_11, 0, __riscv_vfadd(t1836, s734, vl1)), 1, __riscv_vfadd(t1837, s735, vl1));
        __riscv_vsseg2e32((Y + ((2)*((k1 + ((3)*(m1)))))), r123, vl1);
        r124 = __riscv_vset(__riscv_vset(rvvx2_12, 0, __riscv_vfsub(t1836, s734, vl1)), 1, __riscv_vfsub(t1837, s735, vl1));
        __riscv_vsseg2e32((Y + ((2)*((k1 + ((4)*(m1)))))), r124, vl1);
        r125 = __riscv_vset(__riscv_vset(rvvx2_13, 0, __riscv_vfsub(t1838, s736, vl1)), 1, __riscv_vfadd(t1839, s737, vl1));
        __riscv_vsseg2e32((Y + ((2)*((k1 + ((5)*(m1)))))), r125, vl1);
        r126 = __riscv_vset(__riscv_vset(rvvx2_14, 0, __riscv_vfsub(t1832, t1842, vl1)), 1, __riscv_vfsub(t1833, t1843, vl1));
        __riscv_vsseg2e32((Y + ((2)*((k1 + ((6)*(m1)))))), r126, vl1);
    }
}
