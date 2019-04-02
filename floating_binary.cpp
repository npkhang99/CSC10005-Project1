#include "floating_binary.h"

std::string floating_binary::_padding(std::string st, const int& length) const {
    while (st.length() < length) {
        st = '0' + st;
    }
    return st;
}

floating_binary::floating_binary(const std::string &st) {
    std::string temp = _padding(st, _BINARY_LENGTH);
    for (int i = 0; i < _BINARY_LENGTH; i++) {
        bits[i] = (temp[_BINARY_LENGTH - i] == '1');
    }
}

void floating_binary::_align_radix_point(binary& exp, binary& mantissa, const int& delta) const {
    
}

std::string floating_binary::to_string() const {
    return bits.to_string();
}

bool floating_binary::get(const size_t& pos) const {
    return bits.test(pos);
}

floating_binary floating_binary::set(const size_t& pos, const bool& value) {
    bits.set(pos, value);
    return *this;
}

floating_binary floating_binary::operator+(const floating_binary& rhs) const {
    std::string rhs_st = rhs.to_string();
    binary exp_lhs = binary(_padding(to_string().substr(1, 15), _BINARY_LENGTH));
    binary mantissa_lhs = binary('1' + _padding(to_string().substr(16, 112), _BINARY_LENGTH - 1));

    binary exp_rhs = binary(rhs._padding(to_string().substr(1, 15), _BINARY_LENGTH));
    binary mantissa_rhs = binary('1' + rhs._padding(to_string().substr(16, 112), _BINARY_LENGTH - 1));

    if (exp_lhs > exp_rhs) {
        _align_radix_point(exp_rhs, mantissa_rhs, std::bitset<_BINARY_LENGTH>((exp_rhs - exp_lhs).to_string()).to_ulong());
    }
    
    if (exp_lhs < exp_rhs) {
        _align_radix_point(exp_lhs, mantissa_lhs, std::bitset<_BINARY_LENGTH>((exp_rhs - exp_lhs).to_string()).to_ulong());
    }

    
}
