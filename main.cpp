#include <iostream>
#include <string>
#include <cctype>
using namespace std;

#include "QInt.h"

bool is_nan(const string& st) {
    for (int i = 0; i < st.length(); i++) {
        if (!isdigit(st[i])) {
            return true;
        }
    }
    return false;
}

int main() {
    QInt a, b;
    int from_base, to_base;
    string st;
    cin >> from_base >> to_base >> st;
    
    if (from_base == 2) {
        if (to_base == 10) {
            cout << QInt::bin_to_dec(st) << endl;
        }
        else {
            cout << a.bin_to_hex(st) << endl;
        }
    }
    else if (from_base == 10) {
        if (to_base == 2) {
            cout << QInt::dec_to_bin(st) << endl;
        }
        else {
            cout << QInt::dec_to_hex(st) << endl;
        }
    }
    else {
        if (to_base == 2) {
            cout << QInt::hex_to_bin(st) << endl;
        }
        else {
            cout << QInt::hex_to_dec(st) << endl;
        }
    }

    return 0;
}
