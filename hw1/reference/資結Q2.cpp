#include<iostream>
using namespace std;

class SparseMatrix;
class MatrixTerm {
	friend SparseMatrix;
	friend ostream& operator<<(ostream& os, SparseMatrix& ma);
	friend istream& operator>>(istream& is, SparseMatrix& ma);
private:
	int row, col, value;
};

class SparseMatrix
{
public:
    SparseMatrix(int r, int c, int t);  
    SparseMatrix FastTranspose();
    SparseMatrix Add(SparseMatrix b);
    SparseMatrix Multiply(SparseMatrix b);
    void ChangeSize1D(const int newSize);
    void StoreSum(const int sum, const int r, const int c);
    friend ostream& operator<<(ostream& os, SparseMatrix& ma);
	friend istream& operator>>(istream& is, SparseMatrix& ma);
private:
	int rows, cols, terms, capacity;
	MatrixTerm * smArray;
};

SparseMatrix::SparseMatrix(int r, int c, int t)
{
	capacity = 10;
    terms = t;
    rows = r;
    cols = c;
    smArray = new MatrixTerm[capacity];
}
SparseMatrix SparseMatrix::FastTranspose()
{
	SparseMatrix b(cols , rows , terms);
	if (terms > 0) {
		int *rowSize = new int[cols];
		int *rowStart = new int[cols];
		fill(rowSize, rowSize + cols, 0);
		for (int i = 0 ; i < terms ; i ++)
		rowSize[smArray[i].col]++;
		rowStart[0] = 0;
		for (int i = 1 ; i < cols ; i++)
			rowStart[i] = rowStart[i-1] + rowSize[i-1];
		for (int i = 0 ; i < terms ; i++){
			int j = rowStart[smArray[i].col];
			b.smArray[j].row= smArray[i].col;
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
	SparseMatrix c(rows, cols, 0);
	int currIndexA = 0, currIndexB = 0;
	int sum;
	
	if (rows != b.rows || cols != b.cols)
		throw "Incompatible matrices";
	while(currIndexA < terms && currIndexB < b.terms){
		sum = 0;
		if(smArray[currIndexA].row == b.smArray[currIndexB].row){
			if(smArray[currIndexA].col < b.smArray[currIndexB].col){
				c.StoreSum(smArray[currIndexA].value,smArray[currIndexA].row,smArray[currIndexA].col);
				currIndexA++;
			}		
			else if(smArray[currIndexA].col > b.smArray[currIndexB].col){
				c.StoreSum(b.smArray[currIndexB].value,b.smArray[currIndexB].row,b.smArray[currIndexB].col);
				currIndexB++;
			}
			else{
				sum = smArray[currIndexA].value + b.smArray[currIndexB].value;
				c.StoreSum(sum,smArray[currIndexA].row,smArray[currIndexA].col);
				currIndexA++;
				currIndexB++;
			}
		}
		else if(smArray[currIndexA].row < b.smArray[currIndexB].row){
			c.StoreSum(smArray[currIndexA].value,smArray[currIndexA].row,smArray[currIndexA].col);
			currIndexA++;
		}
		else{
			c.StoreSum(b.smArray[currIndexB].value,b.smArray[currIndexB].row,b.smArray[currIndexB].col);
			currIndexB++;
		}		
	}
	while(currIndexA < terms){
		c.StoreSum(smArray[currIndexA].value,smArray[currIndexA].row,smArray[currIndexA].col);
		currIndexA++;
	}
	while(currIndexB < b.terms){
		c.StoreSum(b.smArray[currIndexB].value,b.smArray[currIndexB].row,b.smArray[currIndexB].col);
		currIndexB++;
	}
	return c;
}

SparseMatrix SparseMatrix::Multiply(SparseMatrix b)
{
	if (cols != b.rows)
		throw "Incompatible matrices";
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
		while (currColIndex <= b.terms){
			if (smArray[currRowIndex].row != currRowA) {
				d.StoreSum(sum,currRowA,currColB);
				sum = 0;
				currRowIndex = currRowBegin;
				while (bXpose.smArray[currColIndex].row == currColB)
					currColIndex++;
				currColB = bXpose.smArray[currColIndex].row;
			} else if (bXpose.smArray[currColIndex].row != currColB) {
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
		throw "New size must be >= number of terms";
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
			ChangeSize1D(2*capacity);
		smArray[terms].row = r;
		smArray[terms].col = c;
		smArray[terms++].value = sum;
	}
}

ostream& operator<<(ostream& os, SparseMatrix& ma)
{
	if(ma.terms == 0) os << "{";
	else{
		os << "{(" << ma.smArray[0].row << "," << ma.smArray[0].col;
		os << "," << ma.smArray[0].value << ")";
		if(ma.terms > 1){
			for(int i = 1; i < ma.terms; i++){
				os << ",(" << ma.smArray[i].row << "," << ma.smArray[i].col;
				os << "," << ma.smArray[i].value << ")";
			}
		}
	}
	os << "}" << endl;
	return os;	
}
istream& operator>>(istream& is, SparseMatrix& ma)
{
    int row, col, value;
    char temp;
    
    cout << "How many rows are there in total : ";
    is >> ma.rows; 
    cout << "How many cols are there in total : ";
    is >> ma.cols;
    cout << "Please input in the form {(row,col,value)} : ";
	getchar();
	while ((temp = getchar()) != '}') {
        getchar();
        is >> row >> temp >> col >> temp >> value;
        getchar();
        ma.StoreSum(value, row, col);
    }
    getchar();
    return is;
}

int main(void)
{
	SparseMatrix a(0, 0, 0);
	SparseMatrix b(0, 0, 0);
	SparseMatrix c(0, 0, 0);
	
	cin >> a;
	cout << "matrix1 = " << a;
	cin >> b;
    cout << "matrix2 = " << b;
    c = a.FastTranspose();
    cout << "the transpose of matrix1 is " << c;
    c = b.FastTranspose();
    cout << "the transpose of matrix2 is " << c;
    c = a.Add(b);
    cout << "matrix1 + matrix2 = " << c;
    c = a.Multiply(b);
    cout << "matrix1 * matrix2 = " << c;

	return 0;
}
