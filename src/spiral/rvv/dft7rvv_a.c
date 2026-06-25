// --------------------------------------------------------------------------------------------------
// SPDX-FileCopyrightText: juFFTe developers
// SPDX-License-Identifier: Apache-2.0
// --------------------------------------------------------------------------------------------------

/*
*/

#include <stdint.h>
#include <riscv_vector.h>

void dft7a_(double *Y, double *X, double *TW1, int *lp1) {
    int l1;
    double *a1072;
    vfloat64m1x2_t r50, r51, r52, r53, r54, r55, r56;
    vfloat64m1_t  a1073, a1074, a1075, a1076, a1077, a1078, a1079, a1080, 
            a1081, a1082, a1083, a1084, s748, s749, s750, s751, 
            s752, s753, s754, s755, s756, s757, s758, s759, 
            s760, s761, s762, s763, s764, s765, s766, s767, 
            s768, s769, s770, s771, s772, s773, s774, s775, 
            s776, s777, s778, s779, s780, s781, s782, s783, 
            s784, s785, s786, s787, s788, s789, s790, s791, 
            s792, s793, s794, s795, s796, s797, s798, s799, 
            s800, s801, s802, s803, s804, s805, s806, s807, 
            s808, s809, s810, s811, s812, s813, s814, s815, 
            s816, s817, s818, s819, s820, s821, s822, s823, 
            s824, s825, s826, s827, s828, s829, t1799, t1800, 
            t1801, t1802, t1803, t1804, t1805, t1806, t1807, t1808, 
            t1809, t1810, t1811, t1812, t1813, t1814, t1815, t1816, 
            t1817, t1818, t1819, t1820, t1821, t1822, t1823, t1824, 
            t1825, t1826, t1827, t1828, t1829, t1830, t1831, t1832, 
            t1833, t1834, t1835, t1836, t1837, t1838, t1839, t1840, 
            t1841, t1842, t1843, t1844, t1845, t1846, t1847, t1848, 
            t1849, t1850;
    size_t vl1;
    l1 = *(lp1);
    for (size_t j1 = 0; j1 < l1; j1 += vl1) {
        vl1 = __riscv_vsetvl_e64m1(l1 - j1);
        r50 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*(j1))), vl1);
        s748 = __riscv_vget_f64m1(r50, 0);
        s749 = __riscv_vget_f64m1(r50, 1);
        r51 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((j1 + l1)))), vl1);
        s750 = __riscv_vget_f64m1(r51, 0);
        s751 = __riscv_vget_f64m1(r51, 1);
        r52 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((j1 + ((2)*(l1)))))), vl1);
        s752 = __riscv_vget_f64m1(r52, 0);
        s753 = __riscv_vget_f64m1(r52, 1);
        r53 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((j1 + ((3)*(l1)))))), vl1);
        s754 = __riscv_vget_f64m1(r53, 0);
        s755 = __riscv_vget_f64m1(r53, 1);
        r54 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((j1 + ((4)*(l1)))))), vl1);
        s756 = __riscv_vget_f64m1(r54, 0);
        s757 = __riscv_vget_f64m1(r54, 1);
        r55 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((j1 + ((5)*(l1)))))), vl1);
        s758 = __riscv_vget_f64m1(r55, 0);
        s759 = __riscv_vget_f64m1(r55, 1);
        r56 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((j1 + ((6)*(l1)))))), vl1);
        s760 = __riscv_vget_f64m1(r56, 0);
        s761 = __riscv_vget_f64m1(r56, 1);
        t1799 = __riscv_vfadd(s752, s756, vl1);
        t1800 = __riscv_vfadd(s753, s757, vl1);
        t1801 = __riscv_vfadd(s750, t1799, vl1);
        t1802 = __riscv_vfadd(s751, t1800, vl1);
        t1803 = __riscv_vfnmsac(s750, 0.5, t1799, vl1);
        t1804 = __riscv_vfnmsac(s751, 0.5, t1800, vl1);
        s762 = __riscv_vfmul(__riscv_vfsub(s753, s757, vl1), 0.8660254037844386, vl1);
        s763 = __riscv_vfmul(__riscv_vfsub(s752, s756, vl1), 0.8660254037844386, vl1);
        t1805 = __riscv_vfadd(t1803, s762, vl1);
        t1806 = __riscv_vfsub(t1804, s763, vl1);
        t1807 = __riscv_vfsub(t1803, s762, vl1);
        t1808 = __riscv_vfadd(t1804, s763, vl1);
        t1809 = __riscv_vfadd(s760, s758, vl1);
        t1810 = __riscv_vfadd(s761, s759, vl1);
        t1811 = __riscv_vfadd(s754, t1809, vl1);
        t1812 = __riscv_vfadd(s755, t1810, vl1);
        t1813 = __riscv_vfnmsac(s754, 0.5, t1809, vl1);
        t1814 = __riscv_vfnmsac(s755, 0.5, t1810, vl1);
        s764 = __riscv_vfmul(__riscv_vfsub(s761, s759, vl1), 0.8660254037844386, vl1);
        s765 = __riscv_vfmul(__riscv_vfsub(s760, s758, vl1), 0.8660254037844386, vl1);
        t1815 = __riscv_vfadd(t1813, s764, vl1);
        t1816 = __riscv_vfsub(t1814, s765, vl1);
        t1817 = __riscv_vfsub(t1813, s764, vl1);
        t1818 = __riscv_vfadd(t1814, s765, vl1);
        s814 = __riscv_vfmacc(t1815, 1.7320508075688772, t1816, vl1);
        s766 = __riscv_vfmul(s814, 0.5, vl1);
        s815 = __riscv_vfnmsac(t1816, 1.7320508075688772, t1815, vl1);
        s767 = __riscv_vfmul(s815, 0.5, vl1);
        s816 = __riscv_vfnmsac(t1818, 0.57735026918962584, t1817, vl1);
        s768 = __riscv_vfmul(s816, 0.8660254037844386, vl1);
        s817 = __riscv_vfmacc(t1817, 0.57735026918962584, t1818, vl1);
        s769 = __riscv_vfmul(s817, 0.8660254037844386, vl1);
        t1819 = __riscv_vfadd(t1801, t1811, vl1);
        t1820 = __riscv_vfadd(t1802, t1812, vl1);
        t1821 = __riscv_vfadd(t1805, s766, vl1);
        t1822 = __riscv_vfadd(t1806, s767, vl1);
        t1823 = __riscv_vfsub(t1805, s766, vl1);
        t1824 = __riscv_vfsub(t1806, s767, vl1);
        t1825 = __riscv_vfadd(t1807, s768, vl1);
        t1826 = __riscv_vfsub(t1808, s769, vl1);
        t1827 = __riscv_vfsub(t1807, s768, vl1);
        t1828 = __riscv_vfadd(t1808, s769, vl1);
        t1829 = __riscv_vfnmsac(s748, 0.16666666666666666, t1819, vl1);
        t1830 = __riscv_vfnmsac(s749, 0.16666666666666666, t1820, vl1);
        s818 = __riscv_vfmacc(t1821, 0.41908315722758338, t1822, vl1);
        s770 = __riscv_vfmul(s818, 0.4066888930575896, vl1);
        s819 = __riscv_vfnmsac(t1822, 0.41908315722758338, t1821, vl1);
        s771 = __riscv_vfmul(s819, 0.4066888930575896, vl1);
        s820 = __riscv_vfmacc(t1825, 0.49572725516748389, t1826, vl1);
        s772 = __riscv_vfmul(s820, 0.39507823426270006, vl1);
        s821 = __riscv_vfnmsac(t1826, 0.49572725516748389, t1825, vl1);
        s773 = __riscv_vfmul(s821, 0.39507823426270006, vl1);
        s774 = __riscv_vfmul(__riscv_vfsub(t1802, t1812, vl1), 0.44095855184409843, vl1);
        s775 = __riscv_vfmul(__riscv_vfsub(t1801, t1811, vl1), 0.44095855184409843, vl1);
        s822 = __riscv_vfnmsac(t1823, 0.49572725516748389, t1824, vl1);
        s776 = __riscv_vfmul(s822, 0.39507823426270006, vl1);
        s823 = __riscv_vfmacc(t1823, 2.0172382889501304, t1824, vl1);
        s777 = __riscv_vfmul(s823, 0.1958510486474645, vl1);
        s824 = __riscv_vfnmsac(t1828, 2.386161273135941, t1827, vl1);
        s778 = __riscv_vfmul(s824, 0.17043646531196566, vl1);
        s825 = __riscv_vfmacc(t1827, 2.386161273135941, t1828, vl1);
        s779 = __riscv_vfmul(s825, 0.17043646531196566, vl1);
        s780 = __riscv_vfadd(s748, t1819, vl1);
        s781 = __riscv_vfadd(s749, t1820, vl1);
        t1831 = __riscv_vfadd(s772, s776, vl1);
        t1832 = __riscv_vfadd(s773, s777, vl1);
        t1833 = __riscv_vfadd(t1829, t1831, vl1);
        t1834 = __riscv_vfadd(t1830, t1832, vl1);
        t1835 = __riscv_vfnmsac(t1829, 0.5, t1831, vl1);
        t1836 = __riscv_vfnmsac(t1830, 0.5, t1832, vl1);
        s782 = __riscv_vfmul(__riscv_vfsub(s773, s777, vl1), 0.8660254037844386, vl1);
        s783 = __riscv_vfmul(__riscv_vfsub(s772, s776, vl1), 0.8660254037844386, vl1);
        t1837 = __riscv_vfadd(t1835, s782, vl1);
        t1838 = __riscv_vfsub(t1836, s783, vl1);
        t1839 = __riscv_vfsub(t1835, s782, vl1);
        t1840 = __riscv_vfadd(t1836, s783, vl1);
        t1841 = __riscv_vfadd(s774, s778, vl1);
        t1842 = __riscv_vfadd(s775, s779, vl1);
        t1843 = __riscv_vfadd(s770, t1841, vl1);
        t1844 = __riscv_vfsub(s771, t1842, vl1);
        t1845 = __riscv_vfnmsac(s770, 0.5, t1841, vl1);
        t1846 = __riscv_vfmacc(s771, 0.5, t1842, vl1);
        s784 = __riscv_vfmul(__riscv_vfsub(s779, s775, vl1), 0.8660254037844386, vl1);
        s785 = __riscv_vfmul(__riscv_vfsub(s774, s778, vl1), 0.8660254037844386, vl1);
        t1847 = __riscv_vfadd(t1845, s784, vl1);
        t1848 = __riscv_vfsub(t1846, s785, vl1);
        t1849 = __riscv_vfsub(t1845, s784, vl1);
        t1850 = __riscv_vfadd(t1846, s785, vl1);
        s826 = __riscv_vfmacc(t1847, 1.7320508075688772, t1848, vl1);
        s786 = __riscv_vfmul(s826, 0.5, vl1);
        s827 = __riscv_vfnmsac(t1848, 1.7320508075688772, t1847, vl1);
        s787 = __riscv_vfmul(s827, 0.5, vl1);
        s828 = __riscv_vfnmsac(t1850, 0.57735026918962584, t1849, vl1);
        s788 = __riscv_vfmul(s828, 0.8660254037844386, vl1);
        s829 = __riscv_vfmacc(t1849, 0.57735026918962584, t1850, vl1);
        s789 = __riscv_vfmul(s829, 0.8660254037844386, vl1);
        s790 = __riscv_vfadd(t1833, t1843, vl1);
        s791 = __riscv_vfadd(t1834, t1844, vl1);
        s792 = __riscv_vfsub(t1833, t1843, vl1);
        s793 = __riscv_vfsub(t1834, t1844, vl1);
        s794 = __riscv_vfadd(t1837, s786, vl1);
        s795 = __riscv_vfadd(t1838, s787, vl1);
        s796 = __riscv_vfsub(t1837, s786, vl1);
        s797 = __riscv_vfsub(t1838, s787, vl1);
        s798 = __riscv_vfadd(t1839, s788, vl1);
        s799 = __riscv_vfsub(t1840, s789, vl1);
        s800 = __riscv_vfsub(t1839, s788, vl1);
        s801 = __riscv_vfadd(t1840, s789, vl1);
        a1072 = (TW1 + ((12)*(j1)));
        a1073 = __riscv_vlse64_v_f64m1(a1072, sizeof(double) * 12, vl1);
        a1074 = __riscv_vlse64_v_f64m1((a1072 + 1), sizeof(double) * 12, vl1);
        s802 = __riscv_vfmsac(__riscv_vfmul(a1074, s791, vl1), a1073, s790, vl1);
        s803 = __riscv_vfmacc(__riscv_vfmul(a1073, s791, vl1), a1074, s790, vl1);
        a1075 = __riscv_vlse64_v_f64m1((a1072 + 2), sizeof(double) * 12, vl1);
        a1076 = __riscv_vlse64_v_f64m1((a1072 + 3), sizeof(double) * 12, vl1);
        s804 = __riscv_vfmsac(__riscv_vfmul(a1076, s799, vl1), a1075, s798, vl1);
        s805 = __riscv_vfmacc(__riscv_vfmul(a1075, s799, vl1), a1076, s798, vl1);
        a1077 = __riscv_vlse64_v_f64m1((a1072 + 4), sizeof(double) * 12, vl1);
        a1078 = __riscv_vlse64_v_f64m1((a1072 + 5), sizeof(double) * 12, vl1);
        s806 = __riscv_vfmsac(__riscv_vfmul(a1078, s795, vl1), a1077, s794, vl1);
        s807 = __riscv_vfmacc(__riscv_vfmul(a1077, s795, vl1), a1078, s794, vl1);
        a1079 = __riscv_vlse64_v_f64m1((a1072 + 6), sizeof(double) * 12, vl1);
        a1080 = __riscv_vlse64_v_f64m1((a1072 + 7), sizeof(double) * 12, vl1);
        s808 = __riscv_vfmsac(__riscv_vfmul(a1080, s797, vl1), a1079, s796, vl1);
        s809 = __riscv_vfmacc(__riscv_vfmul(a1079, s797, vl1), a1080, s796, vl1);
        a1081 = __riscv_vlse64_v_f64m1((a1072 + 8), sizeof(double) * 12, vl1);
        a1082 = __riscv_vlse64_v_f64m1((a1072 + 9), sizeof(double) * 12, vl1);
        s810 = __riscv_vfmsac(__riscv_vfmul(a1082, s801, vl1), a1081, s800, vl1);
        s811 = __riscv_vfmacc(__riscv_vfmul(a1081, s801, vl1), a1082, s800, vl1);
        a1083 = __riscv_vlse64_v_f64m1((a1072 + 10), sizeof(double) * 12, vl1);
        a1084 = __riscv_vlse64_v_f64m1((a1072 + 11), sizeof(double) * 12, vl1);
        s812 = __riscv_vfmsac(__riscv_vfmul(a1084, s793, vl1), a1083, s792, vl1);
        s813 = __riscv_vfmacc(__riscv_vfmul(a1083, s793, vl1), a1084, s792, vl1);
        __riscv_vsse64((Y + ((14)*(j1))), sizeof(double) * 14, s780, vl1);
        __riscv_vsse64((1 + Y + ((14)*(j1))), sizeof(double) * 14, s781, vl1);
        __riscv_vsse64((2 + Y + ((14)*(j1))), sizeof(double) * 14, s802, vl1);
        __riscv_vsse64((3 + Y + ((14)*(j1))), sizeof(double) * 14, s803, vl1);
        __riscv_vsse64((4 + Y + ((14)*(j1))), sizeof(double) * 14, s804, vl1);
        __riscv_vsse64((5 + Y + ((14)*(j1))), sizeof(double) * 14, s805, vl1);
        __riscv_vsse64((6 + Y + ((14)*(j1))), sizeof(double) * 14, s806, vl1);
        __riscv_vsse64((7 + Y + ((14)*(j1))), sizeof(double) * 14, s807, vl1);
        __riscv_vsse64((8 + Y + ((14)*(j1))), sizeof(double) * 14, s808, vl1);
        __riscv_vsse64((9 + Y + ((14)*(j1))), sizeof(double) * 14, s809, vl1);
        __riscv_vsse64((10 + Y + ((14)*(j1))), sizeof(double) * 14, s810, vl1);
        __riscv_vsse64((11 + Y + ((14)*(j1))), sizeof(double) * 14, s811, vl1);
        __riscv_vsse64((12 + Y + ((14)*(j1))), sizeof(double) * 14, s812, vl1);
        __riscv_vsse64((13 + Y + ((14)*(j1))), sizeof(double) * 14, s813, vl1);
    }
}
