#! /usr/bin/python
# -*- coding: utf-8 -*-#
#
# Ogonek
#
# Written in 2016 by Martinho Fernandes <ogonek@rmf.io>
#
# To the extent possible under law, the author(s) have dedicated all copyright and related
# and neighboring rights to this software to the public domain worldwide. This software is
# distributed without any warranty.
#
# You should have received a copy of the CC0 Public Domain Dedication along with this software.
# If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
#
# Unicode segmentations tests compiler

import sys
import os
import re
import string
import os
import io

if len(sys.argv) != 10:
    print('usage: ' + os.path.basename(sys.argv[0]) + ' <grapheme_in> <word_in> <sentence_in> <line_in> <header> <grapheme_impl> <word_impl> <sentence_impl> <line_impl>')
    sys.exit(17)

grapheme_input = sys.argv[1]
word_input = sys.argv[2]
sentence_input = sys.argv[3]
line_input = sys.argv[4]
header = sys.argv[5]
grapheme_out = sys.argv[6]
word_out = sys.argv[7]
sentence_out = sys.argv[8]
line_out = sys.argv[9]

def filtertests(lines):
    return list(l.split('#')[0] for l in lines if not l.startswith('#'))

def parsestring(line):
    def makeescapes(ss):
        for s in ss:
            t = s.strip()
            if t != '':
                yield '\\x' + t

    escapes = ''.join(''.join(makeescapes(re.split(u'×|÷', line))))
    return 'U"' + escapes + '"'

def parsebreaks(line):
    def fn(l):
        for i, c in enumerate(c for c in l if c == u'×' or c == u'÷'):
            if c == u'÷':
                yield i

    return list(fn(line))

copyrighttmpl = string.Template('''// Ogonek
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
''')

impltmpl = string.Template('''
// Test data for ${description} tests

#include "${header}"

using namespace test::string_literals;

namespace test {
    break_test ${kind}_test_data[] = {
        ${entries}
    };
} // namespace test
''')

headertmpl = string.Template('''
// Types for segmentation tests

#ifndef OGONEK_TEST_SEGMENTATION_HPP
#define OGONEK_TEST_SEGMENTATION_HPP

#include "util.h++"

#include <vector>

namespace test {
    struct break_test {
        u32string input;
        std::vector<int> breaks;
    };

    extern break_test grapheme_test_data[${graphemes}];
    extern break_test word_test_data[${words}];
    extern break_test sentence_test_data[${sentences}];
    extern break_test line_test_data[${lines}];
} // namespace test

#endif // OGONEK_TEST_SEGMENTATION_HPP
''')

def writedata(file, kind, description, tests):
    strings = list(map(parsestring, tests))
    breaks = list(map(parsebreaks, tests))
    breakstrings = list(', '.join(map(str, b)) for b in  breaks)

    file.write(copyrighttmpl.substitute())
    entries = '\n        '.join('{{ {0}, {{ {1} }} }},'.format(*t) for t in zip(strings, breakstrings))
    file.write(impltmpl.substitute(kind=kind, header=os.path.basename(header), description=description, entries=entries))

with io.open(grapheme_input, 'r', encoding='utf-8') as graphemefile:
    graphemes = list(filtertests(graphemefile.readlines()))
with io.open(word_input, 'r', encoding='utf-8') as wordfile:
    words = list(filtertests(wordfile.readlines()))
with io.open(sentence_input, 'r', encoding='utf-8') as sentencefile:
    sentences = list(filtertests(sentencefile.readlines()))
with io.open(line_input, 'r', encoding='utf-8') as linefile:
    lines = list(filtertests(linefile.readlines()))

with open(header, 'w') as headerfile:
    headerfile.write(copyrighttmpl.substitute())
    headerfile.write(headertmpl.substitute(graphemes=len(graphemes), words=len(words), sentences=len(sentences), lines=len(lines)))

with open(grapheme_out, 'w') as graphemefile:
    writedata(graphemefile, 'grapheme', 'grapheme clusters', graphemes)
with open(word_out, 'w') as wordfile:
    writedata(wordfile, 'word', 'words', words)
with open(sentence_out, 'w') as sentencefile:
    writedata(sentencefile, 'sentence', 'sentences', sentences)
with open(line_out, 'w') as linefile:
    writedata(linefile, 'line', 'lines', lines)

