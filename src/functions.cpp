#include "functions.h"
#include <sstream>

int stoi(const string s) {
    istringstream os(s);
    int d;
    os >> d;
    return d;
}

string to_string(int d) {
    ostringstream os;
    os << d;
    return os.str();
}

void makeSameLength(Number &a, Number &b) {
    int d_int = a.getIntegerLength() - b.getIntegerLength();
    int d_frac = a.getFractionLength() - b.getFractionLength();

    if (d_int > 0) {
        b.padZeros(d_int, true);
    } else if (d_int < 0) {
        a.padZeros(-d_int, true);
    }
    if (d_frac > 0) {
        b.padZeros(d_frac, false);
    } else if (d_frac < 0) {
        a.padZeros(-d_frac, false);
    }
}

Number add(Number a, Number b) {
    cout << "adding ";
    a.print();
    cout << " and ";
    b.print();
    cout << endl;


    if (a.positive && !b.positive){
        b.positive = true;
        return subtract(a, b);
    } else if (!a.positive && b.positive){
        a.positive = true;
        return subtract(b, a);
    }

    makeSameLength(a, b);
    int x, y, sum, carry = 0;
    Number ans;

    for (int k = a.value.length()-1; k >= 0; k--){
        if (a.value[k] == '.'){
            ans.value = "."+ans.value;
            continue;
        }
        x = a.value[k]-'0';
        y = b.value[k]-'0';
        sum = x+y+carry;
        if (sum >= 10){
            carry = 1;
            sum %= 10;
        } else{
            carry = 0;
        }
        ans.value = to_string(sum)+ans.value;
    }
    if (carry)
        ans.value = "1"+ans.value;

    if (!a.positive && !b.positive){
        ans.positive = false;
    }
    ans.trim();
    return ans;
}

Number subtract(Number a, Number b) {
    cout << "subtracting ";
    a.print();
    cout << " and ";
    b.print();
    cout << endl;

    if (a.positive && !b.positive){ //(2) - (-5) == (2) + (5)
        b.positive = true;
        return add(a, b);
    } else if (!a.positive && b.positive){ //(-2) - (5) == -(2+5)
        a.positive = true;
        Number ans = add(a, b);
        ans.positive = false;
        return ans;
    } else if (!a.positive && !b.positive){ //(-2) - (-5) == (-2) + (5)
        b.positive = true;
        return add(a, b);
    }

    makeSameLength(a, b);
    int x, y, sum, carry = 0;
    Number ans;

    for (int k = a.value.length()-1; k >= 0; k--){
        if (a.value[k] == '.'){
            ans.value = "."+ans.value;
            continue;
        }
        x = a.value[k]-'0';
        y = b.value[k]-'0';
        sum = x+y+carry;
        if (sum >= 10){
            carry = 1;
            sum %= 10;
        } else{
            carry = 0;
        }
        ans.value = to_string(sum)+ans.value;
    }
    if (carry)
        ans.value = "1"+ans.value;

    if (!a.positive && !b.positive){
        ans.positive = false;
    }
    ans.trim();
    return ans;

}
Number multiply(Number a, Number b) {
    return Number();

}
Number divide(Number a, Number b) {
    return Number();
}
