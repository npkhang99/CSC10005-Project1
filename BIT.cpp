#include "BIT.h"

template <size_t N>
BIT<N>::BIT() {
    _size = N;
    bits = new bool[N];
}

template <size_t N>
BIT<N>::BIT(const BIT<N>& o) {
    if (bits != nullptr) {
        delete[] bits;
    }
    *this = o;
}

template <size_t N>
BIT<N>::~BIT() {
    _size = 0;
    delete[] bits;
}

template <size_t N>
size_t BIT<N>::size() const {
    return _size;
}

template <size_t N>
BIT<N>& BIT<N>::flip() {
    for (int i = 0; i < _size; i++) {
        bits[i] = !bits[i];
    }
    return *this;
}

template <size_t N>
BIT<N>& BIT<N>::flip(const size_t& pos) {
    if (pos < 0 || pos >= _size) {
        throw "index out of range";
    }
    bits[pos] = !bits[pos];
    return *this;
}

template <size_t N>
BIT<N>& BIT<N>::set(const size_t& pos, const bool& value) {
    if (pos < 0 || pos >= _size) {
        throw "index out of range";
    }
    bits[pos] = value;
    return *this;
}

template <size_t N>
bool BIT<N>::get_bit(const size_t& pos) const {
    if (pos < 0 || pos >= _size) {
        throw "index out of range";
    }
    return bits[pos];
}

template <size_t N>
BIT<N>& BIT<N>::operator=(const BIT<N>& rhs) {
    if (bits != nullptr) {
        delete[] bits;
    }

    _size = rhs.size();
    bits = new bool[rhs.size()];
    for (int i = 0; i < _size; i++) {
        bits[i] = rhs.bits[i];
    }
    return *this;
}

template <size_t N>
bool& BIT<N>::operator[](const size_t& pos) {
    if (pos < 0 || pos >= _size) {
        throw "index out of range";
    }
    return *(bits + pos);
}

template <size_t N>
std::string BIT<N>::to_string() const {
    std::string result = "";
    for (int i = _size - 1; i >= 0; i--) {
        result += std::to_string(bits[i] ? 1 : 0);
    }
    return result;
}
