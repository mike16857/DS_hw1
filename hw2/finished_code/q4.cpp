#include <iostream>
using namespace std;


struct Offsets
{
    int di, dj;
};

Offsets move[8] = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};

enum directions {N, NE, E, SE, S, SW, W, NW};

struct Items
{
    int x, y, dir;
};

int maze[14][17]; // for the whole maze
int mark[14][17]; // array that marks where the probe has been to

/* Stack */
template <class T>
class Stack
{   
    template <class U>
	friend ostream& operator<<(ostream &os, Stack<U> &stack);
	template <class U>
    friend void ChangeSize1D(U* &a, const int oldSize, const int newSize);
public:
    Stack (int stackCapacity = 10);
    ~Stack();
    bool IsEmpty() const;
    void Push(const T& item);
    void Pop();
    T& Top() const;
private:
    T* stack;
    int top;
    int capacity;
};

template <class U>
void ChangeSize1D(U* &a, const int oldSize, const int newSize)
{
    if (newSize < 0) throw "New length must be >= 0";
    U *temp = new U[newSize];
    int number = min(oldSize, newSize);
    copy(a, a + number, temp);
    delete []a;
    a = temp;
}

template <class T> 
Stack<T>::Stack(int stackCapacity):capacity(stackCapacity)
{
    if (capacity < 1) throw "Stack capacity must be > 0";
    stack = new T[capacity];
    top = -1;
}

template <class T> 
Stack<T>::~Stack() 
{
    delete [] stack;
}

template <class T>
bool Stack<T>::IsEmpty() const
{
    return top == -1;
}

template <class T>
void Stack<T>::Push(const T& item)
{// add x to stack
    if (top == capacity - 1) {
        ChangeSize1D (stack, capacity, 2 * capacity);
        capacity *= 2;
    }
    stack[++top] = item;
}

template <class T>
void Stack<T>::Pop()
{
    if (IsEmpty()) throw "Stack is empty, cannot delete";
    stack[top--].~T();
}

template <class T>
T& Stack<T>::Top() const
{
    if (IsEmpty()) throw "Stack is empty.";
    return stack[top];
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
{   // 輸出迷宮的一個路徑（如果有的話）； maze[0][i] = maze[m+1][i] = maze[j][0] = maze[j][p+1] = 1, 0  i  p+1, 0  j  m+1。從 (1, 1) 開始
    mark[1][1] = 1;
    Stack<Items> stack(m * p);
    Items temp{1, 1, E}; // 設定 temp.x、temp.y、與temp.dir
    stack.Push(temp);

    while (!stack.IsEmpty()) { // 堆疊不是空的
        temp = stack.Top();
        stack.Pop(); // 彈出
        int i = temp.x; int j = temp.y; int d = temp.dir;

        while (d < 8) { // 往前移動
            int g = i + ::move[d].di; int h = j + ::move[d].dj;
            if ((g == m) && (h == p)) { // 抵達出口
                cout << stack;                  // 輸出路徑
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
            if ((!maze[g][h]) && (!mark[g][h])) {   // 新位置
                mark[g][h] = 1;
                temp.x = i; temp.y = j; temp.dir = d; //try new direction
                stack.Push(temp);                     // 加入堆疊
                i = g; j = h; d = N;                  // 移到 (g, h)
            }
            else d++; // 試下一個方向
        }
    }
    cout << "No path in maze." << endl;
}

int main() {
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
    cout << endl;
    
    Path(m, p);     // find a path
    
    return 0;
}