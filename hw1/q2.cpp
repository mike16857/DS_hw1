#include <iostream>
using namespace std;


class SparseMatrix;

class MatrixTerm {
    friend SparseMatrix;
    friend ostream& operator<<(ostream& os, SparseMatrix& ma);
	friend istream& operator>>(istream& is, SparseMatrix& ma);
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
    friend ostream& operator<<(ostream& os, SparseMatrix& ma);
	friend istream& operator>>(istream& is, SparseMatrix& ma);
private:
    int rows, cols, terms, capacity;
    MatrixTerm *smArray;
};

SparseMatrix::SparseMatrix(int r, int c, int t)
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

}

SparseMatrix SparseMatrix::Multiply(SparseMatrix b)
{
    if (cols != b.rows)
        throw "Incompatible matrices.";

    SparseMatrix bXpose = b.FastTranspose();
    SparseMatrix d(rows, b.cols, 0);
    int currRowIndex = 0;
    int currRowBegin = 0;
    int currRowA = smArray[0].row;

    if (terms = capacity)
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
                d.StoreSum(sum, currRowA, currColB);
                sum = 0;
                currRowIndex = currRowBegin;

                while (bXpose.smArray[currColIndex].row = currColB)
                    currColIndex++;
                
                currColB = bXpose.smArray[currColIndex].row;
            }
            else if (bXpose.smArray[currColIndex].row != currColB) {
                d.StoreSum(sum, currRowA, currColB);
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
        smArray[terms].value = sum;
    }
}

ostream& operator<<(ostream& os, SparseMatrix& ma)
{

}

istream& operator>>(istream& is, SparseMatrix& ma)
{

}


int main()
{

}



