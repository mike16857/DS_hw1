#include <iostream>
using namespace std;

template <class T> class HeaderCircularList;

class Polynomial;
struct Term
{
    int coef;
    int exp;
    Term Set(int c, int e) {coef = c; exp = e; return *this;};
};

template <class T>
class ChainNode
{
	friend class Polynomial;
    friend class HeaderCircularList<T>;
    template <class U>
    friend ostream &operator<<(ostream &os, HeaderCircularList<U> &L);
	friend istream &operator>>(istream &is, Polynomial &polynomial);
    friend ostream &operator<<(ostream &os, Polynomial &polynomial);
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
    friend istream &operator>>(istream &is, Polynomial &polynomial);
    friend ostream &operator<<(ostream &os, Polynomial &polynomial);
public:
    HeaderCircularList()
	{
        header = new ChainNode<T>;
        header->link = header;
        av = NULL;
    };
    ~HeaderCircularList();
    int count();
    void insertFront(T e);
    void insertBack(T e);
    void deleteFirst();
    void deleteLast();
    ChainNode<T>* GetNode();
    void RetNode(ChainNode<T> *&x);
private:
    ChainNode<T>* header;
    ChainNode<T>* av;
};

template <class T>
HeaderCircularList<T>::~HeaderCircularList()
{
	ChainNode<T>* last = header->link;
	
	while(last->link != header) last = last->link;
	if(last) {
		ChainNode<T>* x = last->link;
		last->link = av; // last node linked to av
		av = x;
		last = 0;
	}
}

template <class T>
int HeaderCircularList<T>::count()
{
	int num = 1;
	ChainNode<T>* temp = header->link;
	
	while(temp->link != header){
		num++;
		temp = temp->link;
	}
	
	return num;
}

template <class T>
void HeaderCircularList<T>::insertFront(T e)
{
    ChainNode<T>* newNode = GetNode();
    newNode->data = e;
    newNode->link = header->link;
    header->link = newNode;
    
    return;
}

template <class T>
void HeaderCircularList<T>::insertBack(T e)
{
    ChainNode<T>* temp = header->link;
    
    while(temp->link != header) temp = temp->link;
  	ChainNode<T>* newNode = GetNode();
    newNode->data = e;
    newNode->link = header;
    temp->link = newNode;
	
    return;
}

template <class T>
void HeaderCircularList<T>::deleteFirst()
{
    if (header->link == NULL) throw "The List is empty, cannot delete.";
    ChainNode<T>* temp = header->link;
    header->link = temp->link;
    RetNode(temp);
    
    return;
}

template <class T>
void HeaderCircularList<T>::deleteLast()
{
    if (header->link == NULL) throw "The List is empty, cannot delete.";
    ChainNode<T>* temp = header->link;
    
    while(temp->link->link != header) temp = temp->link;
	RetNode(temp->link);
    temp->link = header;
    
    return;
}

template <class T>
ChainNode<T>* HeaderCircularList<T>::GetNode()
{ // Provide a node for use
	ChainNode<T>* x;
	if (av){
		x = av;
		av = av->link;
	}
	else x = new ChainNode<T>;
	
	return x;
}

template <class T>
void HeaderCircularList<T>::RetNode(ChainNode<T>* &x)
{// Free the node pointed to by x
	x->link = av;
	av = x;
	x = 0; // not delete x
}

template <class T>
ostream &operator<<(ostream &os, HeaderCircularList<T> &L)
{
    ChainNode<T>* temp = L.header->link;
    int i = 0;
    
	os << temp->data;
	temp = temp->link;
	while(temp != L.header){
		os << " ¡÷ " << temp->data;
		temp = temp->link;
	}
    os << endl;
    
    return os;
}

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

Polynomial::~Polynomial()
{
    while(poly.header->link != poly.header) poly.deleteFirst();

    return;
}
Polynomial::Polynomial(const Polynomial &a)
{
    Term doc;
    Polynomial* newPoly = new Polynomial;
    ChainNode<Term>* temp = a.poly.header->link;
    
    while (temp != a.poly.header){
        newPoly->poly.insertBack(doc.Set(temp->data.coef, temp->data.exp));
        temp = temp->link;
    }
    this->poly = newPoly->poly;
    
    return;
}
const Polynomial& Polynomial::operator=(const Polynomial &a)
{
    Term doc;
    Polynomial* newPoly = new Polynomial;
    ChainNode<Term>* temp = a.poly.header->link;
    
    while (temp != a.poly.header){
        newPoly->poly.insertBack(doc.Set(temp->data.coef, temp->data.exp));
        temp = temp->link;
    }
    this->poly = newPoly->poly;
    
    return *this;
}

Polynomial Polynomial::operator+(const Polynomial& b) const
{
	Term doc;
	ChainNode<Term>* temp1 = poly.header->link;
	ChainNode<Term>* temp2 = b.poly.header->link;
	Polynomial c;
	int sum;
	
	while(temp1 != poly.header && temp2 != b.poly.header){
		if(temp1->data.exp == temp2->data.exp){
			sum = temp1->data.coef + temp2->data.coef;
			if(sum){
				c.poly.insertBack(doc.Set(sum, temp1->data.exp));
			}
			temp1 = temp1->link;
			temp2 = temp2->link;
		}
		else if(temp1->data.exp > temp2->data.exp){
			c.poly.insertBack(doc.Set(temp1->data.coef, temp1->data.exp));
			temp1 = temp1->link;
		}
		else{
			c.poly.insertBack(doc.Set(temp2->data.coef, temp2->data.exp));
			temp2 = temp2->link;
		}
    }
	while(temp1 != poly.header){
		c.poly.insertBack(doc.Set(temp1->data.coef, temp1->data.exp));
		temp1 = temp1->link;
	}
	while(temp2 != b.poly.header){ 
		c.poly.insertBack(doc.Set(temp2->data.coef, temp2->data.exp));
		temp2 = temp2->link;
	}
	
	return c;
}

Polynomial Polynomial::operator-(const Polynomial& b) const
{
	Term doc;
	ChainNode<Term>* temp1 = poly.header->link;
	ChainNode<Term>* temp2 = b.poly.header->link;
	Polynomial c;
	int sum;
	
	while(temp1 != poly.header && temp2 != b.poly.header){
		if(temp1->data.exp == temp2->data.exp){
			sum = temp1->data.coef - temp2->data.coef;
			if(sum != 0){
				c.poly.insertBack(doc.Set(sum, temp1->data.exp));
			}
			temp1 = temp1->link;
			temp2 = temp2->link;
		}
		else if(temp1->data.exp > temp2->data.exp){
			c.poly.insertBack(doc.Set(temp1->data.coef, temp1->data.exp));
			temp1 = temp1->link;
		}
		else{
			c.poly.insertBack(doc.Set(-1 * temp2->data.coef, temp2->data.exp));
			temp2 = temp2->link;
		}
    }
	while(temp1 != poly.header){
		c.poly.insertBack(doc.Set(temp1->data.coef, temp1->data.exp));
		temp1 = temp1->link;
	}
	while(temp2 != b.poly.header){ 
		c.poly.insertBack(doc.Set(-1 * temp2->data.coef, temp2->data.exp));
		temp2 = temp2->link;
	}
	
	return c;
}

Polynomial Polynomial::operator*(const Polynomial &b) const
{
	Term doc;
	ChainNode<Term>* temp1 = poly.header->link;
	ChainNode<Term>* temp2 = b.poly.header->link;
	Polynomial c, newPoly;
	
	while(temp1 != poly.header){
		temp2 = b.poly.header->link;
		while(temp2 != b.poly.header){
            newPoly.poly.insertBack(doc.Set(temp1->data.coef * temp2->data.coef, temp1->data.exp + temp2->data.exp));
            c = newPoly + c;
            newPoly.poly.deleteFirst(); 
            temp2 = temp2->link;
		}
		temp1 = temp1->link;
	}
	
	return c;
}

double Polynomial::Evaluate(double x) const
{
    ChainNode<Term>* temp = poly.header->link;
    double te, sum = 0;
    
    while (temp != poly.header) {
        te = 1;
		for(int i = 0; i < temp->data.exp; i++){
			te *= x;
		}
		te *= temp->data.coef;
		sum += te;
		temp = temp->link;
    }
    
    return sum;
}

void Polynomial::Set(Term term)
{
    poly.insertBack(term);
    
    return;
}

istream& operator>>(istream& is, Polynomial &polynomial)
{
	Term doc;
    int exp, coef;
    char temp;
    Polynomial a;
    
    cout << "Please input in the form {(coef,exp)} : ";

    while ((temp = getchar()) != '}') {
        getchar();
        is >> coef >> temp >> exp;
        getchar();
        a.poly.insertBack(doc.Set(coef, exp));  
    }
    getchar();
    polynomial = a;

    return is;
}

ostream& operator<<(ostream& os, Polynomial &polynomial)
{
	int num = polynomial.poly.count();
	ChainNode<Term>* temp = polynomial.poly.header->link;;
	int a;
	
	if(num == 0 || (temp->data.coef == 0) && (temp->data.exp == 0)) os << "0" << endl;
	else{
		if(temp->data.coef == 0);
		else if(temp->data.coef == 1 && temp->data.exp == 1) os << "x";
		else if(temp->data.coef != 1 && temp->data.exp == 1) 
			os << temp->data.coef << "x";
		else if(temp->data.coef == 1 && temp->data.exp > 1) 
			os << "x^" << temp->data.exp;
		else if(temp->data.coef != 1 && temp->data.exp > 1)
			os << temp->data.coef << "x^" << temp->data.exp;
		else os << temp->data.coef;
		temp = temp->link;
		if(num > 1){
			for(int i = 1; i < num; i++){
				a = temp->data.coef;
				if(a < 0){
					os << " -";
					a = (-1) * a;
				}
				else if (a > 0) os << " +";
				if(a == 0);
				else if(a == 1 && temp->data.exp == 1) os << "x";
				else if(a != 1 && temp->data.exp == 1) 
					os << a << "x";
				else if(a == 1 && temp->data.exp > 1) 
					os << "x^" << temp->data.exp;
				else if(a != 1 && temp->data.exp > 1)
					os << a << "x^" << temp->data.exp;
				else os << a;
				temp = temp->link;
			}
		}
		os << endl;
	}
	return os;
}

int main(void) {
    Polynomial a, b, c, d;
    double num;
    
    cin >> a;
	cin >> b;
    cout << "Polynomial 1 : " << a;
    cout << "Polynomial 2 : " << b;
    c = a + b;
    cout << "P1 + P2 = " << c;
    c = a - b;
    cout << "P1 - P2 = " << c;
    c = a * b;
    cout << "P1 * P2 = " << c;
    cout << "what num do you want to in put x? : ";
    cin >> num;
    cout << "P1 * P2 = " << c.Evaluate(num) << endl;
    
    

    return 0;
}

