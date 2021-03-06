/*!
@file
Forward declares `boost::hana::Range`.

@copyright Louis Dionne 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_RANGE_HPP
#define BOOST_HANA_FWD_RANGE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/fwd/core/make.hpp>
#include <boost/hana/fwd/core/operators.hpp>
#include <boost/hana/fwd/integral_constant.hpp>


namespace boost { namespace hana {
    //! @ingroup group-datatypes
    //! Tag representing a compile-time half-open interval of
    //! `IntegralConstant`s.
    //!
    //! A `Range` represents a half-open interval of the form `[from, to)`
    //! containing `IntegralConstant`s of a given type. The `[from, to)`
    //! notation represents the values starting at `from` (inclusively) up
    //! to but excluding `from`. In other words, it is a bit like the list
    //! `from, from+1, ..., to-1`.
    //!
    //! In particular, note that the bounds of the range can be any
    //! `IntegralConstant`s (negative numbers are allowed) and the range does
    //! not have to start at zero. The only requirement is that `from <= to`.
    //!
    //! Also note that because `Range`s do not specify much about their actual
    //! representation, some interesting optimizations can be applied to
    //! improve their compile-time performance over other similar utilities
    //! like `std::integer_sequence`.
    //!
    //!
    //! Modeled concepts
    //! ----------------
    //! 1. `Comparable` (operators provided)\n
    //! Two ranges are equal if and only if they are both empty or they both
    //! span the same interval.
    //! @snippet example/range.cpp comparable
    //!
    //! 2. `Foldable`\n
    //! Folding a `Range` is equivalent to folding a list of the
    //! `IntegralConstant`s in the interval it spans.
    //! @snippet example/range.cpp foldable
    //!
    //! 3. `Iterable` (operators provided)\n
    //! Iterating over a `Range` is equivalent to iterating over a list of
    //! the values it spans. In other words, iterating over the range
    //! `[from, to)` is equivalent to iterating over a list containing
    //! `from, from+1, from+2, ..., to-1`.
    //! @snippet example/range.cpp iterable
    //!
    //! 4. `Searchable`\n
    //! Searching a `Range` is equivalent to searching a list of the values
    //! in the range `[from, to)`, but it is much more compile-time efficient.
    //! @snippet example/range.cpp searchable
    struct Range { };

    template <typename T, T from, T to>
    struct _range;

#ifdef BOOST_HANA_DOXYGEN_INVOKED
    //! Creates a `Range` representing a half-open interval of
    //! `IntegralConstant`s.
    //! @relates Range
    //!
    //! Given two `Constant`s `from` and `to`, `make<Range>` returns a `Range`
    //! representing the half-open interval of `IntegralConstant`s `[from, to)`.
    //! `from` and `to` must be `Constant`s of an integral type such that
    //! `from <= to`. Otherwise, a compilation error is triggered. Also note
    //! that if `from` and `to` are `Constant`s with different underlying
    //! integral types, the created range contains `IntegralConstant`s whose
    //! underlying type is their common type.
    //!
    //!
    //! Example
    //! -------
    //! @snippet example/range.cpp make<Range>
    template <>
    constexpr auto make<Range> = [](auto from, auto to) {
        return a Range [from, to) of an unspecified type;
    };
#endif

    //! Alias to `make<Range>`; provided for convenience.
    //! @relates Range
    constexpr auto make_range = make<Range>;

    //! @todo
    //! Right now, this is provided for backwards compatibility.
    //! However, should we really remove it? If so, we need a seriously
    //! well-thought naming pattern for all the other objects in Hana,
    //! because `range(from, to)` is awesome; much better than
    //! `make_range(from, to)`.
    constexpr auto range = make<Range>;

    //! Shorthand to create a `Range` of `IntegralConstant`s.
    //! @relates Range
    //!
    //! This shorthand is provided for convenience only and it is equivalent
    //! to `make<Range>`. Specifically, `range_c<T, from, to>` is such that
    //! @code
    //!     range_c<T, from, to> == make<Range>(integral_constant<T, from>,
    //!                                         integral_constant<T, to>)
    //! @endcode
    //!
    //!
    //! @tparam T
    //! The underlying integral type of the `IntegralConstant`s in the
    //! created range.
    //!
    //! @tparam from
    //! The inclusive lower bound of the created range.
    //!
    //! @tparam to
    //! The exclusive upper bound of the created range.
    //!
    //!
    //! Example
    //! -------
    //! @snippet example/range.cpp range_c
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <typename T, T from, T to>
    constexpr auto range_c = make<Range>(integral_constant<T, from>,
                                         integral_constant<T, to>);
#else
    template <typename T, T from, T to>
    constexpr decltype(
        make<Range>(integral_constant<T, from>, integral_constant<T, to>)
    ) range_c{};
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_RANGE_HPP
