/*
 * (C) Copyright 1996-2017 ECMWF.
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 * In applying this licence, ECMWF does not waive the privileges and immunities
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

#include <cmath>

#include "eckit/types/Fraction.h"

#include "eckit/testing/Test.h"

using namespace std;
using namespace eckit;
using namespace eckit::testing;

namespace eckit {
namespace test {

//----------------------------------------------------------------------------------------------------------------------

CASE ( "test_fraction" ) {
    // 0

    EXPECT( Fraction(0, 1) == Fraction() );

    EXPECT_THROWS_AS( Fraction(0, 0), std::exception ); // this prints a backtrace wi Assertion failed

    // negative number

    EXPECT( Fraction(-1, 2) == Fraction(3, -6) );

    // decimals

    EXPECT( Fraction(0.16) == Fraction(16, 100) );
    EXPECT( Fraction(0.1616) == Fraction(1616, 10000) );

    // 5 / 7

    EXPECT( Fraction(0.714285) != Fraction(5, 7) );

    EXPECT( Fraction(0.7142857142) != Fraction(5, 7) );

    EXPECT( Fraction(0.71428571428) == Fraction(5, 7) );
    EXPECT( Fraction(0.714285714285) == Fraction(5, 7) );
    EXPECT( Fraction(0.714285714286) == Fraction(5, 7) );

    EXPECT( Fraction(0.714285714285714285) == Fraction(5, 7) );

    // 1 / 6

    EXPECT( Fraction(0.166) != Fraction(1, 6) );
    EXPECT( Fraction(0.1666) != Fraction(1, 6) );
    EXPECT( Fraction(0.16666) != Fraction(1, 6) );
    EXPECT( Fraction(0.166666) != Fraction(1, 6) );
    EXPECT( Fraction(0.1666666) != Fraction(1, 6) );
    EXPECT( Fraction(0.16666666) != Fraction(1, 6) );
    EXPECT( Fraction(0.166666666) != Fraction(1, 6) );

    EXPECT( Fraction(0.16666666666) == Fraction(1, 6) );
    EXPECT( Fraction(0.166666666666) == Fraction(1, 6) );
    EXPECT( Fraction(0.1666666666666) == Fraction(1, 6) );
    EXPECT( Fraction(0.16666666666666) == Fraction(1, 6) );
    EXPECT( Fraction(0.166666666666666) == Fraction(1, 6) );
    EXPECT( Fraction(0.1666666666666666) == Fraction(1, 6) );

    // 1 / 3

    EXPECT( Fraction(0.3333333333) == Fraction(1, 3) );

    EXPECT( Fraction(0.3333333333333333) == Fraction(1, 3) );

    // 1 / 1

    EXPECT( Fraction(0.9999999999999999) == Fraction(1, 1) );
    EXPECT( Fraction(0.9999999999999999) == Fraction(10, 10) );

    // 7 / 10..

    EXPECT( Fraction(0.7) == Fraction(7, 10) );
    EXPECT( Fraction(0.07) == Fraction(7, 100) );
    EXPECT( Fraction(0.0000007) == Fraction(7, 10000000) );

    // operations

    EXPECT( Fraction(1, 3) + Fraction(2, 3) == Fraction(10, 10) );
    EXPECT( Fraction(1, 3) - Fraction(2, 6) == Fraction(0, 10) );

    EXPECT( Fraction(1, 3) * 3 == Fraction(1) );

    EXPECT( -Fraction(1, 3) == Fraction(1, -3) );

    EXPECT( 2 * Fraction(1, 3)  == Fraction(2, 3) );

    Fraction a(1, 3);
    Fraction b(3, 28);
    EXPECT(a + b == Fraction(37, 84));
    EXPECT(a - b == Fraction(19, 84));
    EXPECT(a * b == Fraction(1, 28));
    EXPECT(a / b == Fraction(28, 9));

    EXPECT(a > b);
    EXPECT(a != b);
    EXPECT_NOT(a < b);
    EXPECT_NOT(a == b);

    EXPECT(Fraction("1/3") == Fraction(1, 3));
    EXPECT(double(Fraction("1/3")) == 1.0 / 3.0);

    EXPECT(Fraction("1") == Fraction(1));
    EXPECT(Fraction("1.2") == Fraction(12, 10));
    EXPECT(Fraction("1e-6") == Fraction(1, 1000000));
    EXPECT(Fraction("1e+6") == Fraction(1000000, 1));
    EXPECT(Fraction("1.2e+6") == Fraction(1200000, 1));

    EXPECT(Fraction(M_PI) > Fraction(M_E) );
    EXPECT(Fraction(M_E) > Fraction(M_SQRT2) );

    std::cout << "pi = " << (M_PI - double(Fraction(M_PI))) << std::endl;
    std::cout << "e = " << (M_E - double(Fraction(M_E))) << std::endl;
    std::cout << "sqrt2 = " << (M_SQRT2 - double(Fraction(M_SQRT2))) << std::endl;

    // EXPECT(Fraction(M_PI), Fraction(1200000, 1));
    {
        Fraction west(-12), east(1.2), increment(1.2);

        Fraction f(west);
        while (f < east) {
            f += increment;
        }
        EXPECT(f == east);
    }

    {
        Fraction west("-77"), east("7"), increment("0.7");

        Fraction f(west);
        while (f < east) {
            f += increment;
        }
        EXPECT(f == east);
    }


    EXPECT(Fraction(241.85) / Fraction(0.175) == 1382);
    EXPECT(Fraction(284.025) / Fraction(0.175) == 1623);


    // EXPECT(Fraction(5, 3).intergralPart() == 1);
    // EXPECT(Fraction(5, 3).decimalPart() == Fraction(1, 3));


}

//-----------------------------------------------------------------------------

} // namespace test
} // namespace eckit

int main(int argc,char **argv)
{
    return run_tests ( argc, argv );
}

