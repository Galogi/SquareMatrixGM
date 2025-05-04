/**
 * @file MyExceptions.hpp
 * @brief Custom exception classes used throughout the Matrix and Vector project.
 * 
 * This file defines user-defined exception classes for handling various error cases
 * such as out-of-range access, invalid arguments, and logical errors.
 *
 * Author: Gal Maymon
 * Email: your.email@example.com
 */

 #ifndef MY_EXCEPTIONS_HPP
 #define MY_EXCEPTIONS_HPP
 
 /**
  * @class MyOutOfRange
  * @brief Exception for invalid access to an index in a vector.
  */
 class MyOutOfRange {
 public:
     const char* what() const {
         return "Index out of range";
     }
 };
 
 /**
  * @class MyOutOfRow
  * @brief Exception for invalid access to a row in a matrix.
  */
 class MyOutOfRow {
 public:
     const char* what() const {
         return "Row index out of range";
     }
 };
 
 /**
  * @class InvalidArgument
  * @brief Exception for functions that received an invalid argument.
  */
 class InvalidArgument {
 public:
     const char* what() const {
         return "Invalid argument";
     }
 };
 
 /**
  * @class MyLogicError
  * @brief Exception used to signal logical errors (e.g., operation on incompatible sizes).
  */
 class MyLogicError {
     const char* message;
 public:
     MyLogicError(const char* msg) : message(msg) {}
 
     const char* what() const {
         return message;
     }
 };
 
 #endif // MY_EXCEPTIONS_HPP
 