#include <iostream>
#include <vector>
#include <string>
using namespace std;

template<typename T>
void InsertionSort(vector<T>& arr) {
    int n = arr.size();
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

template<typename T>
int Partition(vector<T>& arr, int low, int high) {
    T pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (arr[j] <= pivot) {
            ++i;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

template<typename T>
void QuickSort(vector<T>& arr, int low, int high) {
    if (low < high) {
        int pivot = Partition(arr, low, high);
        QuickSort(arr, low, pivot - 1);
        QuickSort(arr, pivot + 1, high);
    }
}

template<typename T>
void Merge(vector<T>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<T> L(n1);
    vector<T> R(n2);

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
void IterativeMergeSort(vector<T>& arr) {
    int n = arr.size();
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

template<typename T>
void RecursiveMergeSortHelper(vector<T>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        RecursiveMergeSortHelper(arr, left, mid);
        RecursiveMergeSortHelper(arr, mid + 1, right);
        Merge(arr, left, mid, right);
    }
}

template<typename T>
void RecursiveMergeSort(vector<T>& arr) {
    RecursiveMergeSortHelper(arr, 0, arr.size() - 1);
}

template<typename T>
void Heapify(vector<T>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        Heapify(arr, n, largest);
    }
}

template<typename T>
void HeapSort(vector<T>& arr) {
    int n = arr.size();

    for (int i = n / 2 - 1; i >= 0; --i)
        Heapify(arr, n, i);

    for (int i = n - 1; i >= 0; --i) {
        swap(arr[0], arr[i]);
        Heapify(arr, i, 0);
    }
}

template<typename T>
void PrintVector(const vector<T>& arr) {
    for (int i = 0; i < arr.size(); ++i)
        cout << arr[i] << " ";
    cout << endl;
}

int main() {
    vector<char> charList;
    charList.push_back('2');
    charList.push_back('0');
    charList.push_back('1');
    charList.push_back('3');
    charList.push_back('4');
    charList.push_back('6');
    charList.push_back('3');
    charList.push_back('8');
    charList.push_back('4');
    charList.push_back('9');
    charList.push_back('3');
    charList.push_back('5');
    charList.push_back('2');
    charList.push_back('4');
    charList.push_back('6');
    charList.push_back('7');
    charList.push_back('9');
    charList.push_back('0');
    charList.push_back('1');
    charList.push_back('3');
    cout << "Unsorted Char List: ";
    PrintVector(charList);

    InsertionSort(charList);
    cout << "Sorted Char List (Insertion Sort): ";
    PrintVector(charList);
    cout << endl;

    vector<int> intList;
    intList.push_back(20);
    intList.push_back(1);
    intList.push_back(3);
    intList.push_back(4);
    intList.push_back(6);
    intList.push_back(3);
    intList.push_back(8);
    intList.push_back(4);
    intList.push_back(9);
    intList.push_back(3);
    intList.push_back(5);
    intList.push_back(2);
    intList.push_back(4);
    intList.push_back(6);
    intList.push_back(7);
    intList.push_back(9);
    intList.push_back(0);
    intList.push_back(13);
    intList.push_back(4);
    intList.push_back(67);
    cout << "Unsorted Int List: ";
    PrintVector(intList);

    QuickSort(intList, 0, intList.size() - 1);
    cout << "Sorted Int List (Quick Sort): ";
    PrintVector(intList);
    cout << endl;

    vector<float> floatList;
    floatList.push_back(20.0f);
    floatList.push_back(1.0f);
    floatList.push_back(3.0f);
    floatList.push_back(4.0f);
    floatList.push_back(6.0f);
    floatList.push_back(3.0f);
    floatList.push_back(8.0f);
    floatList.push_back(4.0f);
    floatList.push_back(9.0f);
    floatList.push_back(3.0f);
    floatList.push_back(5.0f);
    floatList.push_back(2.0f);
    floatList.push_back(4.0f);
    floatList.push_back(6.0f);
    floatList.push_back(7.0f);
    floatList.push_back(9.0f);
    floatList.push_back(0.0f);
    floatList.push_back(13.0f);
    floatList.push_back(4.0f);
    floatList.push_back(67.0f);
    cout << "Unsorted Float List: ";
    PrintVector(floatList);

    IterativeMergeSort(floatList);
    cout << "Sorted Float List (Iterative Merge Sort): ";
    PrintVector(floatList);
    cout << endl;

    vector<string> stringList;
    stringList.push_back("20");
    stringList.push_back("1");
    stringList.push_back("3");
    stringList.push_back("4");
    stringList.push_back("6");
    stringList.push_back("3");
    stringList.push_back("8");
    stringList.push_back("4");
    stringList.push_back("9");
    stringList.push_back("3");
    stringList.push_back("5");
    stringList.push_back("2");
    stringList.push_back("4");
    stringList.push_back("6");
    stringList.push_back("7");
    stringList.push_back("9");
    stringList.push_back("0");
    stringList.push_back("13");
    stringList.push_back("4");
    stringList.push_back("67");
    cout << "Unsorted String List: ";
    PrintVector(stringList);

    RecursiveMergeSort(stringList);
    cout << "Sorted String List (Recursive Merge Sort): ";
    PrintVector(stringList);
    cout << endl;

    vector<int> intList2;
    intList2.push_back(20);
    intList2.push_back(1);
    intList2.push_back(3);
    intList2.push_back(4);
    intList2.push_back(6);
    intList2.push_back(3);
    intList2.push_back(8);
    intList2.push_back(4);
    intList2.push_back(9);
    intList2.push_back(3);
    intList2.push_back(5);
    intList2.push_back(2);
    intList2.push_back(4);
    intList2.push_back(6);
    intList2.push_back(7);
    intList2.push_back(9);
    intList2.push_back(0);
    intList2.push_back(13);
    intList2.push_back(4);
    intList2.push_back(67);
    cout << "Unsorted Int List: ";
    PrintVector(intList2);

    HeapSort(intList2);
    cout << "Sorted Int List (Heap Sort): ";
    PrintVector(intList2);

    return 0;
}

