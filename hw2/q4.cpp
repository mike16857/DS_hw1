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
int mark[14][17]; // to mark where it has been

/* Stack */
template <class T>
class Stack
{   
    template <class U>
	friend ostream& operator<<(ostream &os, Stack<U> &stack);
	template <class U>
	friend istream& operator>>(istream &is, Stack<U> &stack);
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
    int top;
    int capacity;
    T* stack;
};

template <class T>
ostream& operator<<(ostream &os, Stack<T> &stack)
{
    os << "Stack: ( " << stack.array[0];
    for (int i = 1; i <= stack.top; i++)
        os << ", " << stack.array[i];
    os << " )" << endl;
    return os;
}

template <class T>
istream& operator>>(istream &is, Stack<T> &stack)
{
    int n;
    T element;

    cout << "How many elements do you want to push?";
    cin >> n;
    for (int i = 0; i < n; i++) {
        is >> element;
        stack.Push(element);
    }
    return is;
}

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
                cout << i << " " << j << endl;  // 路徑上的上兩個方塊
                cout << m << " " << p << endl;
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

int main()
{

}