#if !defined(_UTIL_H_)
#define _UTIL_H_

#include <string>
#include <bitset>
#include <cmath>

#include "config.h"
#include "binary.h"
#include "QInt.h"

/**
 * @brief Unsigned multiply for mantissas in multiplying two floating point binary number.
 * 
 * @param lhs The number to the left of multiply operator.
 * @param rhs The number to the right of multiply operator.
 * 
 * @return A `binary` with size of 2*N+1 contains the result of the unsigned multiplication.
 */
template<size_t N>
binary<2 * N + 1> unsigned_multiply(const binary<N> &lhs, const binary<N> &rhs) {
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

/**
 * @brief Compare two strings.
 * 
 * @param a The first string.
 * @param b The second string.
 * 
 * @return A value describing the relation between `a` and `b`, if the return value is `-1` it means that a < b,
 *         if the return value is `1` then a > b, otherwise the return value is `0`.
 */
int compare(const std::string &a, const std::string &b);

/**
 * @brief   Remove leading 0s from a string.
 * 
 * @param st The string you want to remove leading 0s.
 */
void remove_leading_zeroes(std::string &st);

/**
 * @brief Remove trailing 0s from a string.
 * 
 * @param st The string you want to remove trailing 0s.
 */
void remove_trailing_zeroes(std::string &st);

/**
 * @brief Divide binaries on string.
 * 
 * The `divisor` must not equal `0` before hand, this function does not check for.
 * division by zero and may lead to wrong answers or runtime errors.
 * 
 * @param dividend  The dividend.
 * @param divisor   The divisor.
 * 
 * @return `0` if dividend is less than divisor, else return `1` and overrides the remainder to the dividend.
 */
bool divide(std::string &dividend, std::string divisor);

/**
 * @brief Check to see whether the string only contains `0`s.
 * 
 * @param st The string you want to check.
 * 
 * @return `true` if `st` only contains `0`s, otherwise, `false`.
 */
bool string_is_zero(const std::string &st);

/**
 * @brief Perforn division like 3rd grade math.
 * 
 * @param lhs Devisor.
 * @param rhs Dividend.
 * 
 * @return A `binary` of length `N` contains the quotient of the division.
 */
template<size_t N>
binary<N> true_division(const binary<N> &lhs, const binary<N> &rhs) {
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
