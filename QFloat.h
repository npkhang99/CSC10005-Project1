#if !defined(_QFLOAT_H_)
#define _QFLOAT_H_

#include <string>
#include <cmath>
#include <algorithm>

#include "config.h"
#include "binary.h"
#include "util.h"
#include "QInt.h"
#include "floating_binary.h"

class QFloat {
private:
    floating_binary n;

public:
    QFloat();
    QFloat(const std::string&);

    QFloat operator+(const QFloat&) const;
    QFloat operator-(const QFloat&) const;
    QFloat operator*(const QFloat&) const;
    QFloat operator/(const QFloat&) const;

    static std::string dec_to_bin(std::string);
    static std::string bin_to_dec(std::string);
};

#ifdef _LOCAL

#include "QFloat.cpp"

#endif

#endif // _QFLOAT_H_
