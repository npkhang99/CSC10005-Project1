#if !defined(_BINARY_H_)
#define _BINARY_H_

#include "config.h"

#include <iostream>
#include <bitset>
#include <string>
#include <cmath>

class binary {
private:
    // init cheat
    std::bitset<_BINARY_LENGTH> bits;
    binary(const std::bitset<_BINARY_LENGTH>&);

    // one (1) and zero (0) in `binary'
    binary _one() const;
    binary _zero() const;

    // arithmetic right / left shift
    binary _shr(const int&) const;

public:
    binary();
    binary(const binary&);
    binary(const std::string&);

    std::string to_string() const;

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

#endif // _BINARY_H_
