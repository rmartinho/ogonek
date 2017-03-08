Encoding
========

.. concept:: template <typename E>\
             EncodingForm

    An |encoding-form| type. It describes an encoding form's mapping
    between |code-points| and |code-units|, as well as some extra
    properties which are used for checking constraints and for
    performing optimizations.

    .. todo:: Document requirements

.. concept:: template <typename E>\
             StatelessEncodingForm

    An |encoding-form| that requires no state for encoding/decoding
    operations.

    .. todo:: Document requirements

.. concept:: template <typename H, typename E>\
             EncodeErrorHandler

    ``H`` is an error handler that can handle errors when encoding with ``E``.

    .. todo:: Document requirements

.. concept:: template <typename H, typename E>\
             DecodeErrorHandler

    ``H`` is an error handler that can handle errors when encoding with ``E``.

    .. todo:: Document requirements

