#if !defined(_BINARY_H_)
#define _BINARY_H_

#include "config.h"

#include <iostream>
#include <bitset>
#include <string>
#include <cmath>
#include <functional>

template <size_t N>
class binary {
private:
    // init cheat
    std::bitset<N> bits;
    binary(const std::bitset<N>&);

    // one (1) and zero (0) in `binary'
    binary<N> _one() const;
    binary<N> _zero() const;

    // arithmetic right shift
    binary<N> _shr(const int&) const;
    
    // returns the value of the most significant bit
    bool _msb() const;

public:
    binary();
    binary(const binary<N>&);
    binary(const std::string&);

    std::string to_string() const;

    // get two's complement
    binary<N> twos_complement() const;

    // get / set bit at a given position
    bool get(const size_t&) const;
    binary<N> set(const size_t&, const bool&);

    // very difficult to understand operator
    binary<N>& operator=(const binary<N>&);

    // this vs that, FIGHT!
    bool operator>(const binary<N>&);
    bool operator<(const binary<N>&);
    bool operator<=(const binary<N>&);
    bool operator>=(const binary<N>&);
    bool operator==(const binary<N>&);

    // just 3rd grade math
    binary<N> operator+(const binary<N>&) const;
    binary<N> operator-(const binary<N>&) const;
    binary<N> operator*(const binary<N>&) const;
    binary<N> operator/(const binary<N>&) const;
    binary<N> operator%(const binary<N>&) const;

    std::pair<binary<N>, binary<N>> divmod(const binary<N>&) const;
    
    // bit-wise operators
    binary<N> operator|(const binary<N>&) const;
    binary<N> operator&(const binary<N>&) const;
    binary<N> operator^(const binary<N>&) const;
    binary<N> operator~() const;
    binary<N> operator>>(const int&) const;
    binary<N> operator<<(const int&) const;

    // rotation
    binary<N> rol(const int&) const;
    binary<N> ror(const int&) const;

    // just for debugging
    template <size_t M>
    friend std::ostream& operator<<(std::ostream& os, const binary<M>&);
};

#ifdef _LOCAL

#include "binary.cpp"

#endif

#endif // _BINARY_H_
