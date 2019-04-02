#if !defined(_BINARY_H_)
#define _BINARY_H_

#include "config.h"

#include <iostream>
#include <bitset>
#include <string>
#include <cmath>
#include <functional>

class binary {
private:
    // init cheat
    std::bitset<_BINARY_LENGTH> bits;
    binary(const std::bitset<_BINARY_LENGTH>&);

    // one (1) and zero (0) in `binary'
    binary _one() const;
    binary _zero() const;

    // arithmetic right shift
    binary _shr(const int&) const;
    
    // returns the value of the most significant bit
    bool _msb() const;

public:
    binary();
    binary(const binary&);
    binary(const std::string&);

    std::string to_string() const;

    // get two's complement
    binary twos_complement() const;

    // get / set bit at a given position
    bool get(const size_t&) const;
    binary set(const size_t&, const bool&);

    // very difficult to understand operator
    binary& operator=(const binary&);

    // this vs that, FIGHT!
    bool operator>(const binary&);
    bool operator<(const binary&);
    bool operator<=(const binary&);
    bool operator>=(const binary&);
    bool operator==(const binary&);

    // just 3rd grade math
    binary operator+(const binary&) const;
    binary operator-(const binary&) const;
    binary operator*(const binary&) const;
    binary operator/(const binary&) const;
    binary operator%(const binary&) const;

    std::pair<binary, binary> divmod(const binary&) const;
    
    // bit-wise operators
    binary operator|(const binary&) const;
    binary operator&(const binary&) const;
    binary operator^(const binary&) const;
    binary operator~() const;
    binary operator>>(const int&) const;
    binary operator<<(const int&) const;

    // rotation
    binary rol(const int&) const;
    binary ror(const int&) const;

    // just for debugging
    friend std::ostream& operator<<(std::ostream& os, const binary&);
};

#ifdef _LOCAL

#include "binary.cpp"

#endif

#endif // _BINARY_H_
