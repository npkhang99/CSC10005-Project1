#ifndef _BIT_H_
#define _BIT_H_

#include <cctype>
#include <string>

template <size_t N>
class BIT {
private:
    bool* bits = nullptr;
    size_t _size;

public:
    BIT();
    BIT(const BIT<N>&);
    ~BIT();

    size_t size() const;

    BIT<N>& flip();
    BIT<N>& flip(const size_t&);

    BIT<N>& set(const size_t&, const bool&);

    bool get_bit(const size_t&) const;

    BIT<N>& operator=(const BIT<N>&);
    bool& operator[](const size_t&);

    std::string to_string() const;
};

#include "BIT.cpp"

#endif
