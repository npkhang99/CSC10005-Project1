#include "floating_binary.h"

template <size_t N>
std::string floating_binary<N>::_padding(std::string st, const int& length) const {
    while (st.length() < length) {
        st = '0' + st;
    }
    return st;
}

template <size_t N>
floating_binary<N>::floating_binary(const std::string &st) {
    std::string temp = _padding(st, _BINARY_LENGTH);
    for (int i = 0; i < _BINARY_LENGTH; i++) {
        bits[i] = (temp[_BINARY_LENGTH - i] == '1');
    }
}

template <size_t N>
void floating_binary<N>::_align_radix_point(binary<N>& exp, binary<N>& mantissa, const int& delta) const {
    
}

template <size_t N>
std::string floating_binary<N>::to_string() const {
    return bits.to_string();
}

template <size_t N>
bool floating_binary<N>::get(const size_t& pos) const {
    return bits.test(pos);
}

template <size_t N>
floating_binary<N> floating_binary<N>::set(const size_t& pos, const bool& value) {
    bits.set(pos, value);
    return *this;
}

template <size_t N>
floating_binary<N> floating_binary<N>::operator+(const floating_binary<N>& rhs) const {
    std::string rhs_st = rhs.to_string();
    binary<N> exp_lhs = binary(_padding(to_string().substr(1, 15), _BINARY_LENGTH));
    binary<N> mantissa_lhs = binary('1' + _padding(to_string().substr(16, 112), _BINARY_LENGTH - 1));

    binary exp_rhs = binary(rhs._padding(to_string().substr(1, 15), _BINARY_LENGTH));
    binary mantissa_rhs = binary('1' + rhs._padding(to_string().substr(16, 112), _BINARY_LENGTH - 1));

    if (exp_lhs > exp_rhs) {
        _align_radix_point(exp_rhs, mantissa_rhs, std::bitset<_BINARY_LENGTH>((exp_rhs - exp_lhs).to_string()).to_ulong());
    }
    
    if (exp_lhs < exp_rhs) {
        _align_radix_point(exp_lhs, mantissa_lhs, std::bitset<_BINARY_LENGTH>((exp_rhs - exp_lhs).to_string()).to_ulong());
    }


}
