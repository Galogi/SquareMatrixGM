/**
 * @file SquareMatrix.cpp
 * @brief Implements the SquareMatrix class representing a square matrix.
 *
 * Each row of the matrix is a Vector object (from the VectorGM namespace),
 * enabling clean and modular matrix operations by reusing the Vector class.
 * Includes full support for arithmetic operations, scalar operations,
 * transposition, determinant, and identity matrix generation.
 *
 * Logging is integrated using the Logger system, allowing debug-level logs
 * during object construction, method calls, and operator overloads.
 *
 * Author: Gal Maymon
 * Email: your.email@example.com
 */


#include "SquareMatrix.hpp"
#include <iostream>
#include "../Exception/MyExceptions.hpp"
#include "../Test_And_Log/Logger.hpp"



using namespace VectorGM;

namespace SquareMatrixGM {

    SquareMatrix::SquareMatrix(int size) : size(size) {
        if (size < 0)
            throw InvalidArgument();
        LOG(LogLevel::DEBUG, "Constructor called with size = " << size);
        rows = new Vector[size];
        for (int i = 0; i < size; ++i)
            rows[i] = Vector(size);
    }

    SquareMatrix::SquareMatrix(const SquareMatrix& other) : size(other.size) {
        LOG(LogLevel::DEBUG, "Copy constructor called");
        rows = new Vector[size];
        for (int i = 0; i < size; ++i)
            rows[i] = other.rows[i];
    }

    SquareMatrix& SquareMatrix::operator=(const SquareMatrix& other) {
        LOG(LogLevel::DEBUG, "Assignment operator called");
        if (this == &other) return *this;
        delete[] rows;
        size = other.size;
        rows = new Vector[size];
        for (int i = 0; i < size; ++i)
            rows[i] = other.rows[i];
        return *this;
    }

    SquareMatrix::~SquareMatrix() {
        LOG(LogLevel::DEBUG, "Destructor called");
        delete[] rows;
    }

    Vector& SquareMatrix::operator[](int row) {
        LOG(LogLevel::DEBUG, "Mutable access to row " << row);
        if (row < 0 || row >= size)
            throw MyOutOfRow();
        return rows[row];
    }

    const Vector& SquareMatrix::operator[](int row) const {
        LOG(LogLevel::DEBUG, "Const access to row " << row);
        if (row < 0 || row >= size)
            throw MyOutOfRow();
        return rows[row];
    }



    int SquareMatrix::getSize() const {
        LOG(LogLevel::DEBUG, "getSize() called");
        return size;
    }

    SquareMatrix SquareMatrix::operator+(const SquareMatrix& other) const {
        LOG(LogLevel::DEBUG, "operator+ called");
        if (size != other.size)
            throw MyLogicError("Matrix sizes must match for addition");
        SquareMatrix result(size);
        forEachRow([&](int i, const Vector& row) {
            result[i] = row + other[i];
        });
        return result;
    }

    SquareMatrix& SquareMatrix::operator+=(const SquareMatrix& other) {
        LOG(LogLevel::DEBUG, "operator+= called");
        if (size != other.size)
            throw MyLogicError("Matrix sizes must match for addition");
        forEachRow([&](int i, Vector& row) {
            row += other[i];
        });
        return *this;
    }

    SquareMatrix SquareMatrix::operator-(const SquareMatrix& other) const {
        LOG(LogLevel::DEBUG, "operator- called");
        if (size != other.size)
            throw MyLogicError("Matrix sizes must match for subtraction");
        SquareMatrix result(size);
        forEachRow([&](int i, const Vector& row) {
            result[i] = row - other[i];
        });
        return result;
    }

    SquareMatrix& SquareMatrix::operator-=(const SquareMatrix& other) {
        LOG(LogLevel::DEBUG, "operator-= called");
        if (size != other.size)
            throw MyLogicError("Matrix sizes must match for subtraction");
        forEachRow([&](int i, Vector& row) {
            row -= other[i];
        });
        return *this;
    }

    SquareMatrix SquareMatrix::operator*(const SquareMatrix& other) const {
        LOG(LogLevel::DEBUG, "operator* (matrix multiplication) called");
        if (size != other.size)
            throw MyLogicError("Matrix sizes must match for multiplication");
        Vector* cols = Vector::transposeColumnsToRows(other.rows, size);
        SquareMatrix result(size);
        forEachRow([&](int i, const Vector& row) {
            for (int j = 0; j < size; ++j) {
                result[i][j] = row * cols[j];
            }
        });
        delete[] cols;
        return result;
    }

    SquareMatrix SquareMatrix::operator%(const SquareMatrix& other) const {
        LOG(LogLevel::DEBUG, "operator% (element-wise matrix) called");
        if (size != other.size)
            throw MyLogicError("Matrix sizes must match for element-wise multiplication");
        SquareMatrix result(size);
        forEachRow([&](int i, const Vector& row) {
            result[i] = row % other[i];
        });
        return result;
    }

    SquareMatrix SquareMatrix::operator-() const {
        LOG(LogLevel::DEBUG, "operator- (unary minus) called");
        SquareMatrix result(size);
        forEachRow([&](int i, const Vector& row) {
            result[i] = -row;
        });
        return result;
    }

    SquareMatrix SquareMatrix::operator*(double scalar) const {
        LOG(LogLevel::DEBUG, "operator* (scalar) called");
        SquareMatrix result(size);
        forEachRow([&](int i, const Vector& row) {
            result[i] = row * scalar;
        });
        return result;
    }

    SquareMatrix& SquareMatrix::operator*=(double scalar) {
        LOG(LogLevel::DEBUG, "operator*= (scalar) called");
        forEachRow([&](int, Vector& row) {
            row *= scalar;
        });
        return *this;
    }

    SquareMatrix SquareMatrix::operator%(int scalar) const {
        LOG(LogLevel::DEBUG, "operator% (scalar) called");
        if (scalar == 0)
            throw MyLogicError("Modulo by zero");
        SquareMatrix result(size);
        forEachRow([&](int i, const Vector& row) {
            result[i] = row % scalar;
        });
        return result;
    }

    SquareMatrix& SquareMatrix::operator%=(int scalar) {
        LOG(LogLevel::DEBUG, "operator%= (scalar) called");
        if (scalar == 0)
            throw MyLogicError("Modulo by zero");
        forEachRow([&](int, Vector& row) {
            row %= scalar;
        });
        return *this;
    }

    SquareMatrix SquareMatrix::operator/(double scalar) const {
        LOG(LogLevel::DEBUG, "operator/ called");
        if (scalar == 0)
            throw MyLogicError("Division by zero");
        SquareMatrix result(size);
        forEachRow([&](int i, const Vector& row) {
            result[i] = row / scalar;
        });
        return result;
    }

    SquareMatrix& SquareMatrix::operator/=(double scalar) {
        LOG(LogLevel::DEBUG, "operator/= called");
        if (scalar == 0)
            throw MyLogicError("Division by zero");
        forEachRow([&](int, Vector& row) {
            row /= scalar;
        });
        return *this;
    }
    SquareMatrix SquareMatrix::operator^(int power) const {
        LOG(LogLevel::DEBUG, "operator^ called with power = " << power);
        if (power < 0)
            throw MyLogicError("Matrix power must be non-negative");
        SquareMatrix result = SquareMatrix::identity(size);
        if (power == 0)
            return result;
        SquareMatrix base = *this;
        while (power > 0) {
            if (power % 2 == 1)
                result = result * base;
            base = base * base;
            power /= 2;
        }
        return result;
    }

    SquareMatrix& SquareMatrix::operator++() {
        forEachRow([](int, Vector& row) {
            ++row;  
        });
        return *this;
    }

    SquareMatrix SquareMatrix::operator++(int) {
        LOG(LogLevel::DEBUG, "operator++ (postfix) called");
        SquareMatrix temp = *this;
        ++(*this);
        return temp;
    }

    SquareMatrix& SquareMatrix::operator--() {
        LOG(LogLevel::DEBUG, "operator-- (prefix) called");
        forEachRow([](int, Vector& row) {
            --row;
        });
        return *this;
    }

    SquareMatrix SquareMatrix::operator--(int) {
        LOG(LogLevel::DEBUG, "operator-- (postfix) called");
        SquareMatrix temp = *this;
        --(*this);
        return temp;
    }

    SquareMatrix& SquareMatrix::operator~() {
        LOG(LogLevel::DEBUG, "operator~ (transpose) called");
        Vector* transposed = Vector::transposeColumnsToRows(rows, size);
        delete[] rows;
        rows = transposed;
        return *this;
    }

    double SquareMatrix::operator!() const {
        LOG(LogLevel::DEBUG, "operator! (determinant) called");
        int n = getSize();
        forEachRow([](int, const Vector& row) {
            if (!row.allInitialized())
                throw MyLogicError("Matrix must be fully initialized to compute determinant");
        });
        if (n == 1) return (*this)[0][0];
        if (n == 2) return (*this)[0][0] * (*this)[1][1] - (*this)[0][1] * (*this)[1][0];
        double det = 0.0;
        for (int col = 0; col < n; ++col) {
            double sign = (col % 2 == 0) ? 1.0 : -1.0;
            double cofactor = sign * (*this)[0][col] * getMinor(0, col);
            det += cofactor;
        }
        return det;
    }

    double SquareMatrix::getMinor(int rowToRemove, int colToRemove) const {
        LOG(LogLevel::DEBUG, "getMinor called for row = " << rowToRemove << ", col = " << colToRemove);
        int n = getSize();
        SquareMatrix minor(n - 1);
        int r = 0;
        for (int i = 0; i < n; ++i) {
            if (i == rowToRemove) continue;
            int c = 0;
            for (int j = 0; j < n; ++j) {
                if (j == colToRemove) continue;
                minor[r][c] = (*this)[i][j];
                ++c;
            }
            ++r;
        }
        return !minor;
    }

    /**
 * @brief Applies a given function to each row of the matrix (modifiable version).
 * 
 * This function is a utility that allows iteration over each row using a custom lambda or callable.
 * It is especially useful for applying changes to the matrix without repeating loop logic.
 * 
 * @tparam Func A callable type (e.g., lambda) that accepts two arguments: (int rowIndex, Vector& row)
 * @param func The function to apply to each row.
 */
    template <typename Func>
    void SquareMatrix::forEachRow(Func func) {
        for (int i = 0; i < size; ++i) {
            func(i, rows[i]);
        }
    }


   /**
 * @brief Applies a given function to each row of the matrix (read-only version).
 * 
 * Similar to the non-const version, but for const contexts. It allows inspection or read-only
 * operations on each row using a lambda function.
 * 
 * @tparam Func A callable type (e.g., lambda) that accepts two arguments: (int rowIndex, const Vector& row)
 * @param func The function to apply to each row.
 */
    template <typename Func>
    void SquareMatrix::forEachRow(Func func) const {
        for (int i = 0; i < size; ++i) {
            func(i, rows[i]);
        }
    }

   /**
 * @brief Calculates the sum of all elements in the matrix.
 * 
 * This method iterates over all rows and sums their values using the Vector::sum() function.
 * It uses the const version of `forEachRow` to avoid code duplication and apply logic cleanly.
 * 
 * @return double The total sum of all matrix elements.
 */
    double SquareMatrix::sum() const {
        LOG(LogLevel::DEBUG, "Calculating sum of all elements using Vector::sum");
        double total = 0.0;
        forEachRow([&](int, const Vector& row) {
            total += row.sum(); // Assumes Vector::sum() is implemented
        });
        return total;
    }


   /**
 * @brief Creates an identity matrix of given size.
 * 
 * An identity matrix is a square matrix where all diagonal elements are 1 and all others are 0.
 * This static method constructs such a matrix and returns it.
 * 
 * @param size The dimension of the identity matrix.
 * @return SquareMatrix The identity matrix of the given size.
 */
    SquareMatrix SquareMatrix::identity(int size) {
        LOG(LogLevel::DEBUG, "Creating identity matrix of size = " << size);
        SquareMatrix result(size);
        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
                result[i][j] = (i == j ? 1.0 : 0.0);
        return result;
    }


}