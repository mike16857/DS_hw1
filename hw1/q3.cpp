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
    // Return an index i such that pat matches the substring
    // of the object begins at position i.  Return -1 if pat
    // is empty or not a substring of the object
    String Delete(int start, int length); // remove length characters beginning
    // at start
    String CharDelete(char c); // returns the string with all occurrence of c
    // removed.
    int Compare(String y); // compare two strings of letters of alphabet.
    // return -1 if <y, 0 if =y, and 1 if >y.
    // If two strings of letter of alphabet, x = (x0,…,xm-1) and y=(y0,…,yn-1) //where xi, yj are letters, then the Compare member function will decide //whether x<y, x=y, or x>y, where x < y means if xi=yi for 0≤i<j and xj<yj //or if xi=yi for 0≤i≤m and m<n. x=y means m=n and xi=yi for 0≤i<n. x>y //means if xi=yi for 0≤i<j and xj>yj or if xi=yi for 0≤i≤n and m>n.
};
