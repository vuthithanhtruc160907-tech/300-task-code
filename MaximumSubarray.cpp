#include <iostream>
#include <string>

using namespace std;


int SumSubarry(int arr[], int n) {
	int currentSum = arr[0];
	int maxSum = arr[0];
	for (int i = 0; i < n; i++) {
		currentSum = max(arr[i], currentSum + arr[i]);
		maxSum = max(maxSum, currentSum);
	}

	return maxSum;
	}
int main() {
	int n = 5;
	int nums[] = { 2,9,3,8,1,5};
	cout << SumSubarry(nums, n);
	return 0;
}