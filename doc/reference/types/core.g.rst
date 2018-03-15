Core types
==========

.. type:: code_point = char32_t

    Many algorithms in ogonek operate on sequences of code points. The
    sequences themselves can have any type, but their elements must be code
    points. ``code_point`` is the type used to represent code points. It is
    an alias for the standard C++ ``char32_t`` type.

    All ``code_point`` arguments in Ogonek are required to be valid, i.e.
    |valid-code-point|; otherwise the behaviour is undefined. The results of
    Ogonek functions never include ``code_point`` values outside this range.

.. type:: byte = std::uint8_t

    Encoding schemes and some encoding forms take input or produce output in
    the form of bytes or sequences of bytes. The type used to represent
    bytes in ogonek is called ``byte``, an alias for the standard C++
    ``uint8_t`` type.

