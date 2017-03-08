Segmentation
=============

.. var:: template <BoundaryCondition Break>\
         constexpr auto max_lookbehind_v

    The maximum number of |code-points| preceding a position that need
    to be checked to determine whether a boundary exists according to
    ``Break``.

.. var:: template <BoundaryCondition Break>\
         constexpr auto max_lookahead_v

    The maximum number of |code-points| succeeding a position that need
    to be checked to determine whether a boundary exists according to
    ``Break``.

.. function:: template <BoundaryCondition Break>\
              bool is_boundary_ignorable(code_point previous, code_point current)

    .. warning:: |unstable-api|

    Tests whether a |code-point| is ignorable when determining boundaries.

    :param previous: the |code-point| that occurs before the one being tested

    :param current: the |code-point| being tested

    :returns: true if ``current`` can be ignored to determine boundaries
              when following ``previous``; false otherwise.

.. function:: template <BoundaryCondition Break, RandomAccessRange Rng>\
              bool is_boundary(Rng rng)

    .. warning:: |unstable-api|

    Tests whether a boundary exists at a given position in a range of
    |code-points|.

    :param rng: the range of |code-points| to check for a boundary. This
                range contains some |code-points| before the position to
                be checked and some after it, as determined by
                var:`max_lookbehind_v` and var:`max_lookahead_v`.

    :returns: true if a boundary exists at the position checked,
              according to ``Break``; false otherwise.

.. function:: template <typename Break, typename Rng>\
              auto boundaries(Rng rng)

    ..todo:: docs

