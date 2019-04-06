#if !defined(_QINT_H_)
#define _QINT_H_

#include <sstream>
#include <algorithm>

#include "config.h"
#include "binary.h"

class QInt {
private:
	binary<_BINARY_LENGTH> n;

	class _utilities {
	public:
		static void _string_div_two(std::string&);
		static int _multiply(int, int[], int);
		static std::string _power(int, int);
		static std::string _add_string(std::string, std::string);
	};

	QInt(const binary<_BINARY_LENGTH>&);

public:
	QInt();
	QInt(const std::string&, const int&);
	QInt(const int&);

	void scan_QInt(const std::string&, const int&);

	std::string print_QInt(const int&);

	// conversion functions
	static std::string bin_to_dec(std::string);
	static std::string bin_to_hex(std::string);
	static std::string dec_to_bin(std::string);
	static std::string dec_to_hex(std::string);
	static std::string hex_to_bin(std::string);
	static std::string hex_to_dec(std::string);

	static std::string two_complements(std::string);

	// wrapper functions
    QInt& operator=(const QInt&);

    bool operator>(const QInt&) const;
    bool operator<(const QInt&) const;
    bool operator<=(const QInt&) const;
    bool operator>=(const QInt&) const;
    bool operator==(const QInt&) const;
    bool operator!=(const QInt&) const;

    QInt operator+(const QInt&) const;
    QInt operator-(const QInt&) const;
    QInt operator*(const QInt&) const;
    QInt operator/(const QInt&) const;
    QInt operator%(const QInt&) const;

    QInt operator|(const QInt&) const;
    QInt operator&(const QInt&) const;
    QInt operator^(const QInt&) const;
    QInt operator~() const;
    QInt operator>>(const int&) const;
    QInt operator<<(const int&) const;

    QInt rol(const int&) const;
    QInt ror(const int&) const;
};

#ifdef _LOCAL

#include "QInt.cpp"

#endif

#endif // _QINT_H_
