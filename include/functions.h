#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "Number.h"

int stoi(const string s);
string to_string(int d);

void makeSameLength(Number &a, Number &b);

Number add(Number a, Number b);
Number subtract(Number a, Number b);
Number multiply(Number a, Number b);
Number divide(Number a, Number b);

#endif // FUNCTIONS_H
