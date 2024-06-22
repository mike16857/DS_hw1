#include <iostream>
#include <string>
using namespace std;


template <class T>
void InsertionSort(T *arr, const int n)
{ // sort a[1:n] into nondecreasing order
    for (int i = 1; i < n; ++i) {
        T key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

template <class T>
void QuickSort(T *a, const int left, const int right)
{ // sort a[left:right] into nondecreasing, a[left] as pivot
    if (left < right) {
        T & pivot = a[left];
        int i = left;
        int j = right + 1;
        do {
            do j--; while (a[j] > pivot); //find a key ≤pivot
            do i++; while (a[i] <= pivot); //find a key >pivot
            if (i < j) swap(a[i], a[j]);
        } while (i < j);
        swap(pivot, a[j]); //place the pivot between 2 lists
        QuickSort(a, left, j - 1); // recursion
        QuickSort(a, j + 1, right); // recursion
    }
}

// template <class T>
// void Merge(T *a, T *b, const int k, const int m, const int n)
// { // a[k:m], a[m+1:n] are sorted, merged to b[k:n]
//     int i1, i2, i3;
//     for (i1 = k, i2 = m+1, i3 = k;
//          i1 <= m && i2 <= n; i3++) {
//         if (a[i1] <= a[i2]) {
//             b[i3] = a[i1];
//             i1++;
//         } 
//         else {
//             b[i3] = a[i2];
//             i2++;
//         }
//     }
//     // copy remaining records, if any, of 1st sublist
//     if(i2 > n) copy(a + i1, a + m + 1, b + i3);
//     // copy remaining records, if any, of 2nd sublist
//     if(i1 > m) copy(a + i2, a + n + 1, b + i3);
// }
// template <class T>
// void MergePass(T *a, T *b, const int n, const int s)
// {//adjacent pairs of sublist of size s are merged from a to b. n = # records in a
//     int i;
//     for (i = 1; //i the first position in first of the sublists merged
//          i <= n-(2*s)+1; //enough elements for 2 sublists of length s?
//          i += 2*s) {
//         Merge(a, b, i, i+s-1, i+(2*s)-1);
//     }
//     // merge remaining lists of size < 2*s
//     if ((i + s-1) < n) //one full and one partial lists
//         Merge(a, b, i, i+s-1, n);
//     else //only one partial lists remained
//         copy(a+i, b+n+1, b+i);
// }
// template <class T>
// void MergeSort(T *a, const int n)
// { // sort a[1:n] into non-decreasing order
//     T *tempList = new T[n+1];
//     // s is the length of the currently merged sublist
//     for (int s = 1; s < n; s *= 2) {
//         MergePass(a, tempList, n, s);
//         s *= 2;
//         MergePass(tempList, a, n, s);
//     }
//     delete [] tempList;
// }
template<typename T>
void Merge(T *arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // vector<T> L(n1);
    // vector<T> R(n2);
    T *L = new T[n1];
    T *R = new T[n2];

    for (int i = 0; i < n1; ++i)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; ++j)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            ++i;
        } else {
            arr[k] = R[j];
            ++j;
        }
        ++k;
    }

    while (i < n1) {
        arr[k] = L[i];
        ++i;
        ++k;
    }

    while (j < n2) {
        arr[k] = R[j];
        ++j;
        ++k;
    }
}
template<typename T>
void MergeSort(T *arr, const int n) {
    int currSize;
    int leftStart;

    for (currSize = 1; currSize <= n - 1; currSize = 2 * currSize) {
        for (leftStart = 0; leftStart < n - 1; leftStart += 2 * currSize) {
            int mid = min(leftStart + currSize - 1, n - 1);
            int rightEnd = min(leftStart + 2 * currSize - 1, n - 1);
            Merge(arr, leftStart, mid, rightEnd);
        }
    }
}

// template <class T>
// int ListMerge(T* a, int* link, const int start1, const int start2)
// {   // 兩個排序好的鏈chain分別從start1及start2開始，將它們合併
//     // 將link[0]當作一個暫時的標頭。回傳合併好的鏈的開頭。
//     int iResult = 0; // 結果鏈的最後一筆記錄
//     int i1, i2;
//     for (i1 = start1, i2 =start2; i1 && i2;)
//         if (a[i1] <= a[i2]) {
//             link[iResult] = i1;
//             iResult = i1; i1 = link[i1];
//         }
//         else {
//             link[iResult] = i2;
//             iResult = i2; i2 =link[i2]; 
//         }
//     // 將其餘的記錄附接至結果鏈
//     if (i1 == 0) link[iResult] = i2;
//     else link[iResult] = i1;
//     return link[0];
// }
// template <class T>
// int rMergeSort(T* a, int* link, const int left, const int right)
// {   // 要排序的是a[left:right]。對於所有i，link[i] 初始化為0。
//     // rMergeSort回傳排序好的鏈chain的第一個元素之索引值。
//     // To sort a[1:n], invoke rMergeSort(a,link,1,n);
//     if (left >= right) return left; //base case
//     int mid = (left + right) /2;
//     return ListMerge(a, link,
//                      rMergeSort(a, link, left, mid), // 排序左半邊
//                      rMergeSort(a, link, mid + 1, right));// 排序右半邊
// }
template<typename T>
void RecursiveMergeSortHelper(T *arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        RecursiveMergeSortHelper(arr, left, mid);
        RecursiveMergeSortHelper(arr, mid + 1, right);
        Merge(arr, left, mid, right);
    }
}
template<typename T>
void rMergeSort(T *arr, const int n) {
    RecursiveMergeSortHelper(arr, 0, n - 1);
}

template <class T>
void Adjust(T *arr, const int root, const int n)
{
    // two subtrees are max heaps already
    // same procedure as the trickling-down procedure
    // T e = a[root];
    // //2*root is root's left child
    // int j;
    // for (j = 2 * root; j <= n; j *=2) {
    //     if (j < n && a[j] < a[j+1]) // j and j+1 are siblings
    //         j++; // make j be the max child
    //     if (e >= a[j]) 
    //         break;
    //     a[j / 2] = a[j]; // move jth record up the path
    // }
    // a[j / 2] = e;
    int largest = root;
    int left = 2 * root + 1;
    int right = 2 * root + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != root) {
        swap(arr[root], arr[largest]);
        Adjust(arr, largest, n);
    }
}
template <class T>
void HeapSort(T *a, const int n)
{   // sort a[1..n] into non-decreasing order
    // a[n/2] is the parent of the last node, a[n]
    for (int i = n / 2 - 1; i >= 0; --i) // buttom-up heapification
        Adjust(a, i, n);// make the tree rooted at i be a max heap

    for (int i = n - 1; i >= 0; --i) {
        swap(a[0], a[i]); // move one record from heap to list
        Adjust(a, 0, i); // heapify
    }
}

template <class T>
void PrintList(T *arr) {
    for (int i = 0; i < 20; ++i)
        cout << arr[i] << " ";
    cout << endl;
}


int main()
{
    char charList[20] = {'2', '0', '1', '9', '1', '0', '2', '1', '2', '3', '1', '1', '2', '0', '1', '9', '1', '0', '2', '1'};
    int intList[20] = {0, 3, 5, 2, 1, 4, 6, 8, 7, 9, 10, 12, 11, 13, 15, 14, 17, 16, 19, 18};
    int intList2[20] = {20, 1, 3, 4, 6, 3, 8, 4, 9, 3, 5, 2, 4, 6, 7, 9, 0, 1, 3, 5};
    float floatList[20] = {2.0f, 0.0f, 3.0f, 4.0f, 6.0f, 3.0f, 8.0f, 4.0f, 9.0f, 3.0f, 5.0f, 2.0f, 4.0f, 6.0f, 7.0f, 9.0f, 0.0f, 1.0f, 3.0f, 5.0f};
    string stringList[20] = {"20", "13", "34", "4", "6", "3", "8", "4", "9", "3", "5", "2", "4", "6", "7", "9", "0", "1", "3", "5"};

    cout << "Unsorted charList: ";
    PrintList(charList);
    InsertionSort(charList, 20);
    cout << "Sorted charList (Insertion Sort): ";
    PrintList(charList);
    cout << endl;
    
    cout << "Unsorted intList: ";
    PrintList(intList);
    QuickSort(intList, 0, 19);
    cout << "Sorted intList (Quick Sort): ";
    PrintList(intList);
    cout << endl;

    cout << "Unsorted floatList: ";
    PrintList(floatList);
    MergeSort(floatList, 20);
    cout << "Sorted floatList (Iterative Merge Sort): ";
    PrintList(floatList);
    cout << endl;

    cout << "Unsorted stringList: ";
    PrintList(stringList);
    rMergeSort(stringList, 20);
    cout << "Sorted stringList (Recursive Merge Sort): ";
    PrintList(stringList);
    cout << endl;

    cout << "Unsorted intList2: ";
    PrintList(intList2);
    HeapSort(intList2, 20);
    cout << "Sorted intList2 (Heap Sort): ";
    PrintList(intList2);
    cout << endl;


    return 0;
}