#include <iostream>
using namespace std;


struct Triple
{
    int row, col, value;
};

class Matrix; // 前向宣告

class MatrixNode 
{
    friend class Matrix;
    friend istream& operator>>(istream&, Matrix&); // 為了能夠讀進矩陣
private:
    MatrixNode *down , *right;
    bool head;
    union { // 沒有名字的union
        MatrixNode *next;
        Triple triple;
    };
    MatrixNode(bool, Triple*); // 建構子
};

MatrixNode::MatrixNode(bool b, Triple *t)  // 建構子
{
    head = b;
    if (b) {right = down = this;} // 列/行的標頭節點
    else triple = *t; // 標頭節點串列的元素節點或標頭節點
}

class Matrix
{
    friend istream& operator>>(istream&, Matrix&);
public:
    ~Matrix(); // 解構子
private:
    MatrixNode *headnode;
};
