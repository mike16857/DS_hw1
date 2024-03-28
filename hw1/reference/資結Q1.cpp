#include<iostream>
using namespace std;

class Polynomial;
class Term{
	friend Polynomial;
	friend ostream& operator<<(ostream& os, Polynomial &poly);
	friend istream& operator>>(istream& is, Polynomial &poly);
private:
   float coef;
   int  exp;
};

class Polynomial {
public:
    Polynomial();
    Polynomial Add(Polynomial poly);
    Polynomial Mult(Polynomial poly);
    float Eval(float f);
    int operator!();
	float Coef(int e);
	int LeadExp();
    void NewTerm(const float theCoeff, const int theExp);
	friend ostream& operator<<(ostream& os, Polynomial &poly);
	friend istream& operator>>(istream& is, Polynomial &poly);
private:
	Term* termArray;
	int	capacity;
	int	terms;
};

Polynomial::Polynomial()
{
    capacity = 1;
    terms = 0;
    termArray = new Term[capacity];
    termArray[0].exp = 0;
    termArray[0].coef = 0;
}

void Polynomial::NewTerm(const float theCoeff, const int theExp)
{
	if (terms == capacity){
		capacity *= 2;
		Term *temp = new Term[capacity];
		copy(termArray, termArray + terms, temp);
		delete [] termArray ;
		termArray = temp;
	}
	termArray [terms].coef = theCoeff;
	termArray [terms++].exp = theExp;
}

Polynomial Polynomial::Add(Polynomial poly)
{
	Polynomial c;
	int aPos = 0, bPos = 0;
	
	while ((aPos < terms) && (bPos < poly.terms)){
		if (termArray[aPos].exp == poly.termArray[bPos].exp) {
			float t = termArray[aPos].coef + poly.termArray[bPos].coef;
			if (t) c.NewTerm(t, termArray[aPos].exp);
			aPos++; bPos++;
		}	
		else if (termArray[aPos].exp < poly.termArray[bPos].exp) {
			c.NewTerm(poly.termArray[bPos].coef, poly.termArray[bPos].exp);
			bPos++;
		}
		else {
			c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
			aPos++;
		}
	} 
	for ( ; aPos < terms ; aPos++)
		c.NewTerm (termArray[aPos].coef, termArray[aPos].exp);
	for ( ; bPos < poly.terms ; bPos++)
		c.NewTerm (poly.termArray[bPos].coef, poly.termArray[bPos].exp);
	return c;
}

Polynomial Polynomial::Mult(Polynomial poly)
{
	Polynomial c, temp;
	int aPos, bPos;
	int exp;
	float coef;
	
	for(aPos = 0; aPos < terms; aPos++){
		for(bPos = 0; bPos < poly.terms; bPos++){		
			temp.terms = 0;
        	temp.termArray[0].exp = 0;
        	temp.termArray[0].coef = 0;
			exp = termArray[aPos].exp + poly.termArray[bPos].exp;
			coef = termArray[aPos].coef * poly.termArray[bPos].coef;
			temp.NewTerm(coef, exp);
			c = c.Add(temp);
		}
	}
	return c;
}

float Polynomial::Eval(float f)
{
	int Pos;
	float temp, sum = 0;
	
	for(Pos = 0; Pos < terms; Pos++){
		temp = 1;
		for(int i = 0; i < termArray[Pos].exp; i++){
			temp *= f;
		}
		temp *= termArray[Pos].coef;
		sum += temp;
	}
	return sum;
}

int Polynomial::operator!()
{
	int zero = 0;
	
	for(int i = 0; i < terms; i++)
		if(termArray[i].coef== 0) zero++;
	if (zero == terms) return 1;
    else return 0;
}

float Polynomial::Coef(int e)
{
	float ans;
	
	for(int i = 0; i < terms; i++){
		if(termArray[i].exp == e) ans = termArray[i].coef;
	}
	return ans;
}

int Polynomial::LeadExp()
{
	int max = termArray[0].exp;
	
	for(int i = 1; i < terms; i++){
		if(termArray[i].exp > max) max = termArray[i].exp;
	}
	return max;
}

ostream& operator<<(ostream& os, Polynomial &poly)
{
	float temp;
	
	if(!poly) os << "0" << endl;
	else{
		if(poly.termArray[0].coef == 0);
		else if(poly.termArray[0].coef == 1 && poly.termArray[0].exp == 1) os << "x";
		else if(poly.termArray[0].coef != 1 && poly.termArray[0].exp == 1) 
			os << poly.termArray[0].coef << "x";
		else if(poly.termArray[0].coef == 1 && poly.termArray[0].exp > 1) 
			os << "x^" << poly.termArray[0].exp;
		else if(poly.termArray[0].coef != 1 && poly.termArray[0].exp > 1)
			os << poly.termArray[0].coef << "x^" << poly.termArray[0].exp;
		else os << poly.termArray[0].coef;
		if(poly.terms > 1){
			for(int i = 1; i < poly.terms; i++){
				temp = poly.termArray[i].coef;
				if(temp < 0){
					os << " -";
					temp = (-1) * temp;
				}
				else if (temp > 0) os << " +";
				if(temp == 0);
				else if(temp == 1 && poly.termArray[i].exp == 1) os << "x";
				else if(temp != 1 && poly.termArray[i].exp == 1) 
					os << temp << "x";
				else if(temp == 1 && poly.termArray[i].exp > 1) 
					os << "x^" << poly.termArray[i].exp;
				else if(temp != 1 && poly.termArray[i].exp > 1)
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
    
    cout << "Please input in the form {(coef,exp)} : ";

    while ((temp = getchar()) != '}') {
        getchar();
        is >> coef >> temp >> exp;
        getchar();
        poly.NewTerm(coef, exp);
    }
    getchar();
    
    return is;
}

int main(void) {
    Polynomial a, b, c, d;
    float f;
    
    cin >> a;
    cin >> b;
    c = a.Add(b);
    d = a.Mult(b);
    
    cout << "p1(x) = " << a;
    cout << "Exponential of Lead term: " << a.LeadExp() << endl;
    cout << "Coefficient of Lead term: " << a.Coef(a.LeadExp()) << endl;
    if (!a) cout << "p1(x) is a zero polynomial" << endl;
    else cout << "p1(x) isn't a zero polynomial" << endl;
    
    cout << "p2(x) = " << b;
    cout << "Exponential of Lead term: " << b.LeadExp() << endl;
    cout << "Coefficient of Lead term: " << b.Coef(b.LeadExp()) << endl;
    if (!b) cout << "p2(x) is a zero polynomial" << endl;
    else cout << "p2(x) isn't a zero polynomial" << endl;
    cout << "p1(x) + p2(x) = " << c;
	cout << "p1(x) * p2(x) = " << d;
    cout << "When x = ";
	cin >> f;
    cout << "p1(x) + p2(x) = " << c.Eval(f) << endl;
    cout << "p1(x) * p2(x) = " << d.Eval(f) << endl;
    
    return 0;
}

