#include "Matrices.h"

using namespace std;

namespace Matrices {

	Matrix::Matrix(int _rows, int _cols)
	{
		a.resize(_rows, vector<double>(_cols));
		rows = _rows;
		cols = _cols;
		for (int i = 0; i < _rows; i++) {
			for (int j = 0; j < _cols; j++) {
				a[i][j] = 0.0;
			}
		}
	}
	double& Matrix::operator()(int i, int j) {
		//return a[i][j];
		return a.at(i).at(j);
	}
	const double& Matrix::operator()(int i, int j) const
	{
		return a.at(i).at(j);
	}
	///Add each corresponding element.
	///usage:  c = a + b;
	Matrix operator+(const Matrix & a, const Matrix & b)
	{
		Matrix c(a.getRows(), a.getCols());
		if (a.getRows() != b.getRows() || a.getCols() != b.getCols()) {
			throw runtime_error("Error: dimensions must agree");

		}
		else {
			for (int i = 0; i < a.getRows(); i++) {
				for (int j = 0; j < a.getCols(); j++) {
					c(i, j) = a(i, j) + b(i, j);
				}
			}
		}
		return c;
	}

	///Matrix multiply.  See description.
	///usage:  c = a * b;
	Matrix operator*(const Matrix & a, const Matrix & b)
	{
		double sum = 0.0;
		Matrix c(a.getRows(), b.getCols());
		if (a.getCols() != b.getRows()) {
			throw runtime_error("Error: dimensions must agree");
		}
		else {
			for (int k = 0; k < b.getCols(); k++) {
				for (int i = 0; i < a.getRows(); i++) {
					for (int j = 0; j < a.getCols(); j++) {
						sum = sum + a(i, j) * b(j, k);
					}
					c(i, k) = sum;
					sum = 0.0;
				}
			}
		}
		return c;
	}

	///Matrix comparison.  See description.
	///usage:  a == b
	bool operator==(const Matrix & a, const Matrix & b)
	{
		if (a.getRows() != b.getRows() || a.getCols() != b.getCols()) {
			return false;
		}
		for (int i = 0; i < a.getRows(); i++) {
			for (int j = 0; j < a.getCols(); j++) {
				if (abs(a(i, j) - b(i, j)) > 0.001) {
					return false;
				}
			}
		}
		return true;
	}

	///Matrix comparison.  See description.
	///usage:  a != b
	bool operator!=(const Matrix & a, const Matrix & b)
	{
		if (a.getRows() != b.getRows() || a.getCols() != b.getCols()) {
			return true;
		}
		for (int i = 0; i < a.getRows(); i++) {
			for (int j = 0; j < a.getCols(); j++) {
				if (abs(a(i, j) - b(i, j)) > 0.001) {
					return true; 
				}
			}
		}
		return false;
	}

	///Output matrix.
	///Separate columns by ' ' and rows by '\n'
	ostream & operator<<(ostream & os, const Matrix & a)
	{
		for (int i = 0; i < a.getRows(); i++) {
			for (int j = 0; j < a.getCols(); j++) {
				os << setw(10) << a(i, j) << " ";
			}
			os << "\n";
		}
		return os;
	}
}
