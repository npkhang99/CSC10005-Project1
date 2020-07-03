#include "util.h"

int compare(const std::string& a, const std::string& b) {
    if (a.length() > b.length()) {
        return 1;
    }

    if (a.length() < b.length()) {
        return -1;
    }

    for (int i = 0; i < (int) a.length(); i++) {
        if (a[i] < b[i]) {
            return -1;
        }
        if (a[i] > b[i]) {
            return 1;
        }
    }

    return 0;
}

void remove_leading_zeroes(std::string& st) {
    while (st.length() > 1 && st[0] == '0') {
        st.erase(st.begin());
    }
}

void remove_trailing_zeroes(std::string& st) {
    while (st.length() > 1 && st.back() == '0') {
        st.erase(--st.end());
    }
}

bool divide(std::string& dividend, std::string divisor) {
    if (compare(dividend, divisor) < 0) {
        return 0;
    }

    if (compare(dividend, divisor) == 0) {
        dividend = std::string();
        return 1;
    }

    while (dividend.length() > divisor.length()) {
        divisor = '0' + divisor;
    }

    binary<227> a(dividend);
    binary<227> b(divisor);

    dividend = (a - b).to_string();

    remove_leading_zeroes(dividend);

    return 1;
}

bool string_is_zero(const std::string& st) {
    for (int i = 0; i < (int) st.length(); i++) {
        if (st[i] != '0') {
            return false;
        }
    }
    return true;
}
