template <class T>
void InsertionSort(T *a, const int n)
{ // sort a[1:n] into nondecreasing order
    for (int j = 2; j <= n ; j++) {
        a[0] = a[j];
        for (int i = j - 1; a[i] > a[0]; i--) {
            a[i + 1] = a [i];
        }
        a[i + 1] = a[0];
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

template <class T>
void Merge(T *a, T *b, const int k, const int m, const int n)
{ // a[k:m], a[m+1:n] are sorted, merged to b[k:n]
    int i1, i2, i3;
    for (i1 = k, i2 = m+1, i3 = k;
         i1 <= m && i2 <= n; i3++) {
        if (a[i1] <= a [i2]) {
            b [i3] = a [i1];
            i1++;
        } 
        else {
            b [i3] = a [i2];
            i2++;
        }
    }
    // copy remaining records, if any, of 1st sublist
    if(i2 > n) copy (a + i1, a + m + 1, b + i3);
    // copy remaining records, if any, of 2nd sublist
    if(i1 > m) copy (a + i2, a + n + 1, b + i3);
}
template <class T>
void MergePass(T *a, T *b, const int n, const int s)
{//adjacent pairs of sublist of size s are merged from a to b. n = # records in a
    int i;
    for (i = 1; //i the first position in first of the sublists merged
         i <= n-(2*s)+1; //enough elements for 2 sublists of length s?
         i += 2*s) {
        Merge(a, b, i, i+s-1, i+(2*s)-1);
    }
    // merge remaining lists of size < 2*s
    if ((i + s-1) < n) //one full and one partial lists
        Merge(a, b, i, i+s-1, n);
    else //only one partial lists remained
        copy(a+i, b+n+1, b+i);
}
template <class T>
void MergeSort(T *a, const int n)
{ // sort a[1:n] into non-decreasing order
    T *tempList = new T[n+1];
    // s is the length of the currently merged sublist
    for (int s = 1; s < n; s *= 2) {
        MergePass(a, tempList, n, s);
        s *= 2;
        MergePass(tempList, a, n, s);
    }
    delete [] tempList;
}

template <class T>
int ListMerge(T* a, int* link, const int start1, const int start2)
{   // 兩個排序好的鏈chain分別從start1及start2開始，將它們合併
    // 將link[0]當作一個暫時的標頭。回傳合併好的鏈的開頭。
    int iResult = 0; // 結果鏈的最後一筆記錄
    int i1, i2;
    for (i1 = start1, i2 =start2; i1 && i2;)
        if (a[i1] <= a[i2]) {
            link[iResult] = i1;
            iResult = i1; i1 = link[i1];
        }
        else {
            link[iResult] = i2;
            iResult = i2; i2 =link[i2]; 
        }
    // 將其餘的記錄附接至結果鏈
    if (i1 == 0) link[iResult] = i2;
    else link[iResult] = i1;
    return link[0];
}
template <class T>
int rMergeSort(T* a, int* link, const int left, const int right)
{   // 要排序的是a[left:right]。對於所有i，link[i] 初始化為0。
    // rMergeSort回傳排序好的鏈chain的第一個元素之索引值。
    // To sort a[1:n], invoke rMergeSort(a,link,1,n);
    if (left >= right) return left; //base case
    int mid = (left + right) /2;
    return ListMerge(a, link,
                     rMergeSort(a, link, left, mid), // 排序左半邊
                     rMergeSort(a, link, mid + 1, right));// 排序右半邊
}

template <class T>
void Adjust(T *a, const int root, const int n)
{
    // two subtrees are max heaps already
    // same procedure as the trickling-down procedure
    T e = a[root];
    //2*root is root's left child
    for (int j = 2*root; j <= n; j *=2) {
        if (j < n && a[j] < a[j+1]) // j and j+1 are siblings
            j++; // make j be the max child
        if (e >= a[j]) 
            break;
        a[j / 2] = a[j]; // move jth record up the path
    }
    a[j / 2] = e;
}
template <class T>
void HeapSort(T *a, const int n)
{   // sort a[1..n] into non-decreasing order
    // a[n/2] is the parent of the last node, a[n]
    for (int i = n/2; i >= 1; i--) // buttom-up heapification
        Adjust(a, i, n);// make the tree rooted at i be a max heap

    for (int i = n-1; i >= 1; i--) {
        swap(a[1], a[i+1]); // move one record from heap to list
        Adjust(a, 1, i); // heapify
    }
}


int main()
{
    
    return 0;
}