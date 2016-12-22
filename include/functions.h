#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "Number.h"

int stoi(const string s);
string to_string(int d);

void makeSameLength(Number &a, Number &b);

Number add(const Number a, const Number b);
Number subtract(const Number a, const Number b);
Number multiply(const Number a, const Number b);
Number divide(const Number a, const Number b);

#endif // FUNCTIONS_H
