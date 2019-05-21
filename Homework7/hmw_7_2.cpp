//
// hmw_7_2.cpp
//
// by Shawn T. Schwartz
// <shawnschwartz@ucla.edu>
// UID: 504-570-447
//
// PIC10B Winter 2019 - UCLA
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

class Matrix
{
public:
	// nickname for the data type storing size of the vector
	typedef vector<double>::size_type size_type;

	// nickname for vector<double>
	typedef vector<double> Vector;

	// constructors
	Matrix() {}
	Matrix(size_type n, size_type m, double val = 0.0); // n x m matrix
	Matrix(const Vector & v); // matrix n x 1 derived from Vector

	// destructor
	~Matrix() {}

	// operator() for getting Matrix (i,j) value
	double operator()(size_type i, size_type j) const;

	// operator() for setting Matrix (i,j) value
	double & operator()(size_type i, size_type j);

	// operator*:
	Matrix operator*(double c) const; // Matrix*constant
	vector<double> operator*(const vector<double> &v) const; // Matrix*Vector
	Matrix operator*(const Matrix & B) const; // Matrix*Matrix

	// operator+:
	Matrix operator+(const Matrix & B) const; // Matrix + Matrix
	Matrix operator-(const Matrix & B) const; // Matrix - Matrix
	Matrix operator-() const; // -Matrix

	// matrix size getters (2 alternatives):
	pair<size_type, size_type> size() const; // returns std::pair
	void size(size_type & n, size_type & m) const; // size is set in n, m

	// printing the matrix as a table
	/* Here width and prec are formatting parameters used for the input.
	* width is used in cout << setw(bw)
	* prec is used in cout << fixed << setprecision(prec)
	* width=6 and prec=2 are default values
	**/
	void print(unsigned short width = 8, unsigned short prec = 2) const;

	// returns true if the matrix is empty
	bool empty() const;

	// resizing matrix to n x m
	void resize(size_type n, size_type m);

	// needed for overloading << operator which uses print()
	friend ostream & operator<<(ostream & os, const Matrix & A);

private:
	vector<vector<double>> values; //2-d array storage of the matrix
	double** arr = NULL;
	size_type r;
	size_type c;
};

Matrix::Matrix(size_type n, size_type m, double val)
{
	r = n;
	c = m;
	arr = new double*[n];
	for (int i = 0; i < n; ++i)
	{
		arr[i] = new double[m];
	}

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			arr[i][j] = val;
		}
	}
}

Matrix::Matrix(const Vector & v)
{
	r = v.size();
	c = 1;

	arr = new double*[v.size()];
	
	for (int i = 0; i < v.size(); ++i)
	{
		arr[i] = new double[v.size()];
	}

	for (int i = 0; i < v.size(); ++i)
	{
		arr[i][0] = v[i];
	}
}

double Matrix::operator()(size_type i, size_type j) const
{
	return arr[i][j];
}

double & Matrix::operator()(size_type i, size_type j)
{
	return arr[i][j];
}

// Matrix*constant
Matrix Matrix::operator*(double c) const
{
	pair<size_type, size_type> mat_size = this->size();
	Matrix prod(mat_size.first, mat_size.second);

	for (int i = 0; i < mat_size.first; ++i)
	{
		for (int j = 0; j < mat_size.second; ++j)
		{
			prod.arr[i][j] = (arr[i][j]) * c;
		}
	}

	return prod;
}

// Matrix*Vector
Matrix::Vector Matrix::operator*(const vector<double> &v) const
{
	size_type mat_size = v.size();
	Vector prod;
	double tmp_sum = 0;

	for (int i = 0; i < this->size().first; ++i)
	{
		tmp_sum = 0;
		for (int j = 0; j < this->size().second; ++j)
		{
			tmp_sum += (arr[i][j] * v[j]);
		}

		prod.push_back(tmp_sum);
	}
	
	return prod;
}

// Matrix*Matrix
Matrix Matrix::operator*(const Matrix & B) const
{
	Matrix prod(this->size().first, B.size().second);

	for (int i = 0; i < this->size().first; ++i)
	{
		for(int j = 0; j < B.size().second; ++j)
		{
			for (int k = 0; k < this->size().second; ++k)
			{
				prod.arr[i][j] += arr[i][k] * B.arr[k][j];
			}
		}
	}

	return prod;
}

// Matrix+Matrix
Matrix Matrix::operator+(const Matrix & B) const
{
	Matrix sum(this->size().first, this->size().second);

	for (int i = 0; i < sum.size().first; ++i)
	{
		for (int j = 0; j < sum.size().second; ++j)
		{
			sum.arr[i][j] = (arr[i][j]) + (B.arr[i][j]);
		}
	}

	return sum;
}

// Matrix-Matrix
Matrix Matrix::operator-(const Matrix & B) const
{
	Matrix difference(this->size().first, this->size().second);

	for (int i = 0; i < difference.size().first; ++i)
	{
		for (int j = 0; j < difference.size().second; ++j)
		{
			difference.arr[i][j] = (arr[i][j]) - (B.arr[i][j]);
		}
	}

	return difference;
}

// -Matrix
Matrix Matrix::operator-() const
{
	Matrix difference(this->size().first, this->size().second);

	for (int i = 0; i < difference.size().first; ++i)
	{
		for (int j = 0; j < difference.size().second; ++j)
		{
			difference.arr[i][j] = (this->arr[i][j]) - (arr[i][j]);
		}
	}

	return difference;
}

pair<Matrix::size_type, Matrix::size_type> Matrix::size() const
{
	pair<size_type, size_type> cur_size = make_pair(r, c);
	return cur_size;
}

void Matrix::size(size_type & n, size_type & m) const
{
	n = r;
	m = c;
}

bool Matrix::empty() const
{
	if (this->size().first < 1 || this->size().second < 1)
	{
		return true;
	}
	
	else
	{
		return false;
	}
}

void Matrix::print(unsigned short width, unsigned short prec) const
{
	cout << fixed << setprecision(prec);
	pair<size_type, size_type> mat_size = this->size();

	for (int i = 0; i < mat_size.first; ++i)
	{
		for (int j = 0; j < mat_size.second; ++j)
		{
			cout << setw(width) << arr[i][j];
		}
		cout << endl;
	}
}

ostream & operator<<(ostream & os, const Matrix & A)
{
	A.print();
	return os;
}

// Get file contents line by line
vector<double> getFileLines(ifstream & in)
{
	double file_contents;
	vector<double> lines;

	while (in >> file_contents)
	{
		lines.push_back(file_contents);
	}

	return lines;
}

// Draw ---- line
void drawLine()
{
	cout << "------------------------" << endl;
}

// Draw ---- line & title
void drawTitle(string title)
{
	drawLine();
	cout << title << endl;
	drawLine();
}

int main()
{
	typedef Matrix::Vector Vector;
	
	char cont; // for looping user continue

	do
	{
		string matrix_one_filename = "";
		string matrix_two_filename = "";

		// Read in matrix A values & push into object of matrix class
		cout << "Enter the file name containing matrix A values: ";
		getline(cin, matrix_one_filename);
		ifstream fstream;
		fstream.open(matrix_one_filename.c_str(), ifstream::in);
		Vector mat_A_vals = getFileLines(fstream);
		fstream.close();
		Matrix A(3,3);

		int counter = 0;
		while (counter < mat_A_vals.size())
		{
			for (int i = 0; i < A.size().first; ++i)
			{
				for (int j = 0; j < A.size().second; ++j)
				{
					A(i, j) = mat_A_vals[counter];
					counter++;
				}
			}
		}
		
		// Read in matrix B values & push into object of matrix class
		cout << "Enter the file name containing matrix B values: ";
		getline(cin, matrix_two_filename);
		fstream.open(matrix_two_filename.c_str(), ifstream::in);
		Vector mat_B_vals = getFileLines(fstream);
		fstream.close();
		Matrix B(3,3);

		counter = 0;
		while (counter < mat_B_vals.size())
		{
			for (int i = 0; i < B.size().first; ++i)
			{
				for (int j = 0; j < B.size().second; ++j)
				{
					B(i, j) = mat_B_vals[counter];
					counter++;
				}
			}
		}

		// Print Matrix A & B Values
		cout << "\nPrinting A values:" << endl;
		A.print();
		
		cout << "\nPrinting B values:" << endl;
		B.print();

		cout << "\n";

		drawTitle("Computation of S=A+B");
		cout << "Printing S values:" << endl;
		Matrix S = A + B;
		S.print();
		cout << "\n";

		drawTitle("Computation of D=A-B");
		cout << "Printing D values:" << endl;
		Matrix D = A - B;
		D.print();
		cout << "\n";

		drawTitle("Computation of P=A*B");
		cout << "Printing P values:" << endl;
		Matrix P = A * B;
		P.print();
		cout << "\n";

		drawTitle("Computation of M=A*c+B*d");
		cout << "\nEnter two floating point numbers c and d: ";
		double c, d;
		cin >> c >> d;
		Matrix M = A * c + B * d;
		cout << "\nPrinting M values:" << endl;
		M.print();
		cout << "\n\n";

		
		drawTitle("Computation of b=A*x");
		cout << "\nEnter components of Vector x of length " << A.size().first << ": ";
		Vector x;
		double tmp_val;
		for (int i = 0; i < A.size().first; ++i)
		{
			cin >> tmp_val;
			x.push_back(tmp_val);
		}

		Vector bvec = A * x;
		Matrix b(bvec);

		cout << "\nPrinting b values:" << endl;
		b.print();
		
		cout << "\n";

		cout << "Continue? (y/n) ";
		cin >> cont;
		cin.ignore();
		if (cont == 'y' || cont == 'Y')
		{
			cout << endl;
		}
	} while (cont == 'y' || cont == 'Y');
	
	return 0;
}