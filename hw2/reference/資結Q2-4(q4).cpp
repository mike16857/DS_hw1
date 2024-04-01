#include <iostream>
using namespace std;

typedef struct {
    int di, dj;
} offsets;

offsets move[8] = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};
struct Items
{
	int x, y, dir;
};

enum directions {N, NE, E, SE, S ,SW, W, NW};

typedef struct
{
	int x;
	int y;
	int dir;
} Item;

int maze[14][17]; // for the whole maze
int mark[14][17]; // to mark where it have been

template <class T>
class Stack
{
    template <class U>
    friend ostream& operator<<(ostream &os, Stack<U> &stack);
public:
    Stack (int stackCapacity = 10);
    bool IsEmpty() const;
    T& Top() const;
    void Push (const T& item);
    void Pop();
    void ChangeSize1D(T* &a, const int oldSize, const int newSize);
private:
    T* stack;
    int top;
    int capacity;
};

template <class T>
Stack<T>:: Stack(int stackCapacity): capacity(stackCapacity)
{
    if (capacity < 1) throw "Stack capacity must be > 0";
    stack = new T[capacity];
    top = -1;
}

template <class T>
inline bool Stack<T>:: IsEmpty() const { return top == -1;}

template <class T>
inline T& Stack<T>:: Top() const
{
    if (IsEmpty()) throw "Stack is empty";
    return stack[top];
}

template <class T>
void Stack<T>:: Push(const T &item)
{
    if (top == capacity - 1) {
        ChangeSize1D(stack, capacity, 2 * capacity);
        capacity *= 2;
    }
    stack[++top] = item;
}

template <class T>
void Stack<T>:: Pop()
{
    if (IsEmpty()) throw "Stack is empty. Cannot delete.";
    stack[top--].~T();
}

template <class T>
void Stack<T>:: ChangeSize1D(T* &a, const int oldSize, const int newSize)
{
    if (newSize < 0) throw "New length must be >= 0";

    T *temp = new T[newSize];
    int number = min(oldSize, newSize);    // choose the smallest Size to store
    copy(a, a + number, temp);              // copy the old array into new
    delete []a;                             // delete old array
    a = temp;
}

template <class T>
ostream& operator<<(ostream &os, Stack<T> &stack)
{
    int i;
    
    os << "total steps = " << stack.top + 2 << endl << endl;
    for (i = 0; i < stack.top + 1; i++) {
        os << "Step" << i + 1 << " : " << stack.stack[i] << endl;
    }
    os << "Step" << i + 1 << " : ";
    
    return os;
}

ostream& operator<<(ostream &os, Items &item)
{
    os << "(" << item.x << ", " << item.y << ", ";
    
    switch (item.dir) {
        case N: os << "N";
            break;
        case NE: os << "NE";
            break;
        case E: os <<"E";
            break;
        case SE: os << "SE";
            break;
        case S: os << "S";
            break;
        case SW: os << "SW";
            break;
        case W: os << "W";
            break;
        case NW: os << "NW";
            break;
        default: break;
    };
    os << ")";
    
    return os;
}

void Path(const int m, const int p)
{// ¿é¥X°g®cªº¤@­Ó¸ô®|¡]¦pªG¦³ªº¸Ü¡^¡F maze[0][i] = maze[m+1][i] = maze[j][0] = maze[j][p+1] = 1, 0 „T i „T p+1, 0 „T j „T m+1¡C±q (1, 1) ¶}©l
	mark[1][1] = 1;
	Stack<Items> stack(m * p);
	Items temp = {1, 1, E}; // ³]©w temp.x¡Btemp.y¡B»Ptemp.dir
	stack.Push(temp);
	
	while (!stack.IsEmpty()){ // °ïÅ|¤£¬OªÅªº
		temp = stack.Top();
		stack.Pop(); // ¼u¥X
		int i = temp.x; int j = temp.y; int d = temp.dir;
		while (d < 8){// ©¹«e²¾°Ê
			int g = i + move[d].di; int h = j + move[d].dj;
			if ((g == m) && (h == p)){ // ©è¹F¥X¤f
				cout << stack; // ¿é¥X¸ô®|
				cout << "(" << i << ", " << j << ", ";
				switch (d) {
        			case N: cout << "N"; break;
        			case NE: cout << "NE"; break;
        			case E: cout <<"E"; break;
        			case SE: cout << "SE"; break;
        			case S: cout << "S"; break;
					case SW: cout << "SW"; break;
        			case W: cout << "W"; break;
        			case NW: cout << "NW"; break;
        			default: break;
    			};
    			cout << ")";
				return;
			}
			if ((!maze[g][h]) && (!mark[g][h])){ 
				mark[g][h] = 1;// ·s¦ì¸m
				temp.x = i; temp.y = j; temp.dir = d; //try new direction
				stack.Push(temp); // ¥[¤J°ïÅ|
				i = g; j = h; d = N; // ²¾¨ì (g, h)
			}
			else d++; // ¸Õ¤U¤@­Ó¤è¦V
		}
	}
	cout << "No path in maze." << endl;
}

int main(void) {
    FILE *MAZE;
    int m, p;
    int i, j;
    MAZE = fopen("maze.txt", "r");          				// open the file
    
    fscanf(MAZE, "%d", &m);                 				// read m
    fscanf(MAZE, "%d", &p);                 				// read p
    for (i = 0; i < m + 2; i++){							// edge
        for (j = 0; j < p + 2; j++) {
            if (i == 0 || i == m + 1) maze[i][j] = 1;       // read in the maze
            else if (j == 0 || j == p + 1) maze[i][j] = 1;
            else fscanf(MAZE, "%d", &maze[i][j]);
        }
    }
    
    cout << "The maze is : " << endl;       				// first print the maze
    for (i = 1; i < m + 1; i++) {
        for (j = 1; j < p + 1 ; j++) {
            cout << maze[i][j] << " ";
        }
        cout << endl;
    }
    Path(m, p);     // find a path
    
    return 0;
}
