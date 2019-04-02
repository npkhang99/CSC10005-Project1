#if !defined(_FLOATING_BINARY_H_)
#define _FLOATING_BINARY_H_

#include "config.h"
#include "binary.h"
#include "QInt.h"

#include <iostream>
#include <bitset>
#include <string>

class floating_binary {
private:
    std::bitset<_BINARY_LENGTH> bits;

    std::string _padding(std::string, const int&) const;
    void _align_radix_point(binary&, binary&, const int&) const;

public:
    floating_binary();
    floating_binary(const std::string&);
    
    std::string to_string() const;

    // get / set bit at a given position
    bool get(const size_t&) const;
    floating_binary set(const size_t&, const bool&);

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
