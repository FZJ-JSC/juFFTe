// --------------------------------------------------------------------------------------------------
// SPDX-FileCopyrightText: juFFTe developers
// SPDX-License-Identifier: Apache-2.0
// --------------------------------------------------------------------------------------------------

/*
*/

#include <stdint.h>
#include <riscv_vector.h>

void dft7b_(double *Y, double *X, double *TW1, int *lp1, int *mp1) {
    double a1138, a1139, a1140, a1141, a1142, a1143, a1144, a1145, 
            a1146, a1147, a1148, a1149;
    int a1136, a1137, j1, l1, m1;
    vfloat64m1x2_t r113, r114, r115, r116, r117, r118, r119, r120, 
            r121, r122, r123, r124, r125, r126, rvvx2_10, rvvx2_11, 
            rvvx2_12, rvvx2_13, rvvx2_14, rvvx2_8, rvvx2_9;
    vfloat64m1_t  s734, s735, s736, s737, s738, s739, s740, s741, 
            s742, s743, s744, s745, s746, s747, s748, s749, 
            s750, s751, s752, s753, s754, s755, s756, s757, 
            s758, s759, s760, s761, s762, s763, s764, s765, 
            s766, s767, s768, s769, s770, s771, s772, s773, 
            s774, s775, s776, s777, s778, s779, s780, s781, 
            s782, s783, s784, s785, s786, s787, s788, s789, 
            s790, s791, s792, s793, s794, s795, s796, s797, 
            s798, s799, s800, s801, t1799, t1800, t1801, t1802, 
            t1803, t1804, t1805, t1806, t1807, t1808, t1809, t1810, 
            t1811, t1812, t1813, t1814, t1815, t1816, t1817, t1818, 
            t1819, t1820, t1821, t1822, t1823, t1824, t1825, t1826, 
            t1827, t1828, t1829, t1830, t1831, t1832, t1833, t1834, 
            t1835, t1836, t1837, t1838, t1839, t1840, t1841, t1842, 
            t1843, t1844, t1845, t1846, t1847, t1848, t1849, t1850;
    size_t vl1;
    l1 = *(lp1);
    m1 = *(mp1);
    for(int j1 = 1; j1 < l1; j1++) {
        for (size_t k1 = 0; k1 < m1; k1 += vl1) {
            vl1 = __riscv_vsetvl_e64m1(m1 - k1);
            a1136 = (k1 + ((j1)*(m1)));
            r113 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*(a1136))), vl1);
            s734 = __riscv_vget_f64m1(r113, 0);
            s735 = __riscv_vget_f64m1(r113, 1);
            r114 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((a1136 + ((l1)*(m1)))))), vl1);
            s736 = __riscv_vget_f64m1(r114, 0);
            s737 = __riscv_vget_f64m1(r114, 1);
            r115 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((a1136 + ((((2)*(l1)))*(m1)))))), vl1);
            s738 = __riscv_vget_f64m1(r115, 0);
            s739 = __riscv_vget_f64m1(r115, 1);
            r116 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((a1136 + ((((3)*(l1)))*(m1)))))), vl1);
            s740 = __riscv_vget_f64m1(r116, 0);
            s741 = __riscv_vget_f64m1(r116, 1);
            r117 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((a1136 + ((((4)*(l1)))*(m1)))))), vl1);
            s742 = __riscv_vget_f64m1(r117, 0);
            s743 = __riscv_vget_f64m1(r117, 1);
            r118 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((a1136 + ((((5)*(l1)))*(m1)))))), vl1);
            s744 = __riscv_vget_f64m1(r118, 0);
            s745 = __riscv_vget_f64m1(r118, 1);
            r119 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((a1136 + ((((6)*(l1)))*(m1)))))), vl1);
            s746 = __riscv_vget_f64m1(r119, 0);
            s747 = __riscv_vget_f64m1(r119, 1);
            t1799 = __riscv_vfadd(s738, s742, vl1);
            t1800 = __riscv_vfadd(s739, s743, vl1);
            t1801 = __riscv_vfadd(s736, t1799, vl1);
            t1802 = __riscv_vfadd(s737, t1800, vl1);
            t1803 = __riscv_vfnmsac(s736, 0.5, t1799, vl1);
            t1804 = __riscv_vfnmsac(s737, 0.5, t1800, vl1);
            s748 = __riscv_vfmul(__riscv_vfsub(s739, s743, vl1), 0.8660254037844386, vl1);
            s749 = __riscv_vfmul(__riscv_vfsub(s738, s742, vl1), 0.8660254037844386, vl1);
            t1805 = __riscv_vfadd(t1803, s748, vl1);
            t1806 = __riscv_vfsub(t1804, s749, vl1);
            t1807 = __riscv_vfsub(t1803, s748, vl1);
            t1808 = __riscv_vfadd(t1804, s749, vl1);
            t1809 = __riscv_vfadd(s746, s744, vl1);
            t1810 = __riscv_vfadd(s747, s745, vl1);
            t1811 = __riscv_vfadd(s740, t1809, vl1);
            t1812 = __riscv_vfadd(s741, t1810, vl1);
            t1813 = __riscv_vfnmsac(s740, 0.5, t1809, vl1);
            t1814 = __riscv_vfnmsac(s741, 0.5, t1810, vl1);
            s750 = __riscv_vfmul(__riscv_vfsub(s747, s745, vl1), 0.8660254037844386, vl1);
            s751 = __riscv_vfmul(__riscv_vfsub(s746, s744, vl1), 0.8660254037844386, vl1);
            t1815 = __riscv_vfadd(t1813, s750, vl1);
            t1816 = __riscv_vfsub(t1814, s751, vl1);
            t1817 = __riscv_vfsub(t1813, s750, vl1);
            t1818 = __riscv_vfadd(t1814, s751, vl1);
            s786 = __riscv_vfmacc(t1815, 1.7320508075688772, t1816, vl1);
            s752 = __riscv_vfmul(s786, 0.5, vl1);
            s787 = __riscv_vfnmsac(t1816, 1.7320508075688772, t1815, vl1);
            s753 = __riscv_vfmul(s787, 0.5, vl1);
            s788 = __riscv_vfnmsac(t1818, 0.57735026918962584, t1817, vl1);
            s754 = __riscv_vfmul(s788, 0.8660254037844386, vl1);
            s789 = __riscv_vfmacc(t1817, 0.57735026918962584, t1818, vl1);
            s755 = __riscv_vfmul(s789, 0.8660254037844386, vl1);
            t1819 = __riscv_vfadd(t1801, t1811, vl1);
            t1820 = __riscv_vfadd(t1802, t1812, vl1);
            t1821 = __riscv_vfadd(t1805, s752, vl1);
            t1822 = __riscv_vfadd(t1806, s753, vl1);
            t1823 = __riscv_vfsub(t1805, s752, vl1);
            t1824 = __riscv_vfsub(t1806, s753, vl1);
            t1825 = __riscv_vfadd(t1807, s754, vl1);
            t1826 = __riscv_vfsub(t1808, s755, vl1);
            t1827 = __riscv_vfsub(t1807, s754, vl1);
            t1828 = __riscv_vfadd(t1808, s755, vl1);
            t1829 = __riscv_vfnmsac(s734, 0.16666666666666666, t1819, vl1);
            t1830 = __riscv_vfnmsac(s735, 0.16666666666666666, t1820, vl1);
            s790 = __riscv_vfmacc(t1821, 0.41908315722758338, t1822, vl1);
            s756 = __riscv_vfmul(s790, 0.4066888930575896, vl1);
            s791 = __riscv_vfnmsac(t1822, 0.41908315722758338, t1821, vl1);
            s757 = __riscv_vfmul(s791, 0.4066888930575896, vl1);
            s792 = __riscv_vfmacc(t1825, 0.49572725516748389, t1826, vl1);
            s758 = __riscv_vfmul(s792, 0.39507823426270006, vl1);
            s793 = __riscv_vfnmsac(t1826, 0.49572725516748389, t1825, vl1);
            s759 = __riscv_vfmul(s793, 0.39507823426270006, vl1);
            s760 = __riscv_vfmul(__riscv_vfsub(t1802, t1812, vl1), 0.44095855184409843, vl1);
            s761 = __riscv_vfmul(__riscv_vfsub(t1801, t1811, vl1), 0.44095855184409843, vl1);
            s794 = __riscv_vfnmsac(t1823, 0.49572725516748389, t1824, vl1);
            s762 = __riscv_vfmul(s794, 0.39507823426270006, vl1);
            s795 = __riscv_vfmacc(t1823, 2.0172382889501304, t1824, vl1);
            s763 = __riscv_vfmul(s795, 0.1958510486474645, vl1);
            s796 = __riscv_vfnmsac(t1828, 2.386161273135941, t1827, vl1);
            s764 = __riscv_vfmul(s796, 0.17043646531196566, vl1);
            s797 = __riscv_vfmacc(t1827, 2.386161273135941, t1828, vl1);
            s765 = __riscv_vfmul(s797, 0.17043646531196566, vl1);
            t1831 = __riscv_vfadd(s758, s762, vl1);
            t1832 = __riscv_vfadd(s759, s763, vl1);
            t1833 = __riscv_vfadd(t1829, t1831, vl1);
            t1834 = __riscv_vfadd(t1830, t1832, vl1);
            t1835 = __riscv_vfnmsac(t1829, 0.5, t1831, vl1);
            t1836 = __riscv_vfnmsac(t1830, 0.5, t1832, vl1);
            s766 = __riscv_vfmul(__riscv_vfsub(s759, s763, vl1), 0.8660254037844386, vl1);
            s767 = __riscv_vfmul(__riscv_vfsub(s758, s762, vl1), 0.8660254037844386, vl1);
            t1837 = __riscv_vfadd(t1835, s766, vl1);
            t1838 = __riscv_vfsub(t1836, s767, vl1);
            t1839 = __riscv_vfsub(t1835, s766, vl1);
            t1840 = __riscv_vfadd(t1836, s767, vl1);
            t1841 = __riscv_vfadd(s760, s764, vl1);
            t1842 = __riscv_vfadd(s761, s765, vl1);
            t1843 = __riscv_vfadd(s756, t1841, vl1);
            t1844 = __riscv_vfsub(s757, t1842, vl1);
            t1845 = __riscv_vfnmsac(s756, 0.5, t1841, vl1);
            t1846 = __riscv_vfmacc(s757, 0.5, t1842, vl1);
            s768 = __riscv_vfmul(__riscv_vfsub(s765, s761, vl1), 0.8660254037844386, vl1);
            s769 = __riscv_vfmul(__riscv_vfsub(s760, s764, vl1), 0.8660254037844386, vl1);
            t1847 = __riscv_vfadd(t1845, s768, vl1);
            t1848 = __riscv_vfsub(t1846, s769, vl1);
            t1849 = __riscv_vfsub(t1845, s768, vl1);
            t1850 = __riscv_vfadd(t1846, s769, vl1);
            s798 = __riscv_vfmacc(t1847, 1.7320508075688772, t1848, vl1);
            s770 = __riscv_vfmul(s798, 0.5, vl1);
            s799 = __riscv_vfnmsac(t1848, 1.7320508075688772, t1847, vl1);
            s771 = __riscv_vfmul(s799, 0.5, vl1);
            s800 = __riscv_vfnmsac(t1850, 0.57735026918962584, t1849, vl1);
            s772 = __riscv_vfmul(s800, 0.8660254037844386, vl1);
            s801 = __riscv_vfmacc(t1849, 0.57735026918962584, t1850, vl1);
            s773 = __riscv_vfmul(s801, 0.8660254037844386, vl1);
            s774 = __riscv_vfadd(t1833, t1843, vl1);
            s775 = __riscv_vfadd(t1834, t1844, vl1);
            s776 = __riscv_vfsub(t1833, t1843, vl1);
            s777 = __riscv_vfsub(t1834, t1844, vl1);
            s778 = __riscv_vfadd(t1837, s770, vl1);
            s779 = __riscv_vfadd(t1838, s771, vl1);
            s780 = __riscv_vfsub(t1837, s770, vl1);
            s781 = __riscv_vfsub(t1838, s771, vl1);
            s782 = __riscv_vfadd(t1839, s772, vl1);
            s783 = __riscv_vfsub(t1840, s773, vl1);
            s784 = __riscv_vfsub(t1839, s772, vl1);
            s785 = __riscv_vfadd(t1840, s773, vl1);
            a1137 = ((12)*(j1));
            a1138 = TW1[a1137];
            a1139 = TW1[(a1137 + 1)];
            a1140 = TW1[(a1137 + 2)];
            a1141 = TW1[(a1137 + 3)];
            a1142 = TW1[(a1137 + 4)];
            a1143 = TW1[(a1137 + 5)];
            a1144 = TW1[(a1137 + 6)];
            a1145 = TW1[(a1137 + 7)];
            a1146 = TW1[(a1137 + 8)];
            a1147 = TW1[(a1137 + 9)];
            a1148 = TW1[(a1137 + 10)];
            a1149 = TW1[(a1137 + 11)];
            r120 = __riscv_vset(__riscv_vset(rvvx2_8, 0, __riscv_vfadd(s734, t1819, vl1)), 1, __riscv_vfadd(s735, t1820, vl1));
            __riscv_vsseg2e64((Y + ((2)*((k1 + ((((7)*(j1)))*(m1)))))), r120, vl1);
            r121 = __riscv_vset(__riscv_vset(rvvx2_9, 0, __riscv_vfsub(__riscv_vfmul(s774, a1138, vl1), __riscv_vfmul(s775, a1139, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s774, a1139, vl1), __riscv_vfmul(s775, a1138, vl1), vl1));
            __riscv_vsseg2e64((Y + ((2)*((k1 + ((((7)*(j1)))*(m1)) + m1)))), r121, vl1);
            r122 = __riscv_vset(__riscv_vset(rvvx2_10, 0, __riscv_vfsub(__riscv_vfmul(s782, a1140, vl1), __riscv_vfmul(s783, a1141, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s782, a1141, vl1), __riscv_vfmul(s783, a1140, vl1), vl1));
            __riscv_vsseg2e64((Y + ((2)*((k1 + ((((7)*(j1)))*(m1)) + ((2)*(m1)))))), r122, vl1);
            r123 = __riscv_vset(__riscv_vset(rvvx2_11, 0, __riscv_vfsub(__riscv_vfmul(s778, a1142, vl1), __riscv_vfmul(s779, a1143, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s778, a1143, vl1), __riscv_vfmul(s779, a1142, vl1), vl1));
            __riscv_vsseg2e64((Y + ((2)*((k1 + ((((7)*(j1)))*(m1)) + ((3)*(m1)))))), r123, vl1);
            r124 = __riscv_vset(__riscv_vset(rvvx2_12, 0, __riscv_vfsub(__riscv_vfmul(s780, a1144, vl1), __riscv_vfmul(s781, a1145, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s780, a1145, vl1), __riscv_vfmul(s781, a1144, vl1), vl1));
            __riscv_vsseg2e64((Y + ((2)*((k1 + ((((7)*(j1)))*(m1)) + ((4)*(m1)))))), r124, vl1);
            r125 = __riscv_vset(__riscv_vset(rvvx2_13, 0, __riscv_vfsub(__riscv_vfmul(s784, a1146, vl1), __riscv_vfmul(s785, a1147, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s784, a1147, vl1), __riscv_vfmul(s785, a1146, vl1), vl1));
            __riscv_vsseg2e64((Y + ((2)*((k1 + ((((7)*(j1)))*(m1)) + ((5)*(m1)))))), r125, vl1);
            r126 = __riscv_vset(__riscv_vset(rvvx2_14, 0, __riscv_vfsub(__riscv_vfmul(s776, a1148, vl1), __riscv_vfmul(s777, a1149, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s776, a1149, vl1), __riscv_vfmul(s777, a1148, vl1), vl1));
            __riscv_vsseg2e64((Y + ((2)*((k1 + ((((7)*(j1)))*(m1)) + ((6)*(m1)))))), r126, vl1);
        }
    }
}
