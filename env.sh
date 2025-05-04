
# Make
alias mvec="make Matrix_tests_vector"
alias mmat="make Matrix_tests_matrix"
alias mapp="make MatrixMain"

#Run
alias app="./MatrixMain"
alias vec="./Matrix_tests_vector"
alias mat="./Matrix_tests_matrix"

# For cover
alias covvec="gcov -p -o Vector Vector/Vector.cpp"
alias covmat="gcov -p -o Matrix Matrix/SquareMatrix.cpp"
alias covapp="gcov -p -o . main.cpp"

# For leak-check
alias lcmat="make memcheck_matrix"
alias lcvec="make memcheck_vector"
alias lcapp="make memcheck_app"

# For clean
alias mcl="make clean"
