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

// Unicode character database - Script property

#ifndef OGONEK_UCD_SCRIPT_HPP
#define OGONEK_UCD_SCRIPT_HPP

#include <ogonek/detail/visibility.h++>
#include <ogonek/types.h++>

#include <cstddef>

namespace ogonek {
    namespace ucd {
        inline namespace abiv0 {
            enum class script {
                adlm,
                aghb,
                ahom,
                arab,
                armi,
                armn,
                avst,
                bali,
                bamu,
                bass,
                batk,
                beng,
                bhks,
                bopo,
                brah,
                brai,
                bugi,
                buhd,
                cakm,
                cans,
                cari,
                cham,
                cher,
                copt,
                cprt,
                cyrl,
                deva,
                dsrt,
                dupl,
                egyp,
                elba,
                ethi,
                geor,
                glag,
                goth,
                gran,
                grek,
                gujr,
                guru,
                hang,
                hani,
                hano,
                hatr,
                hebr,
                hira,
                hluw,
                hmng,
                hrkt,
                hung,
                ital,
                java,
                kali,
                kana,
                khar,
                khmr,
                khoj,
                knda,
                kthi,
                lana,
                laoo,
                latn,
                lepc,
                limb,
                lina,
                linb,
                lisu,
                lyci,
                lydi,
                mahj,
                mand,
                mani,
                marc,
                mend,
                merc,
                mero,
                mlym,
                modi,
                mong,
                mroo,
                mtei,
                mult,
                mymr,
                narb,
                nbat,
                newa,
                nkoo,
                ogam,
                olck,
                orkh,
                orya,
                osge,
                osma,
                palm,
                pauc,
                perm,
                phag,
                phli,
                phlp,
                phnx,
                plrd,
                prti,
                rjng,
                runr,
                samr,
                sarb,
                saur,
                sgnw,
                shaw,
                shrd,
                sidd,
                sind,
                sinh,
                sora,
                sund,
                sylo,
                syrc,
                tagb,
                takr,
                tale,
                talu,
                taml,
                tang,
                tavt,
                telu,
                tfng,
                tglg,
                thaa,
                thai,
                tibt,
                tirh,
                ugar,
                vaii,
                wara,
                xpeo,
                xsux,
                yiii,
                zinh,
                zyyy,
                zzzz,
                adlam = adlm,
                caucasian_albanian = aghb,
                arabic = arab,
                imperial_aramaic = armi,
                armenian = armn,
                avestan = avst,
                balinese = bali,
                bamum = bamu,
                bassa_vah = bass,
                batak = batk,
                bengali = beng,
                bhaiksuki = bhks,
                bopomofo = bopo,
                brahmi = brah,
                braille = brai,
                buginese = bugi,
                buhid = buhd,
                chakma = cakm,
                canadian_aboriginal = cans,
                carian = cari,
                cherokee = cher,
                coptic = copt,
                qaac = copt,
                cypriot = cprt,
                cyrillic = cyrl,
                devanagari = deva,
                deseret = dsrt,
                duployan = dupl,
                egyptian_hieroglyphs = egyp,
                elbasan = elba,
                ethiopic = ethi,
                georgian = geor,
                glagolitic = glag,
                gothic = goth,
                grantha = gran,
                greek = grek,
                gujarati = gujr,
                gurmukhi = guru,
                hangul = hang,
                han = hani,
                hanunoo = hano,
                hatran = hatr,
                hebrew = hebr,
                hiragana = hira,
                anatolian_hieroglyphs = hluw,
                pahawh_hmong = hmng,
                katakana_or_hiragana = hrkt,
                old_hungarian = hung,
                old_italic = ital,
                javanese = java,
                kayah_li = kali,
                katakana = kana,
                kharoshthi = khar,
                khmer = khmr,
                khojki = khoj,
                kannada = knda,
                kaithi = kthi,
                tai_tham = lana,
                lao = laoo,
                latin = latn,
                lepcha = lepc,
                limbu = limb,
                linear_a = lina,
                linear_b = linb,
                lycian = lyci,
                lydian = lydi,
                mahajani = mahj,
                mandaic = mand,
                manichaean = mani,
                marchen = marc,
                mende_kikakui = mend,
                meroitic_cursive = merc,
                meroitic_hieroglyphs = mero,
                malayalam = mlym,
                mongolian = mong,
                mro = mroo,
                meetei_mayek = mtei,
                multani = mult,
                myanmar = mymr,
                old_north_arabian = narb,
                nabataean = nbat,
                nko = nkoo,
                ogham = ogam,
                ol_chiki = olck,
                old_turkic = orkh,
                oriya = orya,
                osage = osge,
                osmanya = osma,
                palmyrene = palm,
                pau_cin_hau = pauc,
                old_permic = perm,
                phags_pa = phag,
                inscriptional_pahlavi = phli,
                psalter_pahlavi = phlp,
                phoenician = phnx,
                miao = plrd,
                inscriptional_parthian = prti,
                rejang = rjng,
                runic = runr,
                samaritan = samr,
                old_south_arabian = sarb,
                saurashtra = saur,
                sign_writing = sgnw,
                shavian = shaw,
                sharada = shrd,
                siddham = sidd,
                khudawadi = sind,
                sinhala = sinh,
                sora_sompeng = sora,
                sundanese = sund,
                syloti_nagri = sylo,
                syriac = syrc,
                tagbanwa = tagb,
                takri = takr,
                tai_le = tale,
                new_tai_lue = talu,
                tamil = taml,
                tangut = tang,
                tai_viet = tavt,
                telugu = telu,
                tifinagh = tfng,
                tagalog = tglg,
                thaana = thaa,
                tibetan = tibt,
                tirhuta = tirh,
                ugaritic = ugar,
                vai = vaii,
                warang_citi = wara,
                old_persian = xpeo,
                cuneiform = xsux,
                yi = yiii,
                inherited = zinh,
                qaai = zinh,
                common = zyyy,
                unknown = zzzz,
            };
            struct script_properties {
                code_point start;
                script value;
            };

            extern OGONEK_PUBLIC script_properties const* script_data;
            extern OGONEK_PUBLIC std::size_t script_data_size;
        } // namespace abiv0
    } // namespace ucd
} // namespace ogonek

#endif // OGONEK_UCD_SCRIPT_HPP
