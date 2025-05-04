# Author: Gal Maymon  
# Email: galmaymon@gmail.com  

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g -fprofile-arcs -ftest-coverage
LDFLAGS = -lgcov

VECTOR_SRC = Vector/Vector.cpp
MATRIX_SRC = Matrix/SquareMatrix.cpp
APP_SRC = main.cpp

VECTOR_LOG_SRC = Test_And_Log/logVector.cpp
MATRIX_LOG_SRC = Test_And_Log/logMatrix.cpp

VECTOR_OBJS = $(VECTOR_SRC:.cpp=.o)
MATRIX_OBJS = $(MATRIX_SRC:.cpp=.o)
APP_OBJS = $(APP_SRC:.cpp=.o)

VECTOR_TEST_OBJS = $(VECTOR_OBJS) $(VECTOR_LOG_SRC:.cpp=.o)
MATRIX_TEST_OBJS = $(MATRIX_OBJS) $(MATRIX_LOG_SRC:.cpp=.o) $(VECTOR_OBJS)

all: app


app: MatrixMain


vector: Matrix_tests_vector


matrix: Matrix_tests_matrix


MatrixMain: $(APP_OBJS) $(VECTOR_OBJS) $(MATRIX_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)


MatrixMain_info: CXXFLAGS += -DGLOBAL_LOG_LEVEL=LogLevel::INFO
MatrixMain_info: MatrixMain


MatrixMain_debug: CXXFLAGS += -DGLOBAL_LOG_LEVEL=LogLevel::DEBUG
MatrixMain_debug: MatrixMain


Matrix_tests_vector: $(VECTOR_TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

Matrix_tests_matrix: $(MATRIX_TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	find . -name "*.o" -delete
	find . -name "*.gcno" -delete
	find . -name "*.gcda" -delete
	find . -name "*.gcov" -delete
	rm -f Matrix_tests* MatrixMain *.out

	
memcheck_matrix:
	valgrind --leak-check=full --track-origins=yes ./Matrix_tests_matrix


memcheck_vector:
	valgrind --leak-check=full --track-origins=yes ./Matrix_tests_vector


memcheck_app:
	valgrind --leak-check=full --track-origins=yes ./MatrixMain