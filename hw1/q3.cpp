#include <iostream>
using namespace std;


class String
{
public:
    String(char *init, int m);      // constructor using input string init of length m
    bool operator==(String t);      // equality test
    bool operator!();               // empty test, true or false
    int Length();                   // get the number of characters of *this
    String Concat(String t);        // concatenation with another string t
    String Substr(int i, int j);    // generate a substring i ~ i+j-1
    int Find(String pat);
    int FastFind(String pat);
    String Delete(int start, int length); // remove length characters beginning at start
    String CharDelete(char c);      // returns the string with all occurrence of c removed.
    int Compare(String y);          // compare two strings of letters of alphabet.
    // return -1 if <y, 0 if =y, and 1 if >y.
    // If two strings of letter of alphabet, x = (x0,…,xm-1) and y=(y0,…,yn-1)
    //where xi, yj are letters, then the Compare member function will decide
    //whether x<y, x=y, or x>y, where x < y means if xi=yi for 0≤i<j and xj<yj or if xi=yi for 0≤i≤m and m<n.
    //x=y means m=n and xi=yi for 0≤i<n.
    //x>y means if xi=yi for 0≤i<j and xj>yj or if xi=yi for 0≤i≤n and m>n.
    friend ostream& operator<<(ostream &, String &);
    friend istream& operator>>(istream &, String &);
    int* FailureFunction();
    int *f;
private:
    // int FailureFunction();
    char *str;
    // int *f; // calculated failure function
};

String::String(char *init, int m)
{
    str = new char[m + 1];
    for (int i = 0; i < m; i++)
        str[i] = init[i];

    str[m] = '\0';

    // int *f = FailureFunction();  // calculate failure function
}

bool String::operator==(String t)
{
    int i;
    for (i = 0; str[i] != '\0' && t.str[i] != '\0'; i++) {
        if (str[i] != t.str[i]) return false;
    }
    if (str[i] == '\0' && t.str[i] == '\0') return true;
    else return false;
}

bool String::operator!()
{
    if (Length()) return false;
    else return true;
}

int String::Length()
{
    int i;
    for (i = 0; str[i] != '\0'; i++);
    return i;
}

String String::Concat(String t)
{
    int totalLen = Length() + t.Length();
    int i, j;
    char *concat = new char[totalLen];

    // for (i = 0; i < Length(); i++) concat[i] = str[i];
    // for (j = 0; j < t.Length(); j++) concat[i + j] = t.str[j];
    copy(str, str + Length(), concat);  // copy str to concat
    copy(t.str, t.str + t.Length(), concat + Length()); // continue copying t.str to concat + len1

    String ans(concat, totalLen);
    delete [] concat;

    return ans;
}

String String::Substr(int i, int j)
{
    char *substr = new char[j];

    copy(str + i, str + i + j, substr);

    String ans(substr, j);
    delete [] substr;

    return ans;
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

int String::FastFind(String pat) // KMP algorithm // need fixing
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
    int totalLen = Length() - length;
    int i, j;
    char *remain = new char[totalLen];

    // for (i = 0; i < start; i++) remain[i] = str[i];
    // for (i = start; i < totalLen; i++) remain[i] = str[i + length];
    copy(str, str + start, remain);
    copy(str + start + length, str + Length(), remain + start);

    String ans(remain, totalLen);
    delete [] remain;

    return ans;
}

String String::CharDelete(char c)
{
    int appear = 0;
    int i, j = 0;

    for (i = 0; i < Length(); i++)
        if (str[i] == c) appear++;
    char *remain = new char[Length() - appear];

    for (i = 0; i < Length(); i++)
        if (str[i] != c)
            remain[j++] = str[i];

    String ans(remain, Length() - appear);
    delete [] remain;

    return ans;
}

int String::Compare(String y)
{
    int lengthX = Length(), lengthY = y.Length();
    int i, j;

}

int* String::FailureFunction()  // KMP failure function
{
    int *f;
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

    return f;
}

ostream& operator<<(ostream& os, String& s)
{
    os << s.str << endl;

    return os;
}

istream& operator>>(istream& is, String& s)
{
    int len;
    cout << "Length of the string: ";
    is >> len;
    char *temp = new char[len];

    cout << "Input the string: ";
    is >> temp;

    s = String(temp, len);
    delete [] temp;

    return is;
}
// istream& operator>>(istream &is, String &s) // not mine
// {
//     int l;
    
//     cout << "How long is your string : ";
//     is >> l;
//     cout << "Input your string : ";
//     char *temp = new char[l];
//     is >> temp;
//     String input(temp, l);
//     s = input;
//     delete [] temp;
    
//     return is;
// }

int main()
{
    String s1(NULL, 0), s2(NULL, 0);
    cin >> s1;
    cin >> s2;
    cout << endl;

    cout << "String s1 is: " << s1 << "with length = " << s1.Length() << endl;
    cout << "String s2 is: " << s2 << "with length = " << s2.Length() << endl;
    cout << endl;

    // operator== test, done
    // if (s1 == s2) cout << "s1 is equal to s2\n";
    // else cout << "s1 is not equal to s2\n";
    // cout << endl;

    // operator! test, done
    // if (!s1) cout << "s1 is empty\n";
    // else cout << "s1 is not empty\n";
    // if (!s2) cout << "s2 is empty\n";
    // else cout << "s2 is not empty\n";   
    // cout << endl;

    // method Concat test, done
    // String s3 = s1.Concat(s2);
    // cout << "s1.Concat(s2) is: " << s3 << "with length = " << s3.Length() << endl;
    // cout << endl;

    // method Substr test, done
    // int i, j;
    // cout << "Input i and j for substring s1: ";
    // cin >> i >> j;
    // String s4 = s1.Substr(i, j);
    // cout << "s1.Substr(" << i << ", " << j << ") = " << s4 << "with length = " << s4.Length() << endl;
    // cout << endl;

    /* method Find, done; FastFind, not done */
    String pat(NULL, 0);
    cout << "Input the pattern to find in s1: " << endl;
    cin >> pat;
    cout << "s1.Find(pat) = " << s1.Find(pat) << endl;
    for (int i = 0; i < pat.Length(); i++) cout << pat.f[i] << " ";
    // cout << "s1.FastFind(pat) = " << s1.FastFind(pat) << endl;
    cout << endl;

    // method Delete test, done
    // int start, length;
    // cout << "Input start and length for deletion of s1: ";
    // cin >> start >> length;
    // String s5 = s1.Delete(start, length);
    // cout << "s1.Delete(" << start << ", " << length << ") = " << s5 << "with length = " << s5.Length() << endl;
    // cout << endl;

    // method CharDelete test, done
    // char c;
    // cout << "Input the character to delete: ";
    // cin >> c;
    // String s6 = s1.CharDelete(c);
    // cout << "s1.CharDelete(" << c << ") = " << s6 << "with length = " << s6.Length() << endl;
    // cout << endl;

    /* method Compare test */ 
    // reinput s1 and s2
    // cout << "Input two strings to compare: ";
    // cin >> s1;
    // cin >> s2;
    // if (s1.Compare(s2) == 0) cout << "String s1 is equal to String s2" << endl;
    // else if (s1.Compare(s2) == 1) cout << "String s1 is larger than String s2" << endl;
    // else cout << "String s1 is smaller than String s2" << endl;

    return 0;
    //You should try out at least two example runs of your program to demonstrate all those functions.
}

