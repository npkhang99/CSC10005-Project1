#include <iostream>
#include <string>
#include <cctype>
using namespace std;

#include "QInt.h"
#include "floating_binary.h"

bool is_nan(const string& st) {
    for (int i = 0; i < st.length(); i++) {
        if (!isdigit(st[i])) {
            return true;
        }
    }
    return false;
}

int main() {
    floating_binary a("01000001000100000000001000001100");
    floating_binary b("01000001001011111111110111110100");
    cout << (a + b).to_string() << endl;
    return 0;
}
