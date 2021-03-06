//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2011.
// Distributed under the Boost
// Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or
// copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/enums for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#include "./EnumClass.hpp"

void f(int ) {
}

void fail() {

  { // The wrapper is not implicit convertible to underlying int
    Ex::EnumClass e ;
    f(e); // error
    int i = e; // error
    (void)i;
  }

}
