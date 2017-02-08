// Ogonek
//
// Written in 2017 by Martinho Fernandes <ogonek@rmf.io>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

// This file was automatically generated.

// Unicode character database - Block property

#include <ogonek/ucd/block.g.h++>
#include <ogonek/detail/size.h++>

#include <cstddef>

namespace ogonek {
    namespace ucd {
        namespace {
            block_properties const block_data_raw[] {
                { 0x0, block::basic_latin },
                { 0x80, block::latin_1_supplement },
                { 0x100, block::latin_extended_a },
                { 0x180, block::latin_extended_b },
                { 0x250, block::ipa_extensions },
                { 0x2B0, block::spacing_modifier_letters },
                { 0x300, block::combining_diacritical_marks },
                { 0x370, block::greek_and_coptic },
                { 0x400, block::cyrillic },
                { 0x500, block::cyrillic_supplement },
                { 0x530, block::armenian },
                { 0x590, block::hebrew },
                { 0x600, block::arabic },
                { 0x700, block::syriac },
                { 0x750, block::arabic_supplement },
                { 0x780, block::thaana },
                { 0x7C0, block::nko },
                { 0x800, block::samaritan },
                { 0x840, block::mandaic },
                { 0x860, block::nb },
                { 0x8A0, block::arabic_extended_a },
                { 0x900, block::devanagari },
                { 0x980, block::bengali },
                { 0xA00, block::gurmukhi },
                { 0xA80, block::gujarati },
                { 0xB00, block::oriya },
                { 0xB80, block::tamil },
                { 0xC00, block::telugu },
                { 0xC80, block::kannada },
                { 0xD00, block::malayalam },
                { 0xD80, block::sinhala },
                { 0xE00, block::thai },
                { 0xE80, block::lao },
                { 0xF00, block::tibetan },
                { 0x1000, block::myanmar },
                { 0x10A0, block::georgian },
                { 0x1100, block::hangul_jamo },
                { 0x1200, block::ethiopic },
                { 0x1380, block::ethiopic_supplement },
                { 0x13A0, block::cherokee },
                { 0x1400, block::unified_canadian_aboriginal_syllabics },
                { 0x1680, block::ogham },
                { 0x16A0, block::runic },
                { 0x1700, block::tagalog },
                { 0x1720, block::hanunoo },
                { 0x1740, block::buhid },
                { 0x1760, block::tagbanwa },
                { 0x1780, block::khmer },
                { 0x1800, block::mongolian },
                { 0x18B0, block::unified_canadian_aboriginal_syllabics_extended },
                { 0x1900, block::limbu },
                { 0x1950, block::tai_le },
                { 0x1980, block::new_tai_lue },
                { 0x19E0, block::khmer_symbols },
                { 0x1A00, block::buginese },
                { 0x1A20, block::tai_tham },
                { 0x1AB0, block::combining_diacritical_marks_extended },
                { 0x1B00, block::balinese },
                { 0x1B80, block::sundanese },
                { 0x1BC0, block::batak },
                { 0x1C00, block::lepcha },
                { 0x1C50, block::ol_chiki },
                { 0x1C80, block::cyrillic_extended_c },
                { 0x1C90, block::nb },
                { 0x1CC0, block::sundanese_supplement },
                { 0x1CD0, block::vedic_extensions },
                { 0x1D00, block::phonetic_extensions },
                { 0x1D80, block::phonetic_extensions_supplement },
                { 0x1DC0, block::combining_diacritical_marks_supplement },
                { 0x1E00, block::latin_extended_additional },
                { 0x1F00, block::greek_extended },
                { 0x2000, block::general_punctuation },
                { 0x2070, block::superscripts_and_subscripts },
                { 0x20A0, block::currency_symbols },
                { 0x20D0, block::combining_diacritical_marks_for_symbols },
                { 0x2100, block::letterlike_symbols },
                { 0x2150, block::number_forms },
                { 0x2190, block::arrows },
                { 0x2200, block::mathematical_operators },
                { 0x2300, block::miscellaneous_technical },
                { 0x2400, block::control_pictures },
                { 0x2440, block::optical_character_recognition },
                { 0x2460, block::enclosed_alphanumerics },
                { 0x2500, block::box_drawing },
                { 0x2580, block::block_elements },
                { 0x25A0, block::geometric_shapes },
                { 0x2600, block::miscellaneous_symbols },
                { 0x2700, block::dingbats },
                { 0x27C0, block::miscellaneous_mathematical_symbols_a },
                { 0x27F0, block::supplemental_arrows_a },
                { 0x2800, block::braille_patterns },
                { 0x2900, block::supplemental_arrows_b },
                { 0x2980, block::miscellaneous_mathematical_symbols_b },
                { 0x2A00, block::supplemental_mathematical_operators },
                { 0x2B00, block::miscellaneous_symbols_and_arrows },
                { 0x2C00, block::glagolitic },
                { 0x2C60, block::latin_extended_c },
                { 0x2C80, block::coptic },
                { 0x2D00, block::georgian_supplement },
                { 0x2D30, block::tifinagh },
                { 0x2D80, block::ethiopic_extended },
                { 0x2DE0, block::cyrillic_extended_a },
                { 0x2E00, block::supplemental_punctuation },
                { 0x2E80, block::cjk_radicals_supplement },
                { 0x2F00, block::kangxi_radicals },
                { 0x2FE0, block::nb },
                { 0x2FF0, block::ideographic_description_characters },
                { 0x3000, block::cjk_symbols_and_punctuation },
                { 0x3040, block::hiragana },
                { 0x30A0, block::katakana },
                { 0x3100, block::bopomofo },
                { 0x3130, block::hangul_compatibility_jamo },
                { 0x3190, block::kanbun },
                { 0x31A0, block::bopomofo_extended },
                { 0x31C0, block::cjk_strokes },
                { 0x31F0, block::katakana_phonetic_extensions },
                { 0x3200, block::enclosed_cjk_letters_and_months },
                { 0x3300, block::cjk_compatibility },
                { 0x3400, block::cjk_unified_ideographs_extension_a },
                { 0x4DC0, block::yijing_hexagram_symbols },
                { 0x4E00, block::cjk_unified_ideographs },
                { 0xA000, block::yi_syllables },
                { 0xA490, block::yi_radicals },
                { 0xA4D0, block::lisu },
                { 0xA500, block::vai },
                { 0xA640, block::cyrillic_extended_b },
                { 0xA6A0, block::bamum },
                { 0xA700, block::modifier_tone_letters },
                { 0xA720, block::latin_extended_d },
                { 0xA800, block::syloti_nagri },
                { 0xA830, block::common_indic_number_forms },
                { 0xA840, block::phags_pa },
                { 0xA880, block::saurashtra },
                { 0xA8E0, block::devanagari_extended },
                { 0xA900, block::kayah_li },
                { 0xA930, block::rejang },
                { 0xA960, block::hangul_jamo_extended_a },
                { 0xA980, block::javanese },
                { 0xA9E0, block::myanmar_extended_b },
                { 0xAA00, block::cham },
                { 0xAA60, block::myanmar_extended_a },
                { 0xAA80, block::tai_viet },
                { 0xAAE0, block::meetei_mayek_extensions },
                { 0xAB00, block::ethiopic_extended_a },
                { 0xAB30, block::latin_extended_e },
                { 0xAB70, block::cherokee_supplement },
                { 0xABC0, block::meetei_mayek },
                { 0xAC00, block::hangul_syllables },
                { 0xD7B0, block::hangul_jamo_extended_b },
                { 0xD800, block::high_surrogates },
                { 0xDB80, block::high_private_use_surrogates },
                { 0xDC00, block::low_surrogates },
                { 0xE000, block::private_use_area },
                { 0xF900, block::cjk_compatibility_ideographs },
                { 0xFB00, block::alphabetic_presentation_forms },
                { 0xFB50, block::arabic_presentation_forms_a },
                { 0xFE00, block::variation_selectors },
                { 0xFE10, block::vertical_forms },
                { 0xFE20, block::combining_half_marks },
                { 0xFE30, block::cjk_compatibility_forms },
                { 0xFE50, block::small_form_variants },
                { 0xFE70, block::arabic_presentation_forms_b },
                { 0xFF00, block::halfwidth_and_fullwidth_forms },
                { 0xFFF0, block::specials },
                { 0x10000, block::linear_b_syllabary },
                { 0x10080, block::linear_b_ideograms },
                { 0x10100, block::aegean_numbers },
                { 0x10140, block::ancient_greek_numbers },
                { 0x10190, block::ancient_symbols },
                { 0x101D0, block::phaistos_disc },
                { 0x10200, block::nb },
                { 0x10280, block::lycian },
                { 0x102A0, block::carian },
                { 0x102E0, block::coptic_epact_numbers },
                { 0x10300, block::old_italic },
                { 0x10330, block::gothic },
                { 0x10350, block::old_permic },
                { 0x10380, block::ugaritic },
                { 0x103A0, block::old_persian },
                { 0x103E0, block::nb },
                { 0x10400, block::deseret },
                { 0x10450, block::shavian },
                { 0x10480, block::osmanya },
                { 0x104B0, block::osage },
                { 0x10500, block::elbasan },
                { 0x10530, block::caucasian_albanian },
                { 0x10570, block::nb },
                { 0x10600, block::linear_a },
                { 0x10780, block::nb },
                { 0x10800, block::cypriot_syllabary },
                { 0x10840, block::imperial_aramaic },
                { 0x10860, block::palmyrene },
                { 0x10880, block::nabataean },
                { 0x108B0, block::nb },
                { 0x108E0, block::hatran },
                { 0x10900, block::phoenician },
                { 0x10920, block::lydian },
                { 0x10940, block::nb },
                { 0x10980, block::meroitic_hieroglyphs },
                { 0x109A0, block::meroitic_cursive },
                { 0x10A00, block::kharoshthi },
                { 0x10A60, block::old_south_arabian },
                { 0x10A80, block::old_north_arabian },
                { 0x10AA0, block::nb },
                { 0x10AC0, block::manichaean },
                { 0x10B00, block::avestan },
                { 0x10B40, block::inscriptional_parthian },
                { 0x10B60, block::inscriptional_pahlavi },
                { 0x10B80, block::psalter_pahlavi },
                { 0x10BB0, block::nb },
                { 0x10C00, block::old_turkic },
                { 0x10C50, block::nb },
                { 0x10C80, block::old_hungarian },
                { 0x10D00, block::nb },
                { 0x10E60, block::rumi_numeral_symbols },
                { 0x10E80, block::nb },
                { 0x11000, block::brahmi },
                { 0x11080, block::kaithi },
                { 0x110D0, block::sora_sompeng },
                { 0x11100, block::chakma },
                { 0x11150, block::mahajani },
                { 0x11180, block::sharada },
                { 0x111E0, block::sinhala_archaic_numbers },
                { 0x11200, block::khojki },
                { 0x11250, block::nb },
                { 0x11280, block::multani },
                { 0x112B0, block::khudawadi },
                { 0x11300, block::grantha },
                { 0x11380, block::nb },
                { 0x11400, block::newa },
                { 0x11480, block::tirhuta },
                { 0x114E0, block::nb },
                { 0x11580, block::siddham },
                { 0x11600, block::modi },
                { 0x11660, block::mongolian_supplement },
                { 0x11680, block::takri },
                { 0x116D0, block::nb },
                { 0x11700, block::ahom },
                { 0x11740, block::nb },
                { 0x118A0, block::warang_citi },
                { 0x11900, block::nb },
                { 0x11AC0, block::pau_cin_hau },
                { 0x11B00, block::nb },
                { 0x11C00, block::bhaiksuki },
                { 0x11C70, block::marchen },
                { 0x11CC0, block::nb },
                { 0x12000, block::cuneiform },
                { 0x12400, block::cuneiform_numbers_and_punctuation },
                { 0x12480, block::early_dynastic_cuneiform },
                { 0x12550, block::nb },
                { 0x13000, block::egyptian_hieroglyphs },
                { 0x13430, block::nb },
                { 0x14400, block::anatolian_hieroglyphs },
                { 0x14680, block::nb },
                { 0x16800, block::bamum_supplement },
                { 0x16A40, block::mro },
                { 0x16A70, block::nb },
                { 0x16AD0, block::bassa_vah },
                { 0x16B00, block::pahawh_hmong },
                { 0x16B90, block::nb },
                { 0x16F00, block::miao },
                { 0x16FA0, block::nb },
                { 0x16FE0, block::ideographic_symbols_and_punctuation },
                { 0x17000, block::tangut },
                { 0x18800, block::tangut_components },
                { 0x18B00, block::nb },
                { 0x1B000, block::kana_supplement },
                { 0x1B100, block::nb },
                { 0x1BC00, block::duployan },
                { 0x1BCA0, block::shorthand_format_controls },
                { 0x1BCB0, block::nb },
                { 0x1D000, block::byzantine_musical_symbols },
                { 0x1D100, block::musical_symbols },
                { 0x1D200, block::ancient_greek_musical_notation },
                { 0x1D250, block::nb },
                { 0x1D300, block::tai_xuan_jing_symbols },
                { 0x1D360, block::counting_rod_numerals },
                { 0x1D380, block::nb },
                { 0x1D400, block::mathematical_alphanumeric_symbols },
                { 0x1D800, block::sutton_sign_writing },
                { 0x1DAB0, block::nb },
                { 0x1E000, block::glagolitic_supplement },
                { 0x1E030, block::nb },
                { 0x1E800, block::mende_kikakui },
                { 0x1E8E0, block::nb },
                { 0x1E900, block::adlam },
                { 0x1E960, block::nb },
                { 0x1EE00, block::arabic_mathematical_alphabetic_symbols },
                { 0x1EF00, block::nb },
                { 0x1F000, block::mahjong_tiles },
                { 0x1F030, block::domino_tiles },
                { 0x1F0A0, block::playing_cards },
                { 0x1F100, block::enclosed_alphanumeric_supplement },
                { 0x1F200, block::enclosed_ideographic_supplement },
                { 0x1F300, block::miscellaneous_symbols_and_pictographs },
                { 0x1F600, block::emoticons },
                { 0x1F650, block::ornamental_dingbats },
                { 0x1F680, block::transport_and_map_symbols },
                { 0x1F700, block::alchemical_symbols },
                { 0x1F780, block::geometric_shapes_extended },
                { 0x1F800, block::supplemental_arrows_c },
                { 0x1F900, block::supplemental_symbols_and_pictographs },
                { 0x1FA00, block::nb },
                { 0x20000, block::cjk_unified_ideographs_extension_b },
                { 0x2A6E0, block::nb },
                { 0x2A700, block::cjk_unified_ideographs_extension_c },
                { 0x2B740, block::cjk_unified_ideographs_extension_d },
                { 0x2B820, block::cjk_unified_ideographs_extension_e },
                { 0x2CEB0, block::nb },
                { 0x2F800, block::cjk_compatibility_ideographs_supplement },
                { 0x2FA20, block::nb },
                { 0xE0000, block::tags },
                { 0xE0080, block::nb },
                { 0xE0100, block::variation_selectors_supplement },
                { 0xE01F0, block::nb },
                { 0xF0000, block::supplementary_private_use_area_a },
                { 0x100000, block::supplementary_private_use_area_b },
            };
        } // namespace
        inline namespace abiv0 {
            block_properties const* block_data = block_data_raw;
            std::size_t block_data_size = detail::size(block_data_raw);
        } // namespace abiv0
    } // namespace ucd
} // namespace ogonek
