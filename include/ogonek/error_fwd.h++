// Ogonek
//
// Written in 2017 by Martinho Fernandes <ogonek@rmf.io>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

#ifndef OGONEK_ERROR_FWD_HPP
#define OGONEK_ERROR_FWD_HPP

namespace ogonek {
    struct unicode_error;
    template <typename Encoding>
    struct encode_error;
    template <typename Encoding>
    struct decode_error;

    struct assume_valid_t;
    struct discard_errors_t;
    struct replace_errors_t;
    struct throw_error_t;
} // namespace ogonek

#endif // OGONEK_ERROR_HPP

