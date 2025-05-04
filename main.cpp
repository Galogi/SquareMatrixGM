/****************************************************
 * Author: Gal Maymon  
 * Email: galmaymon@gmail.com  
 *
 * Description:
 * This file demonstrates the usage of the SquareMatrix class.
 * It includes examples of matrix operations such as:
 * addition, subtraction, multiplication, scalar operations,
 * transposition, determinant calculation, power, and comparisons.
 * It also handles exceptions for invalid operations.
 ****************************************************/


#include <iostream>
#include "Matrix/SquareMatrix.hpp"
#include "Exception/MyExceptions.hpp"

using namespace std;
using namespace SquareMatrixGM;


int main() {
    try {
        SquareMatrix A(2), B(2);

        
        A[0][0] = 1; A[0][1] = 2;
        A[1][0] = 3; A[1][1] = 4;

        
        B[0][0] = 4; B[0][1] = 3;
        B[1][0] = 2; B[1][1] = 1;

        cout << "\nMatrix A:\n" << A;
        cout << "\nMatrix B:\n" << B;

        
        SquareMatrix sum = A + B;
        cout << "\nA + B:\n" << sum;
		cout << "\nA befor A += B:\n" << A;
		A += B;
		cout << "\nA after A\n" << A;
		A -= B;
		cout << "\nA after A -= B:\n" << A;

        
        SquareMatrix diff = A - B;
        cout << "\nA - B:\n" << diff;

        
        SquareMatrix product = A * B;
        cout << "\nA * B:\n" << product;

       
        SquareMatrix scalarProduct = A * 2.0;
        cout << "\nA * 2:\n" << scalarProduct;

        
        SquareMatrix modScalar = B % 2;
        cout << "\nB % 2:\n" << modScalar;

       
        ~A;
        cout << "\nTranspose of A:\n" << A;

       
        cout << "\nDet(A): " << !A << endl;
        cout << "\nDet(B): " << !B << endl;

        
        cout << "\nA == B: " << (A == B) << endl;
        cout << "\nA > B: " << (A > B) << endl;

        
        SquareMatrix power = B ^ 2;
        cout << "\nB ^ 2:\n" << power;

       
        A++;
        cout << "\nA after A++:\n" << A;
        --B;
        cout << "\nB after --B:\n" << B;

    } catch (const MyLogicError& e) {
        cerr << "\nMyLogicError: " << e.what() << endl;
    } catch (const MyOutOfRow& e) {
        cerr << "\nMyOutOfRow: " << e.what() << endl;
    } catch (const MyOutOfRange& e) {
        cerr << "\nMyOutOfRange: " << e.what() << endl;
    } 

    return 0;
}
