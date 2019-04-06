#if !defined(_QFLOAT_H_)
#define _QFLOAT_H_

#include <string>
#include <algorithm>

#include "config.h"
#include "binary.h"
#include "floating_binary.h"

class QFloat {
private:
    floating_binary n;

public:
    QFloat();
    QFloat(const std::string&);
    
};

#endif // _QFLOAT_H_
