/******************************************************
 * Author: Gal Maymon
 * Email: galmaymon@gmail.com
 * File: logVector.cpp
 * Description:
 * This file contains unit tests for the `Vector` class
 * using the doctest framework.
 *
 * These tests verify:
 * - Correct behavior of constructors and destructors
 * - Safe access using operator[]
 * - Vector initialization and validation functions
 * - Arithmetic operations (addition, subtraction, scalar multiplication/division, modulo)
 * - Element-wise operations and dot product
 * - Exception handling for invalid operations
 * - Pre/Post increment and decrement
 * - Output formatting using operator<<
 * - Transpose functionality with `transposeColumnsToRows`
 *
 * Exceptions handled:
 * - `MyLogicError` for invalid logic like size mismatch or uninitialized elements
 * - `InvalidArgument` for invalid constructor arguments
 * - `MyOutOfRange` for invalid index access
 *
 * Usage:
 * Compile this file with the rest of the project and run the binary.
 * It uses `doctest.h` with `DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN`.
 *
 * Make sure to link against `-lgcov` and compile with flags:
 * - `-fprofile-arcs -ftest-coverage` for coverage testing
 *
 ******************************************************/





#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <iostream>
#include "../Vector/Vector.hpp"
#include "Logger.hpp"
#include "../Exception/MyExceptions.hpp"
#include "doctest.h" 
#include <sstream> 


using namespace VectorGM;



TEST_CASE("Vector core functionality and exceptions") {
    Vector v;
    Vector v1(2), v2(2), v4(2), v5(3);
    double x = 2.5;
    double y = 0;
    int a = 2;
    int b = 0;
    const Vector v6 = v5;
    

    v1[0] = 1.0;
    CHECK(v1.isInitialized(0));
    CHECK(!v1.isInitialized(1));
    v1[1] = 2.0;
    CHECK(v1.sum() == 3);
    CHECK_THROWS_AS(v5.sum(), MyLogicError);
    CHECK(v1.allInitialized());
    CHECK_NOTHROW(v4.allInitialized());
    CHECK_THROWS_AS(Vector(-1), InvalidArgument);
    CHECK(v6.getSize()==3);
    CHECK_THROWS_AS(  v6[5]; , MyOutOfRange);
    CHECK_THROWS_AS( v6.isInitialized(5) , MyOutOfRange);
    v2 = v1;
    CHECK(v2[0] == 1.0);
    CHECK(v2[1] == 2.0);
    Vector v3 = v1;
    CHECK(v3[0] == 1.0);
    CHECK(v3[1] == 2.0);
    CHECK_NOTHROW(v1[0]);
    CHECK_THROWS_AS(v1[5] = 1.0, MyOutOfRange);
    CHECK_THROWS_AS( v1[-1], MyOutOfRange);
    CHECK_NOTHROW( v1[0]);
    CHECK_THROWS_AS(v1[5] = 1.0, MyOutOfRange);
    CHECK_THROWS_AS(v1[-1], MyOutOfRange);

    CHECK_THROWS_AS(Vector result = v1 + v5, MyLogicError);
    CHECK_THROWS_AS(Vector result = v1 + v4, MyLogicError);
    CHECK_THROWS_AS(v1 += v5, MyLogicError);
    CHECK_THROWS_AS(Vector result = v1 - v5, MyLogicError);
    CHECK_THROWS_AS(Vector result = v1 - v4, MyLogicError);
    CHECK_THROWS_AS(v1 -= v5, MyLogicError);
    CHECK_THROWS_AS(v1 * v5, MyLogicError);
    CHECK_THROWS_AS(Vector result = v1 * v4, MyLogicError);

    CHECK_THROWS_AS(Vector result = v1 % v5, MyLogicError);
    CHECK_THROWS_AS(Vector result = v1 % v4, MyLogicError);
    CHECK_THROWS_AS(Vector result = v1 % b, MyLogicError);
    CHECK_THROWS_AS(v1 %= b, MyLogicError);
    CHECK_THROWS_AS(Vector result = v1 / y, MyLogicError);
    CHECK_THROWS_AS(v1 /= y, MyLogicError);

    
    CHECK_NOTHROW(v1 *= x);
    CHECK_THROWS_AS(v5 *= x, MyLogicError);
    CHECK_NOTHROW(Vector result = v1 * x);
    CHECK_THROWS_AS(Vector result = v5 * x, MyLogicError);
    CHECK_NOTHROW(v1 %= a);
    CHECK_THROWS_AS(v5 %= a, MyLogicError);
    CHECK_NOTHROW(Vector result = v1 % a);
    CHECK_THROWS_AS(Vector result = v5 % a, MyLogicError);
    CHECK_NOTHROW(v1 /= x);
    CHECK_THROWS_AS(v5 /= x ,MyLogicError );
    CHECK_NOTHROW(Vector result = v1 / x);
    CHECK_THROWS_AS(Vector result = v5 / x ,MyLogicError);
    CHECK_NOTHROW(Vector neg = -v1);
    CHECK_THROWS_AS(Vector neg = -v5, MyLogicError);

    CHECK_NOTHROW(Vector result = v1 + v2);
    CHECK_NOTHROW(v1 += v2);
    CHECK_NOTHROW(Vector result = v1 - v2);
    CHECK_NOTHROW(v1 -= v2);
    CHECK_NOTHROW(v1 * v2);

    CHECK_NOTHROW(Vector result = v1 % v2);
    CHECK_NOTHROW(Vector result = ++v1);
    CHECK_THROWS_AS(v5++, MyLogicError);
    CHECK_NOTHROW(Vector result = v1++);
    CHECK_NOTHROW(Vector result = --v1);
    CHECK_THROWS_AS(v5--, MyLogicError);
    CHECK_NOTHROW(Vector result = v1--);
    std::ostringstream oss1;
    std::ostringstream oss2;
    oss1 << v4;
    

    // הפלט צריך להיות: "1.1 [ ] 3.3 "
    CHECK(oss1.str() == "[ ] [ ] ");
    oss2 << v1;
    CHECK(oss2.str() == "0 0.4 ");


    // בדיקות טרנספוז
    Vector cols[2] = {v1, v2};
    Vector* rows = nullptr;
    CHECK_NOTHROW(rows = Vector::transposeColumnsToRows(cols, 2));
    delete[] rows;

    CHECK_THROWS_AS(Vector::transposeColumnsToRows(nullptr, 0), MyLogicError);

    Vector colsMismatch[2] = {v1, v5};
    CHECK_THROWS_AS(Vector::transposeColumnsToRows(colsMismatch, 2), MyLogicError);

    Vector colsUninit[2] = {v1, v4};
    CHECK_THROWS_AS(Vector::transposeColumnsToRows(colsUninit, 2), MyLogicError);
} 




