#include "solveSLAE.h"

std::string getOneSolution(Matrix<int> &AS);
std::string getInfSolution(Matrix<int> &AS, int countFreeVar);

std::string solveSLAE(Matrix<int> &A, std::vector<int> &S)
{
	int rangA{ A.rang() };
	int Xlen = A.cols;
	int rangAS;

	//Create Advanced Matrix
	Matrix<int> AS{ A.rows(), A.cols() + 1 };

	for (int i{ 0 }; i < A.rows(); ++i)
		for (int j{ 0 }; j < A.cols(); ++j)
				AS[i][j] = A[i][j];
	AS.insertCol(AS.cols - 1, S);

	rangAS = AS.rang();

	//Check existence of solution
	if (rangA != rangAS)
		return "The system haven't got solution";

	//Check count of solution
	if (rangA == Xlen)
		return getOneSolution(AS);
	else
		return getInfSolution(AS, Xlen - rangA);
}