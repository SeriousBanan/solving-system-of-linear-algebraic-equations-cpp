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

std::vector<int> operator+(std::vector<int> row1, std::vector<int> row2)
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

std::string toString(int value)
{
	std::stringstream ss;
	ss << value;
	return ss.str();
}

int GCF(int a, int b)
{
	if (a < 0)
		a = -a;
	if (b < 0)
		b = -b;

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
	if (b % 2 == 0)
		return GCF(a, b / 2);

	if (a > b)
		return GCF((a - b) / 2, b);
	if (a < b)
		return GCF(a, (b - a) / 2);
}

int LCM(int a, int b)
{
	if (a < 0)
		a = -a;
	if (b < 0)
		b = -b;

	return a * b / GCF(a, b);
}

std::string getOneSolution(Matrix<int> &AS)
{
	for (size_t i{ 0 }; i < AS.cols() - 1; ++i)
	{
		//If the coefficient on the main diagonal equal zero change rows.
		size_t swapId{ i + 1 };
		while (AS[i][i] == 0 && swapId < AS.rows())
			AS.changeRows(i, swapId++);

		for (size_t j{ 0 }; j < AS.rows(); ++j)
		{
			if (j == i)
				continue;
			if (AS[j][i] == 0)
				continue;

			int lcm{ LCM(AS[j][i], AS[i][i]) };
			AS[j] = AS[j] * (lcm / AS[j][i]) + AS[i] * -(lcm / AS[i][i]);
		}
	}

	for (size_t i{ 0 }; i < AS.cols() - 1; ++i)
	{
		if (AS[i][i] < 0)
		{
			AS[i][i] = -AS[i][i];
			AS[i][AS.cols() - 1] = -AS[i][AS.cols() - 1];
		}

		int gcf{ GCF(AS[i][i], AS[i][AS.cols() - 1]) };
		AS[i][i] /= gcf;
		AS[i][AS.cols() - 1] /= gcf;
	}

	std::string res{ "" };
	for (size_t i{ 0 }; i < AS.cols() - 1; ++i)
	{
		res += "X" + toString(i + 1) + " = " + toString(AS[i][AS.cols() - 1]);
		if (AS[i][i] != 1 && AS[i][AS.cols() - 1] != 0)
			res += " / " + toString(AS[i][i]);
		res += '\n';
	}

	return res;
}

std::string getInfSolution(Matrix<int> &AS, int countIndepVar)
{
	//Create and fill array with indexes of independent variables
	std::vector<size_t> indepVar(countIndepVar);
	for (size_t i{ 0 }; i < indepVar.size(); ++i)
	{
		indepVar[i] = AS.cols() - 1 - countIndepVar + i;
	}


	for (size_t mainCol{ 0 }, mainRow{ 0 }; mainCol < AS.cols() - 1; ++mainCol)
	{
		//If it's column with independed variable we don't make enything
		if (std::find(indepVar.begin(), indepVar.end(), mainCol) != indepVar.end())
			continue;

		//If the coefficient on the main diagonal equal zero change rows.
		size_t swapId = mainRow + 1;
		while (AS[mainRow][mainCol] == 0 && swapId < AS.rows())
			AS.changeRows(mainRow, swapId++);

		//If not swapped we change independed variables
		if (AS[mainRow][mainCol] == 0 && swapId == AS.rows())
		{
			for (size_t i{ 0 }; i < indepVar.size(); ++i)
			{
				if (indepVar[i] > mainCol)
					indepVar[i] = mainCol;
				break;
			}
			continue;
		}

		for (size_t i{ 0 }; i < AS.rows(); ++i)
		{
			if (i == mainRow)
				continue;
			if (AS[i][mainCol] == 0)
				continue;

			int lcm{ LCM(AS[i][mainCol], AS[mainRow][mainCol]) };
			AS[i] = (AS[i] * (lcm / AS[i][mainCol])) + (AS[mainRow] * -(lcm / AS[mainRow][mainCol]));
		}
		++mainRow;
	}

	for (size_t mainCol{ 0 }, mainRow{ 0 }; mainCol < AS.cols() - 1; ++mainCol)
	{
		//If it's column with independed variable we don't make enything
		if (std::find(indepVar.begin(), indepVar.end(), mainCol) != indepVar.end())
			continue;

		if (AS[mainRow][mainCol] < 0)
			for (size_t i{ 0 }; i < AS.cols(); ++i)
			{
				AS[mainRow][i] = -AS[mainRow][i];
			}

		++mainRow;
	}

	std::string res{ "" };
	for (size_t mainCol{ 0 }, mainRow{ 0 }; mainCol < AS.cols() - 1; ++mainCol)
	{
		//If it's column with independed variable we don't make enything
		if (std::find(indepVar.begin(), indepVar.end(), mainCol) != indepVar.end())
		{
			res += "X" + toString(mainCol + 1) + " = " + "X" + toString(mainCol + 1) + '\n';
			continue;
		}

		res += "X" + toString(mainCol + 1) + " = "; 
		if (AS[mainRow][AS.cols() - 1] != 0)
		{
			if (AS[mainRow][AS.cols() - 1] < 0)
			{
				res += "- ";
				AS[mainRow][AS.cols() - 1] = -AS[mainRow][AS.cols() - 1];
			}

			int gcf{ GCF(AS[mainRow][mainCol], AS[mainRow][AS.cols() - 1]) };

			res += toString(AS[mainRow][AS.cols() - 1] / gcf);
			if (AS[mainRow][mainCol] / gcf != 1)
				res += " / " + toString(AS[mainRow][mainCol] / gcf);
		}
		for (size_t i{ 0 }; i < indepVar.size(); ++i)
		{
			if (AS[mainRow][indepVar[i]] != 0)
			{
				if (-AS[mainRow][indepVar[i]] > 0 && res.at(res.length() - 2) != '=')
					res += " + ";
				else if (-AS[mainRow][indepVar[i]] < 0)
				{
					if (res.at(res.length() - 2) != '=')
						res += ' ';
					res += "- ";
					AS[mainRow][indepVar[i]] = -AS[mainRow][indepVar[i]];
				}

				int gcf{ GCF(AS[mainRow][mainCol], AS[mainRow][indepVar[i]]) };

				if (AS[mainRow][mainCol] / gcf != 1 || -AS[mainRow][indepVar[i]] / gcf != 1)
				{
					res += toString(-AS[mainRow][indepVar[i]] / gcf);
					if (AS[mainRow][mainCol] / gcf != 1)
						res += " / " + toString(AS[mainRow][mainCol] / gcf);
					res += " * ";
				}
				res += "X" + toString(indepVar[i] + 1);
			}
		}
		if (res.at(res.length() - 2) == '=')
			res += '0';
		res += '\n';

		++mainRow;
	}

	return res;
}

