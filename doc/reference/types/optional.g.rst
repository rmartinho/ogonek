Optional type
=============

.. class:: none_t

    The unit type of the :var:`none` constant.

.. var:: constexpr none_t none

    A constant used to create empty optional objects.


.. class:: template <typename T>\
           optional

    An optional object that may or may not contain a value.

    .. function:: constexpr optional() noexcept

        Creates a new empty optional object.

    .. function:: constexpr optional(none_t) noexcept

        Creates a new empty optional object.

    .. function:: constexpr optional(T t) noexcept

        Creates a new optional object.

        :param t: the value of the new optional object

    .. function:: constexpr T operator*() const noexcept

        :requires: this optional isn't empty.

        :returns: the value of this optional.

    .. function:: constexpr explicit operator bool() const noexcept

        :returns: ``true`` if this optional has a value; ``false`` if it's empty.

    .. note:: |std17|

        .. function:: constexpr optional(std::optional<T> o) noexcept

            Creates a new optional from a ``std::optional``.

            :param o: the source

            :returns: an optional with the same value as ``o``

        .. function:: constexpr operator std::optional<T>() const noexcept

            Converts an optional to ``std::optional``.

            :returns: a ``std::optional`` with the same value as this optional

    .. note:: |boost|

        .. function:: constexpr optional(boost::optional<T> o) noexcept

            Creates a new optional from a ``boost::optional``.

            :param o: the source

            :returns: an optional with the same value as ``o``

        .. function:: constexpr operator boost::optional<T>() const noexcept

            Converts an optional to ``boost::optional``.

            :returns: a ``boost::optional`` with the same value as this optional

.. function:: template <typename T, typename U>\
              constexpr bool operator==(optional<T> const& lhs, optional<U> const& rhs) noexcept
.. function:: template <typename T>\
              constexpr bool operator==(optional<T> const& lhs, T const& rhs) noexcept
.. function:: template <typename T>\
              constexpr bool operator==(T const& lhs, optional<T> const& rhs) noexcept
.. function:: template <typename T>\
              constexpr bool operator==(optional<T> const& lhs, none_t) noexcept
.. function:: template <typename T>\
              constexpr bool operator==(none_t, optional<T> const& rhs) noexcept

    Compares optional for equality.

    :returns: ``true`` if both sides have the same value, or if neither
              side has a value; ``false`` otherwise.

.. function:: template <typename T, typename U>\
              constexpr bool operator!=(optional<T> const& lhs, optional<U> const& rhs) noexcept
.. function:: template <typename T>\
              constexpr bool operator!=(optional<T> const& lhs, T const& rhs) noexcept
.. function:: template <typename T>\
              constexpr bool operator!=(T const& lhs, optional<T> const& rhs) noexcept
.. function:: template <typename T>\
              constexpr bool operator!=(optional<T> const& lhs, none_t) noexcept
.. function:: template <typename T>\
              constexpr bool operator!=(none_t, optional<T> const& rhs) noexcept

    Compares optional for inequality.

    :returns: ``!(lhs == rhs)``

