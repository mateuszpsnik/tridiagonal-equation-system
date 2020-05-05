#include <iostream>
#include <vector>
#include <exception>

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

void print_eq(double** arr, vec_doub const& F, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			cout << arr[i][j] << " ";
		}
		cout << "\t" << "u" << i << "\t" << F[i] << endl;
	}
}

int main()
{
	vec_doub A;
	vec_doub B;
	vec_doub C;
	vec_doub F;
	vec_doub u;

	int size;
	cout << "Size of the matrix: ";
	cin >> size;

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

	double** arr = new double* [size]{ 0 };
	for (int i = 0; i < size; i++)
		arr[i] = new double[size]{ 0 };

	initialize_array(arr, A, B, C, size);
	print_eq(arr, F, size);

	for (int i = 0; i < size; i++)
		delete[] arr[i];
	delete[] arr;
}