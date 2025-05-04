/**
 * @file Vector.cpp
 * @brief Implementation of the Vector class, a 1D array-like structure with support for element-wise operations,
 *        scalar operations, and initialization tracking.
 *
 * @author Gal
 * @email your_email@example.com
 */


#include "Vector.hpp"
#include <iostream>
#include "../Exception/MyExceptions.hpp"
#include "../Test_And_Log/Logger.hpp"


namespace VectorGM {
Vector::Vector() : data(nullptr), size(0) {
    LOG(LogLevel::DEBUG, "Default constructor called.");
}

Vector::Vector(int size) : size(size) {
    if (size < 0)
        throw InvalidArgument();
    data = new Cell[size];
    LOG(LogLevel::INFO, "Vector of size " << size << " created.");
}

Vector::Vector(const Vector& other) : size(other.size) {
    data = new Cell[size];
    for (int i = 0; i < size; ++i)
        data[i] = other.data[i];
    LOG(LogLevel::DEBUG, "Vector copied (size " << size << ").");
}

Vector& Vector::operator=(const Vector& other) {
    if (this == &other) return *this;
    delete[] data;
    size = other.size;
    data = new Cell[size];
    for (int i = 0; i < size; ++i)
        data[i] = other.data[i];
    LOG(LogLevel::DEBUG, "Vector assigned (size " << size << ").");
    return *this;
}

Vector::~Vector() {
    delete[] data;
    LOG(LogLevel::DEBUG, "Vector of size " << size << " destroyed.");
}

double& Vector::operator[](int index) {
    if (index < 0 || index >= size)
        throw MyOutOfRange();
    data[index].initialized = true;
    LOG(LogLevel::DEBUG, "Element at index " << index << " accessed (write mode).");
    return data[index].value;
}

const double& Vector::operator[](int index) const {
    if (index < 0 || index >= size)
        throw MyOutOfRange();
    LOG(LogLevel::DEBUG, "Element at index " << index << " accessed (read mode).");
    return data[index].value;
}

bool Vector::isInitialized(int index) const {
    if (index < 0 || index >= size)
        throw MyOutOfRange();
    return data[index].initialized;
}

bool Vector::allInitialized() const {
    for (int i = 0; i < size; ++i) {
        if (!data[i].initialized)
            return false;
    }
    return true;
}

int Vector::getSize() const {
    return size;
}



Vector Vector::operator+(const Vector& other) const {
    LOG(LogLevel::DEBUG, "Performing vector addition.");
    if (size != other.size)
        throw MyLogicError("Vector sizes must match for addition");

    Vector result(size);
    for (int i = 0; i < size; ++i) {
        if (!this->isInitialized(i) || !other.isInitialized(i))
            throw MyLogicError("Both vectors must be fully initialized for addition");
        result[i] = data[i].value + other[i];
    }
    return result;
}

Vector& Vector::operator+=(const Vector& other) {
    LOG(LogLevel::DEBUG, "Performing vector += operation.");
    if (size != other.size)
        throw MyLogicError("Vector sizes must match for addition");

    for (int i = 0; i < size; ++i)
        data[i].value += other.data[i].value;

    return *this;
}

Vector Vector::operator-(const Vector& other) const {
    LOG(LogLevel::DEBUG, "Performing vector subtraction.");
    if (size != other.size)
        throw MyLogicError("Vector sizes must match for subtraction");

    Vector result(size);
    for (int i = 0; i < size; ++i) {
        if (!this->isInitialized(i) || !other.isInitialized(i))
            throw MyLogicError("Both vectors must be fully initialized for subtraction");
        result[i] = data[i].value - other[i];
    }
    return result;
}

Vector& Vector::operator-=(const Vector& other) {
    LOG(LogLevel::DEBUG, "Performing vector -= operation.");
    if (size != other.size)
        throw MyLogicError("Vector sizes must match for subtraction");

    for (int i = 0; i < size; ++i)
        data[i].value -= other.data[i].value;

    return *this;
}

double Vector::operator*(const Vector& other) const {
    LOG(LogLevel::DEBUG, "Performing dot product.");
    if (size != other.size)
        throw MyLogicError("Vector sizes must match for dot product");

    double result = 0.0;
    for (int i = 0; i < size; ++i) {
        if (!this->isInitialized(i) || !other.isInitialized(i))
            throw MyLogicError("Both vectors must be fully initialized for dot product");
        result += data[i].value * other[i];
    }
    return result;
}

Vector Vector::operator%(const Vector& other) const {
    LOG(LogLevel::DEBUG, "Performing element-wise multiplication.");
    if (size != other.size)
        throw MyLogicError("Vector sizes must match for element-wise multiplication");

    Vector result(size);
    for (int i = 0; i < size; ++i) {
        if (!this->isInitialized(i) || !other.isInitialized(i))
            throw MyLogicError("Both vectors must be fully initialized for element-wise multiplication");
        result[i] = data[i].value * other[i];
    }
    return result;
}
/**
 * @brief Converts an array of column vectors into an array of row vectors, for matrix operations.
 * 
 * @param cols An array of Vector objects representing columns.
 * @param count Number of columns.
 * @return A new array of Vector objects, transposed into rows.
 * @throws MyLogicError if input is invalid or uninitialized.
 */
Vector* Vector::transposeColumnsToRows(const Vector* cols, int count) {
    LOG(LogLevel::DEBUG, "Transposing columns to rows.");
    if (count == 0)
        throw MyLogicError("Empty input");

    int rowSize = cols[0].getSize();
    for (int i = 1; i < count; ++i) {
        if (cols[i].getSize() != rowSize)
            throw MyLogicError("All vectors must be the same size");
    }

    Vector* result = new Vector[rowSize];
    try {
        for (int i = 0; i < rowSize; ++i)
            result[i] = Vector(count);

        for (int i = 0; i < rowSize; ++i) {
            for (int j = 0; j < count; ++j) {
                if (!cols[j].isInitialized(i))
                    throw MyLogicError("Column vector is not fully initialized");
                result[i][j] = cols[j][i];
            }
        }
    } catch (...) {
        delete[] result;
        throw;
    }

    return result;
}

Vector Vector::operator-() const {
    LOG(LogLevel::DEBUG, "Negating vector.");
    Vector result(size);
    for (int i = 0; i < size; ++i) {
        if (!this->isInitialized(i))
            throw MyLogicError("Cannot negate uninitialized cell in vector");
        result[i] = -data[i].value;
    }
    return result;
}

Vector Vector::operator*(double scalar) const {
    LOG(LogLevel::DEBUG, "Multiplying vector by scalar.");
    Vector result(size);
    for (int i = 0; i < size; ++i) {
        if (!isInitialized(i))
            throw MyLogicError("Cannot multiply uninitialized cell");
        result[i] = data[i].value * scalar;
    }
    return result;
}

Vector& Vector::operator*=(double scalar) {
    LOG(LogLevel::DEBUG, "Performing vector *= scalar operation.");
    for (int i = 0; i < size; ++i) {
        if (!isInitialized(i))
            throw MyLogicError("Cannot multiply uninitialized cell");
        data[i].value *= scalar;
    }
    return *this;
}

Vector Vector::operator%(int scalar) const {
    LOG(LogLevel::DEBUG, "Performing vector % scalar operation.");
    if (scalar == 0)
        throw MyLogicError("Modulo by zero");

    Vector result(size);
    for (int i = 0; i < size; ++i) {
        if (!isInitialized(i))
            throw MyLogicError("Cannot modulo uninitialized cell");

        int valAsInt = static_cast<int>(data[i].value);
        result[i] = valAsInt % scalar;
    }
    return result;
}

Vector& Vector::operator%=(int scalar) {
    LOG(LogLevel::DEBUG, "Performing vector %= scalar operation.");
    if (scalar == 0)
        throw MyLogicError("Modulo by zero");

    for (int i = 0; i < size; ++i) {
        if (!isInitialized(i))
            throw MyLogicError("Cannot modulo uninitialized cell");

        int valAsInt = static_cast<int>(data[i].value);
        data[i].value = valAsInt % scalar;
    }
    return *this;
}

Vector Vector::operator/(double scalar) const {
    LOG(LogLevel::DEBUG, "Performing vector / scalar operation.");
    if (scalar == 0)
        throw MyLogicError("Division by zero");

    Vector result(size);
    for (int i = 0; i < size; ++i) {
        if (!isInitialized(i))
            throw MyLogicError("Cannot divide uninitialized cell");
        result[i] = data[i].value / scalar;
    }
    return result;
}

Vector& Vector::operator/=(double scalar) {
    LOG(LogLevel::DEBUG, "Performing vector /= scalar operation.");
    if (scalar == 0)
        throw MyLogicError("Division by zero");

    for (int i = 0; i < size; ++i) {
        if (!isInitialized(i))
            throw MyLogicError("Cannot divide uninitialized cell");
        data[i].value /= scalar;
    }
    return *this;
}

Vector& Vector::operator++() {
    LOG(LogLevel::DEBUG, "Pre-incrementing vector.");
    for (int i = 0; i < size; ++i) {
        if (!data[i].initialized)
            throw MyLogicError("Cannot increment uninitialized cell");
        data[i].value += 1;
    }
    return *this;
}

Vector Vector::operator++(int) {
    LOG(LogLevel::DEBUG, "Post-incrementing vector.");
    Vector temp = *this;
    ++(*this);
    return temp;
}

Vector& Vector::operator--() {
    LOG(LogLevel::DEBUG, "Pre-decrementing vector.");
    for (int i = 0; i < size; ++i) {
        if (!data[i].initialized)
            throw MyLogicError("Cannot decrement uninitialized cell");
        data[i].value -= 1;
    }
    return *this;
}

Vector Vector::operator--(int) {
    LOG(LogLevel::DEBUG, "Post-decrementing vector.");
    Vector temp = *this;
    --(*this);
    return temp;
}

std::ostream& operator<<(std::ostream& os, const Vector& vec) {
    for (int i = 0; i < vec.size; ++i) {
        if (vec.data[i].initialized)
            os << vec.data[i].value << " ";
        else
            os << "[ ] ";
    }
    return os;
}

/**
 * @brief Calculates the sum of all initialized elements in the vector.
 * 
 * @return The total sum of all elements.
 * 
 * @throws MyLogicError if any element in the vector is not initialized.
 * 
 * @note This method assumes that all elements must be initialized before summation.
 *       It is useful when evaluating the total magnitude or comparing vectors/matrices.
 */


double Vector::sum() const {
    double total = 0.0;
    for (int i = 0; i < size; ++i) {
        if (!isInitialized(i))
            throw MyLogicError("Uninitialized cell in vector during sum()");
        total += data[i].value;
    }
    return total;
}

}