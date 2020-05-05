#include <iostream>
#include <vector>
#include <exception>

struct DivisionByZeroException: public std::exception
{
	char const* what() const throw()
	{
		return "The denominator was equal to zero.\nRemember that the value of B0 (0,0) cannot be equal to zero.";
	}
};

struct NonPositiveSizeException : public std::exception
{
	char const* what() const throw()
	{
		return "The size of the matrix must be positive.";
	}
};

using vec_doub = std::vector<double>;
using std::cout;
using std::cin;
using std::endl;

void input(vec_doub& vec, int end_index, int start_index = 0)
{
	for (int i = start_index; i < end_index; i++)
	{
		double d;
		cout << i << ": ";
		cin >> d;
		vec.push_back(d);
	}
}

// this function initalizes the array used to print user's input correctly
void initialize_array(double** arr, vec_doub const& A, vec_doub const& B, 
	vec_doub const& C, int size)
{	
	for (int i = 0; i < size; i++)
	{
		arr[i][i] = B[i];
		if (i > 0)
			arr[i][i - 1] = A[i];
		if (i < size - 1)
			arr[i][i + 1] = C[i];
	}
}

// this function prints user's input (the equation)
void print_eq(double** arr, vec_doub const& F, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			cout << arr[i][j] << "\t";
		}
		cout << "\t" << "u" << i << "\t\t" << F[i] << endl;
	}
}

// this is the function where the equation is solved
void tridiag_eq(vec_doub& A, vec_doub& B, vec_doub& C, vec_doub& F, vec_doub& u)
{
	double denom = 0.0;
	int n = u.size();
	vec_doub newc(n, 0.0);

	denom = B[0];
	u[0] = F[0] / denom;

	if (denom == 0.0)
		throw DivisionByZeroException{};

	// forward substitution
	for (int i = 1; i < n; i++)
	{
		newc[i] = C[i - 1] / denom;
		denom = B[i] - A[i] * newc[i];

		if (denom == 0.0)
			throw DivisionByZeroException{};

		u[i] = (F[i] - A[i] * u[i - 1]) / denom;
	}

	// back substitution
	for (int i = n - 2; i >= 0; i--)
	{
		u[i] -= newc[i + 1] * u[i + 1];
	}
}

int main()
{
	try
	{
		cout << "After each entered value press Enter, please." << endl;
		int size;
		cout << "Size of the matrix: ";
		cin >> size;
		if (size <= 0)
			throw NonPositiveSizeException{};

		vec_doub A;
		vec_doub B;
		vec_doub C;
		vec_doub F;
		vec_doub u(size, 0.0);

		cout << "Vector B (diagonal):" << endl;
		input(B, size);

		A.push_back(0.0);
		cout << "Vector A (below diagonal):" << endl;
		input(A, size, 1);

		cout << "Vector C (above diagonal):" << endl;
		input(C, size - 1);
		C.push_back(0.0);

		cout << "Vector F:" << endl;
		input(F, size);

		double** arr = new double* [size] { 0 };
		for (int i = 0; i < size; i++)
			arr[i] = new double[size] { 0 };

		initialize_array(arr, A, B, C, size);

		cout << endl << "You entered:" << endl;
		print_eq(arr, F, size);

		for (int i = 0; i < size; i++)
			delete[] arr[i];
		delete[] arr;

		tridiag_eq(A, B, C, F, u);

		cout << endl << "Results (vector u): ";
		for (double d : u)
			cout << d << " ";
	}
	catch (DivisionByZeroException const& ex)
	{
		cout << endl << ex.what();
	}
	catch (NonPositiveSizeException const& ex)
	{
		cout << endl << ex.what();
	}
}