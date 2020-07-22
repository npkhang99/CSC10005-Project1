#if !defined(_QINT_H_)
#define _QINT_H_

#include <sstream>
#include <algorithm>

#include "config.h"
#include "binary.h"

/**
 * @class QInt QInt.h
 * 
 * @brief Big integer class
 */
class QInt {
private:
	binary<_BINARY_LENGTH> n;

	// Utility class to implement helper functions
	class _utilities {
	public:
		/**
		 * @brief Divide a number, which is a string, by `2` then overrides it.
		 * 
		 * @param value The number you want to divide by `2` (must be a valid number).
		 */
		static void _string_div_two(std::string& value);

		/**
		 * @brief Raw multiply an array of digits with an integer less than 10.
		 * 
		 * @param x The sigle-digit integer to multiply.
		 * @param res The number in you want to multiply represents as an int array.
		 * @param size The array size.
		 * 
		 * @return The size of result array.
		 */
		static int _multiply(int x, int res[], int size);

		/**
		 * @brief Quickly calculate `x` to the power of `n` by using exponentiation by squaring.
		 * 
		 * @param x The number `x`.
		 * @param n The number `n`.
		 * 
		 * @return The result of `x` to the power of `n` in string.
		 */
		static std::string _power(int x, int n);

		/**
		 * @brief Add two numbers represented in string.
		 * 
		 * @param a The first number.
		 * @param b The second number.
		 * 
		 * @return The result of adding two numbers.
		 */
		static std::string _add_string(std::string a, std::string b);
	};

	/**
	 * @brief Provate constructor to contruct a copy of `binary` type
	 * 
	 * @param o The `binary` value you want to copy
	 */
	QInt(const binary<_BINARY_LENGTH>& o);

public:
	/**
	 * @brief Constructs a QInt with value 0
	 */
	QInt();

	/**
	 * @brief Constructs a QInt with value as a string and a specified base
	 * 
	 * @param value The value
	 * @param base The base which the value is represented in
	 */
	QInt(const std::string& value, const int& base);

	/**
	 * @brief Parse a value, which base is given, string to QInt
	 * 
	 * @param value The value
	 * @param base The base which the value is represented in
	 */
	void scan_QInt(const std::string& value, const int& base);

	/**
	 * @brief Convert to a specific base
	 * 
	 * @param base The base to convert to
	 * 
	 * @return A string contains the value of the object represented in the given base
	 */
	std::string print_QInt(const int& base);

	/***********************************************
	 * BASE CONVERTION FUNCTIONS
	 * These should be self-explanatory
	 * 
	 * @param value The value you want to convert
	 ***********************************************/

	static std::string bin_to_dec(std::string value);
	static std::string bin_to_hex(std::string value);
	static std::string dec_to_bin(std::string value);
	static std::string dec_to_hex(std::string value);
	static std::string hex_to_bin(std::string value);
	static std::string hex_to_dec(std::string value);

	/**
	 * @brief Get two's complement of a binary represented in string
	 * 
	 * @param value The value you want to get two's complement
	 */
	static std::string twos_complement(std::string value);

	/***********************************************
	 * BINARY OPERATORS
	 * These should be self-explanatory
	 * 
	 * @param rhs The right hand side operand
	 ***********************************************/

    QInt& operator=(const QInt& rhs);

    bool operator>(const QInt& rhs) const;
    bool operator<(const QInt& rhs) const;
    bool operator<=(const QInt& rhs) const;
    bool operator>=(const QInt& rhs) const;
    bool operator==(const QInt& rhs) const;
    bool operator!=(const QInt& rhs) const;

    QInt operator+(const QInt& rhs) const;
    QInt operator-(const QInt& rhs) const;
    QInt operator*(const QInt& rhs) const;
    QInt operator/(const QInt& rhs) const;
    QInt operator%(const QInt& rhs) const;

    QInt operator|(const QInt& rhs) const;
    QInt operator&(const QInt& rhs) const;
    QInt operator^(const QInt& rhs) const;
    QInt operator~() const;

	/***********************************************
	 * BIT SHIFTING / ROATATING OPERATORS
	 * These should be self-explanatory
	 * 
	 * @param r The number of bits to shift 
	 ***********************************************/

    QInt operator>>(const int& r) const;
    QInt operator<<(const int& r) const;

    QInt rol(const int& r) const;
    QInt ror(const int& r) const;
};

#endif // _QINT_H_
