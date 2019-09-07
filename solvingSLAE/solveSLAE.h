#pragma once

#include "matrix-library-cpp/Matrix.h"
#include <string>
#include <sstream>

//This function get 2 matrix: coefficient matrix; free member matrix. And return string with solution of SLAE.
std::string solveSLAE(Matrix<int> &A, std::vector<int> &S);

//This function add two rows
std::vector<int> operator+(std::vector<int> row1, std::vector<int> row2);

//This function multiply every element in row to number
std::vector<int> operator*(std::vector<int> &row, int k);

std::string toString(int value);

int GCF(int a, int b);
int LCM(int a, int b);

//These functions return a solution depending on the number of solutions.
std::string getOneSolution(Matrix<int> &AS);
std::string getInfSolution(Matrix<int> &AS, int countFreeVar);