#include <iostream>
#include <string>

using namespace std;


int getValue(char c) {
    switch(c) {
        case 'I': return 1;
        case 'V': return 5;
        case 'X': return 10;
        case 'L': return 50;
        case 'C': return 100;
        case 'D': return 500;
        case 'M': return 1000;
        default: return 0;
    }
}
int romanToInt(string s) {
    int sum = 0;
    for (int i = 0; i < s.length(); i++) {
        if (i + 1 < s.length() && getValue(s[i]) < getValue(s[i + 1])) {
            sum -= getValue(s[i]);
        } else {
            sum += getValue(s[i]);
        }
    }
    return sum; }
    
int main(){
    string s = "MCMXCIV";
    cout << romanToInt(s) << endl;
    return 0;

}


