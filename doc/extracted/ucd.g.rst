Unicode character database
==========================

.. note:: The items in this section are in the namespace ``ogonek::ucd``.

.. function:: version get_age(code_point u)

    :returns: the *Age* property of ``u``

.. function:: std::string get_name(code_point u)

    :returns: the *Name* property of ``u``

.. function:: block get_block(code_point u)

    :returns: the *Block* property of ``u``

.. function:: block get_general_category(code_point u)

    :returns: the *General_Category* property of ``u``

.. function:: combining_class get_canonical_combining_class(code_point u)

    :returns: the *Canonical_Combining_Class* property of ``u``

.. function:: bidi_class get_bidi_class(code_point u)

    :returns: the *Bidi_Class* property of ``u``

.. function:: bool is_bidi_mirrored(code_point u)

    :returns: true if ``u`` has the *Bidi_Mirrored* property; false otherwise

.. function:: code_point get_bidi_mirroring_glyph(code_point u)

    :returns: the *Bidi_Mirroring_Glyph* property of ``u``

.. function:: bool is_bidi_control(code_point u)

    :returns: true if ``u`` has the *Bidi_Control* property; false otherwise

.. function:: code_point get_bidi_paired_bracket(code_point u)

    :returns: the *Bidi_Paired_Bracket* property of ``u``

.. function:: bracket_type get_bidi_paired_bracket_type(code_point u)

    :returns: the *Bidi_Paired_Bracket_Type* property of ``u``

.. function:: decomposition_type get_decomposition_type(code_point u)

    :returns: the *Decomposition_Type* property of ``u``

.. function:: std::u32string get_decomposition_mapping(code_point u)

    :returns: the *Decomposition_Mapping* property of ``u``

.. function:: bool is_excluded_from_composition(code_point u)

    :returns: true if ``u`` has the *Full_Composition_Exclusion* property; false otherwise

.. function:: tribool get_nfc_quick_check(code_point u)

    :returns: the *NFC_Quick_Check* property of ``u``

.. function:: bool get_nfd_quick_check(code_point u)

    :returns: the *NFD_Quick_Check* property of ``u``

.. function:: tribool get_nfkc_quick_check(code_point u)

    :returns: the *NFKC_Quick_Check* property of ``u``

.. function:: bool get_nfkd_quick_check(code_point u)

    :returns: the *NFKD_Quick_Check* property of ``u``

.. function:: numeric_type get_numeric_type(code_point u)

    :returns: the *Numeric_Type* property of ``u``

.. function:: boost::optional<boost::rational<long>> get_numeric_value(code_point u)

    :returns: the *Numeric_Value* property of ``u``, if present; none otherwise

.. function:: joining_type get_joining_type(code_point u)

    :returns: the *Joining_Type* property of ``u``

.. function:: joining_group get_joining_group(code_point u)

    :returns: the *Joining_Group* property of ``u``

.. function:: bool is_join_control(code_point u)

    :returns: true if ``u`` has the *Join_Control* property; false otherwise

.. function:: line_break get_line_break(code_point u)

    :returns: the *Line_Break* property of ``u``

.. function:: east_asian_width get_east_asian_width(code_point u)

    :returns: the *East_Asian_Width* property of ``u``

.. function:: bool is_uppercase(code_point u)

    :returns: true if ``u`` has the *Uppercase* property; false otherwise

.. function:: bool is_lowercase(code_point u)

    :returns: true if ``u`` has the *Lowercase* property; false otherwise

.. function:: code_point get_simple_uppercase_mapping(code_point u)

    :returns: the *Simple_Uppercase_Mapping* property of ``u``

.. function:: code_point get_simple_lowercase_mapping(code_point u)

    :returns: the *Simple_Lowercase_Mapping* property of ``u``

.. function:: code_point get_simple_titlecase_mapping(code_point u)

    :returns: the *Simple_Titlecase_Mapping* property of ``u``

.. function:: std::u32string get_uppercase_mapping(code_point u)

    :returns: the *Uppercase_Mapping* property of ``u``

.. function:: std::u32string get_lowercase_mapping(code_point u)

    :returns: the *Lowercase_Mapping* property of ``u``

.. function:: std::u32string get_titlecase_mapping(code_point u)

    :returns: the *Titlecase_Mapping* property of ``u``

.. function:: code_point get_simple_case_folding(code_point u)

    :returns: the *Simple_Case_Folding* property of ``u``

.. function:: std::u32string get_case_folding(code_point u)

    :returns: the *Case_Folding* property of ``u``

.. function:: bool is_case_ignorable(code_point u)

    :returns: true if ``u`` has the *Case_Ignorable* property; false otherwise

.. function:: bool is_cased(code_point u)

    :returns: true if ``u`` has the *Cased* property; false otherwise

.. function:: bool changes_when_lowercased(code_point u)

    :returns: true if ``u`` has the *Changes_When_Lowercased* property; false otherwise

.. function:: bool changes_when_uppercased(code_point u)

    :returns: true if ``u`` has the *Changes_When_Uppercased* property; false otherwise

.. function:: bool changes_when_titlecased(code_point u)

    :returns: true if ``u`` has the *Changes_When_Titlecased* property; false otherwise

.. function:: bool changes_when_casefolded(code_point u)

    :returns: true if ``u`` has the *Changes_When_Casefolded* property; false otherwise

.. function:: bool changes_when_casemapped(code_point u)

    :returns: true if ``u`` has the *Changes_When_Casemapped* property; false otherwise

.. function:: bool changes_when_nfkc_casefolded(code_point u)

    :returns: true if ``u`` has the *Changes_When_NFKC_Casefolded* property; false otherwise

.. function:: std::u32string get_nfkc_casefold(code_point u)

    :returns: the *NFKC_Casefold* property of ``u``

.. function:: script get_script(code_point u)

    :returns: the *Script* property of ``u``

.. function:: hangul_syllable_type get_hangul_syllable_type(code_point u)

    :returns: the *Hangul_Syllable_Type* property of ``u``

.. function:: std::string get_jamo_short_name(code_point u)

    :returns: the *Jamo_Short_Name* property of ``u``

.. function:: indic_positional_category get_indic_positional_category(code_point u)

    :returns: the *Indic_Positional_Category* property of ``u``

.. function:: indic_syllabic_category get_indic_syllabic_category(code_point u)

    :returns: the *Indic_Syllabic_Category* property of ``u``

.. function:: bool is_id_start(code_point u)

    :returns: true if ``u`` has the *ID_Start* property; false otherwise

.. function:: bool is_id_continue(code_point u)

    :returns: true if ``u`` has the *ID_Continue* property; false otherwise

.. function:: bool is_xid_start(code_point u)

    :returns: true if ``u`` has the *XID_Start* property; false otherwise

.. function:: bool is_xid_continue(code_point u)

    :returns: true if ``u`` has the *XID_Continue* property; false otherwise

.. function:: bool is_pattern_syntax(code_point u)

    :returns: true if ``u`` has the *Pattern_Syntax* property; false otherwise

.. function:: bool is_pattern_white_space(code_point u)

    :returns: true if ``u`` has the *Pattern_White_Space* property; false otherwise

.. function:: bool is_dash(code_point u)

    :returns: true if ``u`` has the *Dash* property; false otherwise

.. function:: bool is_quotation_mark(code_point u)

    :returns: true if ``u`` has the *Quotation_Mark* property; false otherwise

.. function:: bool is_terminal_punctuation(code_point u)

    :returns: true if ``u`` has the *Terminal_Punctuation* property; false otherwise

.. function:: bool is_sterm(code_point u)

    :returns: true if ``u`` has the *STerm* property; false otherwise

.. function:: bool is_diacritic(code_point u)

    :returns: true if ``u`` has the *Diacritic* property; false otherwise

.. function:: bool is_extender(code_point u)

    :returns: true if ``u`` has the *Extender* property; false otherwise

.. function:: bool is_soft_dotted(code_point u)

    :returns: true if ``u`` has the *Soft_Dotted* property; false otherwise

.. function:: bool is_hex_digit(code_point u)

    :returns: true if ``u`` has the *Hex_Digit* property; false otherwise

.. function:: bool is_ascii_hex_digit(code_point u)

    :returns: true if ``u`` has the *ASCII_Hex_Digit* property; false otherwise

.. function:: bool is_logical_order_exception(code_point u)

    :returns: true if ``u`` has the *Logical_Order_Exception* property; false otherwise

.. function:: bool is_white_space(code_point u)

    :returns: true if ``u`` has the *White_Space* property; false otherwise

.. function:: bool is_variation_selector(code_point u)

    :returns: true if ``u`` has the *Variation_Selector* property; false otherwise

.. function:: bool is_alphabetic(code_point u)

    :returns: true if ``u`` has the *Alphabetic* property; false otherwise

.. function:: bool is_math(code_point u)

    :returns: true if ``u`` has the *Math* property; false otherwise

.. function:: bool is_default_ignorable_code_point(code_point u)

    :returns: true if ``u`` has the *Default_Ignorable_Code_Point* property; false otherwise

.. function:: bool is_grapheme_base(code_point u)

    :returns: true if ``u`` has the *Grapheme_Base* property; false otherwise

.. function:: bool is_grapheme_extend(code_point u)

    :returns: true if ``u`` has the *Grapheme_Extend* property; false otherwise

.. function:: grapheme_cluster_break get_grapheme_cluster_break(code_point u)

    :returns: the *Grapheme_Cluster_Break* property of ``u``

.. function:: word_break get_word_break(code_point u)

    :returns: the *Word_Break* property of ``u``

.. function:: sentence_break get_sentence_break(code_point u)

    :returns: the *Sentence_Break* property of ``u``

.. function:: bool is_ideographic(code_point u)

    :returns: true if ``u`` has the *Ideographic* property; false otherwise

.. function:: bool is_unified_ideograph(code_point u)

    :returns: true if ``u`` has the *Unified_Ideograph* property; false otherwise

.. function:: bool is_ids_binary_operator(code_point u)

    :returns: true if ``u`` has the *IDS_Binary_Operator* property; false otherwise

.. function:: bool is_ids_trinary_operator(code_point u)

    :returns: true if ``u`` has the *IDS_Trinary_Operator* property; false otherwise

.. function:: bool is_radical(code_point u)

    :returns: true if ``u`` has the *Radical* property; false otherwise

.. function:: bool is_deprecated(code_point u)

    :returns: true if ``u`` has the *Deprecated* property; false otherwise

.. function:: bool is_noncharacter_code_point(code_point u)

    :returns: true if ``u`` has the *Noncharacter_Code_Point* property; false otherwise

