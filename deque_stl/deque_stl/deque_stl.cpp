#include <iostream>
#include <deque> 
#include <algorithm>
using namespace std;

void printKMax(int arr[], int n, int k) {
    //Write your code here.
    int* ptr;
    ptr = max_element(arr, arr + k);
    cout << *ptr << " ";

    for (int i = k; i < n; i++) {
        if ((arr + i) - k == ptr) {
            ptr = max_element((arr + i) - k + 1, arr + i + 1);
        }
        if (arr[i] > *ptr) {
            ptr = arr + i;
        }
        cout << *ptr << " ";
    }
    cout << endl;

}

int main() {

    int t;
    cin >> t;
    while (t > 0) {
        int n, k;
        cin >> n >> k;
        int i;
        int arr[n];
        for (i = 0; i < n; i++)
            cin >> arr[i];
        printKMax(arr, n, k);
        t--;
    }
    return 0;
}