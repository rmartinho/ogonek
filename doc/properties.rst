Character properties
============================

Ogonek exposes the character properties described in the |unicode-standard| and
in the |uax-44|.

The types of these properties are mapped to C++ types as follows.

=============  ========
Unicode type   C++ type
=============  ========
Catalog        specific scoped enum type
-------------  --------
Enumeration    specific scoped enum type
-------------  --------
Binary         ``bool``
-------------  --------
String         ``std::u32string``
-------------  --------
Numeric        ``boost::rational<long>``
-------------  --------
Miscellaneous  varies
=============  ========

In general, property names and values match the Unicode standard names, except
for being written in lowercase and with underscores instead of spaces (i.e. in
the style of the C++ standard library).

.. todo::

    Add examples
