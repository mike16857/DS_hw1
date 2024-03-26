#include <iostream>
using namespace std;


class SparseMatrix;

class MatrixTerm {
  friend SparseMatrix;
  private:
    int row, col, value;
};

class SparseMatrix
{ // 三元組，<列，行，值>，的集合，其中列與行為非負整數，
  // 並且它的組合是唯一的；值也是個整數。
  public:
    SparseMatrix(int r, int c, int t);
    // constructor.
    // r is #row, c is #col, t is #non-zero terms
    SparseMatrix Transpose();
    SparseMatrix FastTranspose();
    // 回傳將 *this中每個三元組的行與列交換後的SparseMatrix
    SparseMatrix Add(SparseMatrix b);
    // 如果 *this和b的維度一樣，那麼就把相對應的項給相加，
    // 亦即，具有相同列和行的值會被回傳；否則的話丟出例外。
    SparseMatrix Multiply(SparseMatrix b);
    // 如果*this中的行數和b中的列數一樣多的話，那麼回傳的矩陣d= *this和b
    // （依據d[i][j]=Σ(a[i][k]．b[k][j]，其中d[i][j]是第 (i, j) 個元素）相乘的結果。
    // k的範圍從0到*this的行數減1；如果不一樣多的話，那麼就丟出例外。
    // other needed functions

  private:
    int rows, cols, terms, capacity;
    MatrixTerm *smArray;
};



int main(){
  // use >> to build sm object a(4x3, 4 terms), b(4x3, 5 terms), c(3x3, 4 terms) 
  // demo  <<
  // demo  << results of Transpose, Fast Transpose, Add, Mul
}