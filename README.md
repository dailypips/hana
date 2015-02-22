# Boost.Hana
> Your standard library for metaprogramming


## Disclaimers
This is not an official Boost library. However, a formal review will be asked
for shortly. The library is fairly stable, but no effort will be made to stay
backward compatible.


## Overview
<!-- Important: keep this in sync with example/overview.cpp -->
```cpp
#include <boost/hana.hpp>
#include <boost/hana/ext/std/integral_constant.hpp>

#include <cassert>
#include <iostream>
#include <string>
#include <type_traits>
using namespace boost::hana;
using namespace boost::hana::literals;


struct Person { std::string name; };
struct Car    { std::string name; };
struct City   { std::string name; };

int main() {
    // Sequences holding heterogeneous objects.
    auto stuff = make<Tuple>(Person{"Louis"}, Car{"Toyota"}, City{"Quebec"});

    // Expressive algorithms to manipulate them.
    auto names = transform(stuff, [](auto x) { return x.name; });
    assert(reverse(names) == make<Tuple>("Quebec", "Toyota", "Louis"));

    // No compile-time information is lost: even if `stuff` can't be constexpr
    // because it holds `std::string`s, its length is known at compile-time.
    static_assert(length(stuff) == 3u, "");

    // A way to represent types as values and metafunctions as normal functions,
    // so everything that can be done with the MPL can be done with Hana.
    constexpr auto types = make<Tuple>(type<Car>, type<City>, type<void>);
    constexpr auto pointers = transform(types, metafunction<std::add_pointer>);
    static_assert(pointers == tuple_t<Car*, City*, void*>, "");

    // And many other goodies to make your life better.
    static_assert(10_c == std::integral_constant<long long, 10>{}, "");

    static_assert(pointers[1_c] == type<City*>, "std::get, revisited");

    int_<10>.times([]{
        std::cout << "rubyists rejoice!" << std::endl;
    });
}
```


## Prerequisites and installation
Boost.Hana is a header only library. To use it in your own project, just add
the [include](include) directory to your compiler's header search path and
you are done.

The library relies on a full-featured C++14 compiler and standard library,
but nothing else is required. As of February 2015, the only compiler known to
compile the full test suite is Clang 3.7.0 (trunk) with libc++ (trunk too).
While Clang 3.6 is advertised as having full support for C++14, it has several
C++14-related bugs that are fixed in the trunk and make it incapable of
compiling the full test suite. However, efforts are being made to port the
library to GCC 4.9 and Clang 3.6.


## Documentation
You can browse the documentation online at http://ldionne.github.io/hana.
You can also get an offline version of the documentation by checking out
the `doc/gh-pages` submodule at its latest version:
```shell
git submodule update --init --remote
```


## Hacking on Hana
Setting yourself up to work on Boost.Hana is easy. First, you will need an
installation of [CMake][]. Once this is done, you can `cd` to the root of
the project and setup the build directory:
```shell
mkdir build
cd build
cmake ..
```

You can now build and run the unit tests and the examples. I assume that you
used the Makefile generator with CMake; the commands may differ for other
generators:
```shell
make tests
make examples
```

> #### Tip
> There is a Makefile at the root of the project which forwards everything
> to the `build` directory. Hence, you can also issue those commands from the
> root of the project instead of the `build` directory.

There are also optional targets which are enabled only when the required
software is available on your computer. For example, generating the
documentation requires [Doxygen][] to be installed. An informative message
will be printed during the CMake generation step whenever an optional target
is disabled. You can install any missing software and then re-run the CMake
generation to update the list of available targets.

> #### Tip
> You can use the `help` target to get a list of all the available targets.

If you want to add unit tests or examples, just add a source file in `test/`
or `example/` and then re-run the CMake generation step so the new source
file is known to the build system. If the relative path from the root of
the  project to the new source file is `path/to/file.cpp`, a target named
`path.to.file` to compile the file will be created when CMake is run.

> #### Tip for Sublime Text users
> If you use the provided [hana.sublime-project](hana.sublime-project) file,
> you can select the "Build current file" build system to build the target
> associated to the current file.


## Project organization
The project is organized in a couple of subdirectories.
- The [benchmark](benchmark) directory contains compile-time and runtime
  benchmarks to make sure the library is as fast as advertised. The benchmark
  code is written mostly in the form of [eRuby][] templates. The templates
  are used to generate C++ files which are then compiled while gathering
  compilation statistics. The benchmarks are driven by CMake files. Note that
  currently the benchmarks will only work with Clang because of the
  [gem used][Benchcc] to drive the compiler and gather the statistics.
- The [cmake](cmake) directory contains additional CMake modules used by the
  build system.
- The [doc](doc) directory contains configuration files needed to generate
  the documentation. Also, the [doc/gh-pages](doc/gh-pages) directory is
  a submodule tracking the `gh-pages` branch of the official repository at
  http://github.com/ldionne/hana, which contains the latest documentation.
- The [example](example) directory contains the source code for all the
  examples of both the tutorial and the reference documentation.
- The [include](include) directory contains the library itself, which is
  header only.
- The [test](test) directory contains the source code for all the unit tests.


## Contributing
Want to contribute? Great!

1. Fork it.
2. Create a branch (`git checkout -b feature_X`)
3. Do your modifications on that branch
4. Make sure you did not break anything (`make tests examples`)
5. Commit your changes (`git commit -am "Added feature X"`)
6. Push to the branch (`git push origin feature_X`)
7. Open a pull request


## Related material
I presented a [talk on Hana][Hana-CppCon] at [CppCon 2014][CppCon].
If you are interested in metaprogramming, you may also take a look at the
[MPL11][], which is how Hana started out, and [this talk][MPL11-C++Now] about
the MPL11 at [C++Now 2014][C++Now].


## License
Please see [LICENSE.md](LICENSE.md).


<!-- Links -->
[Benchcc]: http://github.com/ldionne/benchcc
[C++Now]: http://cppnow.org
[CMake]: http://www.cmake.org
[CppCon]: http://cppcon.org
[Doxygen]: http://www.doxygen.org
[eRuby]: http://en.wikipedia.org/wiki/ERuby
[Hana-CppCon]: http://ldionne.github.io/hana-cppcon-2014
[MPL11-C++Now]: http://ldionne.github.io/mpl11-cppnow-2014
[MPL11]: http://github.com/ldionne/mpl11
