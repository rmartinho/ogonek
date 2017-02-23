#! /usr/bin/python
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
# Unicode normalization tests compiler

import sys
import os
import string

if len(sys.argv) != 4:
    print('usage: ' + os.path.basename(sys.argv[0]) + ' <input> <header> <impl>')
    sys.exit(17)

test_input = sys.argv[1]
header = sys.argv[2]
impl = sys.argv[3]

def filtertests(lines):
    for l in lines:
        if not l.startswith('#') and not l.startswith('@'):
            x = l.split('#')[0]
            if not x.strip() == '':
                yield x

def parseform(item):
    return ('\\x' + u.strip() for u in item.strip().split())

def parsetests(lines):
    return (['U"' + ''.join([str(x) for x in parseform(u)]) + '"_s' for u in l.split(';')] for l in lines)

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

// Unicode normalization test data
''')

headertmpl = string.Template('''
#ifndef OGONEK_TEST_NORMALIZATION_HPP
#define OGONEK_TEST_NORMALIZATION_HPP

#include "util.h++"

namespace test {
    struct normalization_test {
        u32string input;
        u32string nfc;
        u32string nfd;
        u32string nfkc;
        u32string nfkd;
    };

    extern normalization_test normalization_test_data[${count}];
} // namespace test

#endif // OGONEK_TEST_NORMALIZATION_HPP
''')

impltmpl = string.Template('''
#include "${header}"

using namespace test::string_literals;

namespace test {
    normalization_test normalization_test_data[] = {
        ${data}
    };
} // namespace test
''')

with open(test_input, 'r') as sourcefile:
    tests = list(parsetests(filtertests(sourcefile.readlines())))

with open(header, 'w') as headerfile:
    headerfile.write(copyrighttmpl.substitute())
    headerfile.write(headertmpl.substitute(count=len(tests)))

with open(impl, 'w') as implfile:
    implfile.write(copyrighttmpl.substitute())
    entries = '\n        '.join('{{ {0}, {1}, {2}, {3}, {4} }},'.format(*t) for t in tests)
    implfile.write(impltmpl.substitute(data=entries, header=os.path.basename(header)))
