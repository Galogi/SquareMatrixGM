# Square Matrix  (C++)

This project is a modular implementation of square matrices  C++ (C++17). The project is built **without STL**, focusing on core programming principles like memory management, testing, and logging. It also includes:

- Unit tests with [doctest](https://github.com/doctest/doctest)
- Code coverage analysis using `gcov`
- Logging system with log levels (DEBUG, INFO,)
- Support for memory leak detection with Valgrind
- Shortcut aliases for frequent commands (`env.sh`)

---

##  Project Structure

```
.
├── Exception/           # Custom exception classes
│   └── MyExceptions.hpp
├── Matrix/              # SquareMatrix class implementation
│   ├── SquareMatrix.cpp
│   └── SquareMatrix.hpp
├── Vector/              # Vector class implementation
│   ├── Vector.cpp
│   └── Vector.hpp
├── Test_And_Log/        # Logger and unit tests (using doctest)
│   ├── Logger.hpp
│   ├── logMatrix.cpp
│   └── logVector.cpp
├── env.sh               # Script with helpful alias shortcuts          
├── main.cpp             # Entry point for the main application
├── Makefile             # Build automation
└── log.txt              # Logger output
```

---

## 🧩 Class Descriptions

### `SquareMatrix` (in `Matrix/SquareMatrix.cpp/.hpp`)
- Represents a square matrix (NxN) built **without STL**.
- Each row in the matrix is implemented using a custom `Vector` class.
- Implements matrix operations: addition, subtraction, multiplication, scaling, identity, transpose, etc.
- Supports operator overloading (`+`, `-`, `*`, `/`, `[]`, `~`, `!`, `%`, etc.).

### `Vector` (in `Vector/Vector.cpp/.hpp`)
- Represents a 1D array of `double` values with bounds checking and initialization tracking.
- Supports vector arithmetic and element-wise operations.
- Used internally by `SquareMatrix`, where each matrix row is a `Vector`.
- Supports operator overloading (`+`, `-`, `*`, `/`, `[]`, `~`, `!`, `%`, etc.).

### `Logger` (in `Test_And_Log/Logger.hpp`)
- Lightweight custom logger with 2 levels: DEBUG, INFO.
- Controlled using `GLOBAL_LOG_LEVEL`, which can be defined during compilation.
- Logs are written to `log.txt`.

### `logMatrix.cpp` and `logVector.cpp`
- Unit tests using `doctest` framework for `SquareMatrix` and `Vector`.
- Tests cover correct behavior and exception handling.
- Logging and coverage integrated for test monitoring.

### `MyExceptions.hpp`
- Custom exceptions to differentiate logical errors (`MyLogicError`) and range errors (`MyOutOfRange`).
- Thrown from `Vector` and `SquareMatrix` during invalid operations.

---

##  Build Instructions

### Build the Main Application
```bash
make
./MatrixMain
```

### Build & Run Unit Tests
```bash
make matrix   # Run SquareMatrix tests
make vector   # Run Vector tests
```

---

##  Code Coverage

After running tests:
```bash
gcov -p -o Matrix Matrix/SquareMatrix.cpp
gcov -p -o Vector Vector/Vector.cpp
gcov -p -o . main.cpp
```

This generates `.gcov` files showing line-by-line coverage.

---

##  Clean Project

To remove all object and coverage files:
```bash
make clean
```

---

##  Shortcuts with `env.sh`

Run:
```bash
source code/env.sh
```

Then you can use like:

- `mvec`  – make Matrix_tests_vector
- `mmat`  – make Matrix_tests_matrix
- `mapp`  – make MatrixMain

- `covm`  – Code coverage for matrix
- `covv`  – Code coverage for vector
- `cln`   – Clean build & coverage files
Get in and look.

---

## 🧠 Learning Goals

- Manual memory management
- Operator overloading in C++
- Custom data structures
- Testing with Doctest
- Logging & debugging
- Coverage and leak checking

---

## 🧑‍💻 Author

**Gal Maymon**  
Student & Developer  
Project goal: Deepen understanding of core C++ concepts by building a self-contained matrix system from scratch.
