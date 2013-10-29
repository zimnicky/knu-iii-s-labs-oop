#ifndef NUMBER_H
#define NUMBER_H

#include <vector>
#include <iostream>

using namespace std;

class Number
{
protected:
    vector<signed char> digits;
    char sign;

    // operations without considering sign
    Number absAdd(const Number &operand) const;
    Number absSub(const Number &operand) const;
    signed char absCompare(const Number &operand) const; // (1, 0, -1)

    signed char compare(const Number &operand);

public:
    Number();
    ~Number();

    static Number& zero(); //  always returns zero

    Number operator+(const Number &operand);
    Number operator-(const Number &operand);
    Number operator*(const Number &operand);
    Number operator/(const Number &operand);

    bool operator !=(const Number &operand);
    bool operator ==(const Number &operand);
    bool operator <(const Number &operand);
    bool operator <=(const Number &operand);
    bool operator >(const Number &operand);
    bool operator >=(const Number &operand);

    signed char& operator[](unsigned int index); // returns digit with this index

    unsigned int length() const;


    friend istream& operator>>(istream& stream, Number& number);

    friend ostream& operator<<(ostream& stream, const Number& number);

};


#endif // NUMBER_H
