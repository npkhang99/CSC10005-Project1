#if !defined(_QINT_H_)
#define _QINT_H_

#include <sstream>
#include <algorithm>

#include "binary.h"

class QInt {
private:
	binary n;

	class _utilities {
	public:
		static void _string_div_two(std::string&);
		static int _multiply(int, int[], int);
		static std::string _power(int, int);
		static std::string _add_string(std::string, std::string);
	};

public:
	QInt();
	QInt(const int&);

	void scan_QInt(const std::string&, const int&);

	std::string print_QInt(const int&);

	static std::string bin_to_dec(std::string);
	static std::string bin_to_hex(std::string);
	static std::string dec_to_bin(std::string);
	static std::string dec_to_hex(std::string);
	static std::string hex_to_bin(std::string);
	static std::string hex_to_dec(std::string);
};

#ifdef _LOCAL

#include "QInt.cpp"

#endif

#endif // _QINT_H_
