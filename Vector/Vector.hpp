#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <ostream>

namespace VectorGM {

/**
 * @brief A helper struct representing a single cell in the Vector.
 * Author: Gal Maymon
 * Email: your.email@example.com
 * 
 * Each cell holds a `value` (double) and a flag `initialized` to track whether the value has been explicitly set.
 */
struct Cell {
    double value;
    bool initialized;

    Cell() : value(0.0), initialized(false) {}
};

/**
 * @brief A custom one-dimensional vector class with support for initialization tracking and arithmetic operations.
 * 
 * The Vector class supports element access, initialization checks, arithmetic operations (element-wise and scalar),
 * and advanced features like transpose, increment/decrement operators, and summation.
 */
class Vector {

private:
    Cell* data;   ///< Pointer to an array of Cell elements
    int size;     ///< Length of the vector

public:
    // === Constructors and Destructor ===

    /**
     * @brief Default constructor. Creates an empty vector.
     */
    Vector();

    /**
     * @brief Constructs a vector with a given size.
     * @param size The number of elements in the vector.
     */
    Vector(int size);

    /**
     * @brief Copy constructor.
     */
    Vector(const Vector& other);

    /**
     * @brief Copy assignment operator.
     */
    Vector& operator=(const Vector& other);

    /**
     * @brief Destructor. Releases dynamically allocated memory.
     */
    ~Vector();

    // === Element Access ===

    /**
     * @brief Accesses the element at a given index (modifiable).
     * Marks the element as initialized.
     */
    double& operator[](int index);

    /**
     * @brief Accesses the element at a given index (read-only).
     */
    const double& operator[](int index) const;

    /**
     * @brief Checks if a specific index has been initialized.
     */
    bool isInitialized(int index) const;

    /**
     * @brief Checks if all elements in the vector have been initialized.
     */
    bool allInitialized() const;

    /**
     * @brief Returns the size (length) of the vector.
     */
    int getSize() const;

    /**
     * @brief Calculates and returns the sum of all initialized values in the vector.
     */
    double sum() const;

    // === Arithmetic Operations ===

    Vector operator+(const Vector& other) const;
    Vector& operator+=(const Vector& other);
    Vector operator-(const Vector& other) const;
    Vector& operator-=(const Vector& other);
    Vector operator%(const Vector& other) const;

    /**
     * @brief Computes the dot product between two vectors.
     */
    double operator*(const Vector& other) const;

    /**
     * @brief Converts a list of column vectors into a list of row vectors (used for matrix multiplication).
     */
    static Vector* transposeColumnsToRows(const Vector* cols, int count);

    Vector operator-() const;
    Vector operator*(double scalar) const;
    Vector& operator*=(double scalar);
    Vector operator%(int scalar) const;
    Vector& operator%=(int scalar);
    Vector operator/(double scalar) const;
    Vector& operator/=(double scalar);

    // === Increment / Decrement ===
    Vector& operator++();      ///< Prefix increment (adds 1 to each initialized element)
    Vector operator++(int);    ///< Postfix increment
    Vector& operator--();      ///< Prefix decrement (subtracts 1 from each initialized element)
    Vector operator--(int);    ///< Postfix decrement

    /**
     * @brief Prints the vector in human-readable format (e.g., [1.0, 2.0, ...]).
     */
    friend std::ostream& operator<<(std::ostream& os, const Vector& vec);
};

}

#endif
