#include "binary.h"

binary::binary(const std::bitset<_BINARY_LENGTH>& o) {
    bits = o;
}

binary binary::_one() const {
    std::string one = "";
    for (int i = 0; i < _BINARY_LENGTH - 1; i++) {
        one.push_back('0');
    }
    one.push_back('1');
    return binary(one);
}

binary binary::_zero() const {
    return binary();
}

binary binary::_shr(const int& r) const {
    std::bitset<_BINARY_LENGTH> ans(bits);
    bool left_most = bits[_BINARY_LENGTH - 1];
    ans = ans >> r;
    if (left_most == 1) {
        for (int i = 0; i < r; i++) {
            ans.set(_BINARY_LENGTH - 1 - i, left_most);
        }
    }
    return binary(ans);
}

binary binary::twos_complement() const {
    return ~(*this) + _one();
}

bool binary::_msb() const {
    return bits.test(_BINARY_LENGTH - 1);
}

binary::binary() {
    bits = std::bitset<_BINARY_LENGTH>(0);
}

binary::binary(const binary& o) {
    bits = o.bits;
}

binary::binary(const std::string& value) {
    bits = std::bitset<_BINARY_LENGTH>(value);
}

std::string binary::to_string() const {
    return bits.to_string();
}

bool binary::get(const size_t& pos) const {
    return bits.test(pos);
}

binary binary::set(const size_t& pos, const bool& value) {
    bits.set(pos, value);
    return *this;
}

binary& binary::operator=(const binary& rhs) {
    bits = rhs.bits;
    return *this;
}

bool binary::operator>(const binary& rhs) {
    bool answer = false;
    if (bits[_BINARY_LENGTH - 1] == rhs.get(_BINARY_LENGTH - 1)) {
        for (int i = _BINARY_LENGTH - 1; i > 0; i--) {
            if (bits[i] > rhs.bits[i]) {
                answer = true;
                break;
            }
        }
    }
    else {
        answer = bits[_BINARY_LENGTH - 1] < rhs.get(_BINARY_LENGTH - 1) ;
    }
    return answer;
}

bool binary::operator<(const binary& rhs) {
    bool answer = false;
    if (bits[_BINARY_LENGTH - 1] == rhs.get(_BINARY_LENGTH - 1)) {
        for (int i = _BINARY_LENGTH - 1; i > 0; i--) {
            if (bits[i] < rhs.bits[i]) {
                answer = true;
                break;
            }
        }
    }
    else {
        answer = bits[_BINARY_LENGTH - 1] > rhs.get(_BINARY_LENGTH - 1) ;
    }
    return answer;
}

bool binary::operator>=(const binary& rhs) {
    return !operator<(rhs);
}

bool binary::operator<=(const binary& rhs) {
    return !operator>(rhs);
}

bool binary::operator==(const binary& rhs) {
    return !operator>(rhs) && !operator<(rhs);
}

binary binary::operator+(const binary& rhs) const {
    binary ans(bits);
    int remainder = 0;
    for (int i = 0; i < _BINARY_LENGTH; i++) {
        int sum = rhs.get(i) + bits[i] + remainder;
        remainder = sum / 2;
        ans.set(i, sum % 2);
    }
    return ans;
}

binary binary::operator-(const binary& rhs) const {
    binary ans(bits);
    ans = ans + rhs.twos_complement();
    return ans;
}

binary binary::operator*(const binary& rhs) const {
    std::bitset<_BINARY_LENGTH + 1> qq(rhs.to_string() + "0");
    binary a;
    for (int k = 0; k < _BINARY_LENGTH; k++) {
        if (qq.to_string().substr(_BINARY_LENGTH - 1, 2) == "10") {
            a = a - *this;
        }
        else if (qq.to_string().substr(_BINARY_LENGTH - 1, 2) == "01") {
            a = a + *this;
        }

        qq = qq >> 1;
        qq.set(_BINARY_LENGTH, a.get(0));
        a = a._shr(1);
    }

    std::bitset<2 * _BINARY_LENGTH + 1> ans(a.to_string() + qq.to_string());
    return binary(ans.to_string().substr(_BINARY_LENGTH, _BINARY_LENGTH));
}

std::pair<binary, binary> binary::divmod(const binary& rhs) const {
    binary q(bits);
    binary m(rhs);
    binary a;

    int quotient_sign = _msb() + rhs._msb();

    if (q._msb()) {
        q = q.twos_complement();
    }

    if (m._msb()) {
        m = m.twos_complement();
    }

    for (int i = 0; i < _BINARY_LENGTH; i++) {
        a = a << 1;
        a.set(0, q._msb());
        q = q << 1;

        a = a - m;
        if (a._msb()) {
            q.set(0, 0);
            a = a + m;
        }
        else {
            q.set(0, 1);
        }
    }

    if (quotient_sign == 1) {
        q = q.twos_complement();
    }

    return std::make_pair(q, a);
}

binary binary::operator/(const binary& rhs) const {
    return divmod(rhs).first;
}

binary binary::operator%(const binary& rhs) const {
    return divmod(rhs).second;
}

binary binary::operator|(const binary& rhs) const {
    return binary(bits | rhs.bits);
}

binary binary::operator&(const binary& rhs) const {
    return binary(bits & rhs.bits);
}

binary binary::operator^(const binary& rhs) const {
    return binary(bits ^ rhs.bits);
}

binary binary::operator~() const {
    return binary(~bits);
}

binary binary::operator>>(const int& r) const {
    return _shr(r);
}

binary binary::operator<<(const int& r) const {
    return binary(bits << r);
}

std::ostream& operator<<(std::ostream& os, const binary& rhs) {
    os << rhs.to_string();
    return os;
}
