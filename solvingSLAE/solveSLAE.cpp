#include "solveSLAE.h"

std::string solveSLAE(Matrix<int> &A, std::vector<int> &S)
{
	size_t rangA{ A.rang() };
	size_t Xlen = A.cols();
	size_t rangAS;

	//Create Advanced Matrix
	Matrix<int> AS{ A.rows(), A.cols() + 1 };

	for (size_t i{ 0 }; i < A.rows(); ++i)
		for (size_t j{ 0 }; j < A.cols(); ++j)
				AS[i][j] = A[i][j];
	AS.insertCol(AS.cols() - 1, S);

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

std::vector<int> operator+(std::vector<int> &row1, std::vector<int> &row2)
{
	if (row1.size() != row2.size())
		throw(std::out_of_range("Wrong dimention"));

	std::vector<int> res(row1);

	for (size_t i{ 0 }; i < res.size(); ++i)
		res[i] += row2[i];

	return res;
}

std::vector<int> operator*(std::vector<int> &row, int k)
{
	std::vector<int> res(row);

	for (size_t i{ 0 }; i < res.size(); ++i)
		res[i] *= k;

	return res;
}

int GCF(int a, int b)
{
	if (a == 0)
		return b;
	if (b == 0)
		return a;
	if (a == b)
		return a;

	if (a == 1 || b == 1)
		return 1;

	if (a % 2 == 0 && b % 2 == 0)
		return 2 * GCF(a / 2, b / 2);
	if (a % 2 == 0)
		return GCF(a / 2, b);
	if (a % 2 == 0)
		return GCF(a, b / 2);

	if (a > b)
		return GCF((a - b) / 2, b);
	if (a < b)
		return GCF(a, (b - a) / 2);
}

int LCM(int a, int b)
{
	return a * b / GCF(a, b);
}

std::string getOneSolution(Matrix<int> &AS)
{
	return "null";
}

std::string getInfSolution(Matrix<int> &AS, int countFreeVar)
{
	return "null";
}

