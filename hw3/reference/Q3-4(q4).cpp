#include <iostream>
using namespace std;

struct Triple{
    int row, col, value;
};
class Matrix;
class MatrixNode {
    friend class Matrix;
    friend istream &operator>>(istream &, Matrix &);
    friend ostream &operator<<(ostream &, Matrix &);
private:
    MatrixNode *down, *right;
    bool head;
    union{
        MatrixNode *next;
        Triple triple;
    };
    MatrixNode(bool b, Triple *t);
};

MatrixNode::MatrixNode(bool b, Triple *t)  // 建構子
{
    head = b;
    if(b){right = down = this;} // 列/行的標頭節點
    else triple = *t; // 標頭節點串列的元素節點或標頭節點
}

class Matrix {
    friend istream &operator>>(istream&, Matrix &);
    friend ostream &operator<<(ostream &, Matrix &);
public:
    Matrix(){};
    ~Matrix();
    Matrix* operator+(const Matrix& b) const;
    Matrix* operator*(const Matrix& b) const;
    Matrix* Transpose();
	Matrix(const Matrix &b);
private:
    MatrixNode *headnode = NULL;
    MatrixNode *av = NULL;
};

Matrix::~Matrix()
{
	if(!headnode) return; // no nodes to delete
	MatrixNode *x = headnode->right;
	headnode->right = av;
	av = headnode; // return headnode
	while(x != headnode){ // return nodes by rows
		MatrixNode *y = x->right;
		x->right = av;
		av = y;
		x = x->next; // next row
	}
	headnode = 0; // empty linked sparse matrix
}

Matrix* Matrix::operator+(const Matrix &b) const
{ 
	if (headnode->triple.col != b.headnode->triple.col || headnode->triple.row != b.headnode->triple.row) throw "Incompatibla Matrices";
	
	Matrix* c = new Matrix;
    MatrixNode* temp1 = headnode->right;
	MatrixNode* temp2 = b.headnode->right;
    MatrixNode* rowhead;
	MatrixNode* rowheadb;
    Triple s;
    s.col = headnode->triple.col; s.row = headnode->triple.row; s.value = 0;
	int p = max(s.row, s.col);
	c->headnode = new MatrixNode(false, &s);
	MatrixNode **head = new MatrixNode* [p];
	for(int i = 0; i < p; i++){
		head[i] = new MatrixNode(true, 0);
		head[i]->next = head[i]->right = head[i];
	}
	int currentRow = 0; // start from row 0
	MatrixNode *last = head[0];
	
	while(temp1 != headnode && temp2 != b.headnode){
        last = head[currentRow];
        rowhead = temp1; rowheadb = temp2;
        temp1 = temp1->right; temp2 = temp2->right;
        while(temp1 != rowhead && temp2 != rowheadb){
            if(temp1->triple.row == temp2->triple.row){
            	if(temp1->triple.col == temp2->triple.col){
                    int sum = temp2->triple.value + temp1->triple.value;
                    if(sum){
                        Triple add;
                        add.row = temp1->triple.row; add.col = temp2->triple.col; add.value = sum;
                        last = last->right = new MatrixNode(false, &add);
                        head[add.col]->next = ((head[add.col]->next)->down) = last;
                        c->headnode->triple.value++;
                    }
                    temp1 = temp1->right;
                    temp2 = temp2->right;
                }
                else if(temp1->triple.col > temp2->triple.col){
                    Triple add;
                    add.row = temp2->triple.row; add.col = temp2->triple.col; add.value = temp2->triple.value;
                    last = last->right = new MatrixNode(false, &add);
                    head[add.col]->next = ((head[add.col]->next)->down) = last;
                    c->headnode->triple.value++;
                    temp2 = temp2->right;
                }
                else{
                    Triple add;
                    add.row = temp1->triple.row; add.col = temp1->triple.col; add.value = temp1->triple.value;
                    last = last->right = new MatrixNode(false, &add);
                    head[add.col]->next = ((head[add.col]->next)->down) = last;
                    c->headnode->triple.value++;
                    temp1 = temp1->right;
                }
            }
            else if(temp1->triple.row > temp2->triple.row){
            	Triple add;
                add.row = temp2->triple.row; add.col = temp2->triple.col; add.value = temp2->triple.value;
                last = last->right = new MatrixNode(false, &add);
                head[add.col]->next = ((head[add.col]->next)->down) = last;
                c->headnode->triple.value++;
                temp2 = temp2->right;
			}
			else{
				Triple add;
                add.row = temp1->triple.row; add.col = temp1->triple.col; add.value = temp1->triple.value;
                last = last->right = new MatrixNode(false, &add);
                head[add.col]->next = ((head[add.col]->next)->down) = last;
                c->headnode->triple.value++;
                temp1 = temp1->right;
			}
        }
        while(temp1 != rowhead){
            Triple add;
            add.row = temp1->triple.row; add.col = temp1->triple.col; add.value = temp1->triple.value;
            last = last->right = new MatrixNode(false, &add);
            head[add.col]->next = ((head[add.col]->next)->down) = last;
            c->headnode->triple.value++;
            temp1 = temp1->right;
        }
        while(temp2 != rowheadb){
            Triple add;
            add.row = temp2->triple.row; add.col = temp2->triple.col; add.value = temp2->triple.value;
            last = last->right = new MatrixNode(false, &add);
            head[add.col]->next = ((head[add.col]->next)->down) = last;
            c->headnode->triple.value++;
            temp2 = temp2->right;
        }
        last->right = head[currentRow];
        currentRow++;
        temp1 = temp1->next; temp2 = temp2->next;
    }
	for (int i = 0; i < p - 1; i++) head[i]->next->down = head[i];
    for (int i = 0; i < p ; i++) head[i]->next = head[i + 1];
    head[p - 1]->next = c->headnode;
    c->headnode->right = head[0];

    return c;
}

Matrix* Matrix::operator*(const Matrix &b) const
{
	if(headnode->triple.col != b.headnode->triple.row) throw "Incompatibla Matrices";
	
	Matrix* c = new Matrix;
    MatrixNode* temp1 = headnode->right;
	MatrixNode* temp2 = b.headnode->right;
    MatrixNode* rowhead;
	MatrixNode* colheadb;
    Triple s;
    s.col = headnode->triple.col; s.row = headnode->triple.row; s.value = 0;
	int p = max(s.row, s.col);
	c->headnode = new MatrixNode(false, &s);
	MatrixNode **head = new MatrixNode* [p];
	for(int i = 0; i < p; i++){
		head[i] = new MatrixNode(true, 0);
		head[i]->next = head[i]->right = head[i];
	}
	int currentRow = 0; // start from row 0
	MatrixNode *last = head[0];
	
	rowhead = temp1; colheadb = temp2;
	while (rowhead != headnode) {
        last = head[currentRow];
        colheadb = b.headnode->right;
        int currentCol = 0;
        while (colheadb != b.headnode) {
            temp1 = rowhead->right;
            temp2 = colheadb->down;
            int sum = 0;
            while (temp1 != rowhead && temp2 != colheadb) {
                if (temp1->triple.col == temp2->triple.row) {
                    sum += temp1->triple.value * temp2->triple.value;
                    temp1 = temp1->right;
                    temp2 = temp2->down;
                }
                else if (temp1->triple.col < temp2->triple.row)
                    temp1 = temp1->right;
                else
                    temp2 = temp2->down;
            }
            if (sum) {
                Triple tim;
                tim.row = currentRow; tim.col = currentCol; tim.value = sum;
                last = last->right = new MatrixNode(false, &tim);
                head[tim.col]->next = ((head[tim.col]->next)->down) = last;
                c->headnode->triple.value++;
            }
            colheadb = colheadb->next;
            currentCol++;
        }
        rowhead = rowhead->next;
        last->right = head[currentRow];
        currentRow++;
    }
    for (int i = 0; i < p - 1; i++) head[i]->next->down = head[i];
    for (int i = 0; i < p; i++) head[i]->next = head[i + 1];
    head[p - 1]->next = c->headnode;
    c->headnode->right = head[0];
    
    return c;
} 

Matrix::Matrix(const Matrix &b)
{
	Triple s;
    Triple t;
    MatrixNode* newheadnode;
    
    s.row = b.headnode->triple.row;
    s.col = b.headnode->triple.col;
    s.value = b.headnode->triple.value;
    int p = max(s.row, s.col);
    newheadnode = new MatrixNode(false, &s);
    if(p == 0) newheadnode->right = newheadnode;
    else {
        MatrixNode **head = new MatrixNode* [p];
        for (int i = 0; i < p; i++) {
            head[i] = new MatrixNode(true, 0);
            head[i]->down = head[i]->next = head[i]->right = head[i];
        }
        int currentRow = 0;
        MatrixNode *last = head[0];
        MatrixNode *temp = b.headnode->right;
        MatrixNode *rownow = b.headnode->right;
        
        while (rownow != b.headnode) {
            last = head[currentRow];
            temp = rownow->right;
            while (temp != rownow) {
                t.col = temp->triple.col; t.row = temp->triple.row; t.value = temp->triple.value;
                last = last->right = new MatrixNode(false, &t);
                head[t.col]->next = ((head[t.col]->next)->down) = last;
                temp = temp->right;
            }
            last->right = head[currentRow];
            rownow = rownow->next;
            currentRow++;
        }
        for (int i = 0; i < p - 1; i++)
        head[i]->next->down = head[i];
        for (int i = 0; i < p - 1; i++)
        head[i]->next = head[i + 1];
        head[p - 1]->next = newheadnode;
        newheadnode->right = head[0];
    }
    headnode = newheadnode;
    
    return;
}

Matrix* Matrix::Transpose()
{
	Matrix* c;
    MatrixNode* temp;
    
    Triple s;
    s.col = headnode->triple.col; s.row = headnode->triple.row; s.value = headnode->triple.value;
    c = new Matrix;
    c->headnode = new MatrixNode(false, &s);
    int p = max(headnode->triple.col, headnode->triple.row);
    MatrixNode **head = new MatrixNode* [p];
    for (int i = 0; i < p; i++) {
        head[i] = new MatrixNode(true, 0);
        head[i]->next = head[i]->right = head[i];
    }
    int currentRow = 0;
    MatrixNode* last = head[0];
    MatrixNode* colnow = headnode->right;
        
    while (colnow != headnode) {
        temp = colnow->down;
        last = head[currentRow];
        while (temp != colnow) {
            Triple t;
            t.row = temp->triple.col; t.col = temp->triple.row; t.value = temp->triple.value;
            last = last->right = new MatrixNode(false, &t);
            head[t.col]->next = ((head[t.col]->next)->down) = last;
            temp = temp->down;
        }
        last->right = head[currentRow];
        currentRow++;
        colnow = colnow->next;
    }
    for (int i = 0; i < p - 1; i++) head[i]->next->down = head[i];
    for (int i = 0; i < p; i++) head[i]->next = head[i + 1];
    head[p - 1]->next = c->headnode;
    c->headnode->right = head[0];
    
    return c;
}

istream & operator>>(istream &is, Matrix &matrix)
{
    Triple s;
    
    cout << "type in rows cols terms" << endl;
    is >> s.row >> s.col >> s.value;
    int p = max(s.row, s.col);
    matrix.headnode = new MatrixNode(false, &s);
    if(p == 0){
        matrix.headnode->right = matrix.headnode;
        return is;
    }
    
    MatrixNode **head = new MatrixNode* [p];
    for(int i = 0; i < p; i++){
        head[i] = new MatrixNode(true, 0);
        head[i]->right = head[i];
        head[i]->down = head[i];
        head[i]->next = head[i];
    }
    int currentRow = 0;
    MatrixNode *last = head[0];
    cout << "type your row col value" << endl;
    for(int i = 0; i < s.value; i++){
		Triple t;
        is >> t.row >> t.col >> t.value;
        if(t.row > currentRow){
            last->right = head[currentRow];
            currentRow = t.row;
            last = head[currentRow];
        }
        last = last->right = new MatrixNode(false, &t);
        head[t.col]->next = head[t.col]->next->down = last;
    }
    last->right = head[currentRow];
    
    for(int i = 0; i < s.col; i++) head[i]->next->down = head[i];
    for (int i = 0; i < p; i++) head[i]->next = head[i + 1];
    head[p - 1]->next = matrix.headnode;
    matrix.headnode->right = head[0];
	delete [] head;
	
    return is;
    
}

ostream & operator<<(ostream &os, Matrix &matrix)
{
    MatrixNode* temp = matrix.headnode;
	MatrixNode* rowhead;
    int count = 0;
    int terms = matrix.headnode->triple.value;
    int rows = matrix.headnode->triple.row;
    int cols = matrix.headnode->triple.col;
    
    os << "Total (rows, cols, terms) = " << "(" << temp->triple.row << ", " << temp->triple.col << ", " << temp->triple.value << ")" << endl;
    temp = matrix.headnode->right;
    rowhead = temp;
    temp = temp->right;
    while(temp == rowhead){
    	rowhead = temp->next;
    	temp = rowhead->right;
	}
    for(int i = 0; i < rows; i++){
    	for(int j = 0; j < cols; j++){
    		if(count == terms){
    			os << "0 ";
			}
			else if(temp->triple.row == i && temp->triple.col == j){
				os << temp->triple.value << " ";
				count++;
				temp = temp->right;
				while(temp == rowhead){
    				rowhead = temp->next;
    				temp = rowhead->right;
				}		
			}
			else os << "0 ";
		}
		os << endl;
	}
    os << endl;
    
    return os;
}

int main(void)
{
    Matrix a, b;
    Matrix* c;
    
    cin >> a;
    cin >> b;
    cout << "M1 is : " << endl << a;
    cout << "M2 is : " << endl << b;
    
    c = a + b;
    cout << "M1 + M2 = " << endl;
    cout << *c;
    
    c = a * b;
    cout << "M1 * M2 = " << endl;
    cout << *c;
    
    cout << "copy M4 from M3 :" << endl;
    Matrix d(*c);
    cout << "M4 is : " << endl << d;
    
    return 0;
}

