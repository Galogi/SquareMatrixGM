/******************************************************
 * Author: Gal Maymon  
 * Email: galmaymon@gmail.com  
 * File: logMatrix.cpp  
 * Description:
 * This file contains unit tests for the `SquareMatrix` class,
 * using the doctest framework to validate the matrix functionality.
 *
 * These tests cover:
 * - Matrix construction, copying, and assignment
 * - Operator overloads: +, -, *, /, %, ^, !, ~, ==, !=, <, >, <=, >=
 * - Scalar and element-wise arithmetic
 * - Determinant calculation (!), transpose (~), and power (^)
 * - Pre/post increment and decrement
 * - Exception handling for invalid dimensions, out-of-range indices,
 *   uninitialized values, and division/modulo by zero
 * - Output formatting using operator<<
 *
 * Dependencies:
 * - Vector class (used internally to represent rows)
 * - Logger for debugging info
 * - Custom exception classes (InvalidArgument, MyLogicError, etc.)
 *
 * Build Info:
 * - Compile with `-fprofile-arcs -ftest-coverage` for gcov support
 * - Link with `-lgcov` if needed
 *
 * Usage:
 * Run the compiled tests to verify the correctness of the SquareMatrix implementation.
 ******************************************************/




#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <iostream>
#include <cmath>
#include "../Test_And_Log/Logger.hpp"
#include "../Matrix/SquareMatrix.hpp"
#include "doctest.h" 
#include "../Exception/MyExceptions.hpp"
using namespace SquareMatrixGM;
using namespace std;



#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../Matrix/SquareMatrix.hpp"
#include <cmath> // std::abs
using namespace SquareMatrixGM;

TEST_CASE("Matrix basic construction and access") {
    SquareMatrix m(2);
    m[0][0] = 1.0;
    m[0][1] = 2.0;
    m[1][0] = 3.0;
    m[1][1] = 4.0;

    CHECK(m[0][0] == 1.0);
    CHECK(m[1][1] == 4.0);
}

TEST_CASE("Matrix addition and subtraction") {
    SquareMatrix a(2), b(2);
    a[0][0] = 1; a[0][1] = 2;
    a[1][0] = 3; a[1][1] = 4;

    b[0][0] = 4; b[0][1] = 3;
    b[1][0] = 2; b[1][1] = 1;

    SquareMatrix sum = a + b;
    SquareMatrix diff = a - b;

    CHECK(sum[0][0] == 5);
    CHECK(sum[1][1] == 5);
    CHECK(diff[0][1] == -1);
    CHECK(diff[1][0] == 1);

    a += b ;
   

    CHECK(a[0][0] == 5);
    CHECK(a[0][1] == 5);
    CHECK(a[1][0] == 5);
    CHECK(a[1][1] == 5);

    a -= b;
    CHECK(a[0][0] == 1);
    CHECK(a[0][1] == 2);
    CHECK(a[1][0] == 3);
    CHECK(a[1][1] == 4);

}

TEST_CASE("Matrix multiplication") {
    SquareMatrix a(2), b(2);
    a[0][0] = 1; a[0][1] = 2;
    a[1][0] = 3; a[1][1] = 4;

    b[0][0] = 2; b[0][1] = 0;
    b[1][0] = 1; b[1][1] = 2;

    SquareMatrix product = a * b;

    CHECK(product[0][0] == 4);
    CHECK(product[0][1] == 4);
    CHECK(product[1][0] == 10);
    CHECK(product[1][1] == 8);

    SquareMatrix result = a % b;

    CHECK(result[0][0] == 2); 
    CHECK(result[0][1] == 0); 
    CHECK(result[1][0] == 3); 
    CHECK(result[1][1] == 8); 
    a *= 2.0;

    CHECK(a[0][0] == 2);
    CHECK(a[0][1] == 4);
    CHECK(a[1][0] == 6);
    CHECK(a[1][1] == 8);

    result = a % 2;

    CHECK(result[0][0] == 0);
    CHECK(result[0][1] == 0);
    CHECK(result[1][0] == 0);
    CHECK(result[1][1] == 0);

    a %= 3;

    CHECK(a[0][0] == 2);
    CHECK(a[0][1] == 1);
    CHECK(a[1][0] == 0);
    CHECK(a[1][1] == 2);

    result = a ^ 0;

    CHECK(result[0][0] == 1);
    CHECK(result[0][1] == 0);
    CHECK(result[1][0] == 0);
    CHECK(result[1][1] == 1);


    result = a / 0.5;

    CHECK(result[0][0] == 4);
    CHECK(result[0][1] == 2);
    CHECK(result[1][0] == 0);
    CHECK(result[1][1] == 4);
}

TEST_CASE("Scalar operations") {
    SquareMatrix m(2);
    m[0][0] = 1; m[0][1] = 2;
    m[1][0] = 3; m[1][1] = 4;

    SquareMatrix scaled = m * 2.0;
    CHECK(scaled[0][0] == 2.0);
    CHECK(scaled[1][1] == 8.0);

    m /= 2.0;
    CHECK(m[0][0] == 0.5);
    CHECK(m[1][0] == 1.5);
}

TEST_CASE("Transpose operator") {
    SquareMatrix m(2);
    m[0][0] = 1; m[0][1] = 2;
    m[1][0] = 3; m[1][1] = 4;

    ~m;
    CHECK(m[0][1] == 3);
    CHECK(m[1][0] == 2);
   
}

TEST_CASE("Determinant operator") {
    SquareMatrix mat(3);
    mat[0][0] = 1; mat[0][1] = 2; mat[0][2] = 3;
    mat[1][0] = 0; mat[1][1] = 1; mat[1][2] = 4;
    mat[2][0] = 5; mat[2][1] = 6; mat[2][2] = 0;

    double det = !mat;

    CHECK(det == 1);  
}

TEST_CASE("Matrix power") {
    SquareMatrix m(2);
    m[0][0] = 2; m[0][1] = 0;
    m[1][0] = 0; m[1][1] = 2;

    SquareMatrix m2 = m ^ 3;
    CHECK(m2[0][0] == 8);
    CHECK(m2[1][1] == 8);
}

TEST_CASE("Increment and Decrement") {
    SquareMatrix m(2);
    m[0][0] = 1; m[0][1] = 2;
    m[1][0] = 3; m[1][1] = 4;

    ++m;
    CHECK(m[0][0] == 2);
    m++;
    CHECK(m[0][0] == 3);
    --m;
    CHECK(m[0][0] == 2);
    m--;
    CHECK(m[0][0] == 1);
}
TEST_CASE("Matrix unary minus works") {
    SquareMatrix a(2);
    a[0][0] = 1;
    a[0][1] = -2;
    a[1][0] = 3;
    a[1][1] = -4;

    SquareMatrix neg = -a;

    CHECK(neg[0][0] == -1);
    CHECK(neg[0][1] == 2);
    CHECK(neg[1][0] == -3);
    CHECK(neg[1][1] == 4);
}

TEST_CASE("Matrix comparison operators based on sum()") {
    SquareMatrix a(2), b(2), c(2), d(2), e(2);

   
    a[0][0] = 1; a[0][1] = 2;
    a[1][0] = 3; a[1][1] = 4;

 
    b[0][0] = 2; b[0][1] = 1;
    b[1][0] = 4; b[1][1] = 3;

  
    c[0][0] = 5; c[0][1] = 5;
    c[1][0] = 5; c[1][1] = 5;

 
    d[0][0] = 1; d[0][1] = 1;
    d[1][0] = 2; d[1][1] = 1;

  
    e[0][0] = 1; e[0][1] = 2;
    e[1][0] = 3; e[1][1] = 4 + 1e-10;

   
    CHECK(a == b);
    CHECK_FALSE(a != b);
    CHECK(a == e);         
    CHECK_FALSE(a != e);

   
    CHECK(a < c);
    CHECK(c > a);
    CHECK(d < a);
    CHECK(a > d);
    CHECK(a <= b);
    CHECK(a >= b);
    CHECK(d <= a);
    CHECK(c >= a);
}


TEST_CASE("Throw Exception") {
    SquareMatrix m1(2) ,  m2(2) , m5(3) , m6(2);
    m1[0][0] = 1; m1[0][1] = 2;
    m1[1][0] = 3; m1[1][1] = 4;

    


    CHECK_THROWS_AS( SquareMatrix m_t(-1); , InvalidArgument);
    CHECK_THROWS_AS( m2[1][5] = 4 , MyOutOfRange);
    CHECK_THROWS_AS( const SquareMatrix m3=m1;  m3[1][5] , MyOutOfRange);
    CHECK_THROWS_AS( SquareMatrix m4 = m1+m5  , MyLogicError);
    CHECK_THROWS_AS( const SquareMatrix m3=m1;  m3[-1] , MyOutOfRow);
    CHECK_THROWS_AS(m1[-1], MyOutOfRow); // אינדקס שלילי
    CHECK_THROWS_AS(m1[3], MyOutOfRow);
    CHECK_THROWS_AS( m1 += m5, MyLogicError);
    CHECK_THROWS_AS( SquareMatrix m4 = m1-m5  , MyLogicError);
    CHECK_THROWS_AS( m1 -= m5, MyLogicError);
    CHECK_THROWS_AS( m1*m5  , MyLogicError);
    CHECK_THROWS_AS(m1 % m5, MyLogicError);
    CHECK_THROWS_AS(m1 % 0, MyLogicError);
    CHECK_THROWS_AS(m1 %= 0, MyLogicError);
    CHECK_THROWS_AS(m1 /= 0, MyLogicError);
    CHECK_THROWS_AS(m1 / 0, MyLogicError);
    CHECK_THROWS_AS(m1 ^ -3, MyLogicError);
    CHECK_THROWS_AS(!m6, MyLogicError);
    CHECK_THROWS_AS(m1<m6, MyLogicError);
}
