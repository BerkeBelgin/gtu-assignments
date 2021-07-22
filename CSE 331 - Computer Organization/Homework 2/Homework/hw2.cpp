#include <iostream>

#define MAX_SIZE 100

using namespace std;

int checkSumPossibleity(int num, int arr[], int arraySize) {
	if (arraySize <= 0) return 0;
	if (num < 0) return 0;
	else if (num == 0) return 1;
	else {
		bool case1 = checkSumPossibleity(num, arr, arraySize - 1);
		bool case2 = checkSumPossibleity(num - arr[arraySize - 1], arr, arraySize - 1);
		return case1 || case2;
	}
}

int main() {
 int arraySize;
 int arr[MAX_SIZE];
 int num;
 int returnVal;
 cout << "Array Size: ";
 cin >> arraySize;
 cout << "Target Number: ";
 cin >> num;
 for(int i = 0; i < arraySize; ++i) {
    cin >> arr[i];
 }

 returnVal = checkSumPossibleity(num, arr, arraySize);

 if(returnVal == 1) {
    cout << "Possible!" << endl;
 }
 else {
    cout << "Not possible!" << endl;
 }

 return 0;
}