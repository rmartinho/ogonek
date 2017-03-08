Error handling
==============

.. class:: unicode_error

    The base class for all Unicode-related errors.

.. class:: template <EncodingForm Encoding>\
           encode_error : virtual unicode_error

    :thrown: when an error occurs during an encoding operation.

.. class:: template <EncodingForm Encoding>\
           decode_error : virtual unicode_error

    :thrown: when an error occurs during a decoding operation.

.. var:: auto assume_valid

    A tag used to request that encoding/decoding functions assume the
    input has been validated before.

    .. warning::

        Using this tag with input that isn't actually valid yields
        undefined behavior.

.. var:: auto discard_errors

    An error handler for encoding/decoding functions that simply
    discards the portions of the input that have errors.

.. var:: auto replace_errors

    An error handler for encoding/decoding functions that replaces
    portions of the input that have errors with a replacement character.
    When decoding, this is |u-fffd|, but when encoding and the target
    doesn't support it, some encoding-specific character is used
    instead.

.. var:: auto replace_errors

    An error handler for encoding/decoding functions that throws when an
    error is found in the input.

