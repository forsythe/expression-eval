#include <iostream>
#include <vector>
#include <stack>
#include <queue>

#include <string>
#include <sstream>
#include <cmath>

#include <cassert>

using namespace std;

struct Token {
    double val;
    bool isNum;
};

double stod(const string s) {
    istringstream os(s);
    double d;
    os >> d;
    return d;
}

string to_string(double d) {
    ostringstream os;
    os << d;
    return os.str();
}

bool isNumeric(const char c) {
    return (c >= '0' && c<='9') || c == '.';
}

bool isOperator(const string s) {
    return (s == "+" || s == "-" || s == "*" || s == "/" || s == "^" || s == "u");
}

bool isOperator(const char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == 'u');
}

int getPrecedence(const string s) {
    switch(s[0]) {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case '^':
    case 'u': ///unary (negative num)
        return 3;
    default:
        return 0;
    }
}

int main() {
    while (true) {
        ///get inputs
        char c;
        string raw_input = "";
        cout << ">>> ";
        while(cin.get(c) && c!='\n') {
            if (c!= ' ')
                raw_input+=c;
        }
        if (raw_input.length() == 0)
            continue;
        //cout << "raw input: " << raw_input << endl;

        ///process any unary operators
        if (raw_input[0] == '-')
            raw_input[0] = 'u';

        for (int k = 1; k < raw_input.length()-1; k++) {
            if (isOperator(raw_input[k-1]) && raw_input[k] == '-') {
                raw_input[k] = 'u';
            }
            if (raw_input[k-1] == '(' && raw_input[k] == '-') {
                raw_input[k] = 'u';
            }
        }
        //cout << "unary accounted input: " << raw_input << endl;

        ///parse into tokens
        queue<string> tokens;
        string token = "";

        for (int k = 0; k < raw_input.length(); k++) {
            c = raw_input[k];
            if (!isNumeric(c)) {
                if (token!="")
                    tokens.push(token);
                token = c;
                tokens.push(token);
                token = "";
            } else {
                token += c;
            }
        }
        if (token != "") // in case the last token wasn't a closing
            tokens.push(token);

        ///shunting yard to postfix
        stack<string> ops;
        queue<string> output;
        string temp = "";

        bool mismatched_parenth = false;

        while (!tokens.empty()) {
            temp = tokens.front();
            tokens.pop();
            if (isOperator(temp)) {
                while(!ops.empty() && getPrecedence(ops.top()) >= getPrecedence(temp)) {
                    output.push(ops.top());
                    ops.pop();
                }
                ops.push(temp);
            } else if (temp == "(") {
                ops.push(temp);
            } else if (temp == ")") {
                if (ops.size() == 0) {
                    mismatched_parenth = true;
                    break;
                }
                while(ops.top()!= "(") {
                    output.push(ops.top());
                    ops.pop();
                }
                ops.pop();
            } else { ///its just a number
                output.push(temp);
            }
        }
        while(!ops.empty() && !mismatched_parenth) {
            if (ops.top() == "(") {
                mismatched_parenth = true;
            }
            output.push(ops.top());
            ops.pop();
        }

        if (mismatched_parenth) {
            cout << "error: mismatched brackets" << endl;
            continue;
        }


        /*for (int k = output.size(); k > 0; k--) {
            cout << output.front() << " ";
            output.pop();
        }*/

        ///evaluate postfix notation
        stack<string> nums;

        string a = "", b = "";

        while (!output.empty()) {
            temp = output.front();
            output.pop();
            if (!isOperator(temp)) { //a number
                nums.push(temp);
            } else {
                if (temp == "u") { //unary operator
                    a = nums.top();
                    nums.pop();
                    a = "-"+a;
                    nums.push(a);
                } else { //binary operator
                    b = nums.top();
                    nums.pop();
                    a = nums.top();
                    nums.pop();

                    if (temp == "+") {
                        a = to_string(stod(a)+stod(b));
                        nums.push(a);
                    } else if (temp == "-") {
                        a = to_string(stod(a)-stod(b));
                        nums.push(a);
                    } else if (temp == "*") {
                        a = to_string(stod(a)*stod(b));
                        nums.push(a);
                    } else if (temp == "/") {
                        a = to_string(stod(a)/stod(b));
                        nums.push(a);
                    } else if (temp == "^") {
                        nums.push(to_string(pow(stod(a), stod(b))));
                    }
                }
            }

        }
        cout << "= " << nums.top() << endl;
    }
    return 0;
}
