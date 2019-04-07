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
    for (int i = 0; i < st.length(); i++) {
        if (!isxdigit(st[i])) {
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
        sec = sec.substr(1, sec.length() - 1);
        if (op == '~') {
            ans = ~QInt(sec, ori_base);
        }
    }
    else {
        string op;
        ss >> op;

        if (!is_nan(op) || (op[0] == '-' && !is_nan(op.substr(1, op.length() - 1)))) {
            QInt a(op, ori_base);
            cout << a.print_QInt(stoi(sec)) << endl;
            return 0;
        }
        else {
            string operand;
            ss >> operand;

            QInt a(sec, ori_base);
            QInt b(operand, ori_base);

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
        cout << ans.print_QInt(ori_base) << endl;
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

    cerr << ori_base << " " <<sec << endl;

    if (!is_nan(op) || (op[0] == '-' && !is_nan(op.substr(1, op.length() - 1)))) {
        QFloat a(op, ori_base);
        cerr << a.to_string(stoi(sec)) << endl;
        cout << a.to_string(stoi(sec)) << endl;
        cerr << "no\n";
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
        cerr << "usage: <program> [input_file] [output_file] [type]\n";
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
                cerr << ++cnt << endl;
                if (parse_qint() == -1) {
                    break;
                }
            }
        }
        else if (type == 2) {
            while (true) {
                if (parse_qfloat() == -1) {
                    break;
                }
            }
        }
    }
    return 0;
}
