Normalization forms
===================

.. function:: template <NormalizationForm Form, ForwardRange Rng>\
              auto normalize(Rng rng)

    Normalizes a range of |code-points| into ``Form``.

    :param rng: The range of |code-points| to normalize

    :returns: a range of the |code-points| that satisfies the normalization form ``Form``

