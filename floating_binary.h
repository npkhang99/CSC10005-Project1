#if !defined(_FLOATING_BINARY_H_)
#define _FLOATING_BINARY_H_

#include <iostream>
#include <bitset>
#include <string>
#include <cassert>

#include "config.h"
#include "binary.h"
#include "QInt.h"

class floating_binary {
private:
    std::bitset<_FP_LENGTH> bits;

    std::string _padding(std::string, const int&) const;
    void _align_radix_point(binary<_FP_EXPONENT + 1>&, binary<_FP_MANTISSA + 1>&, const unsigned long long&) const;

public:
    floating_binary();
    floating_binary(const std::string&);
    
    std::string to_string() const;

    // get / set bit at a given position
    bool get(const size_t&) const;
    floating_binary set(const size_t&, const bool&);

    floating_binary& operator=(const floating_binary&);

    // just 3rd grade math
    floating_binary operator+(const floating_binary&) const;
    floating_binary operator-(const floating_binary&) const;
    floating_binary operator*(const floating_binary&) const;
    floating_binary operator/(const floating_binary&) const;
};

#ifdef _LOCAL
#include "floating_binary.cpp"
#endif

#endif // _FLOATING_BINARY_H_
