#include <iostream>
using namespace std;


// Custom exception classes for specific errors
class IncompatibleMatricesException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Incompatible matrices for operation.\n";
    }
};

class SparseMatrix;

class MatrixTerm {
    friend SparseMatrix;
    friend ostream& operator<<(ostream& os, SparseMatrix& mat);
	friend istream& operator>>(istream& is, SparseMatrix& mat);
private:
    int row, col, value;
};

class SparseMatrix {
public:
    SparseMatrix(int r, int c, int t);
    SparseMatrix Transpose();
    SparseMatrix FastTranspose();
    SparseMatrix Add(SparseMatrix b);
    SparseMatrix Multiply(SparseMatrix b);
    void ChangeSize1D(const int newSize);
    void StoreSum(const int sum, const int r, const int c);
    friend ostream& operator<<(ostream& os, SparseMatrix& mat);
	friend istream& operator>>(istream& is, SparseMatrix& mat);
private:
    int rows, cols, terms, capacity;
    MatrixTerm *smArray;
};

SparseMatrix::SparseMatrix(int r = 0, int c = 0, int t = 0)
{
    capacity = 10;
    rows = r;
    cols = c;
    terms = t;
    smArray = new MatrixTerm[capacity];
}

SparseMatrix SparseMatrix::Transpose()
{
    SparseMatrix b(cols, rows, terms);
    if (terms > 0) {
        int currentB = 0;
        for (int c = 0; c < cols; c++)
            for (int i  = 0; i < terms; i++)
                if (smArray[i].col == c) {
                    b.smArray[currentB].row = c;
                    b.smArray[currentB].col = smArray[i].row;
                    b.smArray[currentB].value = smArray[i].value;
                    currentB++;
                }
    }

    return b;
}

SparseMatrix SparseMatrix::FastTranspose()
{
    SparseMatrix b(cols, rows, terms);
    if (terms > 0) {
        int *rowSize = new int[cols];
        int *rowStart = new int[cols];

        fill(rowSize, rowSize + cols, 0);
        for (int i = 0; i < terms; i++)
            rowSize[smArray[i].col]++;

        rowStart[0] = 0;
        for (int i = 1; i < cols; i++)
            rowStart[i] = rowStart[i - 1] + rowSize[i - 1];

        for (int i = 0; i < terms; i++) {
            int j = rowStart[smArray[i].col];
            b.smArray[j].row = smArray[i].col;
            b.smArray[j].col = smArray[i].row;
            b.smArray[j].value = smArray[i].value;
            rowStart[smArray[i].col]++;
        }

        delete [] rowSize;
        delete [] rowStart;
    }
    return b;
}

SparseMatrix SparseMatrix::Add(SparseMatrix b)
{
    // Incompatible matrices
    if (rows != b.rows || cols != b.cols)
        throw IncompatibleMatricesException();

    SparseMatrix c(rows, cols, 0);
    int currRowA = 0, currRowB = 0;
    int sum;

    while (currRowA < terms && currRowB < b.terms) {
        sum = 0;
        if (smArray[currRowA].row == b.smArray[currRowB].row) {
            if (smArray[currRowA].col < b.smArray[currRowB].col) {
                c.StoreSum(smArray[currRowA].value, smArray[currRowA].row, smArray[currRowA].col);
                currRowA++;
            }
            else if (smArray[currRowA].col > b.smArray[currRowB].col) {
                c.StoreSum(b.smArray[currRowB].value, b.smArray[currRowB].row, b.smArray[currRowB].col);
                currRowB++;
            }
            else { // same row and col
                sum = smArray[currRowA].value + b.smArray[currRowB].value;
                c.StoreSum(sum, smArray[currRowA].row, smArray[currRowA].col);
                currRowA++;
                currRowB++;
            }
        }
        else if (smArray[currRowA].row < b.smArray[currRowB].row) {
            c.StoreSum(smArray[currRowA].value, smArray[currRowA].row, smArray[currRowA].col);
            currRowA++;
        }
        else {
            c.StoreSum(b.smArray[currRowB].value, b.smArray[currRowB].row, b.smArray[currRowB].col);
            currRowB++;
        }
    }

    // remaining terms in A
    while (currRowA < terms) {
        c.StoreSum(smArray[currRowA].value, smArray[currRowA].row, smArray[currRowA].col);
        currRowA++;
    }
    // remaining terms in B
    while (currRowB < b.terms) {
        c.StoreSum(b.smArray[currRowB].value, b.smArray[currRowB].row, b.smArray[currRowB].col);
        currRowB++;
    }

    return c;
}

SparseMatrix SparseMatrix::Multiply(SparseMatrix b)
{
    // Incompatible matrices
	if (cols != b.rows)
        throw IncompatibleMatricesException();

	SparseMatrix bXpose = b.FastTranspose();
	SparseMatrix d(rows, b.cols, 0);
	int currRowIndex = 0,
	currRowBegin = 0,
	currRowA = smArray[0].row;

	if (terms == capacity)
		ChangeSize1D(terms + 1);
	bXpose.ChangeSize1D(bXpose.terms + 1);
	smArray[terms].row = rows;
	bXpose.smArray[b.terms].row = b.cols;
	bXpose.smArray[b.terms].col = -1;

	int sum = 0;
	while (currRowIndex < terms) {
		int currColB = bXpose.smArray[0].row;
		int currColIndex = 0;
		while (currColIndex <= b.terms) {
			if (smArray[currRowIndex].row != currRowA) {
				d.StoreSum(sum,currRowA,currColB);
				sum = 0;
				currRowIndex = currRowBegin;
				while (bXpose.smArray[currColIndex].row == currColB)
					currColIndex++;
				currColB = bXpose.smArray[currColIndex].row;
			}
            else if (bXpose.smArray[currColIndex].row != currColB) {
				d.StoreSum(sum,currRowA,currColB);
				sum = 0;
				currRowIndex = currRowBegin;
				currColB = bXpose.smArray[currColIndex].row;
			}
			else {
				if (smArray[currRowIndex].col < bXpose.smArray[currColIndex].col)
					currRowIndex++;
				else if (smArray[currRowIndex].col == bXpose.smArray[currColIndex].col) {
					sum += smArray[currRowIndex].value * bXpose.smArray[currColIndex].value;
					currRowIndex++;
					currColIndex++;
				}
				else
					currColIndex++;
			}
		}
		while (smArray[currRowIndex].row == currRowA)
			currRowIndex++;
		currRowBegin = currRowIndex;
		currRowA = smArray[currRowIndex].row;
	}
	return d;
}

void SparseMatrix::ChangeSize1D(const int newSize)
{
    if (newSize < terms)
        throw "New size must be >= number fo terms.";

    MatrixTerm *temp = new MatrixTerm[newSize];

    copy(smArray, smArray + terms, temp);
    delete [] smArray;

    smArray = temp;
    capacity = newSize;
}

void SparseMatrix::StoreSum(const int sum, const int r, const int c)
{
    if (sum != 0) {
        if (terms == capacity)
            ChangeSize1D(2 * capacity);
        smArray[terms].row = r;
        smArray[terms].col = c;
        smArray[terms++].value = sum;
    }
}

ostream& operator<<(ostream& os, SparseMatrix& mat) // not mine
{
	if (mat.terms == 0) os << "{";
	else {
		os << "{(" << mat.smArray[0].row << "," << mat.smArray[0].col;
		os << "," << mat.smArray[0].value << ")";
		if (mat.terms > 1) {
			for (int i = 1; i < mat.terms; i++) {
				os << ",(" << mat.smArray[i].row << "," << mat.smArray[i].col;
				os << "," << mat.smArray[i].value << ")";
			}
		}
	}
	os << "}" << endl;
	return os;
}

istream& operator>>(istream& is, SparseMatrix& mat)
{
    int row, col, value;
    char temp;

    cout << "Number of rows: ";
    is >> mat.rows;

    cout << "Number of cols: ";
    is >> mat.cols;

    cout << "Please input in the form {(row,col,value),(row,col,value),...,(row,col,value)} : ";
    getchar();
    while ((temp = getchar()) != '}') {
        getchar();
        is >> row >> temp >> col >> temp >> value;
        getchar();
        mat.StoreSum(value, row, col);
    }
    getchar();

    return is;
}


int main()
{
    SparseMatrix a, b, c, d;

    cout << "Input matrix a: " << endl; // 4x3, 4 terms
    cin >> a;
    cout << "Sparse Matrix a: " << endl << a << endl;

    cout << "Input matrix b: " << endl; // 4x3, 5 terms
    cin >> b;
    cout << "Sparse Matrix b: " << endl << b << endl;

    cout << "Input matrix c: " << endl; // 3x3, 4 terms
    cin >> c;
    cout << "Sparse Matrix c: " << endl << c << endl;


    d = a.Transpose();
    cout << "Transpose of a: " << d << endl;
    d = b.Transpose();
    cout << "Transpose of b: " << d << endl;
    d = c.Transpose();
    cout << "Transpose of c: " << d << endl;

    d = a.FastTranspose();
    cout << "Fast Transpose of a: " << d << endl;
    d = b.FastTranspose();
    cout << "Fast Transpose of b: " << d << endl;
    d = c.FastTranspose();
    cout << "Fast Transpose of c: " << d << endl;

    // Add
    d = a.Add(b);
    cout << "Add a and b: " << d << endl;
    try {
        d = a.Add(c);
        cout << "Add a and c: " << d << endl; // incompatible matrices
    } catch (const IncompatibleMatricesException& e) {
        cout << "Add a and c: Error: " << e.what() << endl;
    } catch (const exception& e) {
        cout << "Add a and c: Error: " << e.what() << endl;
    }
    try {
        d = b.Add(c);
        cout << "Add b and c: " << d << endl; // incompatible matrices
    } catch (const IncompatibleMatricesException& e) {
        cout << "Add b and c: Error: " << e.what() << endl;
    } catch (const exception& e) {
        cout << "Add b and c: Error: " << e.what() << endl;
    }

    // Multiply
    try {
        d = a.Multiply(b);
        cout << "Multiply a and b: " << d << endl; // incompatible matrices
    } catch (const IncompatibleMatricesException& e) {
        cout << "Multiply a and b: Error: " << e.what() << endl;
    } catch (const exception& e) {
        cout << "Multiply a and b: Error: " << e.what() << endl;
    }
    d = a.Multiply(c);
    cout << "Multiply a and c: " << d << endl;
    d = b.Multiply(c);
    cout << "Multiply b and c: " << d << endl;

    return 0;
    // use >> to build sm object a(4x3, 4 terms), b(4x3, 5 terms), c(3x3, 4 terms)
    // demo  <<
    // demo  << results of Transpose, Fast Transpose, Add, Mul
}



