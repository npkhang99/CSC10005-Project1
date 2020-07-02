#include "floating_binary.h"

floating_binary::floating_binary() {
    bits = std::bitset<_FP_LENGTH>(0);
}

floating_binary::floating_binary(const std::string &st) {
    assert(st.length() == _FP_LENGTH);
    bits = std::bitset<_FP_LENGTH>(st);
}

std::string floating_binary::_mantissa_padding(std::string st, const int& _length) const {
    while ((int) st.length() < _length) {
        st += '0';
    }
    return st;
}

void floating_binary::_align_radix_point(binary<_FP_EXPONENT + 1>& exp, binary<_FP_MANTISSA + 1>& mantissa, const unsigned long long& delta) const {
    exp = exp + binary<_FP_EXPONENT + 1>(delta);
    for (unsigned long long i = 0; i < delta; i++) {
        mantissa = mantissa >> 1;
        mantissa.set(_FP_MANTISSA, 0);
    }
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

floating_binary& floating_binary::operator=(const floating_binary& rhs) {
    bits = std::bitset<_FP_LENGTH>(rhs.to_string());
    return *this;
}

floating_binary floating_binary::operator+(const floating_binary& rhs) const {
    if (get(_FP_LENGTH - 1) != rhs.get(_FP_LENGTH - 1) && to_string().substr(1, _FP_LENGTH - 1) == rhs.to_string().substr(1, _FP_LENGTH - 1)) {
        return floating_binary();
    }

    binary<_FP_EXPONENT + 1> exp_lhs('0' + to_string().substr(1, _FP_EXPONENT));
    binary<_FP_MANTISSA + 1> mantissa_lhs('1' + to_string().substr(_FP_EXPONENT + 1, _FP_MANTISSA));
    
    binary<_FP_EXPONENT + 1> exp_rhs('0' + rhs.to_string().substr(1, _FP_EXPONENT));
    binary<_FP_MANTISSA + 1> mantissa_rhs('1' + rhs.to_string().substr(_FP_EXPONENT + 1, _FP_MANTISSA));

    if (exp_lhs > exp_rhs) {
        unsigned long long delta = std::bitset<_FP_EXPONENT + 1>((exp_lhs - exp_rhs).to_string()).to_ullong();
        _align_radix_point(exp_rhs, mantissa_rhs, delta);
    }

    if (exp_lhs < exp_rhs) {
        unsigned long long delta = std::bitset<_FP_EXPONENT + 1>((exp_rhs - exp_lhs).to_string()).to_ullong();
        _align_radix_point(exp_lhs, mantissa_lhs, delta);
    }

    binary<_FP_EXPONENT> exp = binary<_FP_EXPONENT>(exp_lhs.to_string().substr(1, _FP_EXPONENT));
    binary<_FP_MANTISSA + 2> sign_mantissa_lhs;
    binary<_FP_MANTISSA + 2> sign_mantissa_rhs;

    if (bits[_FP_LENGTH - 1] == 1) {
        mantissa_lhs = ~mantissa_lhs + binary<_FP_MANTISSA + 1>(1);
        sign_mantissa_lhs = binary<_FP_MANTISSA + 2>('1' + mantissa_lhs.to_string());
    }
    else {
        sign_mantissa_lhs = binary<_FP_MANTISSA + 2>('0' + mantissa_lhs.to_string());
    }

    if (rhs.bits[_FP_LENGTH - 1] == 1) {
        mantissa_rhs = ~mantissa_rhs + binary<_FP_MANTISSA + 1>(1);
        sign_mantissa_rhs = binary<_FP_MANTISSA + 2>('1' + mantissa_rhs.to_string());
    }
    else {
        sign_mantissa_rhs = binary<_FP_MANTISSA + 2>('0' + mantissa_rhs.to_string());
    }

    binary<_FP_MANTISSA + 2> sum_mantissa = sign_mantissa_lhs + sign_mantissa_rhs;

    bool sign_bit = sum_mantissa.get(_FP_MANTISSA + 1);

    if (sign_mantissa_lhs.get(_FP_MANTISSA + 1) == sign_mantissa_rhs.get(_FP_MANTISSA + 1)) {
        sign_bit = sign_mantissa_lhs.get(_FP_MANTISSA + 1);
    }
    else if (sum_mantissa < binary<_FP_MANTISSA + 2>(0)) {
        sum_mantissa = ~sum_mantissa + binary<_FP_MANTISSA + 2>(1);
    }

    if (sum_mantissa.get(_FP_MANTISSA + 1) == 1) {
        sum_mantissa = sum_mantissa >> 1;
        exp = exp + binary<_FP_EXPONENT>(1);
    }

    while (sum_mantissa != binary<_FP_MANTISSA + 2>(0) && sum_mantissa.get(_FP_MANTISSA) == 0) {
        sum_mantissa = sum_mantissa << 1;
        exp = exp - binary<_FP_EXPONENT>(1);
    }

    return floating_binary((sign_bit ? '1' : '0') + exp.to_string() + sum_mantissa.to_string().substr(2, _FP_MANTISSA));
}

floating_binary floating_binary::operator-(const floating_binary& rhs) const {
    return *this + floating_binary(rhs).set(_FP_LENGTH - 1, 1 - rhs.get(_FP_LENGTH - 1));
}

floating_binary floating_binary::operator*(const floating_binary& rhs) const {
    if (bits == std::bitset<_FP_LENGTH>(0) || rhs.bits == std::bitset<_FP_LENGTH>(0)) {
        return floating_binary();
    }

    binary<_FP_EXPONENT> mantissa_lhs(to_string().substr(1 + _FP_EXPONENT, _FP_MANTISSA));
    binary<_FP_EXPONENT> mantissa_rhs(rhs.to_string().substr(1 + _FP_EXPONENT, _FP_MANTISSA));

    unsigned long long bias = (int) pow(2, _FP_EXPONENT - 1) - 1;
    
    unsigned long long lhs_exp = std::bitset<_FP_EXPONENT>(to_string().substr(1, _FP_EXPONENT)).to_ullong();
    unsigned long long rhs_exp = std::bitset<_FP_EXPONENT>(rhs.to_string().substr(1, _FP_EXPONENT)).to_ullong();
    binary<_FP_EXPONENT> exp(std::bitset<_FP_EXPONENT>(lhs_exp + rhs_exp - bias));
    
    binary<_FP_MANTISSA + 1> lhs_mantissa('1' + to_string().substr(_FP_EXPONENT + 1, _FP_MANTISSA));
    binary<_FP_MANTISSA + 1> rhs_mantissa('1' + rhs.to_string().substr(_FP_EXPONENT + 1, _FP_MANTISSA));

    binary<2 * _FP_MANTISSA + 3> mantissa = unsigned_multiply(lhs_mantissa, rhs_mantissa);

    mantissa = mantissa >> 2;
    mantissa.set(2 * _FP_MANTISSA + 1, 0);
    mantissa.set(2 * _FP_MANTISSA + 2, 0);
    exp = exp + 2;

    while (mantissa.get(2 * _FP_MANTISSA) != 1) {
        mantissa = mantissa << 1;
        exp = exp - 1;
    }

    bool sign_bit = get(_FP_LENGTH - 1) ^ rhs.get(_FP_LENGTH - 1);

    return floating_binary((sign_bit ? "1" : "0") + exp.to_string() + mantissa.to_string().substr(3, _FP_MANTISSA));
}

floating_binary floating_binary::operator/(const floating_binary& rhs) const {
    if (bits == std::bitset<_FP_LENGTH>(0)) {
        return floating_binary();
    }

    if (rhs.bits == std::bitset<_FP_LENGTH>(0)) {
        throw "Error: Divided by 0";
    }

    binary<_FP_EXPONENT> mantissa_lhs(to_string().substr(1 + _FP_EXPONENT, _FP_MANTISSA));
    binary<_FP_EXPONENT> mantissa_rhs(rhs.to_string().substr(1 + _FP_EXPONENT, _FP_MANTISSA));

    unsigned long long bias = (int) pow(2, _FP_EXPONENT - 1) - 1;
    
    unsigned long long lhs_exp = std::bitset<_FP_EXPONENT>(to_string().substr(1, _FP_EXPONENT)).to_ullong();
    unsigned long long rhs_exp = std::bitset<_FP_EXPONENT>(rhs.to_string().substr(1, _FP_EXPONENT)).to_ullong();
    binary<_FP_EXPONENT> exp(std::bitset<_FP_EXPONENT>(lhs_exp - rhs_exp + bias));
    
    binary<_FP_MANTISSA + 1> lhs_mantissa('1' + to_string().substr(_FP_EXPONENT + 1, _FP_MANTISSA));
    binary<_FP_MANTISSA + 1> rhs_mantissa('1' + rhs.to_string().substr(_FP_EXPONENT + 1, _FP_MANTISSA));

    binary<_FP_MANTISSA + 1> mantissa = true_division(lhs_mantissa, rhs_mantissa);

    while (mantissa.get(_FP_MANTISSA) != 1) {
        mantissa = mantissa << 1;
        exp = exp - 1;
    }

    bool sign_bit = get(_FP_LENGTH - 1) ^ rhs.get(_FP_LENGTH - 1);

    return floating_binary((sign_bit ? "1" : "0") + exp.to_string() + mantissa.to_string().substr(1, _FP_MANTISSA));
}
