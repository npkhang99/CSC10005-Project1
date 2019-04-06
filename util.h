#if !defined(_UTIL_H_)
#define _UTIL_H_

#include <string>
#include <bitset>
#include <cmath>

#include "config.h"
#include "binary.h"
#include "QInt.h"

// unsigned multiply for multiply mantissas in multiplying
// two floating point binary number
template <size_t N>
binary<2 * N + 1> unsigned_multiply(const binary<N>& lhs, const binary<N>& rhs) {
    binary<N + 1> m('0' + lhs.to_string());
    binary<N> q(rhs);
    binary<1 + N> ca;
    binary<1 + N> a;

    for (int i = 0; i < N; i++) {
        if (q.get(0) == 1) {
            ca = a + m;
        }

        q = q >> 1;
        q.set(N - 1, ca.get(0));
        ca = ca >> 1;
        ca.set(N, 0);

        a = binary<N + 1>('0' + ca.to_string().substr(1, N));
    }

    return binary<2 * N + 1>(ca.to_string() + q.to_string());
}

// compare 2 strings
int compare(const std::string& a, const std::string& b) {
    if (a.length() > b.length()) {
        return 1;
    }

    if (a.length() < b.length()) {
        return -1;
    }

    for (int i = 0; i < a.length(); i++) {
        if (a[i] < b[i]) {
            return -1;
        }
        if (a[i] > b[i]) {
            return 1;
        }
    }

    return 0;
}

void remove_leading_zeros(std::string& st) {
    while (st.length() > 1 && st[0] == '0') {
        st.erase(st.begin());
    }
}

// divide binaries on string (dividend / divisor)
// return 0 if cannot perform division
// return 1 if can and change the dividend
bool divide(std::string& dividend, std::string divisor) {
    if (compare(dividend, divisor) < 0) {
        return 0;
    }

    if (compare(dividend, divisor) == 0) {
        dividend = std::string();
        return 1;
    }

    while (dividend.length() > divisor.length()) {
        divisor = '0' + divisor;
    }

    // std::cerr << dividend << std::endl << divisor << std::endl;
    // int remainder = 0;
    // for (int i = 0; i < dividend.length(); i++) {
    //     int sub = dividend[i] - divisor[i] - remainder;
    //     remainder = (sub < 0 ? (abs(sub / 2) + 1) : 0);
    //     dividend[i] = abs(sub % 2) + '0';
    // }
    // std::cerr << dividend << std::endl << std::endl;

    binary<227> a(dividend);
    binary<227> b(divisor);

    dividend = (a - b).to_string();

    remove_leading_zeros(dividend);

    return 1;
}

bool string_is_zero(const std::string& st) {
    for (int i = 0; i < st.length(); i++) {
        if (st[i] != '0') {
            return false;
        }
    }
    return true;
}

// true floating binary number division
template <size_t N>
binary<N> true_division(const binary<N>& lhs, const binary<N>& rhs) {
    binary<N> ans;
    std::string dividend = lhs.to_string();
    std::string divisor = rhs.to_string();

    remove_leading_zeros(dividend);
    remove_leading_zeros(divisor);

    for (int i = N - 1; i >= 0; i--) {
        ans.set(i, divide(dividend, divisor));
        dividend += '0';
        if (string_is_zero(dividend)) {
            break;
        }
    }
    
    return ans;
}

#endif // _UTIL_H_
