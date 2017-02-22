Ranges
======

A large portion of ogonek works with sequences of values, notably of code
points, of code units and of bytes. Throughout the library, the |range-v3|
concepts are used to specify the requirements of input ranges and the
capabilities of returned ranges.

.. note::
    This is under consideration and may change in the future as the
    range-v3 interfaces change, or as the standardization process of ranges
    proceeds.

Note that most ranges returned from ogonek algorithms have deferred-evaluation.
This means that nothing happens until the values of the range are actually
required.
