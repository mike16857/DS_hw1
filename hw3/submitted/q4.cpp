#include <iostream>
using namespace std;


struct Triple
{
    int row, col, value;
};


class Matrix;


class MatrixNode
{
    friend class Matrix;
    friend istream& operator>>(istream&, Matrix&);
    friend ostream& operator<<(ostream&, Matrix&);
private:
    MatrixNode *down , *right;
    bool ishead;
    union {
        MatrixNode *next;
        Triple triple;
    };
    MatrixNode(bool, Triple*);
};

MatrixNode::MatrixNode(bool b, Triple *t)  // constructor
{
    ishead = b;
    if (ishead) {right = down = this;}  // row/column header node
    else triple = *t;                   // element/handler node
}


class Matrix
{
    friend istream& operator>>(istream&, Matrix&);
    friend ostream& operator<<(ostream&, Matrix&); // (c)
public:
    Matrix() {headnode = 0; av = 0;} // constructor
    ~Matrix();
    Matrix(const Matrix&); // copy constructor (e)
    Matrix* operator+(const Matrix&) const;  // (a)
    Matrix* operator*(const Matrix&) const;  // (b)
    void Transpose();  // (d)
private:
    MatrixNode *headnode;
    MatrixNode *av;
};

Matrix::~Matrix()
{// Return all nodes to the av list, which is a chain linked
 // via the right field.
 // av is a static variable pointing to the first of the av list.
    if (!headnode) return; // no nodes to delete

    MatrixNode *x = headnode->right;
    headnode->right = av;
    av = headnode; // return headnode

    while (x != headnode) { // return nodes by rows
        MatrixNode *y = x->right;
        x->right = av;
        av = y;
        x = x->next; // next row
    }
    headnode = 0; // empty linked sparse matrix
}

Matrix::Matrix(const Matrix& b) //
{
    Triple s;
    Triple t;
    MatrixNode *newheadnode;

    s.row = b.headnode->triple.row;
    s.col = b.headnode->triple.col;
    s.value = b.headnode->triple.value;
    int p = max(s.row, s.col);
    newheadnode = new MatrixNode(false, &s);

    if (p == 0) newheadnode->right = newheadnode; // empty matrix
    else {
        MatrixNode **head = new MatrixNode* [p]; // headers for the matrix rows
        for (int i = 0; i < p; i++) { // initialize header array
            head[i] = new MatrixNode(true, 0);
            head[i]->down = head[i]->next = head[i]->right = head[i];
        }

        int currentRow = 0;
        MatrixNode *last = head[0];
        MatrixNode *temp = b.headnode->right;
        MatrixNode *rowNow = b.headnode->right;
        while (rowNow != b.headnode) { // copy content of b
            last = head[currentRow];
            temp = rowNow->right;
            while (temp != rowNow) {
                t.col = temp->triple.col;
                t.row = temp->triple.row;
                t.value = temp->triple.value;

                last = last->right = new MatrixNode(false, &t);
                head[t.col]->next = head[t.col]->next->down = last;
                temp = temp->right;
            }
            last->right = head[currentRow];
            rowNow = rowNow->next;
            currentRow++;
        }

        for (int i = 0; i < p - 1; i++) head[i]->next->down = head[i];  // close all column lists
        for (int i = 0; i < p - 1; i++) head[i]->next = head[i + 1];    // link the header nodes together
        head[p - 1]->next = newheadnode;
        newheadnode->right = head[0];

        delete [] head;
    }

    headnode = newheadnode;

    return;
}

Matrix* Matrix::operator+(const Matrix& b) const
{// Add the matrices *this and b.
    if (headnode->triple.col != b.headnode->triple.col || headnode->triple.row != b.headnode->triple.row)
        throw "Incompatibla Matrices";

	Matrix *c = new Matrix;
    MatrixNode *temp1 = headnode->right;
	MatrixNode *temp2 = b.headnode->right;
    MatrixNode *rowhead;
	MatrixNode *b_rowhead;
    Triple s;

    s.col = headnode->triple.col;
    s.row = headnode->triple.row;
    s.value = 0;
	int p = max(s.row, s.col);

    // handler node for the result matrix
	c->headnode = new MatrixNode(false, &s);

    // headers for the matrix rows
	MatrixNode **head = new MatrixNode* [p];
	for (int i = 0; i < p; i++) { // initialize header array
		head[i] = new MatrixNode(true, 0);
		head[i]->next = head[i]->right = head[i];
	}

	int currentRow = 0; // start from row 0
	MatrixNode *last = head[0];
	while (temp1 != headnode && temp2 != b.headnode) {
        last = head[currentRow];
        rowhead = temp1;
        b_rowhead = temp2;

        temp1 = temp1->right;
        temp2 = temp2->right;

        while (temp1 != rowhead && temp2 != b_rowhead) {
            if (temp1->triple.row == temp2->triple.row) {
            	if (temp1->triple.col == temp2->triple.col) {
                    int sum = temp2->triple.value + temp1->triple.value;
                    if (sum) {
                        Triple add;
                        add.row = temp1->triple.row;
                        add.col = temp2->triple.col;
                        add.value = sum;

                        last = last->right = new MatrixNode(false, &add);
                        head[add.col]->next = ((head[add.col]->next)->down) = last;
                        c->headnode->triple.value++;    // update the number of non-zero elements
                    }
                    temp1 = temp1->right;
                    temp2 = temp2->right;
                }
                else if (temp1->triple.col > temp2->triple.col) {
                    Triple add;
                    add.row = temp2->triple.row;
                    add.col = temp2->triple.col;
                    add.value = temp2->triple.value;

                    last = last->right = new MatrixNode(false, &add);
                    head[add.col]->next = ((head[add.col]->next)->down) = last;
                    c->headnode->triple.value++;
                    temp2 = temp2->right;
                }
                else {
                    Triple add;
                    add.row = temp1->triple.row;
                    add.col = temp1->triple.col;
                    add.value = temp1->triple.value;

                    last = last->right = new MatrixNode(false, &add);
                    head[add.col]->next = ((head[add.col]->next)->down) = last;
                    c->headnode->triple.value++;
                    temp1 = temp1->right;
                }
            }
            else if (temp1->triple.row > temp2->triple.row) {
            	Triple add;
                add.row = temp2->triple.row;
                add.col = temp2->triple.col;
                add.value = temp2->triple.value;

                last = last->right = new MatrixNode(false, &add);
                head[add.col]->next = ((head[add.col]->next)->down) = last;
                c->headnode->triple.value++;
                temp2 = temp2->right;
			}
			else {
				Triple add;
                add.row = temp1->triple.row;
                add.col = temp1->triple.col;
                add.value = temp1->triple.value;

                last = last->right = new MatrixNode(false, &add);
                head[add.col]->next = ((head[add.col]->next)->down) = last;
                c->headnode->triple.value++;
                temp1 = temp1->right;
			}
        }

        // add the remaining elements
        while (temp1 != rowhead) {
            Triple add;
            add.row = temp1->triple.row;
            add.col = temp1->triple.col;
            add.value = temp1->triple.value;

            last = last->right = new MatrixNode(false, &add);
            head[add.col]->next = ((head[add.col]->next)->down) = last;
            c->headnode->triple.value++;    // update the number of non-zero elements
            temp1 = temp1->right;
        }
        while (temp2 != b_rowhead) {
            Triple add;
            add.row = temp2->triple.row;
            add.col = temp2->triple.col;
            add.value = temp2->triple.value;

            last = last->right = new MatrixNode(false, &add);
            head[add.col]->next = ((head[add.col]->next)->down) = last;
            c->headnode->triple.value++;
            temp2 = temp2->right;
        }
        last->right = head[currentRow];
        currentRow++;
        temp1 = temp1->next;
        temp2 = temp2->next;
    }

	for (int i = 0; i < p - 1; i++) head[i]->next->down = head[i];  // close all column lists
    for (int i = 0; i < p ; i++) head[i]->next = head[i + 1];       // link the header nodes together
    head[p - 1]->next = c->headnode;
    c->headnode->right = head[0];

    delete [] head;

    return c;
}

Matrix* Matrix::operator*(const Matrix& b) const
{// Multiply the matrices *this and b.
    if(headnode->triple.col != b.headnode->triple.row)
        throw "Incompatibla Matrices";

	Matrix *c = new Matrix;
    MatrixNode *temp1 = headnode->right;
	MatrixNode *temp2 = b.headnode->right;
    MatrixNode *rowhead;
	MatrixNode *b_colhead;
    Triple s;

    s.col = headnode->triple.col;
    s.row = headnode->triple.row;
    s.value = 0;
	int p = max(s.row, s.col);

	// handler node for the result matrix
    c->headnode = new MatrixNode(false, &s);

    // headers for the matrix rows
	MatrixNode **head = new MatrixNode* [p];
	for (int i = 0; i < p; i++) { // initialize header array
		head[i] = new MatrixNode(true, 0);
		head[i]->next = head[i]->right = head[i];
	}

	int currentRow = 0; // start from row 0
	MatrixNode *last = head[0];
	rowhead = temp1;
    b_colhead = temp2;
	while (rowhead != headnode) {
        last = head[currentRow];
        b_colhead = b.headnode->right;
        int currentCol = 0;
        while (b_colhead != b.headnode) {
            temp1 = rowhead->right;
            temp2 = b_colhead->down;
            int sum = 0;
            while (temp1 != rowhead && temp2 != b_colhead) {
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
            if (sum) { // new element isn't zero
                Triple newTerm;
                newTerm.row = currentRow;
                newTerm.col = currentCol;
                newTerm.value = sum;

                last = last->right = new MatrixNode(false, &newTerm);
                head[newTerm.col]->next = ((head[newTerm.col]->next)->down) = last;
                c->headnode->triple.value++;    // update the number of non-zero elements
            }
            b_colhead = b_colhead->next;
            currentCol++;
        }
        rowhead = rowhead->next;
        last->right = head[currentRow];
        currentRow++;
    }

    for (int i = 0; i < p - 1; i++) head[i]->next->down = head[i];  // close all column lists
    for (int i = 0; i < p; i++) head[i]->next = head[i + 1];        // link the header nodes together
    head[p - 1]->next = c->headnode;
    c->headnode->right = head[0];

    delete [] head;

    return c;
}

void Matrix::Transpose()
{// Transpose the matrix *this.
    Matrix *c = new Matrix;
    MatrixNode *temp;

    Triple s;
    s.col = headnode->triple.col;
    s.row = headnode->triple.row;
    s.value = headnode->triple.value;
    int p = max(headnode->triple.col, headnode->triple.row);

    // handler node for the result matrix
    c->headnode = new MatrixNode(false, &s);

    // headers for the matrix rows
    MatrixNode **head = new MatrixNode* [p];
    for (int i = 0; i < p; i++) { // initialize header array
        head[i] = new MatrixNode(true, 0);
        head[i]->next = head[i]->right = head[i];
    }

    int currentRow = 0;
    MatrixNode *last = head[0];
    MatrixNode *colNow = headnode->right;
    while (colNow != headnode) {
        temp = colNow->down;
        last = head[currentRow];
        while (temp != colNow) {
            Triple t;
            t.row = temp->triple.col;
            t.col = temp->triple.row;
            t.value = temp->triple.value;

            last = last->right = new MatrixNode(false, &t);
            head[t.col]->next = ((head[t.col]->next)->down) = last;
            temp = temp->down;
        }
        last->right = head[currentRow];
        currentRow++;
        colNow = colNow->next;
    }

    for (int i = 0; i < p - 1; i++) head[i]->next->down = head[i];  // close all column lists
    for (int i = 0; i < p; i++) head[i]->next = head[i + 1];        // link the header nodes together
    head[p - 1]->next = c->headnode;
    c->headnode->right = head[0];

    *this = *c;
    // return c;
}

istream& operator>>(istream& is, Matrix& matrix)
{// Read in a maxtix and set up its linked representation
    Triple s;
    int i;
    cout << "Enter total rows, columns, and number of non-zero elements: ";
    is >> s.row >> s.col >> s.value; // matrix dimensions
    int p = max(s.row, s.col);

    // handler node for the result matrix
    matrix.headnode = new MatrixNode(false, &s); // set up header node for list of header nodes

    if (p == 0) {// empty matrix
        matrix.headnode->right = matrix.headnode;
        return is; // for supporting "cin >> mi >> mj;"
    }

    // headers for the matrix rows
    MatrixNode **head = new MatrixNode* [p];
    for (i = 0; i < p; i++) {
        head[i] = new MatrixNode(true, 0);
        head[i]->down = head[i]->next = head[i]->right = head[i];

    }

    int currentRow = 0; // start from row 0
    MatrixNode *last = head[0]; // last node in current row

    cout << "Enter row, column, and value of element : " << endl;
    for (int i = 0; i < s.value; i++) { // input triples
        Triple t;
        is >> t.row >> t.col >> t.value;
        if (t.row > currentRow) { // end of current row
            last->right = head[currentRow]; // close current row
            currentRow = t.row;
            last = head[currentRow];
        }

        last = last->right = new MatrixNode(false, &t); // link new node into row list, last point to new node
        head[t.col]->next = head[t.col]->next->down = last; //use head[]->next as col list last, link into column list
    }
    last->right = head[currentRow]; // close last row

    for (i = 0; i < s.col; i++) head[i]->next->down = head[i]; // close all column lists
    for (i = 0; i < p; i++) head[i]->next = head[i + 1]; // link the header nodes together
    head[p - 1]->next = matrix.headnode; // close the circle
    matrix.headnode->right = head[0];

    delete [] head;

    return is;
}

ostream& operator<<(ostream &os, Matrix &matrix) //
{
    MatrixNode *temp = matrix.headnode;
	MatrixNode *rowhead;
    int count = 0;
    int terms = matrix.headnode->triple.value;
    int rows = matrix.headnode->triple.row;
    int cols = matrix.headnode->triple.col;

    os << "Total (rows, cols, terms) = " << "(" << temp->triple.row << ", " << temp->triple.col << ", " << temp->triple.value << ")" << endl;

    temp = matrix.headnode->right;
    rowhead = temp;
    temp = temp->right;
    while (temp == rowhead) {
    	rowhead = temp->next;
    	temp = rowhead->right;
	}
    for (int i = 0; i < rows; i++) {
    	for (int j = 0; j < cols; j++){
    		if (count == terms) {
    			os << "0 ";
			}
			else if (temp->triple.row == i && temp->triple.col == j) {
				os << temp->triple.value << " ";
				count++;
				temp = temp->right;
				while (temp == rowhead) {
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

int main()
{
    Matrix a, b;
    Matrix *c;

    cout << "Enter matrix A:" << endl;
    cin >> a;
    cout << endl;

    cout << "Enter matrix B:" << endl;
    cin >> b;
    cout << endl;

    cout << "Matrix A is : " << endl << a;
    cout << "Matrix B is : " << endl << b;

    c = a + b;
    cout << "A + B = " << endl << *c;

    c = a * b;
    cout << "A * B = " << endl << *c;

    a.Transpose();
    cout << "Transpose of A = " << endl << a;

    cout << "Copy A to D" << endl;
    Matrix d(a);
    cout << "Matrix D is : " << endl << d;

    return 0;
}
