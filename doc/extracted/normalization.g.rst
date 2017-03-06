Normalization
=============

.. function:: template <NormalizationForm Form, OutputIterator Out>\
              auto decompose_into(code_point u, Out out)

    Writes the full decomposition of a |code-point| into an output iterator,
    according to ``Form``.

    :param u: The |code-points| to decompose

    :param out: The iterator to write to

.. function:: template <NormalizationForm Form, ForwardRange Rng>\
              auto compose(Rng rng)

    Applies the Canonical Composition Algorithm to range.

    :param rng: A range of |code-points|

    :returns: A canonically-composed subrange of ``rng``

.. function:: template <NormalizationForm Form, ForwardRange Rng>\
              auto normalize(Rng rng)

    Normalizes a range of |code-points| into ``Form``.

    :param rng: The range of |code-points| to normalize

    :returns: a range of the |code-points| that satisfies the normalization form ``Form``

