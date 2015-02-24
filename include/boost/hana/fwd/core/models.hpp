/*!
@file
Forward declares `boost::hana::models`.

@copyright Louis Dionne 2014
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_CORE_MODELS_HPP
#define BOOST_HANA_FWD_CORE_MODELS_HPP

namespace boost { namespace hana {
    //! @ingroup group-core
    //! %Metafunction returning whether a data type is a model of the
    //! given concept.
    //!
    //! Given a data type `T` and a concept `Concept`, `models<Concept(T)>`
    //! represents whether `T` is a model of `Concept`. Usually, concepts
    //! provide methods, some of which __must__ be implemented in order to
    //! model the concept, and the others are given a default definition
    //! in terms of the mandatory ones. More specifically, `models` returns
    //! whether a minimal complete definition of a concept is provided by
    //! the data type. However, concepts also usually provide semantic
    //! requirements (called laws) that must be satisfied by their models;
    //! `models` does not attempt to check whether those laws are satisfied.
    //! In fact, `models` does not even check whether the provided minimal
    //! complete definition is syntactically correct, but only if it is there.
    //!
    //! A few concepts (like Sequence) do not introduce methods that suffice
    //! to provide a minimal complete definition. They provide semantic
    //! guarantees through laws and superclasses, and they usually also
    //! provide methods that do useful things with existing methods and
    //! those additional guarantees. In this case, it is usually necessary
    //! to explicitly specialize `models` in the `boost::hana` namespace.
    //! When this is the case, the concept should document it. Also note
    //! that `models` supports flexible specializations with `when`, exactly
    //! like tag-dispatched methods.
    //!
    //!
    //! Example
    //! -------
    //! @snippet example/core/models.cpp models
    //!
    //!
    //! How does it work
    //! ----------------
    //! When a concept writer provides minimal complete definitions in terms
    //! of other methods introduced by the concept, they specialize the
    //! `models` metafunction so that whenever a proper minimal complete
    //! definition is provided by the user, `models` returns true. Here's
    //! an example of how a simple concept could support `models`:
    //!
    //! @include example/core/models.new.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <see_documentation>
    struct models;
#else
    template <typename Concept, typename = void>
    struct models;
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_CORE_MODELS_HPP