/**********************************************************
 * Author: Gal Maymon  
 * Email: galmaymon@gmail.com  
 * File: Logger.hpp  
 * Description:
 * This header defines a lightweight logging mechanism 
 * for use during development and debugging of C++ applications.
 *
 * Features:
 * - Supports two logging levels: INFO and DEBUG
 * - Logs are written to a file named "log.txt" (overwritten on each run)
 * - Allows compile-time control of log verbosity using GLOBAL_LOG_LEVEL
 *
 * Components:
 * - `enum class LogLevel`: Defines available log levels
 * - `getLogStream()`: Returns a reference to a singleton log file stream
 * - `LOG(level, msg)`: Macro for writing log messages conditionally based on level
 *
 * Usage Example:
 *   LOG(LogLevel::INFO, "Application started");
 *   LOG(LogLevel::DEBUG, "Value of x: " << x);
 *
 * Notes:
 * - To set the log level, define GLOBAL_LOG_LEVEL before including this file.
 *   Example:
 *      #define GLOBAL_LOG_LEVEL LogLevel::INFO
 *      #include "Logger.hpp"
 **********************************************************/

 #ifndef LOGGER_HPP
 #define LOGGER_HPP
 
 #include <iostream>
 #include <fstream>
 
 enum class LogLevel {
     INFO  = 0,
     DEBUG = 1,
 };
 
 inline std::ofstream& getLogStream() {
     static std::ofstream logFile("log.txt", std::ios::trunc); 
     return logFile;
 }
 
 #ifndef GLOBAL_LOG_LEVEL
 #define GLOBAL_LOG_LEVEL LogLevel::DEBUG
 #endif
 
 #define LOG(level, msg)                                                                 \
     do {                                                                                \
         if (static_cast<int>(level) == static_cast<int>(GLOBAL_LOG_LEVEL)) {           \
             getLogStream() << "[" << #level << "] " << msg << std::endl;               \
         }                                                                               \
     } while (0)
 
 #endif
 
