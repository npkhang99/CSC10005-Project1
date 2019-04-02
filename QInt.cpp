#include "QInt.h"

void QInt::_utilities::_string_div_two(std::string& value) {
	std::string tmp = "";
	unsigned short int i = 0, j = 0, k = 0;
	tmp.resize(value.length());

	if (value[0] - '0' < 2) {
		i = 1;
		j = 10;
	}

	for (; i < value.length(); i++) {
		tmp[k++] = ((value[i] - '0' + j) / 2 + '0');
		j = ((value[i] - '0' + j) % 2) * 10;
	}

	tmp.resize(k);
	value = tmp;
}

int QInt::_utilities::_multiply(int x, int res[], int size) {
	int carry = 0;
	for (int i = 0; i < size; i++) {
		int prod = res[i] * x + carry;
		res[i] = prod % 10;
		carry = prod / 10;
	}

	while (carry) {
		res[size] = carry % 10;
		carry /= 10;
		size++;
	}
	return size;
}

std::string QInt::_utilities::_power(int x, int n) {
	std::stringstream out;
	if (n == 0)
		return "1";

	int res[100000], size = 0, tmp = x;
	while (tmp != 0) {
		res[size++] = tmp % 10;
		tmp /= 10;
	}

	for (int i = 2; i <= n; i++)
		size = _multiply(x, res, size);

	for (int i = size - 1; i >= 0; i--) {
		out << res[i];
	}
	return out.str();
}

std::string QInt::_utilities::_add_string(std::string a, std::string b) {
	int r = 0, a_len = a.length(), b_len = b.length();
	std::string tmp = "", res = "";
	for (int i = 0; i < abs(a_len - b_len); i++) {
		tmp += "0";
	}
	if (a_len > b_len) {
		b = tmp + b;
		b_len = a_len;
	}
	else {
		a = tmp + a;
		a_len = b_len;
	}

	for (int i = a_len - 1; i >= 0; i--) {
		int q = (a[i] - '0') + (b[i] - '0') + r;
		if (q > 9) {
			r = 1;
			q = q - 10;
		}
		else
			r = 0;

		res += (q + '0');
	}

	std::reverse(res.rbegin(), res.rend());
	if (r == 1) res = "1" + res;
	return res;
}

QInt::QInt() {

}

void QInt::scan_QInt(const std::string& value, const int& base) {
	if (base == 2) {
		n = binary(std::bitset<_BINARY_LENGTH>(value).to_string());
	}
	else if (base == 10) {
		if (value[0] == '-') {
			std::string tmp = value;
			tmp = tmp.erase(0, 1);
			n = binary(std::bitset<_BINARY_LENGTH>(dec_to_bin(tmp)).to_string()).twos_complement();
		}
		else
			n = binary(std::bitset<_BINARY_LENGTH>(dec_to_bin(value)).to_string());
	}
	else {
		n = binary(std::bitset<_BINARY_LENGTH>(hex_to_bin(value)).to_string());
	}
}

std::string QInt::print_QInt(const int& base) {
	if (base == 2) {
		return n.to_string();
	}
	else if (base == 10) {
		std::string tmp = n.to_string();
		if (tmp[0] == '1') {
			tmp = n.twos_complement().to_string();
			return "-" + bin_to_dec(tmp);
		}	
		return bin_to_dec(tmp);
	}
	else {
		return bin_to_hex(n.to_string());
	}
}

std::string QInt::bin_to_dec(std::string value) {
	std::string res = "";
	int count = 0;
	for (int i = value.length() - 1; i >= 0; i--) {
		if (value[i] == '1')
			res =_utilities:: _add_string(res, _utilities::_power(2, count));
		count++;
	}
	return res;
}

std::string QInt::bin_to_hex(std::string value) {
	std::string con_str = "0123456789ABCDEF", res = "";

	while (value.length() % 4 != 0) {
		value = '0' + value;
	}

	while (value != "") {
		std::string tmp = value.substr(0, 4);
		value.erase(0, 4);
		int in = (tmp[0] - '0') * 8 + (tmp[1] - '0') * 4 + (tmp[2] - '0') * 2 + (tmp[3] - '0');
		res += con_str[in];
	}

	return res;
}

std::string QInt::dec_to_bin(std::string value) {
	std::string tmp = "", res = "";

	while (value != "") {
		if ((value[value.length() - 1] - '0') % 2 == 0)
			tmp = "0";
		else
			tmp = "1";

		res = tmp + res;
		_utilities::_string_div_two(value);
	}

	return res;
}

std::string QInt::dec_to_hex(std::string value) {
	return bin_to_hex(dec_to_bin(value));
}

std::string QInt::hex_to_bin(std::string value) {
	std::string tmp = "0123456789ABCDEF", res = "";
	int index = 0;
	for (size_t i = 0; i < value.length(); ++i) {
		for (size_t j = 0; j < tmp.length(); ++j) {
			if (value[i] == tmp[j])
				index = j;
		}
		res += std::bitset<4>(index).to_string();
	}
	return res;
}

std::string QInt::hex_to_dec(std::string value) {
	return std::bitset<_BINARY_LENGTH>(bin_to_dec(hex_to_bin(value))).to_string();
}
