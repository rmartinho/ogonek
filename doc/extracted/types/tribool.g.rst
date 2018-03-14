3-state boolean type
====================

.. class:: maybe_t

    The unit type of the :var:`maybe` constant.

    .. function:: constexpr bool operator()(tribool t) const noexcept

        :param t: a :class:`tribool` to check for a maybe state

        :returns: ``true`` if ``t`` is maybe; ``false`` otherwise


.. var:: constexpr maybe_t maybe

    A constant used to represent the third boolean state.

.. class:: tribool

    A 3-state boolean type. The third state represents a superposition
    of the ``true`` and ``false`` states.

    .. function:: constexpr tribool() noexcept

        Creates a new tribool, with the ``false`` value.

    .. function:: constexpr tribool(bool v) noexcept

        Creates a new tribool, with the given value.

        :param v: the value of the new tribool

    .. function:: constexpr tribool(maybe_t) noexcept

        Creates a new tribool, with the maybe state.

    .. function:: constexpr explicit operator bool() const noexcept

        :returns: ``true`` if the state is true; ``false`` otherwise.

    .. note:: |boost|

        .. function:: constexpr tribool(boost::tribool t) noexcept

            Creates a new tribool with the value of a ``boost::tribool``.

        .. function:: constexpr operator boost::tribool() const noexcept

            :returns: a ``boost::tribool`` equivalent to this tribool.

.. function:: constexpr tribool operator!(tribool t) noexcept

    Negates a tribool.

    :returns: :var:`maybe` if `t` is :var:`maybe`; otherwise ``!bool(t)``

.. function:: constexpr tribool operator&&(tribool lhs, tribool rhs) noexcept
.. function:: constexpr tribool operator&&(tribool lhs, bool rhs) noexcept
.. function:: constexpr tribool operator&&(bool lhs, tribool rhs) noexcept
.. function:: constexpr tribool operator&&(maybe_t lhs, tribool rhs) noexcept
.. function:: constexpr tribool operator&&(tribool lhs, maybe_t rhs) noexcept

    Logical conjunction of tribools.

    :returns: :var:`maybe` if either side is :var:`maybe`; otherwise
              ``bool(lhs) && bool(rhs)``

.. function:: constexpr tribool operator||(tribool lhs, tribool rhs) noexcept
.. function:: constexpr tribool operator||(tribool lhs, bool rhs) noexcept
.. function:: constexpr tribool operator||(bool lhs, tribool rhs) noexcept
.. function:: constexpr tribool operator||(maybe_t lhs, tribool rhs) noexcept
.. function:: constexpr tribool operator||(tribool lhs, maybe_t rhs) noexcept

    Logical disjunction of tribools.

    :returns: ``true`` if either side is ``true``; otherwise :var:`maybe`
              if either side is :var:`maybe`; otherwise ``false``

.. function:: constexpr tribool operator==(tribool lhs, tribool rhs) noexcept
.. function:: constexpr tribool operator==(tribool lhs, bool rhs) noexcept
.. function:: constexpr tribool operator==(bool lhs, tribool rhs) noexcept
.. function:: constexpr tribool operator==(maybe_t lhs, tribool rhs) noexcept
.. function:: constexpr tribool operator==(tribool lhs, maybe_t rhs) noexcept

    Compares tribools for equality.

    :returns: :var:`maybe` if either side is :var:`maybe`; otherwise
              ``bool(lhs) == bool(rhs)``

.. function:: constexpr tribool operator!=(tribool lhs, tribool rhs) noexcept
.. function:: constexpr tribool operator!=(tribool lhs, bool rhs) noexcept
.. function:: constexpr tribool operator!=(bool lhs, tribool rhs) noexcept
.. function:: constexpr tribool operator!=(maybe_t lhs, tribool rhs) noexcept
.. function:: constexpr tribool operator!=(tribool lhs, maybe_t rhs) noexcept

    Compares tribools for inequality.

    :returns: :var:`maybe` if either side is :var:`maybe`; otherwise
              ``bool(lhs) != bool(rhs)``

