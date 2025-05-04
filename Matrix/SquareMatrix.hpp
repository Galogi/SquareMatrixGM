/**
 * Author: Gal Maymon
 * Email: your.email@example.com
 * @brief Definition of the SquareMatrix class for square matrix operations.
 *
 * This class represents a square matrix using an array of Vector objects.
 * Each row of the matrix is stored as a Vector, allowing use of Vector's operators
 * and functionalities such as addition, scalar multiplication, transposition, and more.
 * 
 * The class provides rich operator overloading, including arithmetic, comparison,
 * transpose (~), power (^), determinant (!), and increment/decrement.
 * It also integrates with a logging system and custom exception handling.
 */

 #ifndef SQUARE_MATRIX_HPP
 #define SQUARE_MATRIX_HPP
 
 #include <ostream>
 #include <cmath>
 #include "../Vector/Vector.hpp"
 
 namespace SquareMatrixGM {
 
	 /**
	  * @class SquareMatrix
	  * @brief A class representing a square matrix using dynamically allocated rows of Vectors.
	  */
	 class SquareMatrix {
	 private:
		 VectorGM::Vector* rows; ///< Array of Vector rows
		 int size; ///< Size of the square matrix (NxN)
 
		 /**
		  * @brief Applies a function to each row (non-const).
		  * @tparam Func A callable object taking (int index, Vector&)
		  */
		 template <typename Func>
		 void forEachRow(Func func);
 
		 /**
		  * @brief Applies a function to each row (const version).
		  * @tparam Func A callable object taking (int index, const Vector&)
		  */
		 template <typename Func>
		 void forEachRow(Func func) const;
 
		 static SquareMatrix identity(int size); ///< Creates identity matrix of given size.
		 double sum() const; ///< Computes the sum of all elements in the matrix.
		 double getMinor(int rowToRemove, int colToRemove) const; ///< Computes determinant minor.
 
	 public:
		 // === Constructors and Destructor ===
 
		 /**
		  * @brief Constructs a square matrix of given size (NxN).
		  * @param size Size of the matrix.
		  */
		 SquareMatrix(int size);
 
		 /**
		  * @brief Copy constructor.
		  */
		 SquareMatrix(const SquareMatrix& other);
 
		 /**
		  * @brief Copy assignment operator.
		  */
		 SquareMatrix& operator=(const SquareMatrix& other);
 
		 /**
		  * @brief Destructor.
		  */
		 ~SquareMatrix();
 
		 // === Element Access ===
 
		 /**
		  * @brief Access row by index (modifiable).
		  */
		 VectorGM::Vector& operator[](int row);
 
		 /**
		  * @brief Access row by index (read-only).
		  */
		 const VectorGM::Vector& operator[](int row) const;
 
		 /**
		  * @brief Returns the size (dimension) of the matrix.
		  */
		 int getSize() const;
 
		 // === Arithmetic Operators ===
 
		 SquareMatrix operator+(const SquareMatrix& other) const; ///< Matrix addition
		 SquareMatrix& operator+=(const SquareMatrix& other); ///< Matrix addition (in-place)
		 SquareMatrix operator-(const SquareMatrix& other) const; ///< Matrix subtraction
		 SquareMatrix& operator-=(const SquareMatrix& other); ///< Matrix subtraction (in-place)
		 SquareMatrix operator*(const SquareMatrix& other) const; ///< Matrix multiplication
		 SquareMatrix operator%(const SquareMatrix& other) const; ///< Element-wise multiplication
		 SquareMatrix operator-() const; ///< Unary minus
		 SquareMatrix operator*(double scalar) const; ///< Scalar multiplication
		 SquareMatrix& operator*=(double scalar); ///< Scalar multiplication (in-place)
		 SquareMatrix operator%(int scalar) const; ///< Scalar modulo
		 SquareMatrix& operator%=(int scalar); ///< Scalar modulo (in-place)
		 SquareMatrix operator/(double scalar) const; ///< Scalar division
		 SquareMatrix& operator/=(double scalar); ///< Scalar division (in-place)
		 SquareMatrix operator^(int power) const; ///< Matrix exponentiation
 
		 // === Increment/Decrement ===
 
		 SquareMatrix& operator++(); ///< Prefix increment (++mat)
		 SquareMatrix operator++(int); ///< Postfix increment (mat++)
		 SquareMatrix& operator--(); ///< Prefix decrement (--mat)
		 SquareMatrix operator--(int); ///< Postfix decrement (mat--)
 
		 // === Utility Operators ===
 
		 SquareMatrix& operator~(); ///< Transpose matrix
		 double operator!() const; ///< Determinant
 
		 // === Comparison Operators (based on total sum of elements) ===
 
		 bool operator==(const SquareMatrix& other) const;
		 bool operator!=(const SquareMatrix& other) const;
		 bool operator<(const SquareMatrix& other) const;
		 bool operator>(const SquareMatrix& other) const;
		 bool operator<=(const SquareMatrix& other) const;
		 bool operator>=(const SquareMatrix& other) const;
 
		 // === Output Operator ===
 
		 /**
		  * @brief Outputs matrix rows using std::ostream.
		  */
		 friend std::ostream& operator<<(std::ostream& os, const SquareMatrix& mat) {
			 for (int i = 0; i < mat.size; ++i)
				 os << mat[i] << '\n';
			 return os;
		 }
	 };
 
 } // namespace SquareMatrixGM
 
 #endif
 