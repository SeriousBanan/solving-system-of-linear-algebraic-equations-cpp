#pragma once

#include "../matrix-library-cpp/Matrix.h"
#include <string>

//This function get 2 matrix: coefficient matrix; free member matrix. And return string with solution of SLAE
std::string solveSLAE(Matrix<int> &A, Matrix<int> &S);