#include <iostream>
#include<ctime>

using namespace std;
int input() {
	int n;
	do {
		cout << "Nhap so luobg phan tu:";
		cin >> n;
	} while (n <= 0);
	return n;
}
void genArrRand(int* a, int n) {
	for (int i = 0; i < n; i++) {
		*(a + i) = rand() % 50 + 1;
	}

}
void outputArr(int* a, int n) {
	for (int i = 0; i < n; i++) {
		cout << *(a + i) << " ";
	}
	cout << endl;
}
//Kiem tra so le:
bool isLe(int n) {
	if (n % 2 != 0) {
		return true;
	}
	else
		return false;
}
int demLe(int* a, int n, bool func(int)= isLe) {
	if (a == 0) {
		return 0;
	}
	int dem = 0;
	for (int i = 0; i < n; i++) {
		if (isLe(a[i])) {
			dem++;
		}
	}
	return dem;
}
int sumOddTail(int* a, int n, int i, int sumHT) {
	if (i == n) return sumHT;
	if (isLe(a[i])) {
		sumHT += a[i];
	}
	return sumOddTail(a, n, i + 1, sumHT);
}
int main() {
	int n=input();
	int* a = new int[n];
	genArrRand(a, n);
	outputArr(a, n);
	cout << demLe(a, n) << endl;
	cout<<sumOddTail(a, n,0,0 );
	delete[]a;
	return 0;
}
// Sửa tên cho file số may mắn