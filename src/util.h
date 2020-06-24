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

    for (size_t i = 0; i < N; i++) {
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
int compare(const std::string&, const std::string&);

void remove_leading_zeroes(std::string&);

void remove_trailing_zeroes(std::string&);

// divide binaries on string (dividend / divisor)
// return 0 if cannot perform division
// return 1 if can and change the dividend
bool divide(std::string&, std::string);

bool string_is_zero(const std::string&);

// true floating binary number division
template <size_t N>
binary<N> true_division(const binary<N>& lhs, const binary<N>& rhs) {
    binary<N> ans;
    std::string dividend = lhs.to_string();
    std::string divisor = rhs.to_string();

    remove_leading_zeroes(dividend);
    remove_leading_zeroes(divisor);

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
