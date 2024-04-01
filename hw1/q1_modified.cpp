#include <iostream>
#include <algorithm>
using namespace std;

class Polynomial;

class Term
{
    friend Polynomial;
    friend ostream &operator<<(ostream &os, Polynomial &poly);
    friend istream &operator>>(istream &is, Polynomial &poly);

private:
    float coef;
    int exp;
};

class Polynomial
{
    // p(x) = a0 x^e0 + … + an x^en
    // where ai is nonzero float and ei is non-negative int
public:
    Polynomial();
    // construct the polynomial p(x) = 0
    ~Polynomial();
    // destructor
    Polynomial(const Polynomial &other); 
    // Copy constructor
    Polynomial& operator=(const Polynomial &other); 
    // Copy assignment operator
    Polynomial Add(Polynomial poly);
    Polynomial Subt(Polynomial poly);
    Polynomial Mult(Polynomial poly);
    // return the product of *this and poly
    void NewTerm(const float theCoeff, const int theExp);
    float Eval(float f);
    int operator!();
    // if *this is the zero polynomial, return 1; else return 0;
    float Coef(int e);
    int LeadExp();
    friend ostream &operator<<(ostream &os, Polynomial &poly);
    friend istream &operator>>(istream &is, Polynomial &poly);

private:
    Term *termArray;
    int capacity;
    int terms;
};


Polynomial::Polynomial()
{
    capacity = 1;
    terms = 0;
    termArray = new Term[capacity];
    termArray[0].exp = 0;
    termArray[0].coef = 0;
}

// Copy constructor
Polynomial::Polynomial(const Polynomial &other) {
    capacity = other.capacity;
    terms = other.terms;
    termArray = new Term[capacity];
    for (int i = 0; i < terms; ++i) {
        termArray[i] = other.termArray[i];
    }
}

// Copy assignment operator
Polynomial& Polynomial::operator=(const Polynomial &other) {
    if (this != &other) {
        delete[] termArray;
        capacity = other.capacity;
        terms = other.terms;
        termArray = new Term[capacity];
        for (int i = 0; i < terms; ++i) {
            termArray[i] = other.termArray[i];
        }
    }
    return *this;
}

Polynomial::~Polynomial()
{
    delete [] termArray;
}

Polynomial Polynomial::Add(Polynomial b)
{
    Polynomial c;
    int aPos = 0, bPos = 0;

    while ((aPos < terms) && (bPos < b.terms)) {
        if (termArray[aPos].exp == b.termArray[bPos].exp) {
            float t = termArray[aPos].coef + b.termArray[bPos].coef;
            if (t) c.NewTerm(t, termArray[aPos].exp);
            aPos++, bPos++;
        }
        else if (termArray[aPos].exp > b.termArray[bPos].exp) {
            c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
            aPos++;
        }
        else {
            c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
            bPos++;
        }
    }

    for (; aPos < terms; aPos++)
        c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
    for (; bPos < b.terms; bPos++)
        c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);

    return c;
}

Polynomial Polynomial::Subt(Polynomial b)
{
    Polynomial c;
    int aPos = 0, bPos = 0;

    while ((aPos < terms) && (bPos < b.terms)) {
        if (termArray[aPos].exp == b.termArray[bPos].exp) {
            float t = termArray[aPos].coef - b.termArray[bPos].coef;
            if (t) c.NewTerm(t, termArray[aPos].exp);
            aPos++, bPos++;
        }
        else if (termArray[aPos].exp > b.termArray[bPos].exp) {
            c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
            aPos++;
        }
        else {
            c.NewTerm((-1) * b.termArray[bPos].coef, b.termArray[bPos].exp);
            bPos++;
        }
    }

    for (; aPos < terms; aPos++)
        c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
    for (; bPos < b.terms; bPos++)
        c.NewTerm((-1) * b.termArray[bPos].coef, b.termArray[bPos].exp);

    return c;
}

Polynomial Polynomial::Mult(Polynomial b)
{
	Polynomial c, temp;
	int aPos, bPos;
	int exp;
	float coef;

	for (aPos = 0; aPos < terms; aPos++) {
		for (bPos = 0; bPos < b.terms; bPos++) {
			temp.terms = 0;
        	temp.termArray[0].exp = 0;
        	temp.termArray[0].coef = 0;
			exp = termArray[aPos].exp + b.termArray[bPos].exp;
			coef = termArray[aPos].coef * b.termArray[bPos].coef;
			temp.NewTerm(coef, exp);
			c = c.Add(temp);
		}
	}
	return c;
}

void Polynomial::NewTerm(const float theCoeff, const int theExp)
{
    if (terms == capacity) {
        capacity *= 2;
        Term *temp = new Term[capacity];
        copy(termArray, termArray + terms, temp);
        delete [] termArray;
        termArray = temp;
    }
    termArray[terms].coef = theCoeff;
    termArray[terms++].exp = theExp;
}

float Polynomial::Eval(float f)
{
    float val = 0;
    for (int i = 0; i < terms; i++) {
        float tmp = 1;
        for (int j = 0; j < termArray[i].exp; j++)
            tmp *= f;
        val += tmp * termArray[i].coef;
    }

    return val;
}

int Polynomial::operator!()
{
    int isZero = 1;
    for (int i = 0; i < terms; i++)
        if (termArray[i].coef != 0) isZero = 0;

    return isZero;
}

float Polynomial::Coef(int e)
{
    float coe = 0;

    for (int i = 0; i < terms; i++)
        if (termArray[i].exp == e) {
            coe = termArray[i].coef;
            break;
        }

    return coe;
}

int Polynomial::LeadExp()
{
    int leadExp = termArray[0].exp;
    for (int i = 1; i < terms; i++) {
        if (termArray[i].exp > leadExp)
            leadExp = termArray[i].exp;
    }
    return leadExp;
}

ostream& operator<<(ostream& os, Polynomial &poly)
{
	float temp;

	if (!poly) os << "0" << endl;
	else {
		if (poly.termArray[0].coef == 0);
		else if (poly.termArray[0].coef == 1 && poly.termArray[0].exp == 1)
            os << "x";
		else if (poly.termArray[0].coef != 1 && poly.termArray[0].exp == 1)
			os << poly.termArray[0].coef << "x";
		else if (poly.termArray[0].coef == 1 && poly.termArray[0].exp > 1)
			os << "x^" << poly.termArray[0].exp;
		else if (poly.termArray[0].coef != 1 && poly.termArray[0].exp > 1)
			os << poly.termArray[0].coef << "x^" << poly.termArray[0].exp;
		else os << poly.termArray[0].coef;

		if (poly.terms > 1){
			for (int i = 1; i < poly.terms; i++) {
				temp = poly.termArray[i].coef;
				if (temp < 0) {
					os << " -";
					temp = (-1) * temp;
				}
				else if (temp > 0) os << " +";

				if (temp == 0);
				else if (temp == 1 && poly.termArray[i].exp == 1)
                    os << "x";
				else if (temp != 1 && poly.termArray[i].exp == 1)
					os << temp << "x";
				else if (temp == 1 && poly.termArray[i].exp > 1)
					os << "x^" << poly.termArray[i].exp;
				else if (temp != 1 && poly.termArray[i].exp > 1)
					os << temp << "x^" << poly.termArray[i].exp;
				else os << temp;
			}
		}
		os << endl;
	}
	return os;
}

istream& operator>>(istream& is, Polynomial &poly)
{
    float coef;
    int exp;
    char temp;

    cout << "Please input in the form {(coef,exp),(coef,exp),...} : ";

    while ((temp = getchar()) != '}') {
        getchar();
        is >> coef >> temp >> exp;
        getchar();
        poly.NewTerm(coef, exp);
    }
    getchar();

    return is;
}


int main(){
    Polynomial a, b, add, sub, mul;

    cout << "Input Polynomial a: " << endl;
    cin >> a;
    cout << "Input Polynomial b: " << endl;
    cin >> b;

    add = a.Add(b);
    sub = a.Subt(b);
    mul = a.Mult(b);

    cout << "Polynomial a = " << a;
    cout << "Polynomial b = " << b;
    cout << "a + b = " << add;
    cout << "a - b = " << sub;
    cout << "a * b = " << mul;

    cout << "a(x = 1) = " << a.Eval(1) << endl;
    cout << "b(x = 2) = " << b.Eval(2) << endl;
    cout << "a.Coef(5) = " << a.Coef(5) << endl;
    cout << "b.LeadExp = " << b.LeadExp() << endl;
    // use >> to build polynomial object a = 2x3 + 3x2 + 4x + 5, b = x3 – x2 + x – 1
    // demo  <<
    // demo  << results of Add, Subt, Mul
    // demo results of a.Exal(1), b.Eval(2), a.Coef(5), b.LeadExp
    return 0;
}

