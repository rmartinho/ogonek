Fraction type
=============

.. class:: fraction

    A fraction type to support the ``Numeric_Value`` Unicode property.
    This is merely a numerator/denominator pair and does not perform any
    reduction nor provides any arithmetic functionality.

    .. function:: constexpr fraction() noexcept

        Creates a new fraction representing 0/1.

    .. function:: constexpr fraction(long numerator, long denominator) noexcept

        Creates a new fraction representing ``numerator``/``denominator``.

        :param numerator: the fraction's numerator

        :param denominator: the fraction's denominator

        :requires: ``denominator`` is not zero

    .. function:: constexpr long numerator() const noexcept

        :returns: the numerator of this fraction

    .. function:: constexpr long denominator() const noexcept

        :returns: the denominator of this fraction

    .. function:: constexpr double as_double() const noexcept

        :returns: the result of dividing the numerator by the
                  denominator of this fraction, as a ``double``.

    .. note:: |boost|

        .. function:: constexpr fraction(boost::rational<long> r) noexcept

            Creates a new fraction from a ``boost::rational<long>``.

        .. function:: constexpr operator boost::rational<long>() const noexcept

            :returns: a ``boost::rational<long>`` equivalent to this fraction.

.. function:: constexpr bool operator==(fraction lhs, fraction rhs) noexcept

    Compares two fractions for equality.

    :returns: ``true`` if both fractions have the same numerator and the
              same denominator; ``false`` otherwise.

.. function:: constexpr bool operator!=(fraction lhs, fraction rhs) noexcept

    Compares two fractions for inequality.

    :returns: ``true`` if both fractions have the different numerators
              or different denominators; ``false`` otherwise.

