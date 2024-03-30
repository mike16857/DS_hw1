#include <iostream>
using namespace std;


class String
{
public:
    String(char *init, int m);
    // constructor using input string init of length m
    bool operator==(String t); // equality test
    bool operator!();          // empty test, true or false
    int Length();              // get the number of characters of *this
    String Concat(String t);
    // concatenation with another string t
    String Substr(int i, int j); // generate a substring i~i+j-1
    int Find(String pat);
    int FastFind(String pat);
    String Delete(int start, int length); // remove length characters beginning at start
    String CharDelete(char c); // returns the string with all occurrence of c removed.
    int Compare(String y); // compare two strings of letters of alphabet.
    // return -1 if <y, 0 if =y, and 1 if >y.
    // If two strings of letter of alphabet, x = (x0,…,xm-1) and y=(y0,…,yn-1) 
    //where xi, yj are letters, then the Compare member function will decide 
    //whether x<y, x=y, or x>y, where x < y means if xi=yi for 0≤i<j and xj<yj or if xi=yi for 0≤i≤m and m<n. 
    //x=y means m=n and xi=yi for 0≤i<n. 
    //x>y means if xi=yi for 0≤i<j and xj>yj or if xi=yi for 0≤i≤n and m>n.
    friend ostream& operator<<(ostream &, String &);
    friend istream& operator>>(istream &, String &);
private:
    void FailureFunction();
    char *str; 
    int *f; // calculated failure function
};

String::String(char *init, int m)
{   
    int i;
    str = new char[m + 1];
    for (i = 0; i < m; i++)
        str[i] = init[i];
    
    str[i] = '\0';
}

bool String::operator==(String t)
{
    
}

bool String::operator!()
{
    if (Length()) return true;
    else return false;
}

int String::Length()
{
    int i;
    for (i = 0; str[i] != '\0'; i++);
    return i;
}

String String::Concat(String t)
{

}

String String::Substr(int i, int j)
{

}

int String::Find(String pat)
{
    for (int start = 0; start <= Length() - pat.Length(); start ++) {
        int j;
        for (j=0; j < pat.Length() && str[start+j] == pat.str[j]; j++);
        if (j == pat.Length()) return start;
    }
    return -1;
}

int String::FastFind(String pat)
{
    int posP = 0, posS = 0;
    int lengthP = pat.Length(), lengthS = Length();
    while ((posP < lengthP) && (posS < lengthS)) {
        if (pat.str[posP] == str[posS]) {
            posP++;
            posS++;
        }
        else {
            if (posP == 0) posS++;
            else posP = pat.f[posP - 1] + 1;
        }
    }
    if (posP < lengthP) 
        return -1;
    else 
        return posS - lengthP;
}

String String::Delete(int start, int length)
{

}

String String::CharDelete(char c)
{

}

int String::Compare(String y)
{

}

void String::FailureFunction()
{
    int lengthP = Length();
    f[0] = -1;
    for (int j = 1; j < lengthP; j++) {
        int i = f[j - 1];
        while ((str[j] != str[i + 1]) && (i >= 0))
            i = f[i];
        if (str[j] == str[i + 1])
            f[j] = i + 1;
        else
            f[j] = -1;
    }
}

ostream& operator<<(ostream &, String &)
{

}

istream& operator>>(istream &, String &)
{

}


int main()
{
    //You should try out at least two example runs of your program to demonstrate all those functions.
}

