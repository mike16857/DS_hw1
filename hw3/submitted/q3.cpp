#include <iostream>
#include <math.h>
using namespace std;


template <class T> class HeaderCircularList;
class Polynomial;


struct Term
{
    double coef;
    int exp;
    Term Set(double c, int e) { coef = c; exp = e; return *this; }
};


template <class T>
class ChainNode
{
    friend class HeaderCircularList<T>;
    friend class Polynomial;
    template <class U>
    friend ostream &operator<<(ostream &os, HeaderCircularList<U> &L);
    // template <class U>
	// friend istream &operator>>(istream& is, HeaderCircularList<U> &L);
    friend istream &operator>>(istream &is, Polynomial &polynomial);
    friend ostream &operator<<(ostream &os, Polynomial &polynomial);
// public:
//     ChainNode(const T& e, ChainNode<T>* next = 0): data(e), link(next) {}
private:
    T data;
    ChainNode<T>* link;
};


template <class T>
class HeaderCircularList
{
    friend class Polynomial;
    template <class U>
    friend ostream &operator<<(ostream &os, HeaderCircularList<U> &L);
    // template <class U>
    // friend istream &operator>>(istream& is, HeaderCircularList<U> &L);
    friend istream &operator>>(istream &is, Polynomial &polynomial);
    friend ostream &operator<<(ostream &os, Polynomial &polynomial);
public:
    HeaderCircularList()
	{
		head = new ChainNode<T>;
        head->link = head;
        av = NULL;
	};
    ~HeaderCircularList();
    int length();
    void InsertFront(T e);
    void InsertBack(T e);
    void DeleteFirst();
    void DeleteBack();
    ChainNode<T>* GetNode();
    void RetNode(ChainNode<T> *&x);
private:
    ChainNode<T> *head;
    ChainNode<T> *av;
};

template <class T>
HeaderCircularList<T>::~HeaderCircularList()
{
    ChainNode<T> *last = head->link;

	while (last->link != head) last = last->link;
	if (last) {
		ChainNode<T>* x = last->link;
		last->link = av; // last node linked to av
		av = x;
		last = 0;
	}
}

template <class T>
int HeaderCircularList<T>::length()
{
    int count = 0;
    ChainNode<T> *tmp = head;
    while (tmp->link != head) {
        count++;
        tmp = tmp->link;
    }
    return count;
}

template <class T>
void HeaderCircularList<T>::InsertFront(T element)
{
    ChainNode<T> *newNode = GetNode();
    newNode->data = element;
    newNode->link = head->link;
    head->link = newNode;
}

template <class T>
void HeaderCircularList<T>::InsertBack(T element)
{
    ChainNode<T> *newNode = GetNode();
    ChainNode<T> *tmp = head;
    newNode->data = element;
    while (tmp->link != head) {
        tmp = tmp->link;
    }
    tmp->link = newNode;
    newNode->link = head;
}

template <class T>
void HeaderCircularList<T>::DeleteFirst()
{
    ChainNode<T> *toDel = head->link;
    head->link = toDel->link;
    RetNode(toDel);
}

template <class T>
void HeaderCircularList<T>::DeleteBack()
{
    ChainNode<T> *tmp = head;
    ChainNode<T> *toDel;
    while (tmp->link->link != head) {
        tmp = tmp->link;
    }
    toDel = tmp->link;
    tmp->link = head;
    RetNode(toDel);
}

template <class T>
ChainNode<T>* HeaderCircularList<T>::GetNode()
{   // Provide a node for use
    ChainNode<T>* x;
    if (av) {
        x = av;
        av = av->link;
    }
    else { // out of available nodes
        x = new ChainNode<T>;
    }
    return x;
}

template <class T>
void HeaderCircularList<T>::RetNode(ChainNode<T>*& x)
{   // Free the node pointed to by x
    x->link = av;
    av = x;
    x = 0; // not delete x
}

template <class T>
ostream &operator<<(ostream &os, HeaderCircularList<T> &L)
{
    ChainNode<T>* temp = L.head->link;

	os << temp->data;
	temp = temp->link;
	while(temp != L.head){
		os << " -> " << temp->data;
		temp = temp->link;
	}
    os << endl;

    return os;
}

// template <class T>
// istream &operator>>(istream& is, HeaderCircularList<T> &L)
// {
//     int num;
//     int temp;

// 	cout << "How many element do you want to plug in : ";
// 	is >> num;
// 	cout << "What do you want to plug in : ";
// 	for(int i = 0; i < num; i++){
// 		is >> temp;
// 		L.InsertBack(temp);
// 	}

//     return is;
// }


class Polynomial
{
    friend istream &operator>>(istream &is, Polynomial &polynomial);
    friend ostream &operator<<(ostream &os, Polynomial &polynomial);
public:
    Polynomial(){};
    ~Polynomial();
    Polynomial(const Polynomial& a);
    const Polynomial &operator=(const Polynomial &a);
    Polynomial operator+(const Polynomial &b) const;
    Polynomial operator-(const Polynomial &b) const;
    Polynomial operator*(const Polynomial &b) const;
    void Set(Term);
    double Evaluate(double x) const;
private:
    HeaderCircularList<Term> poly;
};

// (e)
Polynomial::~Polynomial()
{
    // poly.~HeaderCircularList();
    while(poly.head->link != poly.head) poly.DeleteFirst();

    return;
}

// (c)
Polynomial::Polynomial(const Polynomial& a)
{
    // ChainNode<Term> *temp = a.poly.head->link;
    // while (temp != a.poly.head) {
    //     poly.InsertBack(temp->data);
    //     temp = temp->link;
    // }
    Term doc;
    Polynomial* tempPoly = new Polynomial;
    ChainNode<Term>* temp = a.poly.head->link;

    while (temp != a.poly.head){
        tempPoly->poly.InsertBack(doc.Set(temp->data.coef, temp->data.exp));
        temp = temp->link;
    }
    this->poly = tempPoly->poly;

    return;
}

// (d)
const Polynomial &Polynomial::operator=(const Polynomial &a)
{
    // if (&a != this) {
    //     poly.~HeaderCircularList();
    //     ChainNode<Term> *temp = a.poly.head->link;
    //     while (temp != a.poly.head) {
    //         poly.InsertBack(temp->data);
    //         temp = temp->link;
    //     }
    // }
    // return *this;
    Term doc;
    Polynomial* tempPoly = new Polynomial;
    ChainNode<Term>* temp = a.poly.head->link;

    while (temp != a.poly.head){
        tempPoly->poly.InsertBack(doc.Set(temp->data.coef, temp->data.exp));
        temp = temp->link;
    }
    this->poly = tempPoly->poly;

    return *this;
}

// (f)
Polynomial Polynomial::operator+(const Polynomial& b) const
{
    Term temp;
    ChainNode<Term> *ai = poly.head->link;
    ChainNode<Term> *bi = b.poly.head->link;
    Polynomial c;
    double sum;

    while (ai != poly.head && bi != b.poly.head) {
        if (ai->data.exp == bi->data.exp) {
            sum = ai->data.coef + bi->data.coef;
            if (sum) c.poly.InsertBack(temp.Set(sum, ai->data.exp));
            ai = ai->link;
            bi = bi->link;
        }
        else if (ai->data.exp < bi->data.exp) {
            c.poly.InsertBack(temp.Set(bi->data.coef, bi->data.exp)) ;
            bi = bi->link;
        }
        else {
            c.poly.InsertBack(temp.Set(ai->data.coef, ai->data.exp)) ;
            ai = ai->link;
        }
    }

    while (ai != poly.head) {
        c.poly.InsertBack(temp.Set(ai->data.coef, ai->data.exp));
        ai = ai->link;
    }
    while (bi != b.poly.head) {
        c.poly.InsertBack (temp.Set(bi->data.coef, bi->data.exp));
        bi = bi->link;
    }
    return c;
}

// (g)
Polynomial Polynomial::operator-(const Polynomial& b) const
{
    Term temp;
    ChainNode<Term> *ai = poly.head->link;
    ChainNode<Term> *bi = b.poly.head->link;
    Polynomial c;
    double sum;

    while (ai != poly.head && bi != b.poly.head) {
        if (ai->data.exp == bi->data.exp) {
            sum = ai->data.coef - bi->data.coef;
            if (sum) c.poly.InsertBack(temp.Set(sum, ai->data.exp));
            ai = ai->link;
            bi = bi->link;
        }
        else if (ai->data.exp < bi->data.exp) {
            c.poly.InsertBack(temp.Set((-1) * bi->data.coef, bi->data.exp)) ;
            bi = bi->link;
        }
        else {
            c.poly.InsertBack(temp.Set(ai->data.coef, ai->data.exp)) ;
            ai = ai->link;
        }
    }

    while (ai != poly.head) {
        c.poly.InsertBack(temp.Set(ai->data.coef, ai->data.exp));
        ai = ai->link;
    }
    while (bi != b.poly.head) {
        c.poly.InsertBack(temp.Set((-1) * bi->data.coef, bi->data.exp));
        bi = bi->link;
    }
    return c;
}

// (h)
Polynomial Polynomial::operator*(const Polynomial& b) const
{
    Term temp;
    ChainNode<Term> *ai = poly.head->link;
    ChainNode<Term> *bi = b.poly.head->link;
    Polynomial c, tempPoly;

    while (ai != poly.head) {
        while (bi != b.poly.head) {
            tempPoly.poly.InsertBack(temp.Set(ai->data.coef * bi->data.coef, ai->data.exp + bi->data.exp));
            c = c + tempPoly;
            tempPoly.poly.DeleteFirst();
            bi = bi->link;
        }
        ai = ai->link;
        bi = b.poly.head->link;
    }
    return c;
}

void Polynomial::Set(Term temp)
{
    poly.InsertBack(temp);
}

// (i)
double Polynomial::Evaluate(double x) const
{
    double sum = 0;
    ChainNode<Term> *temp = poly.head->link;

    while (temp != poly.head) {
        sum += temp->data.coef * pow(x, temp->data.exp);
        temp = temp->link;
    }
    return sum;
}

// (a)
istream &operator>>(istream &is, Polynomial &polynomial)
{
    int num;
    int exp;
    double coef;
    Term temp;

    cout << "How many terms do you want to plug in : ";
    is >> num;
    cout << "What do you want to plug in : ";
    for(int i = 0; i < num; i++){
        is >> coef >> exp;
        polynomial.Set(temp.Set(coef, exp));
    }

    return is;
}

// (b)
ostream &operator<<(ostream &os, Polynomial &polynomial)
{
    ChainNode<Term> *temp = polynomial.poly.head->link;

    os << temp->data.coef << "x^" << temp->data.exp;
    temp = temp->link;
    while(temp != polynomial.poly.head){
        os << " + " << temp->data.coef << "x^" << temp->data.exp;
        temp = temp->link;
    }
    os << endl;

    return os;
}


int main()
{
    Polynomial a, b, c;
    double x;

    cout << "Enter polynomial A : " << endl;
    cin >> a;
    cout << "Enter polynomial B : " << endl;
    cin >> b;
    cout << "Enter the value of x : ";
    cin >> x;

    cout << " A(x) = " << a;
    cout << " B(x) = " << b;

    c = a + b;
    cout << " A + B = " << c;

    c = a - b;
    cout << " A - B = " << c;

    c = a * b;
    cout << " A * B = " << c;

    cout << " A(x = " << x << ") = " << a.Evaluate(x) << endl;
    cout << " B(x = " << x << ") = " << b.Evaluate(x) << endl;

    cout << " C(x = " << x << ") = A(x = " << x << ") * B(x = "<< x <<") = " << c.Evaluate(x) << endl;

    return 0;
}
