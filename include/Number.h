#ifndef NUMBER_H
#define NUMBER_H

#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

class Number {
public:
    Number();
    Number(const string s);
    Number(const Number& other);

    bool positive;
    string value;

    int compare(const Number other); //-1 we are lower, 0 equal, 1 we are higher

    void padZeros(int n, bool left = true);
    int getFractionLength() const;
    int getIntegerLength() const;

    inline void print() const {
        cout << (positive?"+":"-")+value;
    }

    void trim();

};



#endif // NUMBER_H
