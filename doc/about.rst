About
=====

Ogonek is a C++ library for Unicode support. The goal is to support all the
algorithms described in the |unicode-standard|, with a focus on correctness and on the
use of modern C++.

Design goals
------------

Ogonek’s design is driven by the following principles.

validity and correctness
    Ogonek values validity and correctness above speed and other concerns.
    The semantics of operations are defined as much as possible by the Unicode
    Standard and its standard annexes (UAX), technical standards (UTS), and
    technical reports (UTR).

    Ideally it should be impossible to obtain invalid Unicode data after any
    operation provided by Ogonek.

modern C++
    Ogonek uses modern C++ techniques as much as possible. At any given point,
    the minimum required level of standard C++ support is the C++ standard
    version before the latest, starting with C++14.

explicit is better than implicit
    Ogonek performs as little as possible implicitly. If the users don't want
    to care about certain details, they don't care about correctness, and thus
    they probably don't need ogonek.

    Specifically, Ogonek does not silently perform encoding conversions, and
    does not assume any encoding except for ``char16_t`` and ``char32_t``
    (which are clearly intended by the standard as UTF-16 and UTF-32 code
    units); anything else needs to be made explicit.

fail fast
    Ogonek does not let errors go away silently. When appropriate, the API
    accepts error handling callbacks; in all other scenarios exceptions are
    thrown.

be a good citizen
    Ogonek works well with the standard library, by providing and using models
    of the existing standard concepts, like iterators and containers.

Dependencies
------------

Ogonek depends on the following third-party libraries.

|range-v3|
    Eric Niebler's range-v3 library provides machinery for implementing and
    using ranges.

`Boost <https://boost.org/>`_
    Boost.Optional, Boost.Rational and Boost.Tribool are used for certain
    interface types.

`Catch <https://github.com/philsquared/Catch/>`_
    Phil Nash's Catch library provides unit test support.


Versioning
----------

Ogonek version numbers use the `semantic versioning 2.0.0
<http://semver.org/spec/v2.0.0.html>`_ rules.

Each Ogonek release is tied to a specific Unicode version. This is unavoidable
because Unicode updates may require changes not only in the Unicode character
data, but also in the algorithms. Because of this, arbitrarily mixing Ogonek
versions and Unicode versions is not supported.

At any given time, Ogonek supports the two latest released Unicode major
versions, starting with Unicode 9.0.0.

Licensing
---------

The source code of Ogonek is dedicated to the public domain. Where not
applicable, source code is licensed under the terms of the `CC0 1.0 Universal
<https://creativecommons.org/publicdomain/zero/1.0/>`_ public domain
dedication.

.. note::

    The person who associated a work with this deed has dedicated the work to the
    public domain by waiving all of his or her rights to the work worldwide under
    copyright law, including all related and neighboring rights, to the extent
    allowed by law.

    You can copy, modify, distribute and perform the work, even for commercial
    purposes, all without asking permission.

    In no way are the patent or trademark rights of any person affected by CC0,
    nor are the rights that other persons may have in the work or in how the
    work is used, such as publicity or privacy rights.

    Unless expressly stated otherwise, the person who associated a work with
    this deed makes no warranties about the work, and disclaims liability for
    all uses of the work, to the fullest extent permitted by applicable law.

    When using or citing the work, you should not imply endorsement by the
    author or the affirmer.

Trivia
------

Ogonek means "little tail" in Polish. It is the name of a diacritic used in
several European and Native American languages. It exists in the Unicode
repertoire as a combining character (U+0328 ᴄᴏᴍʙɪɴɪɴɢ ᴏɢᴏɴᴇᴋ), as an isolated
character (U+02DB ᴏɢᴏɴᴇᴋ), or precomposed with Latin alphabet letters (like
U+01EA ʟᴀᴛɪɴ ᴄᴀᴘɪᴛᴀʟ ʟᴇᴛᴛᴇʀ ᴏ ᴡɪᴛʜ ᴏɢᴏɴᴇᴋ).

In Russian (огонёк) it can mean "little flame", which arguably makes it sound
cooler than "little tail".

The name was picked randomly and it has absolutely no special meaning as the
name of this project. It is just a label the author appropriated for it. In
English it is pronounced /ˈoʊɡənɛk/.
