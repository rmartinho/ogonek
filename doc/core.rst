Core concepts
=============

Some types and concepts are used pervasively throughout the ogonek library. In
the description of the various parts it is assumed that the reader is familiar
with these.

Fundamental types
-----------------

.. type:: code_point = char32_t

    Many algorithms in ogonek operate on sequences of code points. The
    sequences themselves can have any type, but their elements must be code
    points. ``code_point`` is the type used to represent code points. It is an
    alias for the standard C++ ``char32_t`` type.

.. type:: byte = std::uint8_t

    Encoding schemes and some encoding forms take input or produce output in
    the form of bytes or sequences of bytes. The type used to represent bytes
    in ogonek is called ``byte``, an alias for the standard C++ ``uint8_t`` type.

Ranges
------

A large portion of ogonek works with sequences of values, notably of code
points, of code units and of bytes. Throughout the library, the |range-v3|
concepts are used to specify the requirements of input ranges and the
capabilities of returned ranges.

.. note::
    This is under consideration and may change in the future as the
    range-v3 interfaces change, or as the standardization process of ranges
    proceeds.

Note that most ranges returned from ogonek algorithms have deferred-evaluation.
This means that nothing happens until the values of the range are actually
required.
