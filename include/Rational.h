#ifndef RATIONAL_H
#define RATIONAL_H

class Rational {
public:
    Rational(int n = 0, int d = 1) {
        numerator = n, denominator = d;
    }
    int numerator;
    int denom;

    void simplify();
};

void Rational::simplify() {

}

#endif // RATIONAL_H
