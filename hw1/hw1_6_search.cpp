#include <iostream>

int binary_search(int *a, const int length, const int want)
{
    int left = 0;
    int right = length - 1;

    while (left <= right) {
        int mid = (left + right) / 2;
        if (a[mid] < want) left = mid + 1;
        else if (a[mid] > want) right = mid - 1;
        else return mid;
    }

    return -1;
}

int linear_search(int *a, const int length, const int want)
{
    int i;
    for (i = 0; i < length ; i++) {
        if (a[i] == want) return i;
    }
    
    return -1;
}


