#include <iostream>
#include <cstring>
using namespace std;

const int TABLE_SIZE = 26;

// Symbol Table using Linear Probing
class LinearProbingSymbolTable
{
private:
    char* table[TABLE_SIZE];
public:
    LinearProbingSymbolTable(){for(int i = 0; i < TABLE_SIZE; i++) table[i] = NULL;}
    int hash(char key){return key - 'a';}
    void insert(const char* key)
	{
        int index = hash(key[0]);
        int i = index;

        while (table[i] != NULL) {
            i = (i + 1) % TABLE_SIZE;
            if (i == index) {
                cout << "Symbol table is full." << endl;
                return;
            }
        }

        table[i] = new char[strlen(key) + 1];
        strcpy(table[i], key);
        cout << "Inserted \"" << key << "\" in the table" << endl;
    }
    bool search(const char* key)
	{
        int index = hash(key[0]);
        int i = index;

        while(table[i] != NULL){
            if(strcmp(table[i], key) == 0) return true;
            i = (i + 1) % TABLE_SIZE;
            if(i == index) break;
        }

        return false;
    }
};

// Symbol Table using Chaining
class ChainingSymbolTable
{
private:
    struct Node{
        char* key;
        Node* next;
    };
	Node* table[TABLE_SIZE];
public:
    ChainingSymbolTable(){for(int i = 0; i < TABLE_SIZE; i++) table[i] = NULL;}

    int hash(char key){return key - 'a';}

    void insert(const char* key)
	{
        int index = hash(key[0]);

        Node* newNode = new Node;
        newNode->key = new char[strlen(key) + 1];
        strcpy(newNode->key, key);
        newNode->next = NULL;

        if(table[index] == NULL) table[index] = newNode;
		else{
            Node* curr = table[index];
            while (curr->next != NULL) curr = curr->next;
            curr->next = newNode;
        }
        cout << "Inserted \"" << key << "\" in the table" << endl;
    }

    bool search(const char* key)
	{
        int index = hash(key[0]);

        Node* curr = table[index];
        while (curr != NULL){
            if (strcmp(curr->key, key) == 0) return true;
            curr = curr->next;
        }

        return false;
    }
};

int main() {
    LinearProbingSymbolTable d1;
    ChainingSymbolTable d2;

    // Setting up 10 key objects
    const char* keys[] = {"abc", "def", "ghi", "jkl", "mno", "pqr", "stu", "vwx", "yz", "hello"};

    // Inserting keys into d1
    for(int i = 0; i < 10; i++){
        d1.insert(keys[i]);
    }
	cout << endl;
	
	// Displaying d1
	cout << "d1:" << endl;
	for(int i = 0; i < 10; i++){
    	if(d1.search(keys[i])){
        	cout << keys[i] << endl;
    	}
	}
    cout << endl;

    // Demo search function of d1
    cout << "Search Results in d1:" << endl;
    const char* searchKeys[] = {"abc", "def", "xyz", "jkl", "hello"};

    for(int i = 0; i < 5; i++){
        cout << "Search " << searchKeys[i] << " : ";
        if(d1.search(searchKeys[i])){
            cout << "Found" << endl;
        }
		else{
            cout << "Not Found" << endl;
        }
    }
    cout << endl;

    // Setting up 10 key objects
    const char* keys2[] = {"apple", "banana", "cherry", "date", "elderberry", "fig", "grape", "honeydew", "kiwi", "lemon"};

    // Inserting keys into d2
    for (int i = 0; i < 10; i++){
        d2.insert(keys2[i]);
    }
    cout << endl;

    // Displaying d2
	cout << "d2:" << endl;
	for(int i = 0; i < 10; i++){
    	if(d2.search(keys2[i])){
        	cout << keys2[i] << endl;
    	}
	}
    cout << endl;

    // Demo search function of d2
    cout << "Search Results in d2:" << endl;
    const char* searchKeys2[] = {"apple", "banana", "xyz", "date", "lemon"};

    for(int i = 0; i < 5; i++) {
        cout << "Search " << searchKeys2[i] << " : ";
        if(d2.search(searchKeys2[i])) {
            cout << "Found" << endl;
        }
		else{
            cout << "Not Found" << endl;
        }
    }

    return 0;
}
