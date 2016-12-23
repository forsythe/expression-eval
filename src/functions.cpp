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

void printArr(string s, int arr[], int n){
    cout << endl;
    cout << "array: " << s << endl;
    for (int k = 0; k < n; k++){
        cout << arr[k] << ",";
    }
    cout << endl;
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

Number add(const Number aa, const Number bb) {
    Number a = aa, b = bb;
    cout << endl;
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

Number subtract(const Number aa, const Number bb) {
    Number a = aa, b = bb;
    cout << endl;
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
    //both positive
    int diff = a.compare(b);
    if (diff == 1){ //a is bigger than  b
        makeSameLength(a, b);
        //cout << endl;
        //a.print();
        //cout << endl;
        //b.print();
        int* arr = new int[a.value.length()-1];
        int* brr = new int[a.value.length()-1];
        int offset = 0;
        int pos = 0;
        for (int k = 0; k < a.value.length(); k++){
            if (a.value[k] == '.'){
                offset = 1;
                pos = k;
                continue;
            }
            arr[k-offset] = a.value[k] - '0';
            brr[k-offset] = b.value[k] - '0';
        }
        //printArr("larger", arr, a.value.length()-1);
        //printArr("smaller", brr, a.value.length()-1);
        int* ans = new int[a.value.length()-1];

        for (int k = a.value.length()-2; k >= 0; k--){
        //printArr("larger", arr, a.value.length()-1);
            if (arr[k] >= brr[k]){
                ans[k] = arr[k] - brr[k]; //char on char math is fine
                //cout << "on digit " << k << endl;
                //cout << "subtracted " << arr[k] << " - " << brr[k] << endl;
                //cout << "stored ans[" << k << "] with " <<ans[k] << endl;
            } else {
                //cout << "on digit k = " << k << ",  had to borrow" << endl;
                int borrow = k-1;
                while (arr[borrow] == 0){
                    borrow--;
                }
                arr[borrow]--;
                borrow++;
                while (borrow <= k-1){
                    arr[borrow] += 9;
                    borrow++;
                }
                arr[borrow] += 10;
                ans[k] = arr[k] - brr[k]; //char on char math is fine
            }
        }
        //cout << "pos: " << pos << endl;
        string ansVal = "";
        for (int k = 0; k < a.value.length(); k++){
            if (k != pos)
                ansVal += to_string(ans[k + (k> pos?-1:0)]);
            else
                ansVal += '.';
        }
        //printArr("ans", ans, a.value.length()-1);
        delete[] arr;
        Number n = Number(ansVal);
        n.trim();
        return n;
    } else if (diff == -1){ //b is bigger than a
        Number ans = subtract(b, a);
        ans.positive = !ans.positive;
        return ans;
    } else {
        return Number("0.0");
    }
}

Number multiply(const Number aa, const Number bb) {
    Number a = aa, b = bb;
    cout << "multiplying ";
    a.print();
    cout << " and ";
    b.print();
    cout << endl;
    Number ans = Number("0.0");

    if (a.value.length() >= b.value.length()){
        int numBehindDecimal = a.getFractionLength() + b.getFractionLength();
        a.value.erase(a.value.begin()+a.getIntegerLength());
        b.value.erase(b.value.begin()+b.getIntegerLength());
        a.value = "0" + a.value;
        string tempVal = "";
        for (int l = b.value.length()-1; l >= 0; l--){ //lower number
            int curDigit = b.value[l] - '0';
            int prodDigit = 0;
            int carry = 0;
            if (curDigit == 0){
                cout << endl <<  "skipping mult by 0..." << endl;
                continue;
            }
            for (int u = a.value.length()-1; u >= 0; u--){ //upper number
                prodDigit = (a.value[u]-'0')*curDigit;
                prodDigit += carry;

                carry = prodDigit/10;
                prodDigit %= 10;
                tempVal = to_string(prodDigit) + tempVal;
            }
            //add extra 0s
            for (int k = 0; k < (b.value.length()-1)-l; k++){
                tempVal += "0";
            }
            ans = add(ans, Number(tempVal+".0"));
            tempVal = "";
        }
        ans.value.erase(ans.value.begin()+ans.getIntegerLength());
        ans.value.insert(ans.value.length()-1-numBehindDecimal, ".");
        ans.trim();
    } else{
        return multiply(b, a);
    }
    if (a.positive != b.positive){
        ans.positive = false;
    }
    return ans;
}
Number divide(Number a, Number b) {
    return Number();
}
