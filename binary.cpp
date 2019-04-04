#include "binary.h"

template <size_t N>
binary<N>::binary(const std::bitset<N>& o) {
    bits = o;
}

template <size_t N>
binary<N> binary<N>::_one() const {
    std::string one = "";
    for (int i = 0; i < N - 1; i++) {
        one.push_back('0');
    }
    one.push_back('1');
    return binary(one);
}

template <size_t N>
binary<N> binary<N>::_zero() const {
    return binary();
}

template <size_t N>
binary<N> binary<N>::_shr(const int& r) const {
    std::bitset<N> ans(bits);
    bool left_most = bits[N - 1];
    ans = ans >> r;
    if (left_most == 1) {
        for (int i = 0; i < r; i++) {
            ans.set(N - 1 - i, left_most);
        }
    }
    return binary(ans);
}

template <size_t N>
binary<N> binary<N>::twos_complement() const {
    return ~(*this) + _one();
}

template <size_t N>
binary<2 * N + 1> binary<N>::unsigned_multiply(const binary<N>& rhs) const {
    binary<N + 1> m('0' + bits.to_string());
    binary<N> q(rhs);
    binary<1 + N> ca;
    binary<1 + N> a;

    for (int i = 0; i < N; i++) {
        if (q.get(0) == 1) {
            ca = a + m;
        }

        q = q >> 1;
        q.set(N - 1, ca.get(0));
        ca = ca >> 1;
        ca.set(N, 0);

        a = binary<N + 1>('0' + ca.to_string().substr(1, N));
    }

    return binary<2 * N + 1>(ca.to_string() + q.to_string());
}

template <size_t N>
bool binary<N>::_msb() const {
    return bits.test(N - 1);
}

template <size_t N>
binary<N>::binary() {
    bits = std::bitset<N>(0);
}

template <size_t N>
binary<N>::binary(const int& value) {
    bits = std::bitset<N>(value);
}

template <size_t N>
binary<N>::binary(const binary& o) {
    bits = o.bits;
}

template <size_t N>
binary<N>::binary(const std::string& value) {
    bits = std::bitset<N>(value);
}

template <size_t N>
std::string binary<N>::to_string() const {
    return bits.to_string();
}

template <size_t N>
bool binary<N>::get(const size_t& pos) const {
    return bits.test(pos);
}

template <size_t N>
binary<N> binary<N>::set(const size_t& pos, const bool& value) {
    bits.set(pos, value);
    return *this;
}

template <size_t N>
binary<N>& binary<N>::operator=(const binary<N>& rhs) {
    bits = rhs.bits;
    return *this;
}

template <size_t N>
bool binary<N>::operator>(const binary<N>& rhs) const {
    bool answer;
    if (bits[N - 1] == rhs.get(N - 1)) {
        answer = to_string() > rhs.to_string();
    }
    else {
        answer = bits[N - 1] < rhs.get(N - 1);
    }
    return answer;
}

template <size_t N>
bool binary<N>::operator<(const binary<N>& rhs) const {
    bool answer = false;
    if (bits[N - 1] == rhs.get(N - 1)) {
        answer = to_string() < rhs.to_string();
    }
    else {
        answer = bits[N - 1] > rhs.get(N - 1);
    }
    return answer;
}

template <size_t N>
bool binary<N>::operator>=(const binary<N>& rhs) const {
    return !operator<(rhs);
}

template <size_t N>
bool binary<N>::operator<=(const binary<N>& rhs) const {
    return !operator>(rhs);
}

template <size_t N>
bool binary<N>::operator==(const binary<N>& rhs) const {
    return !operator>(rhs) && !operator<(rhs);
}

template <size_t N>
bool binary<N>::operator!=(const binary<N>& rhs) const {
    return !operator==(rhs);
}

template <size_t N>
binary<N> binary<N>::operator+(const binary<N>& rhs) const {
    binary<N> ans(bits);
    int remainder = 0;
    for (int i = 0; i < N; i++) {
        int sum = (int) rhs.get(i) + (int) bits[i] + (int) remainder;
        remainder = sum / 2;
        ans.set(i, sum % 2);
    }
    return ans;
}

template <size_t N>
binary<N> binary<N>::operator-(const binary<N>& rhs) const {
    binary<N> ans(bits);
    ans = ans + rhs.twos_complement();
    return ans;
}

template <size_t N>
binary<2 * N> binary<N>::operator*(const binary<N>& rhs) const {
    std::bitset<N + 1> qq(rhs.to_string() + "0");
    binary<N> a;
    for (int k = 0; k < N; k++) {
        if (qq.to_string().substr(N - 1, 2) == "10") {
            a = a - *this;
        }
        else if (qq.to_string().substr(N - 1, 2) == "01") {
            a = a + *this;
        }

        qq = qq >> 1;
        qq.set(N, a.get(0));
        a = a._shr(1);
    }

    return binary<2 * N>(a.to_string() + qq.to_string().substr(0, N));
}

template <size_t N>
std::pair<binary<N>, binary<N>> binary<N>::divmod(const binary<N>& rhs) const {
    binary<N> q(bits);
    binary<N> m(rhs);
    binary<N> a;

    int quotient_sign = _msb() + rhs._msb();

    if (q._msb()) {
        q = q.twos_complement();
    }

    if (m._msb()) {
        m = m.twos_complement();
    }

    for (int i = 0; i < N; i++) {
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

template <size_t N>
binary<N> binary<N>::operator/(const binary<N>& rhs) const {
    return divmod(rhs).first;
}

template <size_t N>
binary<N> binary<N>::operator%(const binary<N>& rhs) const {
    return divmod(rhs).second;
}

template <size_t N>
binary<N> binary<N>::operator|(const binary<N>& rhs) const {
    return binary<N>(bits | rhs.bits);
}

template <size_t N>
binary<N> binary<N>::operator&(const binary<N>& rhs) const {
    return binary<N>(bits & rhs.bits);
}

template <size_t N>
binary<N> binary<N>::operator^(const binary<N>& rhs) const {
    return binary<N>(bits ^ rhs.bits);
}

template <size_t N>
binary<N> binary<N>::operator~() const {
    return binary<N>(~bits);
}

template <size_t N>
binary<N> binary<N>::operator>>(const int& r) const {
    return _shr(r);
}

template <size_t N>
binary<N> binary<N>::operator<<(const int& r) const {
    return binary<N>(bits << r);
}

template <size_t N>
binary<N> binary<N>::rol(const int& r) const {
    binary<N> temp(bits);
    for (int i = 0; i < r; i++) {
        int msb = temp._msb();
        temp = temp << 1;
        temp.set(0, msb);
    }
    return temp;
}

template <size_t N>
binary<N> binary<N>::ror(const int& r) const {
    binary<N> temp(bits);
    for (int i = 0; i < r; i++) {
        int lsb = temp.get(0);
        temp = temp >> 1;
        temp.set(_BINARY_LENGTH - 1, lsb);
    }
    return temp;
}

template <size_t N>
std::ostream& operator<<(std::ostream& os, const binary<N>& rhs) {
    os << rhs.to_string();
    return os;
}
