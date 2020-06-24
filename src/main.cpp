#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <sstream>
using namespace std;

#include "QInt.h"
#include "QFloat.h"
#include "floating_binary.h"

bool is_nan(const string& st) {
    for (size_t i = 0; i < st.length(); i++) {
        if (!isxdigit(st[i])) {
            return true;
        }
    }
    return false;
}

bool is_nan_float(const string& st) {
    for (size_t i = 0; i < st.length(); i++) {
        if (st[i] != '.' && !isxdigit(st[i])) {
            return true;
        }
    }
    return false;
}

bool is_bitwise_operation(char c) {
    const string bitwise_operator = "&|^~";
    return bitwise_operator.find(c) != string::npos;
}

int parse_qint() {
    QInt ans;
    int logic_answer = -1;
    string line;

    while (isspace(cin.peek())) {
        cin.ignore();
    }

    if (!getline(cin, line)) {
        return -1;
    }

    stringstream ss(line);

    int ori_base;
    ss >> ori_base;

    string sec;
    ss >> sec;

    if (is_bitwise_operation(sec[0])) {
        char op = sec[0];
        ss >> sec;
        if (op == '~') {
            ans = ~QInt(sec, ori_base);
        }
    }
    else {
        string op;
        ss >> op;
        if (!is_nan(op) || (op.length() > 1 && op[0] == '-' && !is_nan(op.substr(1, op.length() - 1)))) {
            QInt a(op, ori_base);
            string trimmed = a.print_QInt(stoi(sec));
            remove_leading_zeroes(trimmed);
            cout << trimmed << endl;
            return 0;
        }
        else {
            string operand;
            ss >> operand;

            QInt a(sec, ori_base);
            QInt b;

            // shift and rotate operators have right hand side operands always in base 10
            if (op == "<<" || op == ">>" || op == "ror" || op == "rol") {
                b = QInt(operand, 10);
            }
            else {
                b = QInt(operand, ori_base);
            }

            if (op == "+") {
                ans = a + b;
            }
            else if (op == "-") {
                ans = a - b;
            }
            else if (op == "*") {
                ans = a * b;
            }
            else if (op == "/") {
                ans = a / b;
            }
            else if (op == "%") {
                ans = a % b;
            }
            else if (op == ">>") {
                ans = a >> stoi(b.print_QInt(10));
            }
            else if (op == "<<") {
                ans = a << stoi(b.print_QInt(10));
            }
            else if (op == "rol") {
                ans = a.rol(stoi(b.print_QInt(10)));
            }
            else if (op == "ror") {
                ans = a.ror(stoi(b.print_QInt(10)));
            }
            else if (op == "^") {
                ans = a ^ b;
            }
            else if (op == "|") {
                ans = a | b;
            }
            else if (op == "&") {
                ans = a & b;
            }
            else if (op == "==") {
                logic_answer = a == b;
            }
            else if (op == ">") {
                logic_answer = a > b;
            }
            else if (op == ">=") {
                logic_answer = a >= b;
            }
            else if (op == "<") {
                logic_answer = a < b;
            }
            else if (op == "<=") {
                logic_answer = a <= b;
            }
            else {
                cerr << "Un-supported operation! (" << op << ")\n";
                exit(1);
            }
        }
    }

    if (logic_answer != -1)  {
        cout << (logic_answer ? "true" : "false") << endl;
    }
    else {
        string trimmed = ans.print_QInt(ori_base);
        remove_leading_zeroes(trimmed);
        cout << trimmed << endl;
    }
    return 0;
}

int parse_qfloat() {
    QFloat ans;
    string line;

    while (isspace(cin.peek())) {
        cin.ignore();
    }

    if (!getline(cin, line)) {
        return -1;
    }

    stringstream ss(line);

    int ori_base;
    ss >> ori_base;

    string sec;
    ss >> sec;

    string op;
    ss >> op;

    if (!is_nan_float(op) || (op.length() > 1 && op[0] == '-' && !is_nan_float(op.substr(1, op.length() - 1)))) {
        QFloat a(op, ori_base);
        // cerr << a.to_string(stoi(sec)) << endl;
        cout << a.to_string(stoi(sec)) << endl;
        return 0;
    }
    else {
        string operand;
        ss >> operand;

        QFloat a(sec, ori_base);
        QFloat b(operand, ori_base);

        if (op == "+") {
            ans = a + b;
        }
        else if (op == "-") {
            ans = a - b;
        }
        else if (op == "*") {
            ans = a * b;
        }
        else if (op == "/") {
            ans = a / b;
        }
        else {
            cerr << "Un-supported operation! (" << op << ")\n";
            exit(1);
        }
    }

    cout << ans.to_string(ori_base) << endl;
    return 0;
}

int main(int argc, const char* argv[]) {
    if (argc != 1 && argc != 4) {
        cerr << "usage: <program> [<input_file> <output_file> <type>]\n";
        return 1;
    }
    else if (argc == 1) {
        int type;
        cout << "Choose a type (1 - QInt | 2 - QFloat): ";
        cin >> type;
        cout << "Enter input command: ";
        if (type == 1) {
            parse_qint();
        }
        else {
            parse_qfloat();
        }
    }
    else {
        freopen(argv[1], "r", stdin);
        freopen(argv[2], "w", stdout);
        int type = atoi(argv[3]);
        int cnt = 0;
        if (type == 1) {
            while (true) {
                cerr << "Running QInt on test " << ++cnt << endl;
                if (parse_qint() == -1) {
                    break;
                }
            }
        }
        else if (type == 2) {
            while (true) {
                cerr << "Running QFloat on test " << ++cnt << endl;
                if (parse_qfloat() == -1) {
                    break;
                }
            }
        }
        else {
            cerr << "[type] can only be '1' or '2'\n";
            return 1;
        }
    }
    return 0;
}
