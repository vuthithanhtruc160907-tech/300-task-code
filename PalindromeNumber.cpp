#include <iostream>
#include <string>

using namespace std;

bool isPalindrome(int n) {
	string s = to_string(n);
	int nSize = s.size();
	for (int i = 0; i < nSize / 2; i++) {
		if (s[i] != s[nSize - i - 1]) {
			return false;
		}
	}
		return true;
	
}
    int main() {
        int n = -4568;
       if (isPalindrome(n)) {
        cout << n << " la so doi xung!" << endl;
    } else {
        cout << n << " khong phai la so doi xung!" << endl;
    }

    return 0;
}
    
