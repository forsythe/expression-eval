#include "Number.h"

Number::Number() {
    value = "";
    positive = true;
}

Number::Number(const string s) {
    if (s.at(0) == '-') {
        positive = false;
        value = s.substr(1);
    } else {
        value = s;
        positive = true;
    }
}

Number::Number(const Number& other){
    positive = other.positive;
    value = other.value;
}

int Number::getIntegerLength() const {
    return value.substr(0, value.find(".")).length();
}

int Number::getFractionLength() const {
    return value.substr(value.find(".")+1).length();
}

void Number::padZeros(int n, bool left) {
    if (left)
        for (int k = 0; k < n; k++)
            value = "0"+value;
    else
        for (int k = 0; k < n; k++)
            value += "0";
}

void Number::trim(){
    if (value.length() < 1)
        return;

    while(value[0] == '0' && value[1] != '.')
        value = value.substr(1);
    reverse(value.begin(), value.end());
    while(value.substr(0, 2) == "00")
        value = value.substr(1);
    reverse(value.begin(), value.end());
}

int Number::compare(const Number o) { //-1 we are lower, 0 equal, 1 we are higher
    trim();
    Number other = o;
    other.trim();
    if (positive && !other.positive) {
        return 1;
    } else if (other.positive && !positive) {
        return -1;
    } else if (positive && other.positive) {
        if (getIntegerLength() > other.getIntegerLength()){
            return 1;
        } else if (getIntegerLength() < other.getIntegerLength()){
            return -1;
        } else {
            for (int k = 0; k < getIntegerLength(); k++){
                if (value[k] > other.value[k]){
                    return 1;
                } else if (value[k] < other.value[k]){
                    return -1;
                }
            }
            int minLength = getFractionLength() < other.getFractionLength()? getFractionLength() : other.getFractionLength();
            int offset = getIntegerLength()+1;
            for (int k = offset; k < minLength+offset; k++){
                if (value[k] > other.value[k]){
                    return 1;
                } else if (value[k] < other.value[k]){
                    return -1;
                }
            }
            int diff = getFractionLength() - other.getFractionLength();
            if (diff > 0){
                return 1;
            } else if (diff < 0){
                return -1;
            }
            return 0;
        }
    } else if (!positive && !other.positive) {
        Number selfCopy = *this;
        selfCopy.positive = true;
        other.positive = true;
        return other.compare(selfCopy);
    } else {
        return 0;
    }

}

