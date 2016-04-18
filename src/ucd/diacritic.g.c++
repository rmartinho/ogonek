// Ogonek
//
// Written in 2016 by Martinho Fernandes <ogonek@rmf.io>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

// This file was automatically generated on 2016-04-18T15:55:59.637793Z

// Unicode character database - Diacritic property

#include <ogonek/ucd/diacritic.g.h++>
#include <ogonek/detail/size.h++>

#include <cstddef>

namespace ogonek {
    namespace ucd {
        namespace {
            diacritic_properties const diacritic_data_raw[] {
                { 0x0, false },
                { 0x5E, true },
                { 0x5F, false },
                { 0x60, true },
                { 0x61, false },
                { 0xA8, true },
                { 0xA9, false },
                { 0xAF, true },
                { 0xB0, false },
                { 0xB4, true },
                { 0xB5, false },
                { 0xB7, true },
                { 0xB9, false },
                { 0x2B0, true },
                { 0x34F, false },
                { 0x350, true },
                { 0x358, false },
                { 0x35D, true },
                { 0x363, false },
                { 0x374, true },
                { 0x376, false },
                { 0x37A, true },
                { 0x37B, false },
                { 0x384, true },
                { 0x386, false },
                { 0x483, true },
                { 0x488, false },
                { 0x559, true },
                { 0x55A, false },
                { 0x591, true },
                { 0x5A2, false },
                { 0x5A3, true },
                { 0x5BE, false },
                { 0x5BF, true },
                { 0x5C0, false },
                { 0x5C1, true },
                { 0x5C3, false },
                { 0x5C4, true },
                { 0x5C5, false },
                { 0x64B, true },
                { 0x653, false },
                { 0x657, true },
                { 0x659, false },
                { 0x6DF, true },
                { 0x6E1, false },
                { 0x6E5, true },
                { 0x6E7, false },
                { 0x6EA, true },
                { 0x6ED, false },
                { 0x730, true },
                { 0x74B, false },
                { 0x7A6, true },
                { 0x7B1, false },
                { 0x7EB, true },
                { 0x7F6, false },
                { 0x818, true },
                { 0x81A, false },
                { 0x8E3, true },
                { 0x8FF, false },
                { 0x93C, true },
                { 0x93D, false },
                { 0x94D, true },
                { 0x94E, false },
                { 0x951, true },
                { 0x955, false },
                { 0x971, true },
                { 0x972, false },
                { 0x9BC, true },
                { 0x9BD, false },
                { 0x9CD, true },
                { 0x9CE, false },
                { 0xA3C, true },
                { 0xA3D, false },
                { 0xA4D, true },
                { 0xA4E, false },
                { 0xABC, true },
                { 0xABD, false },
                { 0xACD, true },
                { 0xACE, false },
                { 0xB3C, true },
                { 0xB3D, false },
                { 0xB4D, true },
                { 0xB4E, false },
                { 0xBCD, true },
                { 0xBCE, false },
                { 0xC4D, true },
                { 0xC4E, false },
                { 0xCBC, true },
                { 0xCBD, false },
                { 0xCCD, true },
                { 0xCCE, false },
                { 0xD4D, true },
                { 0xD4E, false },
                { 0xDCA, true },
                { 0xDCB, false },
                { 0xE47, true },
                { 0xE4D, false },
                { 0xE4E, true },
                { 0xE4F, false },
                { 0xEC8, true },
                { 0xECD, false },
                { 0xF18, true },
                { 0xF1A, false },
                { 0xF35, true },
                { 0xF36, false },
                { 0xF37, true },
                { 0xF38, false },
                { 0xF39, true },
                { 0xF3A, false },
                { 0xF3E, true },
                { 0xF40, false },
                { 0xF82, true },
                { 0xF85, false },
                { 0xF86, true },
                { 0xF88, false },
                { 0xFC6, true },
                { 0xFC7, false },
                { 0x1037, true },
                { 0x1038, false },
                { 0x1039, true },
                { 0x103B, false },
                { 0x1087, true },
                { 0x108E, false },
                { 0x108F, true },
                { 0x1090, false },
                { 0x109A, true },
                { 0x109C, false },
                { 0x17C9, true },
                { 0x17D4, false },
                { 0x17DD, true },
                { 0x17DE, false },
                { 0x1939, true },
                { 0x193C, false },
                { 0x1A75, true },
                { 0x1A7D, false },
                { 0x1A7F, true },
                { 0x1A80, false },
                { 0x1AB0, true },
                { 0x1ABE, false },
                { 0x1B34, true },
                { 0x1B35, false },
                { 0x1B44, true },
                { 0x1B45, false },
                { 0x1B6B, true },
                { 0x1B74, false },
                { 0x1BAA, true },
                { 0x1BAC, false },
                { 0x1C36, true },
                { 0x1C38, false },
                { 0x1C78, true },
                { 0x1C7E, false },
                { 0x1CD0, true },
                { 0x1CE9, false },
                { 0x1CED, true },
                { 0x1CEE, false },
                { 0x1CF4, true },
                { 0x1CF5, false },
                { 0x1CF8, true },
                { 0x1CFA, false },
                { 0x1D2C, true },
                { 0x1D6B, false },
                { 0x1DC4, true },
                { 0x1DD0, false },
                { 0x1DF5, true },
                { 0x1DF6, false },
                { 0x1DFD, true },
                { 0x1E00, false },
                { 0x1FBD, true },
                { 0x1FBE, false },
                { 0x1FBF, true },
                { 0x1FC2, false },
                { 0x1FCD, true },
                { 0x1FD0, false },
                { 0x1FDD, true },
                { 0x1FE0, false },
                { 0x1FED, true },
                { 0x1FF0, false },
                { 0x1FFD, true },
                { 0x1FFF, false },
                { 0x2CEF, true },
                { 0x2CF2, false },
                { 0x2E2F, true },
                { 0x2E30, false },
                { 0x302A, true },
                { 0x3030, false },
                { 0x3099, true },
                { 0x309D, false },
                { 0x30FC, true },
                { 0x30FD, false },
                { 0xA66F, true },
                { 0xA670, false },
                { 0xA67C, true },
                { 0xA67E, false },
                { 0xA67F, true },
                { 0xA680, false },
                { 0xA69C, true },
                { 0xA69E, false },
                { 0xA6F0, true },
                { 0xA6F2, false },
                { 0xA717, true },
                { 0xA722, false },
                { 0xA788, true },
                { 0xA789, false },
                { 0xA7F8, true },
                { 0xA7FA, false },
                { 0xA8C4, true },
                { 0xA8C5, false },
                { 0xA8E0, true },
                { 0xA8F2, false },
                { 0xA92B, true },
                { 0xA92F, false },
                { 0xA953, true },
                { 0xA954, false },
                { 0xA9B3, true },
                { 0xA9B4, false },
                { 0xA9C0, true },
                { 0xA9C1, false },
                { 0xA9E5, true },
                { 0xA9E6, false },
                { 0xAA7B, true },
                { 0xAA7E, false },
                { 0xAABF, true },
                { 0xAAC3, false },
                { 0xAAF6, true },
                { 0xAAF7, false },
                { 0xAB5B, true },
                { 0xAB60, false },
                { 0xABEC, true },
                { 0xABEE, false },
                { 0xFB1E, true },
                { 0xFB1F, false },
                { 0xFE20, true },
                { 0xFE30, false },
                { 0xFF3E, true },
                { 0xFF3F, false },
                { 0xFF40, true },
                { 0xFF41, false },
                { 0xFF70, true },
                { 0xFF71, false },
                { 0xFF9E, true },
                { 0xFFA0, false },
                { 0xFFE3, true },
                { 0xFFE4, false },
                { 0x102E0, true },
                { 0x102E1, false },
                { 0x10AE5, true },
                { 0x10AE7, false },
                { 0x110B9, true },
                { 0x110BB, false },
                { 0x11133, true },
                { 0x11135, false },
                { 0x11173, true },
                { 0x11174, false },
                { 0x111C0, true },
                { 0x111C1, false },
                { 0x111CA, true },
                { 0x111CD, false },
                { 0x11235, true },
                { 0x11237, false },
                { 0x112E9, true },
                { 0x112EB, false },
                { 0x1133C, true },
                { 0x1133D, false },
                { 0x1134D, true },
                { 0x1134E, false },
                { 0x11366, true },
                { 0x1136D, false },
                { 0x11370, true },
                { 0x11375, false },
                { 0x114C2, true },
                { 0x114C4, false },
                { 0x115BF, true },
                { 0x115C1, false },
                { 0x1163F, true },
                { 0x11640, false },
                { 0x116B6, true },
                { 0x116B8, false },
                { 0x1172B, true },
                { 0x1172C, false },
                { 0x16AF0, true },
                { 0x16AF5, false },
                { 0x16F8F, true },
                { 0x16FA0, false },
                { 0x1D167, true },
                { 0x1D16A, false },
                { 0x1D16D, true },
                { 0x1D173, false },
                { 0x1D17B, true },
                { 0x1D183, false },
                { 0x1D185, true },
                { 0x1D18C, false },
                { 0x1D1AA, true },
                { 0x1D1AE, false },
                { 0x1E8D0, true },
                { 0x1E8D7, false },
            };
        } // namespace
        namespace abiv0 {
            diacritic_properties const* diacritic_data = diacritic_data_raw;
            std::size_t diacritic_data_size = detail::size(diacritic_data_raw);
        } // namespace abiv0
    } // namespace ucd
} // namespace ogonek
