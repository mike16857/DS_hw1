#include<iostream>
using namespace std;

class String
{
public:
    String(char *init, int m);
    bool operator == (String t);
    bool operator!();
    int Length();
    String Concat(String t);  
    String Substr(int i, int j);
    int Find(String pat);
    String Delete(int start, int length);
    String CharDelete(char c);
    int Compare(String y);
    friend ostream& operator<<(ostream &, String &);
    friend istream& operator>>(istream &, String &);
private:
    char *str;
};

String::String(char *init, int m)
{
	str = new char[m + 1];
	for(int i = 0; i < m; i++)
		str[i] = init[i];
	str[m] = '\0';
}

int String::Length()
{
	int i = 0;
	while(str[i] != '\0')
		i++;
	return i;
}

bool String::operator == (String t)
{
	if(Length() != t.Length()) return false;
	else {
		for(int i = 0; i < Length(); i++){
			if(str[i] != t.str[i]) return false;
		}
	}
	return true;
}
bool String::operator!()
{
	if(Length()) return false;
	else return true;
}

String String::Concat(String t)
{
	int l, i, j;
	
	l = Length() + t.Length();
	char *temp = new char[l];
	for(i = 0; i < Length(); i++) temp[i] = str[i];
	for(i = Length(),j = 0; i < l; i++, j++){
		temp[i] = t.str[j];
	}
	String s(temp, l);
	return s;
}

String String::Substr(int i, int j)
{
	char *temp = new char[j];
	for(int k = 0; k < j; k++){
		temp[k] = str[i + k];
	}
	String s(temp,j);
	return s;
}

String String::Delete(int start, int length)
{
	int l;
	l = Length() - length;
	char *temp = new char[l];
	
	for(int i = 0; i < start; i++) temp[i] = str[i];
	for(int i = start; i < l; i++) temp[i] = str[i + length];
	String s(temp, l);
	return s;
}

String String::CharDelete(char c)
{
	int times = 0, i, j = 0;
	
	for(i = 0; i < Length(); i++)
		if(str[i] == c) times++;
	char *temp = new char[Length() - times];
	i = 0; j = 0;
	while(i < Length() - times){
		if(str[j] != c){
			temp[i] = str[j];
			i++; j++;
		}
		else j++;
	}
	String s(temp, Length() - times);	
	return s;
}
int String::Compare(String y)
{
	int i = 0, j = 0;
	
	while(i < Length() && j < y.Length()){
		if(str[i] == y.str[j]){
			i++; j++;
		}
		else if(str[i] < y.str[j]) return -1;
		else return 1;
	}
	return 0;
}

int String::Find(String pat)
{
	for (int start=0; start <= Length( )-pat.Length();start ++){
		int j;
		for(j=0;j<pat.Length( ) && str[start+j]==pat.str[j]; j++);
			if (j == pat.Length( ))
		return start;
	}
	return -1 ;
}
ostream& operator<<(ostream &os, String &s)
{
    os << s.str << endl;
    
    return os;
}

istream& operator>>(istream &is, String &s)
{
    int l;
    
    cout << "How long is your string : ";
    is >> l;
    cout << "Input your string : ";
    char *temp = new char[l];
    is >> temp;
    String input(temp, l);
    s = input;
    delete [] temp;
    
    return is;
}
int main(void) {
    String s1(NULL, 0);
    String s2(NULL, 0);
    String s3(NULL, 0);
    char letter, temp;
    int start, length;

    cin >> s1;
    cin >> s2;
    cout << "String 1 is : ";
    cout << s1;
    cout << "String 2 is : ";
    cout << s2;
    if (!s1) cout << "String 1 is a NULL String";
    else cout << "String 1 isn't a NULL String";
    cout << endl;
    if (!s2) cout << "String 2 is a NULL String";
    else cout << "String 2 isn't a NULL String";
    cout << endl;
    if (s1 == s2) cout << "String 1 is equal to String 2" << endl;
    else if (s1.Compare(s2) == 1) cout << "String 1 is larger than String 2" << endl;
    else cout << "String 1 is smaller than String 2" << endl;
    s3 = s1.Concat(s2);
    cout << "String 1 concate String 2 :" << s3;
    
    cout << "Which part do you want to substr in string 1(start, length): ";
    cin >> temp >> start >> temp >> length >>temp;
    s3 = s1.Substr(start, length);
	cout << "String Substr is : ";
    cout << s3;
    cout << "We can find the pattern starts in String 2 from ";
    cout << s2.Find(s3) << endl;
    cout << "Which part do you want to delete in string 1(start, length): ";
    cin >> temp >> start >> temp >> length >>temp;
    s3 = s1.Delete(start, length);
    cout << "String 1 is : ";
    cout << s3;
    cout << "Which letter do you want to delete in string 1 : ";
    cin >> letter;
    s3 = s1.CharDelete(letter);
    cout << "String 1 is : ";
    cout << s3;

    return 0;
}
