Encoding
========

.. type:: template <EncodingForm Encoding>\
          code_unit_t

    The type of the |code-units| used by ``Encoding``.

.. var:: template <EncodingForm Encoding>\
         constexpr auto max_width_v

    The maximum number of |code-units| needed by ``Encoding`` to
    represent one |code-point|.

.. var:: template <EncodingForm Encoding>\
         constexpr auto replacement_character_v

    The character used to replace invalid input when
    :var:`replace_errors` is used for an encoding operation.

    .. note:: Decoding always uses |u-fffd| to replace errors.

.. type:: template <EncodingForm Encoding>\
          coding_state_t

    The type of the state used by ``Encoding``. For stateless encoding forms
    this is an empty type.

.. type:: template <EncodingForm Encoding>\
          is_stateless

    Derives from ``std::true_type`` if ``Encoding`` is stateless; from
    ``std::false_type`` otherwise.

.. var:: template <EncodingForm Encoding>\
         constexpr bool is_stateless_v

    True if ``Encoding`` is stateless; false otherwise.

.. function:: template <EncodingForm Encoding>\
              coded_character_t<Encoding> encode_one(code_point u, coding_state_t<Encoding>& state)

    Encodes ``u`` according to ``Encoding``.

    :param u: the |code-point| to be encoded

    :param state: the current encoding state; it is modified according to the encoding performed

    :returns: a range of the |code-units| that encode ``u``

    :throws: :type:`encode_error` when the input cannot be encoded by ``Encoding``

.. type:: template <EncodingForm Encoding>\
          coded_character_t

    Range of the |code-units| that encode one |code-point|.

.. function:: template <EncodingForm Encoding, ForwardRange Rng, EncodeErrorHandler Handler>\
              auto encode(Rng rng, Handler&& handler)

    Encodes a range of |code-points|, according to ``Encoding``.

    :param rng: The range of |code-points| to encode

    :param handler: The strategy for error handling

    :returns: a range of the |code-units| that encode the |code-points| in ``rng``

    :validation: as performed by ``Encoding``; errors are handled by ``handler``

.. function:: template <EncodingForm Encoding, ForwardIterator It, Sentinel St>\
              std::pair<code_point, It> decode_one(It first, St last, coding_state_t<Encoding>& state)

    Decodes the first |code-point| from the range [``first``, ``last``), according to ``Encoding``.

    :param first: an iterator to the first |code-unit| to be decoded

    :param last: an iterator/sentinel to the end of the range of |code-units|

    :param state: the current decoding state; it is modified according to the decoding performed

    :returns: a pair of the decoded |code-point| and an iterator to first |code-unit| of the next encoded |code-point|

    :throws: :type:`decode_error` when the input cannot be decoded by ``Encoding``

.. function:: template <EncodingForm Encoding, ForwardRange Rng, EncodeErrorHandler Handler>\
              auto decode(Rng rng, Handler&& handler)

    Decodes a range of |code-points|, according to ``Encoding``.

    :param rng: The range of |code-points| to encode

    :param handler: The strategy for error handling

    :returns: a range of the |code-points| that the |code-units| in ``rng`` represent

    :validation: as performed by ``Encoding``; errors are handled by ``handler``

.. type:: template <EncodingForm Encoding>\
          coded_character

    A container type for the |code-units| that encode a single
    |code-point| according to ``Encoding``.

