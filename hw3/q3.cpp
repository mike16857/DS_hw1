#include <iostream>
using namespace std;

struct Term 
{
    int coef;
    int exp;
    Term Set(int c, int e) { coef = c; exp = e; return *this; }
};

class Polynomial
{
public:
// Polynomial operations
private:
    Chain<Term> poly; // Chain poly is a data member of Poly
}
