#include <iostream>
#include <ctime>

using namespace std;

// Yeu Cau 1
int input() {
	int n;
	do {
		cout << "Nhap n: ";
		cin >> n;
	} while (n<= 0);
	return n;

}
void genArrrand(int* a, int n) {
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
bool isPrime(int n) {
	if (n < 2) return false;
	for (int i = 2; i <= std::sqrt(n); ++i) {
		if (n % i == 0) return false;
	}
	return true;
}
int* findPrime(int*a, int n, bool func(int) =isPrime){
	if (a == NULL) {
		return NULL;
	}
	for (int i = 0; i < n; i++) {
		if (func(*(a + i)))
			return (a + i);
	}
	return NULL;

}
bool isChan(int n) {
	if (n % 2 == 0) {
		return true;
	}
	else
		return false;
}
int demChan(int* a, int n, int dem = 0) {
	for (int i = 0; i < n; i++) {
		if (isChan(a[i]))
			dem++;
	}
	return dem;
}

int main() {
	int n=input();
	int* a = new int[n];
	genArrrand(a, n);
	outputArr(a, n);
	if (findPrime(a, n) != NULL) {
		cout << "So nguyen to: " << *findPrime(a, n) << endl;
	}
	else {
		cout << "Khong tim thay so nguyen to!" << endl;
	}
	cout << "So luong chan la:" << demChan(a,n);
	delete[]a;
	return 0;
}
