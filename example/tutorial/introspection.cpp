/*
@copyright Louis Dionne 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#include <boost/hana.hpp>
#include <boost/hana/ext/std/utility.hpp>

#include <string>
#include <type_traits>
#include <utility>
using namespace boost::hana;


struct yes { std::string toString() const { return "yes"; } };
struct no { };

namespace has_toString_then {
//! [has_toString.then]
template <typename T, typename = void>
struct has_toString
  : std::false_type
{ };

template <typename T>
struct has_toString<T, decltype((void)std::declval<T>().toString())>
  : std::true_type
{ };
//! [has_toString.then]

static_assert(has_toString<yes>::value, "");
static_assert(!has_toString<no>::value, "");
}

//! [has_toString.now]
auto has_toString = is_valid([](auto&& obj) -> decltype(obj.toString()) { });
//! [has_toString.now]

BOOST_HANA_CONSTANT_CHECK(has_toString(yes{}));
BOOST_HANA_CONSTANT_CHECK(not_(has_toString(no{})));

namespace optionalToString_then {
//! [optionalToString.then]
template <typename T>
auto optionalToString(T const& obj)
  -> std::enable_if_t<decltype(has_toString(obj))::value, std::string>
{ return obj.toString(); }

template <typename T>
auto optionalToString(T const& obj)
  -> std::enable_if_t<decltype(!has_toString(obj))::value, std::string>
{ return "toString not defined"; }
//! [optionalToString.then]

// make sure they compile
template std::string optionalToString(yes const&);
template std::string optionalToString(no const&);
}

//! [optionalToString]
template <typename T>
std::string optionalToString(T const& obj) {
  return if_(has_toString(obj),
    [](auto& x) { return x.toString(); },
    [](auto& x) { return "toString not defined"; }
  )(obj);
}
//! [optionalToString]


int main() {
BOOST_HANA_RUNTIME_CHECK(optionalToString(yes{}) == "yes");
BOOST_HANA_RUNTIME_CHECK(optionalToString(no{}) == "toString not defined");


{

//! [non_static_member_from_object]
auto has_member = is_valid([](auto&& x) -> decltype((void)x.member) { });

struct Foo { int member[4]; };
struct Bar { };
BOOST_HANA_CONSTANT_CHECK(has_member(Foo{}));
BOOST_HANA_CONSTANT_CHECK(!has_member(Bar{}));
//! [non_static_member_from_object]

}{

//! [non_static_member_from_type]
auto has_member = is_valid([](auto t) -> decltype(
  (void)traits::declval(t).member
) { });

struct Foo { int member[4]; };
struct Bar { };
BOOST_HANA_CONSTANT_CHECK(has_member(type<Foo>));
BOOST_HANA_CONSTANT_CHECK(!has_member(type<Bar>));
//! [non_static_member_from_type]

}{

//! [nested_type_name]
auto has_member = is_valid([](auto t) -> decltype(type<
  typename decltype(t)::type::member
//^^^^^^^^ needed because of the dependent context
>) { });

struct Foo { struct member; /* not defined! */ };
struct Bar { };
BOOST_HANA_CONSTANT_CHECK(has_member(type<Foo>));
BOOST_HANA_CONSTANT_CHECK(!has_member(type<Bar>));
//! [nested_type_name]

}

}

namespace static_member {
//! [static_member]
auto has_member = is_valid([](auto t) -> decltype(
  (void)decltype(t)::type::member
) { });

struct Foo { static int member[4]; };
struct Bar { };
BOOST_HANA_CONSTANT_CHECK(has_member(type<Foo>));
BOOST_HANA_CONSTANT_CHECK(!has_member(type<Bar>));
//! [static_member]
}

namespace nested_template {
//! [nested_template]
auto has_member = is_valid([](auto t) -> decltype(template_<
  decltype(t)::type::template member
  //                 ^^^^^^^^ needed because of the dependent context
>) { });

struct Foo { template <typename ...> struct member; };
struct Bar { };
BOOST_HANA_CONSTANT_CHECK(has_member(type<Foo>));
BOOST_HANA_CONSTANT_CHECK(!has_member(type<Bar>));
//! [nested_template]
}
