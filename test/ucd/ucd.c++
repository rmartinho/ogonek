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

// Tests for <ogonek/ucd.h++>

#include <ogonek/ucd.h++>

#include <catch.hpp>
#include "util.h++"

namespace ucd = ogonek::ucd;

using namespace test::string_literals;

TEST_CASE("Age can be queried", "[properties]") {
    CHECK(ucd::get_age(U'\x0041') == ucd::version::v1_1);
    CHECK(ucd::get_age(U'\x00C5') == ucd::version::v1_1);
    CHECK(ucd::get_age(U'\x1EA0') == ucd::version::v1_1);
    CHECK(ucd::get_age(U'\x1F4A9') == ucd::version::v6_0);
}
TEST_CASE("Name can be queried", "[properties]") {
    SECTION("explicit", "some characters have explicit names") {
        CHECK(ucd::get_name(U'\x0041') == u8"LATIN CAPITAL LETTER A");
        CHECK(ucd::get_name(U'\x00C5') == u8"LATIN CAPITAL LETTER A WITH RING ABOVE");
        CHECK(ucd::get_name(U'\x1EA0') == u8"LATIN CAPITAL LETTER A WITH DOT BELOW");
        CHECK(ucd::get_name(U'\xAC00') == u8"HANGUL SYLLABLE GA");
        CHECK(ucd::get_name(U'\x1F4A9') == u8"PILE OF POO");
    }
    SECTION("control", "control characters have empty names") {
        CHECK(ucd::get_name(U'\x000A') == u8"");
        CHECK(ucd::get_name(U'\x0083') == u8"");
    }
    SECTION("surrogate", "surrogates have empty names") {
        CHECK(ucd::get_name(U'\xD842') == u8"");
        CHECK(ucd::get_name(U'\xDB82') == u8"");
        CHECK(ucd::get_name(U'\xDC42') == u8"");
    }
    SECTION("private use", "private use characters have empty names") {
        CHECK(ucd::get_name(U'\xE042') == u8"");
        CHECK(ucd::get_name(U'\xF0042') == u8"");
        CHECK(ucd::get_name(U'\x100042') == u8"");
    }
    SECTION("ideograph", "ideographs have generated names") {
        CHECK(ucd::get_name(U'\x3442') == u8"CJK UNIFIED IDEOGRAPH-3442");
        CHECK(ucd::get_name(U'\x4E42') == u8"CJK UNIFIED IDEOGRAPH-4E42");
        CHECK(ucd::get_name(U'\x20042') == u8"CJK UNIFIED IDEOGRAPH-20042");
        CHECK(ucd::get_name(U'\x2A742') == u8"CJK UNIFIED IDEOGRAPH-2A742");
        CHECK(ucd::get_name(U'\x2B742') == u8"CJK UNIFIED IDEOGRAPH-2B742");
        CHECK(ucd::get_name(U'\x2B842') == u8"CJK UNIFIED IDEOGRAPH-2B842");
        CHECK(ucd::get_name(U'\x2F842') == u8"CJK COMPATIBILITY IDEOGRAPH-2F842");
    }
    SECTION("hangul", "hangul syllables have generated names") {
        CHECK(ucd::get_name(U'\xAC00') == u8"HANGUL SYLLABLE GA");
        CHECK(ucd::get_name(U'\xAC42') == u8"HANGUL SYLLABLE GYALM");
        CHECK(ucd::get_name(U'\xD7A3') == u8"HANGUL SYLLABLE HIH");
    }
}
TEST_CASE("Block can be queried", "[properties]") {
    CHECK(ucd::get_block(U'\x0041') == ucd::block::ascii);
    CHECK(ucd::get_block(U'\x00C5') == ucd::block::latin_1_sup);
    CHECK(ucd::get_block(U'\x1EA0') == ucd::block::latin_ext_additional);
    CHECK(ucd::get_block(U'\x1F4A9') == ucd::block::misc_pictographs);
    CHECK(ucd::get_block(U'\x0860') == ucd::block::no_block);
}
TEST_CASE("General_Category can be queried", "[properties]") {
    CHECK(ucd::get_general_category(U'\x000A') == ucd::general_category::cc);
    CHECK(ucd::get_general_category(U'\x00C5') == ucd::general_category::lu);
    CHECK(ucd::get_general_category(U'\x1EA0') == ucd::general_category::lu);
    CHECK(ucd::get_general_category(U'\x1F4A9') == ucd::general_category::so);
    CHECK(ucd::get_general_category(U'\xFFFF') == ucd::general_category::cn);
    CHECK(ucd::get_general_category(U'\xD800') == ucd::general_category::cs);
    CHECK(ucd::get_general_category(U'\xE042') == ucd::general_category::co);
}
TEST_CASE("Canonical_Combining_Class can be queried", "[properties]") {
    CHECK(ucd::get_canonical_combining_class(U'\x0041') == 0);
    CHECK(ucd::get_canonical_combining_class(U'\x0300') == 230);
    CHECK(ucd::get_canonical_combining_class(U'\x0334') == 1);
    CHECK(ucd::get_canonical_combining_class(U'\x0618') == 30);
    CHECK(ucd::get_canonical_combining_class(U'\xFFFF') == 0);
}
TEST_CASE("Bidi_Class can be queried", "[properties]") {
    CHECK(ucd::get_bidi_class(U'\x0041') == ucd::bidi_class::l);
    CHECK(ucd::get_bidi_class(U'\x0600') == ucd::bidi_class::an);
    CHECK(ucd::get_bidi_class(U'\x0610') == ucd::bidi_class::nsm);
    CHECK(ucd::get_bidi_class(U'\x1F4A9') == ucd::bidi_class::on);
    CHECK(ucd::get_bidi_class(U'\xFFFF') == ucd::bidi_class::bn);
}
TEST_CASE("Bidi_Mirrored can be queried", "[properties]") {
    CHECK(ucd::is_bidi_mirrored(U'\x0041') == false);
    CHECK(ucd::is_bidi_mirrored(U'\x0F3A') == true);
    CHECK(ucd::is_bidi_mirrored(U'\x222B') == true);
    CHECK(ucd::is_bidi_mirrored(U'\x1F4A9') == false);
    CHECK(ucd::is_bidi_mirrored(U'\xFFFF') == false);
}
TEST_CASE("Bidi_Mirroring_Glyph can be queried", "[properties]") {
    CHECK(ucd::get_bidi_mirroring_glyph(U'\x0041') == U'\x0041');
    CHECK(ucd::get_bidi_mirroring_glyph(U'\x222B') == U'\x222B');
    CHECK(ucd::get_bidi_mirroring_glyph(U'\x223C') == U'\x223D');
    CHECK(ucd::get_bidi_mirroring_glyph(U'\xFF63') == U'\xFF62');
    CHECK(ucd::get_bidi_mirroring_glyph(U'\xFFFF') == U'\xFFFF');
}
TEST_CASE("Bidi_Control can be queried", "[properties]") {
    CHECK(ucd::is_bidi_control(U'\x0041') == false);
    CHECK(ucd::is_bidi_control(U'\x00C5') == false);
    CHECK(ucd::is_bidi_control(U'\x200E') == true);
    CHECK(ucd::is_bidi_control(U'\x202E') == true);
    CHECK(ucd::is_bidi_control(U'\xFFFF') == false);
}
TEST_CASE("Bidi_Paired_Bracket can be queried", "[properties]") {
    CHECK(ucd::get_bidi_paired_bracket(U'\x0041') == U'\x0041');
    CHECK(ucd::get_bidi_paired_bracket(U'\x00C5') == U'\x00C5');
    CHECK(ucd::get_bidi_paired_bracket(U'\x0028') == U'\x0029');
    CHECK(ucd::get_bidi_paired_bracket(U'\x0029') == U'\x0028');
    CHECK(ucd::get_bidi_paired_bracket(U'\xFF5B') == U'\xFF5D');
    CHECK(ucd::get_bidi_paired_bracket(U'\xFF5D') == U'\xFF5B');
    CHECK(ucd::get_bidi_paired_bracket(U'\xFFFF') == U'\xFFFF');
}
TEST_CASE("Bidi_Paired_Bracket_Type can be queried", "[properties]") {
    CHECK(ucd::get_bidi_paired_bracket_type(U'\x0041') == ucd::bracket_type::none);
    CHECK(ucd::get_bidi_paired_bracket_type(U'\x00C5') == ucd::bracket_type::none);
    CHECK(ucd::get_bidi_paired_bracket_type(U'\x0028') == ucd::bracket_type::open);
    CHECK(ucd::get_bidi_paired_bracket_type(U'\x0029') == ucd::bracket_type::close);
    CHECK(ucd::get_bidi_paired_bracket_type(U'\xFF5B') == ucd::bracket_type::open);
    CHECK(ucd::get_bidi_paired_bracket_type(U'\xFF5D') == ucd::bracket_type::close);
    CHECK(ucd::get_bidi_paired_bracket_type(U'\xFFFF') == ucd::bracket_type::none);
}
TEST_CASE("Decomposition_Type can be queried", "[properties]") {
    CHECK(ucd::get_decomposition_type(U'\x0041') == ucd::decomposition_type::none);
    CHECK(ucd::get_decomposition_type(U'\x00A8') == ucd::decomposition_type::compat);
    CHECK(ucd::get_decomposition_type(U'\x00C5') == ucd::decomposition_type::can);
    CHECK(ucd::get_decomposition_type(U'\x1EA0') == ucd::decomposition_type::can);
    CHECK(ucd::get_decomposition_type(U'\x3000') == ucd::decomposition_type::wide);
    // TODO Add Hangul tests
}
TEST_CASE("Decomposition_Mapping can be queried", "[properties]") {
    CHECK(ucd::get_decomposition_mapping(U'\x0041') == U"\x0041"_s);
    CHECK(ucd::get_decomposition_mapping(U'\x00A8') == U"\x0020\x0308"_s);
    CHECK(ucd::get_decomposition_mapping(U'\x00C5') == U"\x0041\x030A"_s);
    CHECK(ucd::get_decomposition_mapping(U'\x1EA0') == U"\x0041\x0323"_s);
    CHECK(ucd::get_decomposition_mapping(U'\x3000') == U"\x0020"_s);
    // TODO Add Hangul tests
}
TEST_CASE("Full_Composition_Exclusion can be queried", "[properties]") {
    CHECK(ucd::is_excluded_from_composition(U'\x0041') == false);
    CHECK(ucd::is_excluded_from_composition(U'\x0344') == true);
    CHECK(ucd::is_excluded_from_composition(U'\x0958') == true);
    CHECK(ucd::is_excluded_from_composition(U'\x2ADC') == true);
    CHECK(ucd::is_excluded_from_composition(U'\x2126') == true);
}
TEST_CASE("NFC_Quick_Check can be queried", "[properties]") {
    CHECK(ucd::get_nfc_quick_check(U'\x0041') == true);
    CHECK(ogonek::maybe(ucd::get_nfc_quick_check(U'\x0300')));
    CHECK(ucd::get_nfc_quick_check(U'\x0340') == false);
    CHECK(ucd::get_nfc_quick_check(U'\x1F4A9') == true);
}
TEST_CASE("NFD_Quick_Check can be queried", "[properties]") {
    CHECK(ucd::get_nfd_quick_check(U'\x0041') == true);
    CHECK(ucd::get_nfd_quick_check(U'\x00C5') == false);
    CHECK(ucd::get_nfd_quick_check(U'\x2F801') == false);
    CHECK(ucd::get_nfd_quick_check(U'\x1F4A9') == true);
}
TEST_CASE("NFKC_Quick_Check can be queried", "[properties]") {
    CHECK(ucd::get_nfkc_quick_check(U'\x0041') == true);
    CHECK(ogonek::maybe(ucd::get_nfkc_quick_check(U'\x0300')));
    CHECK(ucd::get_nfkc_quick_check(U'\x0340') == false);
    CHECK(ucd::get_nfkc_quick_check(U'\x1F4A9') == true);
}
TEST_CASE("NFKD_Quick_Check can be queried", "[properties]") {
    CHECK(ucd::get_nfkd_quick_check(U'\x0041') == true);
    CHECK(ucd::get_nfkd_quick_check(U'\x00C5') == false);
    CHECK(ucd::get_nfkd_quick_check(U'\x013F') == false);
    CHECK(ucd::get_nfkd_quick_check(U'\x1F4A9') == true);
}
TEST_CASE("Numeric_Type can be queried", "[properties]") {
    CHECK(ucd::get_numeric_type(U'\x0041') == ucd::numeric_type::none);
    CHECK(ucd::get_numeric_type(U'\xA621') == ucd::numeric_type::decimal);
    CHECK(ucd::get_numeric_type(U'\x00B2') == ucd::numeric_type::digit);
    CHECK(ucd::get_numeric_type(U'\xA831') == ucd::numeric_type::numeric);
}
TEST_CASE("Numeric_Value can be queried", "[properties]") {
    CHECK(ucd::get_numeric_value(U'\x0041') == ogonek::none);
    CHECK(ucd::get_numeric_value(U'\xA621') == ogonek::fraction(1, 1));
    CHECK(ucd::get_numeric_value(U'\x00B2') == ogonek::fraction(2, 1));
    CHECK(ucd::get_numeric_value(U'\xA831') == ogonek::fraction(1, 2));
}
TEST_CASE("Joining_Type can be queried", "[properties]") {
    CHECK(ucd::get_joining_type(U'\x0041') == ucd::joining_type::u);
    CHECK(ucd::get_joining_type(U'\x0648') == ucd::joining_type::r);
    CHECK(ucd::get_joining_type(U'\x064B') == ucd::joining_type::t);
    CHECK(ucd::get_joining_type(U'\x066E') == ucd::joining_type::d);
}
TEST_CASE("Joining_Group can be queried", "[properties]") {
    CHECK(ucd::get_joining_group(U'\x0041') == ucd::joining_group::no_joining_group);
    CHECK(ucd::get_joining_group(U'\x0648') == ucd::joining_group::waw);
    CHECK(ucd::get_joining_group(U'\x064B') == ucd::joining_group::no_joining_group);
    CHECK(ucd::get_joining_group(U'\x066E') == ucd::joining_group::beh);
}
TEST_CASE("Join_Control can be queried", "[properties]") {
    CHECK(ucd::is_join_control(U'\x0041') == false);
    CHECK(ucd::is_join_control(U'\x200C') == true);
    CHECK(ucd::is_join_control(U'\x200D') == true);
    CHECK(ucd::is_join_control(U'\x1F4A9') == false);
}
TEST_CASE("Line_Break can be queried", "[properties]") {
    CHECK(ucd::get_line_break(U'\x000A') == ucd::line_break::lf);
    CHECK(ucd::get_line_break(U'\x000D') == ucd::line_break::cr);
    CHECK(ucd::get_line_break(U'\x0041') == ucd::line_break::al);
    CHECK(ucd::get_line_break(U'\x2028') == ucd::line_break::bk);
}
TEST_CASE("East_Asian_Width can be queried", "[properties]") {
    CHECK(ucd::get_east_asian_width(U'\x000A') == ucd::east_asian_width::n);
    CHECK(ucd::get_east_asian_width(U'\x0041') == ucd::east_asian_width::na);
    CHECK(ucd::get_east_asian_width(U'\x1128') == ucd::east_asian_width::w);
    CHECK(ucd::get_east_asian_width(U'\x201C') == ucd::east_asian_width::a);
}
TEST_CASE("Uppercase can be queried", "[properties]") {
    CHECK(ucd::is_uppercase(U'\x0041') == true);
    CHECK(ucd::is_uppercase(U'\x0061') == false);
    CHECK(ucd::is_uppercase(U'\x1EA0') == true);
    CHECK(ucd::is_uppercase(U'\x1F4A9') == false);
}
TEST_CASE("Lowercase can be queried", "[properties]") {
    CHECK(ucd::is_lowercase(U'\x0041') == false);
    CHECK(ucd::is_lowercase(U'\x0061') == true);
    CHECK(ucd::is_lowercase(U'\x1EA0') == false);
    CHECK(ucd::is_lowercase(U'\x1F4A9') == false);
}
TEST_CASE("Simple_Uppercase_Mapping can be queried", "[properties]") {
    CHECK(ucd::get_simple_uppercase_mapping(U'\x0041') == U'\x0041');
    CHECK(ucd::get_simple_uppercase_mapping(U'\x00C5') == U'\x00C5');
    CHECK(ucd::get_simple_uppercase_mapping(U'\x1EA0') == U'\x1EA0');
    CHECK(ucd::get_simple_uppercase_mapping(U'\x0061') == U'\x0041');
    CHECK(ucd::get_simple_uppercase_mapping(U'\x00E5') == U'\x00C5');
    CHECK(ucd::get_simple_uppercase_mapping(U'\x1EA1') == U'\x1EA0');
    CHECK(ucd::get_simple_uppercase_mapping(U'\x1F4A9') == U'\x1F4A9');
}
TEST_CASE("Simple_Lowercase_Mapping can be queried", "[properties]") {
    CHECK(ucd::get_simple_lowercase_mapping(U'\x0061') == U'\x0061');
    CHECK(ucd::get_simple_lowercase_mapping(U'\x00E5') == U'\x00E5');
    CHECK(ucd::get_simple_lowercase_mapping(U'\x1EA1') == U'\x1EA1');
    CHECK(ucd::get_simple_lowercase_mapping(U'\x0041') == U'\x0061');
    CHECK(ucd::get_simple_lowercase_mapping(U'\x00C5') == U'\x00E5');
    CHECK(ucd::get_simple_lowercase_mapping(U'\x1EA0') == U'\x1EA1');
    CHECK(ucd::get_simple_lowercase_mapping(U'\x1F4A9') == U'\x1F4A9');
}
TEST_CASE("Simple_Titlecase_Mapping can be queried", "[properties]") {
    CHECK(ucd::get_simple_titlecase_mapping(U'\x0041') == U'\x0041');
    CHECK(ucd::get_simple_titlecase_mapping(U'\x0061') == U'\x0041');
    CHECK(ucd::get_simple_titlecase_mapping(U'\x00C5') == U'\x00C5');
    CHECK(ucd::get_simple_titlecase_mapping(U'\x00E5') == U'\x00C5');
    CHECK(ucd::get_simple_titlecase_mapping(U'\x1EA0') == U'\x1EA0');
    CHECK(ucd::get_simple_titlecase_mapping(U'\x1EA1') == U'\x1EA0');
    CHECK(ucd::get_simple_titlecase_mapping(U'\x1F4A9') == U'\x1F4A9');
}
TEST_CASE("Uppercase_Mapping can be queried", "[properties]") {
    CHECK(ucd::get_uppercase_mapping(U'\x0041') == U"\x0041"_s);
    CHECK(ucd::get_uppercase_mapping(U'\x0061') == U"\x0041"_s);
    CHECK(ucd::get_uppercase_mapping(U'\x00DF') == U"\x0053\x0053"_s);
    CHECK(ucd::get_uppercase_mapping(U'\x1E96') == U"\x0048\x0331"_s);
    CHECK(ucd::get_uppercase_mapping(U'\x1F4A9') == U"\x1F4A9"_s);
}
TEST_CASE("Lowercase_Mapping can be queried", "[properties]") {
    CHECK(ucd::get_lowercase_mapping(U'\x0041') == U"\x0061"_s);
    CHECK(ucd::get_lowercase_mapping(U'\x0061') == U"\x0061"_s);
    CHECK(ucd::get_lowercase_mapping(U'\x0130') == U"\x0069\x0307"_s);
    CHECK(ucd::get_lowercase_mapping(U'\x1E96') == U"\x1E96"_s);
    CHECK(ucd::get_lowercase_mapping(U'\x1F4A9') == U"\x1F4A9"_s);
}
TEST_CASE("Titlecase_Mapping can be queried", "[properties]") {
    CHECK(ucd::get_titlecase_mapping(U'\x0041') == U"\x0041"_s);
    CHECK(ucd::get_titlecase_mapping(U'\x0061') == U"\x0041"_s);
    CHECK(ucd::get_titlecase_mapping(U'\x00DF') == U"\x0053\x0073"_s);
    CHECK(ucd::get_titlecase_mapping(U'\x1E96') == U"\x0048\x0331"_s);
    CHECK(ucd::get_titlecase_mapping(U'\x1F4A9') == U"\x1F4A9"_s);
}
TEST_CASE("Simple_Case_Folding can be queried", "[properties]") {
    CHECK(ucd::get_simple_case_folding(U'\x0041') == U'\x0061');
    CHECK(ucd::get_simple_case_folding(U'\x0061') == U'\x0061');
    CHECK(ucd::get_simple_case_folding(U'\x00DF') == U'\x00DF');
    CHECK(ucd::get_simple_case_folding(U'\x1EA0') == U'\x1EA1');
    CHECK(ucd::get_simple_case_folding(U'\x1EA1') == U'\x1EA1');
    CHECK(ucd::get_simple_case_folding(U'\x1F4A9') == U'\x1F4A9');
}
TEST_CASE("Case_Folding can be queried", "[properties]") {
    CHECK(ucd::get_case_folding(U'\x0041') == U"\x0061"_s);
    CHECK(ucd::get_case_folding(U'\x0061') == U"\x0061"_s);
    CHECK(ucd::get_case_folding(U'\x00DF') == U"\x0073\x0073"_s);
    CHECK(ucd::get_case_folding(U'\x1E96') == U"\x0068\x0331"_s);
    CHECK(ucd::get_case_folding(U'\x1F4A9') == U"\x1F4A9"_s);
}
TEST_CASE("Case_Ignorable can be queried", "[properties]") {
    CHECK(ucd::is_case_ignorable(U'\x0041') == false);
    CHECK(ucd::is_case_ignorable(U'\x0061') == false);
    CHECK(ucd::is_case_ignorable(U'\x0027') == true);
    CHECK(ucd::is_case_ignorable(U'\x002E') == true);
    CHECK(ucd::is_case_ignorable(U'\x1F4A9') == false);
}
TEST_CASE("Cased can be queried", "[properties]") {
    CHECK(ucd::is_cased(U'\x0027') == false);
    CHECK(ucd::is_cased(U'\x002E') == false);
    CHECK(ucd::is_cased(U'\x0041') == true);
    CHECK(ucd::is_cased(U'\x0061') == true);
    CHECK(ucd::is_cased(U'\x00DF') == true);
    CHECK(ucd::is_cased(U'\x1F4A9') == false);
}
TEST_CASE("Changes_When_Lowercased can be queried", "[properties]") {
    CHECK(ucd::changes_when_lowercased(U'\x0041') == true);
    CHECK(ucd::changes_when_lowercased(U'\x0061') == false);
    CHECK(ucd::changes_when_lowercased(U'\x00C5') == true);
    CHECK(ucd::changes_when_lowercased(U'\x00E5') == false);
    CHECK(ucd::changes_when_lowercased(U'\x0130') == true);
    CHECK(ucd::changes_when_lowercased(U'\x1E96') == false);
    CHECK(ucd::changes_when_lowercased(U'\x1EA1') == false);
    CHECK(ucd::changes_when_lowercased(U'\x1EA0') == true);
    CHECK(ucd::changes_when_lowercased(U'\x1F4A9') == false);
}
TEST_CASE("Changes_When_Uppercased can be queried", "[properties]") {
    CHECK(ucd::changes_when_uppercased(U'\x0041') == false);
    CHECK(ucd::changes_when_uppercased(U'\x00C5') == false);
    CHECK(ucd::changes_when_uppercased(U'\x00DF') == true);
    CHECK(ucd::changes_when_uppercased(U'\x1EA0') == false);
    CHECK(ucd::changes_when_uppercased(U'\x0061') == true);
    CHECK(ucd::changes_when_uppercased(U'\x00E5') == true);
    CHECK(ucd::changes_when_uppercased(U'\x1E96') == true);
    CHECK(ucd::changes_when_uppercased(U'\x1EA1') == true);
    CHECK(ucd::changes_when_uppercased(U'\x1F4A9') == false);
}
TEST_CASE("Changes_When_Titlecased can be queried", "[properties]") {
    CHECK(ucd::changes_when_titlecased(U'\x0041') == false);
    CHECK(ucd::changes_when_titlecased(U'\x0061') == true);
    CHECK(ucd::changes_when_titlecased(U'\x00C5') == false);
    CHECK(ucd::changes_when_titlecased(U'\x00DF') == true);
    CHECK(ucd::changes_when_titlecased(U'\x00E5') == true);
    CHECK(ucd::changes_when_titlecased(U'\x1E96') == true);
    CHECK(ucd::changes_when_titlecased(U'\x1EA0') == false);
    CHECK(ucd::changes_when_titlecased(U'\x1EA1') == true);
    CHECK(ucd::changes_when_titlecased(U'\x1F4A9') == false);
}
TEST_CASE("Changes_When_Casefolded can be queried", "[properties]") {
    CHECK(ucd::changes_when_casefolded(U'\x0041') == true);
    CHECK(ucd::changes_when_casefolded(U'\x0061') == false);
    CHECK(ucd::changes_when_casefolded(U'\x00DF') == true);
    CHECK(ucd::changes_when_casefolded(U'\x1E96') == false);
    CHECK(ucd::changes_when_casefolded(U'\x1EA0') == true);
    CHECK(ucd::changes_when_casefolded(U'\x1EA1') == false);
    CHECK(ucd::changes_when_casefolded(U'\x1F4A9') == false);
}
TEST_CASE("Changes_When_Casemapped can be queried", "[properties]") {
    CHECK(ucd::changes_when_casemapped(U'\x0041') == true);
    CHECK(ucd::changes_when_casemapped(U'\x0061') == true);
    CHECK(ucd::changes_when_casemapped(U'\x00C5') == true);
    CHECK(ucd::changes_when_casemapped(U'\x00DF') == true);
    CHECK(ucd::changes_when_casemapped(U'\x00E5') == true);
    CHECK(ucd::changes_when_casemapped(U'\x0130') == true);
    CHECK(ucd::changes_when_casemapped(U'\x1E96') == true);
    CHECK(ucd::changes_when_casemapped(U'\x1EA0') == true);
    CHECK(ucd::changes_when_casemapped(U'\x1EA1') == true);
    CHECK(ucd::changes_when_casemapped(U'\x1F4A9') == false);
}
TEST_CASE("Changes_When_NFKC_Casefolded can be queried", "[properties]") {
    CHECK(ucd::changes_when_nfkc_casefolded(U'\x0041') == true);
    CHECK(ucd::changes_when_nfkc_casefolded(U'\x0061') == false);
    CHECK(ucd::changes_when_nfkc_casefolded(U'\x00A0') == true);
    CHECK(ucd::changes_when_nfkc_casefolded(U'\x00DF') == true);
    CHECK(ucd::changes_when_nfkc_casefolded(U'\x0390') == false);
    CHECK(ucd::changes_when_nfkc_casefolded(U'\x0675') == true);
    CHECK(ucd::changes_when_nfkc_casefolded(U'\x1E96') == false);
    CHECK(ucd::changes_when_nfkc_casefolded(U'\x1EA0') == true);
    CHECK(ucd::changes_when_nfkc_casefolded(U'\x1EA1') == false);
    CHECK(ucd::changes_when_nfkc_casefolded(U'\x1F4A9') == false);
}
TEST_CASE("NFKC_Casefold can be queried", "[properties]") {
    CHECK(ucd::get_nfkc_casefold(U'\x0041') == U"\x0061"_s);
    CHECK(ucd::get_nfkc_casefold(U'\x0061') == U"\x0061"_s);
    CHECK(ucd::get_nfkc_casefold(U'\x00A0') == U"\x0020"_s);
    CHECK(ucd::get_nfkc_casefold(U'\x00DF') == U"\x0073\x0073"_s);
    CHECK(ucd::get_nfkc_casefold(U'\x0390') == U"\x0390"_s);
    CHECK(ucd::get_nfkc_casefold(U'\x0675') == U"\x0627\x0674"_s);
    CHECK(ucd::get_nfkc_casefold(U'\x1E96') == U"\x1E96"_s);
    CHECK(ucd::get_nfkc_casefold(U'\x1EA0') == U"\x1EA1"_s);
    CHECK(ucd::get_nfkc_casefold(U'\x1EA1') == U"\x1EA1"_s);
    CHECK(ucd::get_nfkc_casefold(U'\x1F4A9') == U"\x1F4A9"_s);
}
TEST_CASE("Script can be queried", "[properties]") {
    CHECK(ucd::get_script(U'\x000A') == ucd::script::common);
    CHECK(ucd::get_script(U'\x0041') == ucd::script::latin);
    CHECK(ucd::get_script(U'\x0378') == ucd::script::unknown);
    CHECK(ucd::get_script(U'\x1102') == ucd::script::hangul);
    CHECK(ucd::get_script(U'\x10003') == ucd::script::linear_b);
    CHECK(ucd::get_script(U'\x1F4A9') == ucd::script::common);
}
TEST_CASE("Hangul_Syllable_Type can be queried", "[properties]") {
    CHECK(ucd::get_hangul_syllable_type(U'\x000A') == ucd::hangul_syllable_type::na);
    CHECK(ucd::get_hangul_syllable_type(U'\x0041') == ucd::hangul_syllable_type::na);
    CHECK(ucd::get_hangul_syllable_type(U'\x1132') == ucd::hangul_syllable_type::l);
    CHECK(ucd::get_hangul_syllable_type(U'\x1192') == ucd::hangul_syllable_type::v);
    CHECK(ucd::get_hangul_syllable_type(U'\x11B0') == ucd::hangul_syllable_type::t);
    CHECK(ucd::get_hangul_syllable_type(U'\x1232') == ucd::hangul_syllable_type::na);
    CHECK(ucd::get_hangul_syllable_type(U'\xA964') == ucd::hangul_syllable_type::l);
    CHECK(ucd::get_hangul_syllable_type(U'\xA97D') == ucd::hangul_syllable_type::na);
    CHECK(ucd::get_hangul_syllable_type(U'\xAC00') == ucd::hangul_syllable_type::lv);
    CHECK(ucd::get_hangul_syllable_type(U'\xAC01') == ucd::hangul_syllable_type::lvt);
    CHECK(ucd::get_hangul_syllable_type(U'\xD7A8') == ucd::hangul_syllable_type::na);
    CHECK(ucd::get_hangul_syllable_type(U'\x1F4A9') == ucd::hangul_syllable_type::na);
}
TEST_CASE("Indic_Positional_Category can be queried", "[properties]") {
    CHECK(ucd::get_indic_positional_category(U'\x0041') == ucd::indic_positional_category::na);
    CHECK(ucd::get_indic_positional_category(U'\x0D3F') == ucd::indic_positional_category::right);
    CHECK(ucd::get_indic_positional_category(U'\x0D44') == ucd::indic_positional_category::bottom);
    CHECK(ucd::get_indic_positional_category(U'\x0D47') == ucd::indic_positional_category::left);
    CHECK(ucd::get_indic_positional_category(U'\x0D4B') == ucd::indic_positional_category::left_and_right);
    CHECK(ucd::get_indic_positional_category(U'\x0D4D') == ucd::indic_positional_category::top);
    CHECK(ucd::get_indic_positional_category(U'\x0D59') == ucd::indic_positional_category::na);
    CHECK(ucd::get_indic_positional_category(U'\x1F4A9') == ucd::indic_positional_category::na);
}
TEST_CASE("Indic_Syllabic_Category can be queried", "[properties]") {
    CHECK(ucd::get_indic_syllabic_category(U'\x0041') == ucd::indic_syllabic_category::other);
    CHECK(ucd::get_indic_syllabic_category(U'\x00B3') == ucd::indic_syllabic_category::syllable_modifier);
    CHECK(ucd::get_indic_syllabic_category(U'\x093B') == ucd::indic_syllabic_category::vowel_dependent);
    CHECK(ucd::get_indic_syllabic_category(U'\x090A') == ucd::indic_syllabic_category::vowel_independent);
    CHECK(ucd::get_indic_syllabic_category(U'\x093D') == ucd::indic_syllabic_category::avagraha);
    CHECK(ucd::get_indic_syllabic_category(U'\x1F4A9') == ucd::indic_syllabic_category::other);
}
TEST_CASE("ID_Start can be queried", "[properties]") {
    CHECK(ucd::is_id_start(U'\x0020') == false);
    CHECK(ucd::is_id_start(U'\x0021') == false);
    CHECK(ucd::is_id_start(U'\x0031') == false);
    CHECK(ucd::is_id_start(U'\x0041') == true);
    CHECK(ucd::is_id_start(U'\x005F') == false);
    CHECK(ucd::is_id_start(U'\x0532') == true);
    CHECK(ucd::is_id_start(U'\x0560') == false);
    CHECK(ucd::is_id_start(U'\xFE74') == true);
    CHECK(ucd::is_id_start(U'\xFE75') == false);
    CHECK(ucd::is_id_start(U'\xFE76') == true);
    CHECK(ucd::is_id_start(U'\x1F4A9') == false);
}
TEST_CASE("ID_Continue can be queried", "[properties]") {
    CHECK(ucd::is_id_continue(U'\x0020') == false);
    CHECK(ucd::is_id_continue(U'\x0021') == false);
    CHECK(ucd::is_id_continue(U'\x0031') == true);
    CHECK(ucd::is_id_continue(U'\x0041') == true);
    CHECK(ucd::is_id_continue(U'\x005F') == true);
    CHECK(ucd::is_id_continue(U'\x0532') == true);
    CHECK(ucd::is_id_continue(U'\x0560') == false);
    CHECK(ucd::is_id_continue(U'\xFE74') == true);
    CHECK(ucd::is_id_continue(U'\xFE75') == false);
    CHECK(ucd::is_id_continue(U'\xFE76') == true);
    CHECK(ucd::is_id_continue(U'\x1F4A9') == false);
}
TEST_CASE("XID_Start can be queried", "[properties]") {
    CHECK(ucd::is_xid_start(U'\x0020') == false);
    CHECK(ucd::is_xid_start(U'\x0021') == false);
    CHECK(ucd::is_xid_start(U'\x0031') == false);
    CHECK(ucd::is_xid_start(U'\x0041') == true);
    CHECK(ucd::is_xid_start(U'\x005F') == false);
    CHECK(ucd::is_xid_start(U'\x0532') == true);
    CHECK(ucd::is_xid_start(U'\x0560') == false);
    CHECK(ucd::is_xid_start(U'\xFE74') == false);
    CHECK(ucd::is_xid_start(U'\xFE75') == false);
    CHECK(ucd::is_xid_start(U'\xFE76') == false);
    CHECK(ucd::is_xid_start(U'\x1F4A9') == false);
}
TEST_CASE("XID_Continue can be queried", "[properties]") {
    CHECK(ucd::is_xid_continue(U'\x0020') == false);
    CHECK(ucd::is_xid_continue(U'\x0021') == false);
    CHECK(ucd::is_xid_continue(U'\x0031') == true);
    CHECK(ucd::is_xid_continue(U'\x0041') == true);
    CHECK(ucd::is_xid_continue(U'\x005F') == true);
    CHECK(ucd::is_xid_continue(U'\x0532') == true);
    CHECK(ucd::is_xid_continue(U'\x0560') == false);
    CHECK(ucd::is_xid_continue(U'\xFE74') == false);
    CHECK(ucd::is_xid_continue(U'\xFE75') == false);
    CHECK(ucd::is_xid_continue(U'\xFE76') == false);
    CHECK(ucd::is_xid_continue(U'\x1F4A9') == false);
}
TEST_CASE("Pattern_Syntax can be queried", "[properties]") {
    CHECK(ucd::is_pattern_syntax(U'\x0020') == false);
    CHECK(ucd::is_pattern_syntax(U'\x0021') == true);
    CHECK(ucd::is_pattern_syntax(U'\x0031') == false);
    CHECK(ucd::is_pattern_syntax(U'\x003E') == true);
    CHECK(ucd::is_pattern_syntax(U'\x2E5F') == true);
    CHECK(ucd::is_pattern_syntax(U'\x2E93') == false);
    CHECK(ucd::is_pattern_syntax(U'\x1F4A9') == false);
}
TEST_CASE("Pattern_White_Space can be queried", "[properties]") {
    CHECK(ucd::is_pattern_white_space(U'\x0008') == false);
    CHECK(ucd::is_pattern_white_space(U'\x0009') == true);
    CHECK(ucd::is_pattern_white_space(U'\x000A') == true);
    CHECK(ucd::is_pattern_white_space(U'\x000B') == true);
    CHECK(ucd::is_pattern_white_space(U'\x000C') == true);
    CHECK(ucd::is_pattern_white_space(U'\x000D') == true);
    CHECK(ucd::is_pattern_white_space(U'\x000E') == false);
    CHECK(ucd::is_pattern_white_space(U'\x0014') == false);
    CHECK(ucd::is_pattern_white_space(U'\x001F') == false);
    CHECK(ucd::is_pattern_white_space(U'\x0020') == true);
    CHECK(ucd::is_pattern_white_space(U'\x0021') == false);
    CHECK(ucd::is_pattern_white_space(U'\x0022') == false);
    CHECK(ucd::is_pattern_white_space(U'\x0041') == false);
    CHECK(ucd::is_pattern_white_space(U'\x0084') == false);
    CHECK(ucd::is_pattern_white_space(U'\x0085') == true);
    CHECK(ucd::is_pattern_white_space(U'\x0086') == false);
    CHECK(ucd::is_pattern_white_space(U'\x0125') == false);
    CHECK(ucd::is_pattern_white_space(U'\x200D') == false);
    CHECK(ucd::is_pattern_white_space(U'\x200E') == true);
    CHECK(ucd::is_pattern_white_space(U'\x200F') == true);
    CHECK(ucd::is_pattern_white_space(U'\x2010') == false);
    CHECK(ucd::is_pattern_white_space(U'\x2027') == false);
    CHECK(ucd::is_pattern_white_space(U'\x2028') == true);
    CHECK(ucd::is_pattern_white_space(U'\x2029') == true);
    CHECK(ucd::is_pattern_white_space(U'\x202A') == false);
    CHECK(ucd::is_pattern_white_space(U'\x1F4A9') == false);
}
TEST_CASE("Dash can be queried", "[properties]") {
    CHECK(ucd::is_dash(U'\x002D') == true);
    CHECK(ucd::is_dash(U'\x0041') == false);
    CHECK(ucd::is_dash(U'\x05BE') == true);
    CHECK(ucd::is_dash(U'\x1F4A9') == false);
}
TEST_CASE("Quotation_Mark can be queried", "[properties]") {
    CHECK(ucd::is_quotation_mark(U'\x0022') == true);
    CHECK(ucd::is_quotation_mark(U'\x0024') == false);
    CHECK(ucd::is_quotation_mark(U'\x0027') == true);
    CHECK(ucd::is_quotation_mark(U'\x0041') == false);
    CHECK(ucd::is_quotation_mark(U'\x2018') == true);
    CHECK(ucd::is_quotation_mark(U'\x2019') == true);
    CHECK(ucd::is_quotation_mark(U'\x201A') == true);
    CHECK(ucd::is_quotation_mark(U'\x201B') == true);
    CHECK(ucd::is_quotation_mark(U'\x201C') == true);
    CHECK(ucd::is_quotation_mark(U'\x201D') == true);
    CHECK(ucd::is_quotation_mark(U'\x201E') == true);
    CHECK(ucd::is_quotation_mark(U'\x201F') == true);
    CHECK(ucd::is_quotation_mark(U'\x1F4A9') == false);
}
TEST_CASE("Terminal_Punctuation can be queried", "[properties]") {
    CHECK(ucd::is_terminal_punctuation(U'\x0021') == true);
    CHECK(ucd::is_terminal_punctuation(U'\x0022') == false);
    CHECK(ucd::is_terminal_punctuation(U'\x0387') == true);
    CHECK(ucd::is_terminal_punctuation(U'\x085E') == true);
    CHECK(ucd::is_terminal_punctuation(U'\x1C7E') == true);
    CHECK(ucd::is_terminal_punctuation(U'\x1F4A9') == false);
}
TEST_CASE("STerm can be queried", "[properties]") {
    CHECK(ucd::is_sterm(U'\x0021') == true);
    CHECK(ucd::is_sterm(U'\x0022') == false);
    CHECK(ucd::is_sterm(U'\x002E') == true);
    CHECK(ucd::is_sterm(U'\x0041') == false);
    CHECK(ucd::is_sterm(U'\x061F') == true);
    CHECK(ucd::is_sterm(U'\x1F4A9') == false);
}
TEST_CASE("Diacritic can be queried", "[properties]") {
    CHECK(ucd::is_diacritic(U'\x0041') == false);
    CHECK(ucd::is_diacritic(U'\x0060') == true);
    CHECK(ucd::is_diacritic(U'\x0061') == false);
    CHECK(ucd::is_diacritic(U'\x1DC6') == true);
    CHECK(ucd::is_diacritic(U'\x16AF3') == true);
    CHECK(ucd::is_diacritic(U'\x1F4A9') == false);
}
TEST_CASE("Extender can be queried", "[properties]") {
    CHECK(ucd::is_extender(U'\x00B7') == true);
    CHECK(ucd::is_extender(U'\x02D1') == true);
    CHECK(ucd::is_extender(U'\x02D2') == false);
    CHECK(ucd::is_extender(U'\x1844') == false);
    CHECK(ucd::is_extender(U'\x1AA7') == true);
    CHECK(ucd::is_extender(U'\x3033') == true);
    CHECK(ucd::is_extender(U'\x1F4A9') == false);
}
TEST_CASE("Soft_Dotted can be queried", "[properties]") {
    CHECK(ucd::is_soft_dotted(U'\x0041') == false);
    CHECK(ucd::is_soft_dotted(U'\x006A') == true);
    CHECK(ucd::is_soft_dotted(U'\x006B') == false);
    CHECK(ucd::is_soft_dotted(U'\x0458') == true);
    CHECK(ucd::is_soft_dotted(U'\x2149') == true);
    CHECK(ucd::is_soft_dotted(U'\x1D55B') == true);
    CHECK(ucd::is_soft_dotted(U'\x1F4A9') == false);
}
TEST_CASE("Hex_Digit can be queried", "[properties]") {
    CHECK(ucd::is_hex_digit(U'\x0033') == true);
    CHECK(ucd::is_hex_digit(U'\x003B') == false);
    CHECK(ucd::is_hex_digit(U'\x0043') == true);
    CHECK(ucd::is_hex_digit(U'\x0049') == false);
    CHECK(ucd::is_hex_digit(U'\x0063') == true);
    CHECK(ucd::is_hex_digit(U'\x0069') == false);
    CHECK(ucd::is_hex_digit(U'\xFF23') == true);
    CHECK(ucd::is_hex_digit(U'\xFF43') == true);
    CHECK(ucd::is_hex_digit(U'\x1F4A9') == false);
}
TEST_CASE("ASCII_Hex_Digit can be queried", "[properties]") {
    CHECK(ucd::is_ascii_hex_digit(U'\x0033') == true);
    CHECK(ucd::is_ascii_hex_digit(U'\x003B') == false);
    CHECK(ucd::is_ascii_hex_digit(U'\x0043') == true);
    CHECK(ucd::is_ascii_hex_digit(U'\x0049') == false);
    CHECK(ucd::is_ascii_hex_digit(U'\x0063') == true);
    CHECK(ucd::is_ascii_hex_digit(U'\x0069') == false);
    CHECK(ucd::is_ascii_hex_digit(U'\xFF23') == false);
    CHECK(ucd::is_ascii_hex_digit(U'\xFF43') == false);
    CHECK(ucd::is_ascii_hex_digit(U'\x1F4A9') == false);
}
TEST_CASE("Logical_Order_Exception can be queried", "[properties]") {
    CHECK(ucd::is_logical_order_exception(U'\x0041') == false);
    CHECK(ucd::is_logical_order_exception(U'\x0EC4') == true);
    CHECK(ucd::is_logical_order_exception(U'\x19B9') == false);
    CHECK(ucd::is_logical_order_exception(U'\xAABC') == true);
    CHECK(ucd::is_logical_order_exception(U'\x1F4A9') == false);
}
TEST_CASE("White_Space can be queried", "[properties]") {
    CHECK(ucd::is_white_space(U'\x0008') == false);
    CHECK(ucd::is_white_space(U'\x000A') == true);
    CHECK(ucd::is_white_space(U'\x000D') == true);
    CHECK(ucd::is_white_space(U'\x000E') == false);
    CHECK(ucd::is_white_space(U'\x0020') == true);
    CHECK(ucd::is_white_space(U'\x0021') == false);
    CHECK(ucd::is_white_space(U'\x0041') == false);
    CHECK(ucd::is_white_space(U'\x200E') == false);
    CHECK(ucd::is_white_space(U'\x200F') == false);
    CHECK(ucd::is_white_space(U'\x1680') == true);
    CHECK(ucd::is_white_space(U'\x1F4A9') == false);
}
TEST_CASE("Variation_Selector can be queried", "[properties]") {
    CHECK(ucd::is_variation_selector(U'\x0041') == false);
    CHECK(ucd::is_variation_selector(U'\x180D') == true);
    CHECK(ucd::is_variation_selector(U'\xFE03') == true);
    CHECK(ucd::is_variation_selector(U'\xFF00') == false);
    CHECK(ucd::is_variation_selector(U'\x1F4A9') == false);
    CHECK(ucd::is_variation_selector(U'\xE0123') == true);
}
TEST_CASE("Alphabetic can be queried", "[properties]") {
    CHECK(ucd::is_alphabetic(U'\x0021') == false);
    CHECK(ucd::is_alphabetic(U'\x0041') == true);
    CHECK(ucd::is_alphabetic(U'\x005D') == false);
    CHECK(ucd::is_alphabetic(U'\x0061') == true);
    CHECK(ucd::is_alphabetic(U'\x02EC') == true);
    CHECK(ucd::is_alphabetic(U'\x02ED') == false);
    CHECK(ucd::is_alphabetic(U'\x3408') == true);
    CHECK(ucd::is_alphabetic(U'\xAB46') == true);
    CHECK(ucd::is_alphabetic(U'\x1F4A9') == false);
    CHECK(ucd::is_alphabetic(U'\x20321') == true);
}
TEST_CASE("Math can be queried", "[properties]") {
    CHECK(ucd::is_math(U'\x000A') == false);
    CHECK(ucd::is_math(U'\x002B') == true);
    CHECK(ucd::is_math(U'\x002C') == false);
    CHECK(ucd::is_math(U'\x0041') == false);
    CHECK(ucd::is_math(U'\x00B1') == true);
    CHECK(ucd::is_math(U'\x03D2') == true);
    CHECK(ucd::is_math(U'\x2118') == true);
    CHECK(ucd::is_math(U'\x2119') == true);
    CHECK(ucd::is_math(U'\x1F4A9') == false);
}
TEST_CASE("Default_Ignorable_Code_Point can be queried", "[properties]") {
    CHECK(ucd::is_default_ignorable_code_point(U'\x0041') == false);
    CHECK(ucd::is_default_ignorable_code_point(U'\x00AD') == true);
    CHECK(ucd::is_default_ignorable_code_point(U'\x0100') == false);
    CHECK(ucd::is_default_ignorable_code_point(U'\x034F') == true);
    CHECK(ucd::is_default_ignorable_code_point(U'\x1F4A9') == false);
    CHECK(ucd::is_default_ignorable_code_point(U'\xE0003') == true);
    CHECK(ucd::is_default_ignorable_code_point(U'\xE1003') == false);
}
TEST_CASE("Grapheme_Base can be queried", "[properties]") {
    CHECK(ucd::is_grapheme_base(U'\x000A') == false);
    CHECK(ucd::is_grapheme_base(U'\x0041') == true);
    CHECK(ucd::is_grapheme_base(U'\x0100') == true);
    CHECK(ucd::is_grapheme_base(U'\x0301') == false);
    CHECK(ucd::is_grapheme_base(U'\x0D60') == true);
    CHECK(ucd::is_grapheme_base(U'\x0D62') == false);
    CHECK(ucd::is_grapheme_base(U'\x1F4A9') == true);
}
TEST_CASE("Grapheme_Extend can be queried", "[properties]") {
    CHECK(ucd::is_grapheme_extend(U'\x000A') == false);
    CHECK(ucd::is_grapheme_extend(U'\x0041') == false);
    CHECK(ucd::is_grapheme_extend(U'\x0100') == false);
    CHECK(ucd::is_grapheme_extend(U'\x0301') == true);
    CHECK(ucd::is_grapheme_extend(U'\x0D60') == false);
    CHECK(ucd::is_grapheme_extend(U'\x0D62') == true);
    CHECK(ucd::is_grapheme_extend(U'\x1F4A9') == false);
}
TEST_CASE("Grapheme_Cluster_Break can be queried", "[properties]") {
    CHECK(ucd::get_grapheme_cluster_break(U'\x0008') == ucd::grapheme_cluster_break::cn);
    CHECK(ucd::get_grapheme_cluster_break(U'\x000A') == ucd::grapheme_cluster_break::lf);
    CHECK(ucd::get_grapheme_cluster_break(U'\x000B') == ucd::grapheme_cluster_break::cn);
    CHECK(ucd::get_grapheme_cluster_break(U'\x000D') == ucd::grapheme_cluster_break::cr);
    CHECK(ucd::get_grapheme_cluster_break(U'\x001D') == ucd::grapheme_cluster_break::cn);
    CHECK(ucd::get_grapheme_cluster_break(U'\x0041') == ucd::grapheme_cluster_break::xx);
    CHECK(ucd::get_grapheme_cluster_break(U'\xA8C4') == ucd::grapheme_cluster_break::ex);
    CHECK(ucd::get_grapheme_cluster_break(U'\xC4A0') == ucd::grapheme_cluster_break::lvt);
    CHECK(ucd::get_grapheme_cluster_break(U'\x1F4A9') == ucd::grapheme_cluster_break::xx);
    CHECK(ucd::get_grapheme_cluster_break(U'\xE000E') == ucd::grapheme_cluster_break::cn);
}
TEST_CASE("Word_Break can be queried", "[properties]") {
    CHECK(ucd::get_word_break(U'\x0008') == ucd::word_break::xx);
    CHECK(ucd::get_word_break(U'\x000A') == ucd::word_break::lf);
    CHECK(ucd::get_word_break(U'\x000C') == ucd::word_break::nl);
    CHECK(ucd::get_word_break(U'\x000D') == ucd::word_break::cr);
    CHECK(ucd::get_word_break(U'\x0022') == ucd::word_break::dq);
    CHECK(ucd::get_word_break(U'\x0027') == ucd::word_break::sq);
    CHECK(ucd::get_word_break(U'\x002E') == ucd::word_break::mb);
    CHECK(ucd::get_word_break(U'\x0032') == ucd::word_break::nu);
    CHECK(ucd::get_word_break(U'\x0041') == ucd::word_break::le);
    CHECK(ucd::get_word_break(U'\xE0101') == ucd::word_break::extend);
    CHECK(ucd::get_word_break(U'\x1F4A9') == ucd::word_break::xx);
}
TEST_CASE("Sentence_Break can be queried", "[properties]") {
    CHECK(ucd::get_sentence_break(U'\x0008') == ucd::sentence_break::xx);
    CHECK(ucd::get_sentence_break(U'\x000A') == ucd::sentence_break::lf);
    CHECK(ucd::get_sentence_break(U'\x000B') == ucd::sentence_break::sp);
    CHECK(ucd::get_sentence_break(U'\x000C') == ucd::sentence_break::sp);
    CHECK(ucd::get_sentence_break(U'\x000D') == ucd::sentence_break::cr);
    CHECK(ucd::get_sentence_break(U'\x0020') == ucd::sentence_break::sp);
    CHECK(ucd::get_sentence_break(U'\x003F') == ucd::sentence_break::st);
    CHECK(ucd::get_sentence_break(U'\x0041') == ucd::sentence_break::up);
    CHECK(ucd::get_sentence_break(U'\x005B') == ucd::sentence_break::cl);
    CHECK(ucd::get_sentence_break(U'\x1F4A9') == ucd::sentence_break::xx);
    CHECK(ucd::get_sentence_break(U'\xE0030') == ucd::sentence_break::ex);
    CHECK(ucd::get_sentence_break(U'\xE0200') == ucd::sentence_break::xx);
}
TEST_CASE("Ideographic can be queried", "[properties]") {
    CHECK(ucd::is_ideographic(U'\x0021') == false);
    CHECK(ucd::is_ideographic(U'\x0041') == false);
    CHECK(ucd::is_ideographic(U'\x005D') == false);
    CHECK(ucd::is_ideographic(U'\x0061') == false);
    CHECK(ucd::is_ideographic(U'\x02EC') == false);
    CHECK(ucd::is_ideographic(U'\x02ED') == false);
    CHECK(ucd::is_ideographic(U'\x3408') == true);
    CHECK(ucd::is_ideographic(U'\x4DC0') == false);
    CHECK(ucd::is_ideographic(U'\x4E08') == true);
    CHECK(ucd::is_ideographic(U'\xAB46') == false);
    CHECK(ucd::is_ideographic(U'\xF909') == true);
    CHECK(ucd::is_ideographic(U'\x1F4A9') == false);
    CHECK(ucd::is_ideographic(U'\x20321') == true);
    CHECK(ucd::is_ideographic(U'\x2F808') == true);
}
TEST_CASE("Unified_Ideograph can be queried", "[properties]") {
    CHECK(ucd::is_unified_ideograph(U'\x0021') == false);
    CHECK(ucd::is_unified_ideograph(U'\x0041') == false);
    CHECK(ucd::is_unified_ideograph(U'\x005D') == false);
    CHECK(ucd::is_unified_ideograph(U'\x0061') == false);
    CHECK(ucd::is_unified_ideograph(U'\x02EC') == false);
    CHECK(ucd::is_unified_ideograph(U'\x02ED') == false);
    CHECK(ucd::is_unified_ideograph(U'\x3408') == true);
    CHECK(ucd::is_unified_ideograph(U'\x4DC0') == false);
    CHECK(ucd::is_unified_ideograph(U'\x4E08') == true);
    CHECK(ucd::is_unified_ideograph(U'\xAB46') == false);
    CHECK(ucd::is_unified_ideograph(U'\xF909') == false);
    CHECK(ucd::is_unified_ideograph(U'\x1F4A9') == false);
    CHECK(ucd::is_unified_ideograph(U'\x20321') == true);
    CHECK(ucd::is_unified_ideograph(U'\x2F808') == false);
}
TEST_CASE("IDS_Binary_Operator can be queried", "[properties]") {
    CHECK(ucd::is_ids_binary_operator(U'\x0041') == false);
    CHECK(ucd::is_ids_binary_operator(U'\x2FF0') == true);
    CHECK(ucd::is_ids_binary_operator(U'\x2FF1') == true);
    CHECK(ucd::is_ids_binary_operator(U'\x2FF2') == false);
    CHECK(ucd::is_ids_binary_operator(U'\x2FF3') == false);
    CHECK(ucd::is_ids_binary_operator(U'\x2FF4') == true);
    CHECK(ucd::is_ids_binary_operator(U'\x2FF5') == true);
    CHECK(ucd::is_ids_binary_operator(U'\x2FFB') == true);
    CHECK(ucd::is_ids_binary_operator(U'\x2FFC') == false);
    CHECK(ucd::is_ids_binary_operator(U'\x1F4A9') == false);
}
TEST_CASE("IDS_Trinary_Operator can be queried", "[properties]") {
    CHECK(ucd::is_ids_trinary_operator(U'\x0041') == false);
    CHECK(ucd::is_ids_trinary_operator(U'\x2FF1') == false);
    CHECK(ucd::is_ids_trinary_operator(U'\x2FF2') == true);
    CHECK(ucd::is_ids_trinary_operator(U'\x2FF3') == true);
    CHECK(ucd::is_ids_trinary_operator(U'\x2FF4') == false);
    CHECK(ucd::is_ids_trinary_operator(U'\x2FF5') == false);
    CHECK(ucd::is_ids_trinary_operator(U'\x2FFB') == false);
    CHECK(ucd::is_ids_trinary_operator(U'\x2FFC') == false);
    CHECK(ucd::is_ids_trinary_operator(U'\x1F4A9') == false);
}
TEST_CASE("Radical can be queried", "[properties]") {
    CHECK(ucd::is_radical(U'\x0041') == false);
    CHECK(ucd::is_radical(U'\x2E88') == true);
    CHECK(ucd::is_radical(U'\x2E9A') == false);
    CHECK(ucd::is_radical(U'\x2EAA') == true);
    CHECK(ucd::is_radical(U'\x2EFF') == false);
    CHECK(ucd::is_radical(U'\x2F0F') == true);
    CHECK(ucd::is_radical(U'\x2FFF') == false);
    CHECK(ucd::is_radical(U'\x1F4A9') == false);
}
TEST_CASE("Deprecated can be queried", "[properties]") {
    CHECK(ucd::is_deprecated(U'\x0041') == false);
    CHECK(ucd::is_deprecated(U'\x0149') == true);
    CHECK(ucd::is_deprecated(U'\x014A') == false);
    CHECK(ucd::is_deprecated(U'\x0673') == true);
    CHECK(ucd::is_deprecated(U'\x0674') == false);
    CHECK(ucd::is_deprecated(U'\x0F77') == true);
    CHECK(ucd::is_deprecated(U'\x0F78') == false);
    CHECK(ucd::is_deprecated(U'\x2329') == true);
    CHECK(ucd::is_deprecated(U'\x232A') == true);
    CHECK(ucd::is_deprecated(U'\x232B') == false);
    CHECK(ucd::is_deprecated(U'\x1F4A9') == false);
    CHECK(ucd::is_deprecated(U'\xE0001') == true);
    CHECK(ucd::is_deprecated(U'\xE0002') == false);
}
TEST_CASE("Noncharacter_Code_Point can be queried", "[properties]") {
    CHECK(ucd::is_noncharacter_code_point(U'\x0041') == false);
    CHECK(ucd::is_noncharacter_code_point(U'\xFDCF') == false);
    for(auto u = U'\xFDD0'; u < U'\xFDF0'; ++u) {
        CHECK(ucd::is_noncharacter_code_point(u) == true);
    }
    CHECK(ucd::is_noncharacter_code_point(U'\xFDF0') == false);
    for(auto u = U'\xFFFE'; u < U'\x110000'; u += 0x10000) {
        CHECK(ucd::is_noncharacter_code_point(u-1) == false);
        CHECK(ucd::is_noncharacter_code_point(u+0) == true);
        CHECK(ucd::is_noncharacter_code_point(u+1) == true);
        if(u+2 < U'\x110000')
            CHECK(ucd::is_noncharacter_code_point(u+2) == false);
    }
}
